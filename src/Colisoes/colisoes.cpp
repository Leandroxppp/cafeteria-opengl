#include "colisoes.h"

#include "../Interacoes/interacoes.h"


// ============================================================
// RAIO DA CAMERA
//
// Trata o jogador como se ocupasse um pequeno circulo.
// Isso evita que a camera encoste completamente nos objetos.
// ============================================================

static const float RAIO_CAMERA = 0.20f;


// ============================================================
// COLISAO COM RETANGULO
//
// Verifica se a camera esta dentro de uma caixa no plano XZ.
// O raio da camera e considerado automaticamente.
// ============================================================

static bool colideComCaixa(
    float x,
    float z,
    float minX,
    float maxX,
    float minZ,
    float maxZ
) {

    return
        x + RAIO_CAMERA > minX &&
        x - RAIO_CAMERA < maxX &&
        z + RAIO_CAMERA > minZ &&
        z - RAIO_CAMERA < maxZ;
}


// ============================================================
// COLISAO COM PAREDES EXTERNAS
// ============================================================

static bool colideComParedesExternas(
    float x,
    float z
) {

    // ========================================================
    // PAREDE ESQUERDA
    // ========================================================

    if (x < -5.75f) {

        return true;
    }


    // ========================================================
    // PAREDE DIREITA
    // ========================================================

    if (x > 5.75f) {

        return true;
    }


    // ========================================================
    // PAREDE DO FUNDO
    // ========================================================

    if (z < -3.75f) {

        return true;
    }


    // ========================================================
    // PAREDE DA FRENTE / PORTA PRINCIPAL
    //
    // A porta principal fica aproximadamente no centro.
    //
    // Quando a porta esta fechada:
    // o jogador nao pode atravessar.
    //
    // Quando esta aberta:
    // pode passar pelo vao.
    // ========================================================

    if (z > 3.75f) {

        bool dentroDoVao =
            x > -0.45f &&
            x <  0.45f;


        // Fora do vao existe parede.
        if (!dentroDoVao) {

            return true;
        }


        // Dentro do vao, mas a porta ainda esta fechada.
        if (obterAnguloPorta() < 70.0f) {

            return true;
        }


        // Limite externo.
        //
        // Permite sair um pouco pela porta,
        // mas evita caminhar infinitamente para fora.
        if (z > 4.80f) {

            return true;
        }
    }


    return false;
}


// ============================================================
// COLISAO COM PAREDES DO BANHEIRO
//
// Banheiro:
//
// X aproximadamente 3.6 ate 6.0
// Z aproximadamente -4.0 ate -2.2
//
// A entrada fica na parede frontal.
// ============================================================

static bool colideComParedesBanheiro(
    float x,
    float z
) {

    // ========================================================
    // PAREDE ESQUERDA DO BANHEIRO
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

            3.52f,
            3.68f,

           -4.00f,
           -2.15f
        )
    ) {

        return true;
    }


    // ========================================================
    // PARTE ESQUERDA DA PAREDE FRONTAL
    //
    // Deixa livre o vao da porta.
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

            3.60f,
            4.25f,

           -2.28f,
           -2.12f
        )
    ) {

        return true;
    }


    // ========================================================
    // PARTE DIREITA DA PAREDE FRONTAL
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

            5.33f,
            6.00f,

           -2.28f,
           -2.12f
        )
    ) {

        return true;
    }


    return false;
}


// ============================================================
// PORTA DO BANHEIRO
// ============================================================

static bool colideComPortaBanheiro(
    float x,
    float z
) {

    // Quando ela esta praticamente aberta,
    // liberamos completamente o vao.
    if (obterAnguloPortaBanheiro() >= 70.0f) {

        return false;
    }


    // Quando fechada, bloqueia o vao.
    if (
        colideComCaixa(
            x,
            z,

            4.30f,
            5.28f,

           -2.18f,
           -2.04f
        )
    ) {

        return true;
    }


    return false;
}


// ============================================================
// COLISAO COM O BALCAO
// ============================================================

static bool colideComBalcao(
    float x,
    float z
) {

    return colideComCaixa(
        x,
        z,

       -4.99f,
       -2.21f,

       -3.04f,
       -2.26f
    );
}


// ============================================================
// COLISAO COM AS MESAS
// ============================================================

static bool colideComMesas(
    float x,
    float z
) {

    // ========================================================
    // MESA ESQUERDA
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

           -3.65f,
           -2.35f,

            0.05f,
            0.95f
        )
    ) {

        return true;
    }


    // ========================================================
    // MESA CENTRAL
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

           -0.65f,
            0.65f,

            0.05f,
            0.95f
        )
    ) {

        return true;
    }


    // ========================================================
    // MESA DIREITA
    // ========================================================

    if (
        colideComCaixa(
            x,
            z,

            2.35f,
            3.65f,

            0.05f,
            0.95f
        )
    ) {

        return true;
    }


    return false;
}


// ============================================================
// COLISAO COM UMA CADEIRA
// ============================================================

static bool colideComCadeira(
    float jogadorX,
    float jogadorZ,
    float cadeiraX,
    float cadeiraZ
) {

    const float metade =
        0.32f;


    return colideComCaixa(
        jogadorX,
        jogadorZ,

        cadeiraX - metade,
        cadeiraX + metade,

        cadeiraZ - metade,
        cadeiraZ + metade
    );
}


// ============================================================
// COLISAO COM TODAS AS CADEIRAS
//
// A colisao acompanha o movimento individual de cada cadeira.
// ============================================================

static bool colideComCadeiras(
    float x,
    float z
) {

    // ========================================================
    // MESA ESQUERDA
    // ========================================================

    if (
        colideComCadeira(
            x,
            z,

           -3.0f,
            1.2f +
            obterDeslocamentoCadeira(0)
        )
    ) {

        return true;
    }


    if (
        colideComCadeira(
            x,
            z,

           -3.0f,
           -0.2f +
            obterDeslocamentoCadeira(1)
        )
    ) {

        return true;
    }


    // ========================================================
    // MESA CENTRAL
    // ========================================================

    if (
        colideComCadeira(
            x,
            z,

            0.0f,
            1.2f +
            obterDeslocamentoCadeira(2)
        )
    ) {

        return true;
    }


    if (
        colideComCadeira(
            x,
            z,

            0.0f,
           -0.2f +
            obterDeslocamentoCadeira(3)
        )
    ) {

        return true;
    }


    // ========================================================
    // MESA DIREITA
    // ========================================================

    if (
        colideComCadeira(
            x,
            z,

            3.0f,
            1.2f +
            obterDeslocamentoCadeira(4)
        )
    ) {

        return true;
    }


    if (
        colideComCadeira(
            x,
            z,

            3.0f,
           -0.2f +
            obterDeslocamentoCadeira(5)
        )
    ) {

        return true;
    }


    return false;
}


// ============================================================
// COLISAO COM VASO SANITARIO
// ============================================================

static bool colideComVasoSanitario(
    float x,
    float z
) {

    // Vaso:
    //
    // centro aproximado:
    // X = 4.25
    // Z = -3.48

    return colideComCaixa(
        x,
        z,

        3.86f,
        4.64f,

       -3.84f,
       -3.05f
    );
}


// ============================================================
// COLISAO COM PIA DO BANHEIRO
// ============================================================

static bool colideComPiaBanheiro(
    float x,
    float z
) {

    // A pia foi rotacionada -90 graus.
    //
    // Por isso a profundidade original passa
    // a ocupar principalmente o eixo X,
    // enquanto a largura ocupa o eixo Z.

    return colideComCaixa(
        x,
        z,

        5.34f,
        5.90f,

       -3.52f,
       -2.58f
    );
}


// ============================================================
// POSICAO DA CAMERA E VALIDA?
// ============================================================

bool posicaoCameraValida(
    float x,
    float z
) {

    // ========================================================
    // PAREDES EXTERNAS
    // ========================================================

    if (
        colideComParedesExternas(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // PAREDES DO BANHEIRO
    // ========================================================

    if (
        colideComParedesBanheiro(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // PORTA DO BANHEIRO
    // ========================================================

    if (
        colideComPortaBanheiro(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // BALCAO
    // ========================================================

    if (
        colideComBalcao(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // MESAS
    // ========================================================

    if (
        colideComMesas(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // CADEIRAS
    // ========================================================

    if (
        colideComCadeiras(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // VASO SANITARIO
    // ========================================================

    if (
        colideComVasoSanitario(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // PIA
    // ========================================================

    if (
        colideComPiaBanheiro(
            x,
            z
        )
    ) {

        return false;
    }


    // ========================================================
    // LIVRE
    // ========================================================

    return true;
}
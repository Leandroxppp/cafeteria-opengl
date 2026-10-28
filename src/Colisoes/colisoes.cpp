#include "colisoes.h"

#include "../Interacoes/interacoes.h"

#include <cmath>


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

// ============================================================
// COLISAO COM A FOLHA DE UMA PORTA ROTACIONADA
//
// A folha e representada por um segmento entre a dobradica e
// a ponta da porta. O raio do jogador e somado a meia espessura
// da folha para impedir que a camera atravesse a madeira.
// O sinal do angulo deve ser o mesmo usado no glRotatef.
// ============================================================

static bool colideComFolhaPorta(
    float x,
    float z,
    float dobradicaX,
    float dobradicaZ,
    float anguloGraus,
    float largura,
    float meiaEspessura
) {

    const float PI = 3.14159265f;
    const float radianos = anguloGraus * PI / 180.0f;

    // glRotatef(angulo, 0, 1, 0):
    // x' = cos(angulo) * x
    // z' = -sin(angulo) * x
    const float pontaX = dobradicaX + std::cos(radianos) * largura;
    const float pontaZ = dobradicaZ - std::sin(radianos) * largura;

    const float segmentoX = pontaX - dobradicaX;
    const float segmentoZ = pontaZ - dobradicaZ;
    const float comprimentoQuadrado =
        segmentoX * segmentoX + segmentoZ * segmentoZ;

    if (comprimentoQuadrado <= 0.000001f) {
        return false;
    }

    const float jogadorX = x - dobradicaX;
    const float jogadorZ = z - dobradicaZ;

    float t =
        (jogadorX * segmentoX + jogadorZ * segmentoZ) /
        comprimentoQuadrado;

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    const float pontoMaisProximoX = dobradicaX + t * segmentoX;
    const float pontoMaisProximoZ = dobradicaZ + t * segmentoZ;

    const float dx = x - pontoMaisProximoX;
    const float dz = z - pontoMaisProximoZ;
    const float raioColisao = RAIO_CAMERA + meiaEspessura;

    return dx * dx + dz * dz < raioColisao * raioColisao;
}


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

    // A dobradica fica em X = 4.79 - 0.492 = 4.298.
    // No modelo, a folha gira com -angulo em torno do eixo Y.
    return colideComFolhaPorta(
        x,
        z,
        4.298f,
       -2.10f,
       -obterAnguloPortaBanheiro(),
        0.985f,
        0.035f
    );
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
    // FOLHA DA PORTA PRINCIPAL
    //
    // A dobradica e (-0.70, 3.96), e a folha gira com
    // o mesmo angulo usado em desenharPorta().
    // ========================================================

    if (
        colideComFolhaPorta(
            x,
            z,
           -0.70f,
            3.96f,
            obterAnguloPorta(),
            1.40f,
            0.04f
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
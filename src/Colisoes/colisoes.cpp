#include "colisoes.h"

#include "../Interacoes/interacoes.h"


// ============================================================
// TAMANHO DA CAMERA
//
// A camera nao e tratada como apenas um ponto.
// Consideramos um pequeno raio ao redor do jogador.
// ============================================================

static const float raioCamera = 0.20f;


// ============================================================
// COLISAO COM RETANGULO
//
// Verifica colisao no plano X/Z.
// ============================================================

static bool colideComCaixa(
    float cameraX,
    float cameraZ,

    float minX,
    float maxX,

    float minZ,
    float maxZ
) {

    return
        cameraX + raioCamera > minX &&
        cameraX - raioCamera < maxX &&
        cameraZ + raioCamera > minZ &&
        cameraZ - raioCamera < maxZ;
}


// ============================================================
// COLISAO COM CADEIRA
// ============================================================

static bool colideComCadeira(
    float cameraX,
    float cameraZ,

    float cadeiraX,
    float cadeiraZ
) {

    const float metadeCadeira = 0.32f;


    return colideComCaixa(
        cameraX,
        cameraZ,

        cadeiraX - metadeCadeira,
        cadeiraX + metadeCadeira,

        cadeiraZ - metadeCadeira,
        cadeiraZ + metadeCadeira
    );
}


// ============================================================
// POSICAO VALIDA
// ============================================================

bool posicaoCameraValida(
    float x,
    float z
) {

    // ========================================================
    // PAREDES LATERAIS
    // ========================================================

    if (x < -5.75f) {
        return false;
    }

    if (x > 5.75f) {
        return false;
    }


    // ========================================================
    // PAREDE DO FUNDO
    // ========================================================

    if (z < -3.75f) {
        return false;
    }


    // ========================================================
    // PAREDE DA FRENTE + PORTA
    //
    // Parede frontal fica em Z = 4.
    //
    // Fora da abertura da porta:
    // nunca pode passar.
    //
    // Dentro da abertura:
    // so pode passar se a porta estiver aberta.
    // ========================================================

    if (z > 3.75f) {

        // Centro precisa estar dentro da abertura
        // com uma margem para o raio da camera.
        bool dentroDaPorta =
            x > -0.45f &&
            x <  0.45f;


        if (!dentroDaPorta) {

            return false;
        }


        // Consideramos a passagem liberada quando
        // a porta ja abriu suficientemente.
        bool portaLiberada =
            obterAnguloPorta() >= 70.0f;


        if (!portaLiberada) {

            return false;
        }


        // Permite andar um pouco para fora da cafeteria,
        // mas impede sair infinitamente pelo mundo.
        if (z > 4.80f) {

            return false;
        }
    }


    // ========================================================
    // BANHEIRO
    // ========================================================


    // Parede lateral esquerda
    if (colideComCaixa(
        x, z,

        3.50f,
        3.70f,

       -4.00f,
       -2.15f
    )) {

        return false;
    }


    // Parede frontal esquerda
    if (colideComCaixa(
        x, z,

        3.55f,
        4.35f,

       -2.30f,
       -2.10f
    )) {

        return false;
    }


    // Parede frontal direita
    if (colideComCaixa(
        x, z,

        5.25f,
        6.00f,

       -2.30f,
       -2.10f
    )) {

        return false;
    }


    // ========================================================
    // MESAS
    // ========================================================


    // Mesa esquerda
    if (colideComCaixa(
        x, z,

       -3.65f,
       -2.35f,

        0.05f,
        0.95f
    )) {

        return false;
    }


    // Mesa central
    if (colideComCaixa(
        x, z,

       -0.65f,
        0.65f,

        0.05f,
        0.95f
    )) {

        return false;
    }


    // Mesa direita
    if (colideComCaixa(
        x, z,

        2.35f,
        3.65f,

        0.05f,
        0.95f
    )) {

        return false;
    }


    // ========================================================
    // CADEIRAS MOVEIS
    //
    // A colisao usa exatamente o mesmo deslocamento
    // que o renderizador usa.
    //
    // Assim:
    //
    // cadeira move visualmente
    //          +
    // colisao move junto
    // ========================================================


    // --------------------------------------------------------
    // CADEIRA 0
    // Mesa esquerda / Z positivo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

        -3.0f,
         1.2f + obterDeslocamentoCadeira(0)
    )) {

        return false;
    }


    // --------------------------------------------------------
    // CADEIRA 1
    // Mesa esquerda / Z negativo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

        -3.0f,
        -0.2f + obterDeslocamentoCadeira(1)
    )) {

        return false;
    }


    // --------------------------------------------------------
    // CADEIRA 2
    // Mesa central / Z positivo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

         0.0f,
         1.2f + obterDeslocamentoCadeira(2)
    )) {

        return false;
    }


    // --------------------------------------------------------
    // CADEIRA 3
    // Mesa central / Z negativo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

         0.0f,
        -0.2f + obterDeslocamentoCadeira(3)
    )) {

        return false;
    }


    // --------------------------------------------------------
    // CADEIRA 4
    // Mesa direita / Z positivo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

         3.0f,
         1.2f + obterDeslocamentoCadeira(4)
    )) {

        return false;
    }


    // --------------------------------------------------------
    // CADEIRA 5
    // Mesa direita / Z negativo
    // --------------------------------------------------------

    if (colideComCadeira(
        x,
        z,

         3.0f,
        -0.2f + obterDeslocamentoCadeira(5)
    )) {

        return false;
    }


    // ========================================================
    // POSICAO LIVRE
    // ========================================================

    return true;
}
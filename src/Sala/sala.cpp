#include "sala.h"
#include "../Renderizacao/primitivas.h"


// ============================================================
// CHAO
// ============================================================

static void desenharChao() {

    desenharQuad(
        -6.0f, 0.0f, -4.0f,
         6.0f, 0.0f, -4.0f,
         6.0f, 0.0f,  4.0f,
        -6.0f, 0.0f,  4.0f,

        0.42f, 0.30f, 0.20f
    );
}


// ============================================================
// TETO
// ============================================================

static void desenharTeto() {

    desenharQuad(
        -6.0f, 3.0f,  4.0f,
         6.0f, 3.0f,  4.0f,
         6.0f, 3.0f, -4.0f,
        -6.0f, 3.0f, -4.0f,

        0.90f, 0.88f, 0.82f
    );
}


// ============================================================
// PAREDE DO FUNDO
// Z = -4
// ============================================================

static void desenharParedeFundo() {

    desenharQuad(
        -6.0f, 0.0f, -4.0f,
         6.0f, 0.0f, -4.0f,
         6.0f, 3.0f, -4.0f,
        -6.0f, 3.0f, -4.0f,

        0.72f, 0.64f, 0.54f
    );
}


// ============================================================
// PAREDE DIREITA
// X = +6
// ============================================================

static void desenharParedeDireita() {

    desenharQuad(
        6.0f, 0.0f, -4.0f,
        6.0f, 0.0f,  4.0f,
        6.0f, 3.0f,  4.0f,
        6.0f, 3.0f, -4.0f,

        0.76f, 0.68f, 0.57f
    );
}


// ============================================================
// PAREDE ESQUERDA
//
// Possui abertura para a janela.
//
// Janela:
// Z = 0.5 ate 3.5
// Y = 0.8 ate 2.6
// ============================================================

static void desenharParedeEsquerda() {

    // Parte antes da janela
    desenharQuad(
        -6.0f, 0.0f, -4.0f,
        -6.0f, 0.0f,  0.5f,
        -6.0f, 3.0f,  0.5f,
        -6.0f, 3.0f, -4.0f,

        0.76f, 0.68f, 0.57f
    );


    // Parte abaixo da janela
    desenharQuad(
        -6.0f, 0.0f, 0.5f,
        -6.0f, 0.0f, 3.5f,
        -6.0f, 0.8f, 3.5f,
        -6.0f, 0.8f, 0.5f,

        0.76f, 0.68f, 0.57f
    );


    // Parte acima da janela
    desenharQuad(
        -6.0f, 2.6f, 0.5f,
        -6.0f, 2.6f, 3.5f,
        -6.0f, 3.0f, 3.5f,
        -6.0f, 3.0f, 0.5f,

        0.76f, 0.68f, 0.57f
    );


    // Parte depois da janela
    desenharQuad(
        -6.0f, 0.0f, 3.5f,
        -6.0f, 0.0f, 4.0f,
        -6.0f, 3.0f, 4.0f,
        -6.0f, 3.0f, 3.5f,

        0.76f, 0.68f, 0.57f
    );
}


// ============================================================
// PAREDE DA FRENTE
//
// Porta principal:
// largura = 1.4 m
// altura = 2.2 m
// centro = X 0
// ============================================================

static void desenharParedeFrente() {

    // Lado esquerdo da porta
    desenharQuad(
        -6.0f, 0.0f, 4.0f,
        -0.7f, 0.0f, 4.0f,
        -0.7f, 3.0f, 4.0f,
        -6.0f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );


    // Lado direito da porta
    desenharQuad(
         0.7f, 0.0f, 4.0f,
         6.0f, 0.0f, 4.0f,
         6.0f, 3.0f, 4.0f,
         0.7f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );


    // Parte acima da porta
    desenharQuad(
        -0.7f, 2.2f, 4.0f,
         0.7f, 2.2f, 4.0f,
         0.7f, 3.0f, 4.0f,
        -0.7f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );
}


// ============================================================
// BANHEIRO
//
// Canto traseiro direito.
//
// Usa a parede do fundo e a parede direita da cafeteria.
//
// Area aproximada:
//
// X = 3.6 ate 6.0  -> 2.4 m
// Z = -4.0 ate -2.2 -> 1.8 m
//
// Porta:
// largura = 0.9 m
// altura = 2.1 m
// ============================================================

static void desenharBanheiro() {

    const float corR = 0.62f;
    const float corG = 0.58f;
    const float corB = 0.52f;


    // ========================================================
    // PAREDE LATERAL ESQUERDA
    //
    // Separa o banheiro da cafeteria.
    // ========================================================

    desenharCaixa(
        3.60f,     // X
        1.50f,     // Y
       -3.10f,     // Z

        0.10f,     // largura
        3.00f,     // altura
        1.80f,     // profundidade

        corR,
        corG,
        corB
    );


    // ========================================================
    // PAREDE FRONTAL
    //
    // A porta fica no meio:
    //
    // X = 4.35 ate 5.25
    //
    // largura da porta = 0.90 m
    // ========================================================


    // Parte esquerda da porta
    desenharCaixa(
        3.975f,
        1.50f,
       -2.20f,

        0.75f,
        3.00f,
        0.10f,

        corR,
        corG,
        corB
    );


    // Parte direita da porta
    desenharCaixa(
        5.625f,
        1.50f,
       -2.20f,

        0.75f,
        3.00f,
        0.10f,

        corR,
        corG,
        corB
    );


    // ========================================================
    // PARTE ACIMA DA PORTA
    //
    // Porta tem 2.1 m.
    // Sala tem 3 m.
    //
    // Sobram 0.9 m acima.
    // ========================================================

    desenharCaixa(
        4.80f,
        2.55f,
       -2.20f,

        0.90f,
        0.90f,
        0.10f,

        corR,
        corG,
        corB
    );
}


// ============================================================
// SALA COMPLETA
// ============================================================

void desenharSala() {

    desenharChao();

    desenharTeto();

    desenharParedeFundo();

    desenharParedeDireita();

    desenharParedeEsquerda();

    desenharParedeFrente();

    desenharBanheiro();
}
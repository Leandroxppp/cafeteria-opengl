#include "interacoes.h"
#include "../Camera/camera.h"

#include <cmath>


// ============================================================
// PORTA PRINCIPAL
// ============================================================

static float anguloPorta = 0.0f;
static float anguloAlvoPorta = 0.0f;

static bool portaAberta = false;


// ============================================================
// CADEIRAS
//
// Indices:
//
// 0 = esquerda, Z positivo
// 1 = esquerda, Z negativo
//
// 2 = central, Z positivo
// 3 = central, Z negativo
//
// 4 = direita, Z positivo
// 5 = direita, Z negativo
// ============================================================

static const int QUANTIDADE_CADEIRAS = 6;


// Posicoes originais
static const float cadeiraBaseX[QUANTIDADE_CADEIRAS] = {

    -3.0f,
    -3.0f,

     0.0f,
     0.0f,

     3.0f,
     3.0f
};


static const float cadeiraBaseZ[QUANTIDADE_CADEIRAS] = {

     1.2f,
    -0.2f,

     1.2f,
    -0.2f,

     1.2f,
    -0.2f
};


// Direcao na qual cada cadeira e puxada.
//
// Cadeiras que ficam em Z positivo:
// afastam ainda mais para +Z.
//
// Cadeiras em Z negativo:
// afastam para -Z.
static const float direcaoCadeira[QUANTIDADE_CADEIRAS] = {

     1.0f,
    -1.0f,

     1.0f,
    -1.0f,

     1.0f,
    -1.0f
};


// Estado individual de cada cadeira
static float deslocamentoCadeira[QUANTIDADE_CADEIRAS];
static float deslocamentoAlvoCadeira[QUANTIDADE_CADEIRAS];

static bool cadeiraPuxada[QUANTIDADE_CADEIRAS];


// ============================================================
// ILUMINACAO
// ============================================================

static bool luzLigada = true;


// ============================================================
// INICIALIZAR
// ============================================================

void inicializarInteracoes() {

    // ========================================================
    // PORTA
    // ========================================================

    anguloPorta = 0.0f;
    anguloAlvoPorta = 0.0f;
    portaAberta = false;


    // ========================================================
    // CADEIRAS
    // ========================================================

    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        deslocamentoCadeira[i] = 0.0f;
        deslocamentoAlvoCadeira[i] = 0.0f;

        cadeiraPuxada[i] = false;
    }


    // ========================================================
    // LUZ
    // ========================================================

    luzLigada = true;
}


// ============================================================
// DISTANCIA ENTRE JOGADOR E CADEIRA
// ============================================================

static float calcularDistanciaCadeira(
    int indice,
    float jogadorX,
    float jogadorZ
) {

    float cadeiraX =
        cadeiraBaseX[indice];


    float cadeiraZ =
        cadeiraBaseZ[indice] +
        deslocamentoCadeira[indice];


    float dx =
        jogadorX - cadeiraX;

    float dz =
        jogadorZ - cadeiraZ;


    return sqrtf(
        dx * dx +
        dz * dz
    );
}


// ============================================================
// PROCURAR CADEIRA MAIS PROXIMA
// ============================================================

static int encontrarCadeiraMaisProxima(
    float jogadorX,
    float jogadorZ
) {

    int cadeiraMaisProxima = -1;

    float menorDistancia = 999.0f;


    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        float distancia =
            calcularDistanciaCadeira(
                i,
                jogadorX,
                jogadorZ
            );


        if (distancia < menorDistancia) {

            menorDistancia =
                distancia;

            cadeiraMaisProxima =
                i;
        }
    }


    // O jogador precisa realmente estar
    // perto da cadeira.
    const float distanciaMaxima = 1.10f;


    if (menorDistancia > distanciaMaxima) {

        return -1;
    }


    return cadeiraMaisProxima;
}


// ============================================================
// INTERAGIR COM CADEIRA
// ============================================================

static void interagirComCadeira(
    int indice
) {

    if (
        indice < 0 ||
        indice >= QUANTIDADE_CADEIRAS
    ) {

        return;
    }


    cadeiraPuxada[indice] =
        !cadeiraPuxada[indice];


    if (cadeiraPuxada[indice]) {

        // Afasta aproximadamente 60 cm da mesa.
        deslocamentoAlvoCadeira[indice] =
            direcaoCadeira[indice] *
            0.60f;
    }

    else {

        // Volta para a posicao original.
        deslocamentoAlvoCadeira[indice] =
            0.0f;
    }
}


// ============================================================
// TENTAR INTERAGIR
// ============================================================

void tentarInteragir() {

    float jogadorX =
        obterCameraX();

    float jogadorZ =
        obterCameraZ();


    // ========================================================
    // PORTA PRINCIPAL
    // ========================================================

    bool pertoDaPorta =
        jogadorX > -1.8f &&
        jogadorX <  1.8f &&
        jogadorZ >  2.0f;


    if (pertoDaPorta) {

        portaAberta =
            !portaAberta;


        if (portaAberta) {

            anguloAlvoPorta =
                90.0f;
        }

        else {

            anguloAlvoPorta =
                0.0f;
        }


        return;
    }


    // ========================================================
    // INTERRUPTOR
    // ========================================================

    bool pertoDoInterruptor =
        jogadorX > 4.6f &&
        jogadorZ > 1.8f &&
        jogadorZ < 3.7f;


    if (pertoDoInterruptor) {

        luzLigada =
            !luzLigada;

        return;
    }


    // ========================================================
    // CADEIRAS
    //
    // Procura automaticamente a cadeira mais proxima.
    // ========================================================

    int cadeira =
        encontrarCadeiraMaisProxima(
            jogadorX,
            jogadorZ
        );


    if (cadeira != -1) {

        interagirComCadeira(
            cadeira
        );
    }
}


// ============================================================
// ATUALIZAR INTERACOES
// ============================================================

void atualizarInteracoes() {

    // ========================================================
    // PORTA
    // ========================================================

    const float velocidadePorta =
        2.5f;


    if (anguloPorta < anguloAlvoPorta) {

        anguloPorta +=
            velocidadePorta;


        if (
            anguloPorta >
            anguloAlvoPorta
        ) {

            anguloPorta =
                anguloAlvoPorta;
        }
    }

    else if (
        anguloPorta >
        anguloAlvoPorta
    ) {

        anguloPorta -=
            velocidadePorta;


        if (
            anguloPorta <
            anguloAlvoPorta
        ) {

            anguloPorta =
                anguloAlvoPorta;
        }
    }


    // ========================================================
    // CADEIRAS
    // ========================================================

    const float velocidadeCadeira =
        0.025f;


    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        // ----------------------------------------------------
        // PRECISA AUMENTAR
        // ----------------------------------------------------

        if (
            deslocamentoCadeira[i] <
            deslocamentoAlvoCadeira[i]
        ) {

            deslocamentoCadeira[i] +=
                velocidadeCadeira;


            if (
                deslocamentoCadeira[i] >
                deslocamentoAlvoCadeira[i]
            ) {

                deslocamentoCadeira[i] =
                    deslocamentoAlvoCadeira[i];
            }
        }


        // ----------------------------------------------------
        // PRECISA DIMINUIR
        // ----------------------------------------------------

        else if (
            deslocamentoCadeira[i] >
            deslocamentoAlvoCadeira[i]
        ) {

            deslocamentoCadeira[i] -=
                velocidadeCadeira;


            if (
                deslocamentoCadeira[i] <
                deslocamentoAlvoCadeira[i]
            ) {

                deslocamentoCadeira[i] =
                    deslocamentoAlvoCadeira[i];
            }
        }
    }
}


// ============================================================
// PORTA
// ============================================================

float obterAnguloPorta() {

    return anguloPorta;
}


// ============================================================
// CADEIRAS
// ============================================================

float obterDeslocamentoCadeira(
    int indice
) {

    if (
        indice < 0 ||
        indice >= QUANTIDADE_CADEIRAS
    ) {

        return 0.0f;
    }


    return deslocamentoCadeira[indice];
}


// ============================================================
// ILUMINACAO
// ============================================================

bool luzEstaLigada() {

    return luzLigada;
}
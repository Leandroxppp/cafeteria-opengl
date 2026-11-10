#include "interacoes.h"
#include "../Camera/camera.h"

#include <algorithm>
#include <cmath>

namespace {

// ============================================================
// CONSTANTES
// ============================================================

const int QUANTIDADE_CADEIRAS = 6;

const float ANGULO_PORTA_ABERTA = 90.0f;
const float VELOCIDADE_PORTA = 150.0f;      // graus por segundo

const float DESLOCAMENTO_CADEIRA = 0.60f;
const float VELOCIDADE_CADEIRA = 1.5f;      // unidades por segundo
const float DISTANCIA_MAXIMA_CADEIRA = 1.10f;

const float DISTANCIA_MAXIMA_PORTA_BANHEIRO = 1.15f;
const float PORTA_BANHEIRO_X = 4.80f;
const float PORTA_BANHEIRO_Z = -2.05f;

// ============================================================
// LAYOUT DAS CADEIRAS
//
// Cada cadeira guarda sua posicao original, a direcao em que
// e afastada da mesa e a rotacao usada ao desenha-la.
// ============================================================

struct LayoutCadeira {

    float x;
    float z;
    float direcao;
    float angulo;
};

const LayoutCadeira CADEIRAS[QUANTIDADE_CADEIRAS] = {

    // Mesa esquerda
    { -3.0f,  1.2f,  1.0f, 180.0f },
    { -3.0f, -0.2f, -1.0f,   0.0f },

    // Mesa central
    {  0.0f,  1.2f,  1.0f, 180.0f },
    {  0.0f, -0.2f, -1.0f,   0.0f },

    // Mesa direita
    {  3.0f,  1.2f,  1.0f, 180.0f },
    {  3.0f, -0.2f, -1.0f,   0.0f }
};

// ============================================================
// ESTADO
// ============================================================

float anguloPorta = 0.0f;
float anguloAlvoPorta = 0.0f;
bool portaAberta = false;

float anguloPortaBanheiro = 0.0f;
float anguloAlvoPortaBanheiro = 0.0f;
bool portaBanheiroAberta = false;

float deslocamentoCadeira[QUANTIDADE_CADEIRAS] = {};
float deslocamentoAlvoCadeira[QUANTIDADE_CADEIRAS] = {};
bool cadeiraPuxada[QUANTIDADE_CADEIRAS] = {};

bool luzLigada = true;

// ============================================================
// UTILITARIOS
// ============================================================

bool indiceValido(int indice) {

    return indice >= 0 && indice < QUANTIDADE_CADEIRAS;
}

// Move um valor em direcao ao alvo sem ultrapassa-lo.
void aproximar(float& valor, float alvo, float passo) {

    if (valor < alvo) {

        valor = std::min(valor + passo, alvo);
    }

    else if (valor > alvo) {

        valor = std::max(valor - passo, alvo);
    }
}

void alternarPorta(bool& aberta, float& anguloAlvo) {

    aberta = !aberta;
    anguloAlvo = aberta ? ANGULO_PORTA_ABERTA : 0.0f;
}

// ============================================================
// CADEIRA MAIS PROXIMA
// ============================================================

float calcularDistanciaCadeira(
    int indice,
    float jogadorX,
    float jogadorZ
) {

    const float dx =
        jogadorX - CADEIRAS[indice].x;

    const float dz =
        jogadorZ - obterCadeiraZ(indice);

    return std::sqrt(dx * dx + dz * dz);
}

int encontrarCadeiraMaisProxima(
    float jogadorX,
    float jogadorZ
) {

    int maisProxima = -1;
    float menorDistancia = DISTANCIA_MAXIMA_CADEIRA;

    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        const float distancia =
            calcularDistanciaCadeira(i, jogadorX, jogadorZ);

        if (distancia < menorDistancia) {

            menorDistancia = distancia;
            maisProxima = i;
        }
    }

    return maisProxima;
}

void interagirComCadeira(int indice) {

    if (!indiceValido(indice)) {

        return;
    }

    cadeiraPuxada[indice] = !cadeiraPuxada[indice];

    deslocamentoAlvoCadeira[indice] =
        cadeiraPuxada[indice]
            ? CADEIRAS[indice].direcao * DESLOCAMENTO_CADEIRA
            : 0.0f;
}

// ============================================================
// PORTA DO BANHEIRO
// ============================================================

bool jogadorPertoPortaBanheiro() {

    const float dx =
        obterCameraX() - PORTA_BANHEIRO_X;

    const float dz =
        obterCameraZ() - PORTA_BANHEIRO_Z;

    return
        dx * dx + dz * dz <= // teorema de pitagoras
        DISTANCIA_MAXIMA_PORTA_BANHEIRO *
        DISTANCIA_MAXIMA_PORTA_BANHEIRO;
}

void alternarPortaBanheiro() {

    alternarPorta(
        portaBanheiroAberta,
        anguloAlvoPortaBanheiro
    );
}

} // namespace


// INICIALIZACAO
void inicializarInteracoes() {

    anguloPorta = 0.0f;
    anguloAlvoPorta = 0.0f;
    portaAberta = false;

    anguloPortaBanheiro = 0.0f;
    anguloAlvoPortaBanheiro = 0.0f;
    portaBanheiroAberta = false;

    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        deslocamentoCadeira[i] = 0.0f;
        deslocamentoAlvoCadeira[i] = 0.0f;
        cadeiraPuxada[i] = false;
    }

    luzLigada = true;
}



// INTERACAO
void tentarInteragir() {

    const float jogadorX = obterCameraX();
    const float jogadorZ = obterCameraZ();

    // Verificada primeiro porque o jogador pode estar
    // exatamente na entrada do banheiro.
    if (jogadorPertoPortaBanheiro()) {

        alternarPortaBanheiro();
        return;
    }

    const bool pertoDaPorta =
        jogadorX > -1.8f &&
        jogadorX <  1.8f &&
        jogadorZ >  2.0f;

    if (pertoDaPorta) {

        alternarPorta(portaAberta, anguloAlvoPorta);
        return;
    }

    const bool pertoDoInterruptor =
        jogadorX > 4.6f &&
        jogadorZ > 1.8f &&
        jogadorZ < 3.7f;

    if (pertoDoInterruptor) {

        luzLigada = !luzLigada;
        return;
    }

    const int cadeira =
        encontrarCadeiraMaisProxima(jogadorX, jogadorZ);

    if (cadeira != -1) {

        interagirComCadeira(cadeira);
    }
}

// ============================================================
// ANIMACOES
// ============================================================

void atualizarInteracoes(float deltaTempo) {

    const float passoPorta =
        VELOCIDADE_PORTA * deltaTempo;

    const float passoCadeira =
        VELOCIDADE_CADEIRA * deltaTempo;

    aproximar(anguloPorta, anguloAlvoPorta, passoPorta);
    aproximar(
        anguloPortaBanheiro,
        anguloAlvoPortaBanheiro,
        passoPorta
    );

    for (int i = 0; i < QUANTIDADE_CADEIRAS; i++) {

        aproximar(
            deslocamentoCadeira[i],
            deslocamentoAlvoCadeira[i],
            passoCadeira
        );
    }
}

// ============================================================
// GETTERS
// ============================================================

float obterAnguloPorta() {

    return anguloPorta;
}

float obterAnguloPortaBanheiro() {

    return anguloPortaBanheiro;
}

int quantidadeCadeiras() {

    return QUANTIDADE_CADEIRAS;
}

float obterCadeiraX(int indice) {

    return indiceValido(indice) ? CADEIRAS[indice].x : 0.0f;
}

float obterCadeiraZ(int indice) {

    return indiceValido(indice)
        ? CADEIRAS[indice].z + deslocamentoCadeira[indice]
        : 0.0f;
}

float obterAnguloCadeira(int indice) {

    return indiceValido(indice) ? CADEIRAS[indice].angulo : 0.0f;
}

bool luzEstaLigada() {

    return luzLigada;
}

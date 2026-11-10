#include "colisoes.h"

#include "../Interacoes/interacoes.h"

#include <cmath>

namespace {

// ============================================================
// GEOMETRIA DE COLISAO
//
// O jogador e tratado como um circulo de raio RAIO_CAMERA.
// Cada obstaculo e representado por um retangulo no plano XZ.
// ============================================================

const float RAIO_CAMERA = 0.20f;
const float PI = 3.14159265f;

const float LIMITE_X = 5.75f;
const float LIMITE_Z_FUNDO = -3.75f;
const float LIMITE_Z_FRENTE = 3.75f;
const float VAO_PORTA = 0.45f;
const float ANGULO_PORTA_LIVRE = 70.0f;
const float LIMITE_EXTERNO = 4.80f;

const float METADE_CADEIRA = 0.32f;

struct RetanguloXZ {

    float minX;
    float maxX;
    float minZ;
    float maxZ;
};

const RetanguloXZ BALCAO = {
    -4.99f, -2.21f,
    -3.04f, -2.26f
};

const RetanguloXZ VASO_SANITARIO = {
    3.86f, 4.64f,
    -3.84f, -3.05f
};

const RetanguloXZ PIA_BANHEIRO = {
    5.34f, 5.90f,
    -3.52f, -2.58f
};

const RetanguloXZ MESAS[] = {

    // Mesa esquerda
    { -3.65f, -2.35f, 0.05f, 0.95f },

    // Mesa central
    { -0.65f, 0.65f, 0.05f, 0.95f },

    // Mesa direita
    { 2.35f, 3.65f, 0.05f, 0.95f }
};

const RetanguloXZ PAREDES_BANHEIRO[] = {

    // Parede esquerda
    { 3.52f, 3.68f, -4.00f, -2.15f },

    // Parte esquerda da parede frontal (deixa o vao da porta)
    { 3.60f, 4.25f, -2.28f, -2.12f },

    // Parte direita da parede frontal
    { 5.33f, 6.00f, -2.28f, -2.12f }
};

// ============================================================
// COLISAO COM RETANGULO
// ============================================================

bool colideComRetangulo(
    float x,
    float z,
    const RetanguloXZ& area
) {

    return
        x + RAIO_CAMERA > area.minX &&
        x - RAIO_CAMERA < area.maxX &&
        z + RAIO_CAMERA > area.minZ &&
        z - RAIO_CAMERA < area.maxZ;
}

// ============================================================
// COLISAO COM A FOLHA DE UMA PORTA ROTACIONADA
//
// A folha e um segmento entre a dobradica e a ponta da porta.
// O raio do jogador e somado a meia espessura da folha.
// O sinal do angulo deve ser o mesmo usado no glRotatef.
// ============================================================

bool colideComFolhaPorta(
    float x,
    float z,
    float dobradicaX,
    float dobradicaZ,
    float anguloGraus,
    float largura,
    float meiaEspessura
) {

    const float radianos = anguloGraus * PI / 180.0f;

    // glRotatef(angulo, 0, 1, 0):
    // x' = cos(angulo) * x
    // z' = -sin(angulo) * x
    const float pontaX =
        dobradicaX + std::cos(radianos) * largura;

    const float pontaZ =
        dobradicaZ - std::sin(radianos) * largura;

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

    const float dx =
        x - (dobradicaX + t * segmentoX);

    const float dz =
        z - (dobradicaZ + t * segmentoZ);

    const float raioColisao =
        RAIO_CAMERA + meiaEspessura;

    return dx * dx + dz * dz < raioColisao * raioColisao;
}

// ============================================================
// PAREDES EXTERNAS
// ============================================================

bool colideComParedesExternas(float x, float z) {

    if (
        x < -LIMITE_X ||
        x >  LIMITE_X ||
        z <  LIMITE_Z_FUNDO
    ) {

        return true;
    }

    if (z <= LIMITE_Z_FRENTE) {

        return false;
    }

    // Na parede da frente so existe passagem pelo vao central.
    const bool dentroDoVao =
        x > -VAO_PORTA &&
        x <  VAO_PORTA;

    if (!dentroDoVao) {

        return true;
    }

    // Dentro do vao, a porta precisa estar aberta.
    if (obterAnguloPorta() < ANGULO_PORTA_LIVRE) {

        return true;
    }

    // Evita caminhar infinitamente para fora da cafeteria.
    return z > LIMITE_EXTERNO;
}

// ============================================================
// PAREDES DO BANHEIRO
// ============================================================

bool colideComParedesBanheiro(float x, float z) {

    for (const RetanguloXZ& parede : PAREDES_BANHEIRO) {

        if (colideComRetangulo(x, z, parede)) {

            return true;
        }
    }

    return false;
}

// ============================================================
// PORTA DO BANHEIRO
// ============================================================

bool colideComPortaBanheiro(float x, float z) {

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
// CADEIRAS
//
// Usa as mesmas posicoes consultadas pela renderizacao, entao a
// colisao acompanha automaticamente a animacao de cada cadeira.
// ============================================================

bool colideComCadeiras(float x, float z) {

    for (int i = 0; i < quantidadeCadeiras(); i++) {

        const float cadeiraX = obterCadeiraX(i);
        const float cadeiraZ = obterCadeiraZ(i);

        const RetanguloXZ area = {
            cadeiraX - METADE_CADEIRA,
            cadeiraX + METADE_CADEIRA,
            cadeiraZ - METADE_CADEIRA,
            cadeiraZ + METADE_CADEIRA
        };

        if (colideComRetangulo(x, z, area)) {

            return true;
        }
    }

    return false;
}

} // namespace

// ============================================================
// POSICAO DA CAMERA E VALIDA?
// ============================================================

bool posicaoCameraValida(float x, float z) {

    if (colideComParedesExternas(x, z)) {

        return false;
    }

    // Folha da porta principal.
    // A dobradica e (-0.70, 3.96) e o angulo e o mesmo usado
    // em desenharPorta().
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

    if (colideComParedesBanheiro(x, z)) {

        return false;
    }

    if (colideComPortaBanheiro(x, z)) {

        return false;
    }

    if (colideComRetangulo(x, z, BALCAO)) {

        return false;
    }

    for (const RetanguloXZ& mesa : MESAS) {

        if (colideComRetangulo(x, z, mesa)) {

            return false;
        }
    }

    if (colideComCadeiras(x, z)) {

        return false;
    }

    if (colideComRetangulo(x, z, VASO_SANITARIO)) {

        return false;
    }

    if (colideComRetangulo(x, z, PIA_BANHEIRO)) {

        return false;
    }

    return true;
}

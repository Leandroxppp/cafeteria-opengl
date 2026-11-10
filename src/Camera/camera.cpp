#include "camera.h"

#include "../Colisoes/colisoes.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>

namespace {
// DADOS DA CAMERA
const float POSICAO_INICIAL_X = 1.00f;
const float POSICAO_INICIAL_Y = 1.65f;
const float POSICAO_INICIAL_Z = 2.00f;

const float PI = 3.14159265f;
const float SENSIBILIDADE_MOUSE = 0.10f;
const float LIMITE_PITCH = 85.0f;

float cameraX = POSICAO_INICIAL_X;
float cameraY = POSICAO_INICIAL_Y;
float cameraZ = POSICAO_INICIAL_Z;

float yaw = 0.0f;
float pitch = 0.0f;

// ============================================================
// MOVIMENTO COM COLISAO
//
// Primeiro tenta o movimento completo. Se houver colisao,
// tenta apenas X e depois apenas Z, permitindo deslizar.
// ============================================================

void tentarMover(float deslocamentoX, float deslocamentoZ) {

    const float novoX = cameraX + deslocamentoX;
    const float novoZ = cameraZ + deslocamentoZ;

    if (posicaoCameraValida(novoX, novoZ)) {

        cameraX = novoX;
        cameraZ = novoZ;
        return;
    }

    if (posicaoCameraValida(novoX, cameraZ)) {

        cameraX = novoX;
    }

    if (posicaoCameraValida(cameraX, novoZ)) {

        cameraZ = novoZ;
    }
}

// ============================================================
// MOVIMENTO RELATIVO A CAMERA
//
// frente:   +1 anda para frente, -1 para tras.
// lateral:  +1 anda para a direita, -1 para a esquerda.
// ============================================================

void moverCamera(float frente, float lateral, float distancia) {

    const float radianos = yaw * PI / 180.0f;

    const float deslocamentoX = (
        -std::sin(radianos) * frente +
         std::cos(radianos) * lateral
    ) * distancia;

    const float deslocamentoZ = (
        -std::cos(radianos) * frente -
         std::sin(radianos) * lateral
    ) * distancia;

    tentarMover(deslocamentoX, deslocamentoZ);
}

void limitarPitch() {

    pitch = std::max(-LIMITE_PITCH, std::min(pitch, LIMITE_PITCH));
}

} // namespace


// INICIALIZACAO E APLICACAO
void inicializarCamera() {

    cameraX = POSICAO_INICIAL_X;
    cameraY = POSICAO_INICIAL_Y;
    cameraZ = POSICAO_INICIAL_Z;

    yaw = 0.0f; // rotação em torno do eixo vertical (Y); esquerda -> positivo, direita -> negativo
    pitch = 0.0f; // rotação em torno do eixo vertical (X); cima -> positivo, baixo -> negativo
}

void aplicarCamera() {

    glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);
}


void moverCameraFrente(float distancia) {

    moverCamera(1.0f, 0.0f, distancia);
}

void moverCameraTras(float distancia) {

    moverCamera(-1.0f, 0.0f, distancia);
}

void moverCameraEsquerda(float distancia) {

    moverCamera(0.0f, -1.0f, distancia);
}

void moverCameraDireita(float distancia) {

    moverCamera(0.0f, 1.0f, distancia);
}

// ============================================================
// ROTACAO
// ============================================================

void rotacionarCamera(float deltaX, float deltaY) {

    yaw -= deltaX * SENSIBILIDADE_MOUSE;
    pitch -= deltaY * SENSIBILIDADE_MOUSE;

    limitarPitch();
}

void girarCamera(float deltaYaw, float deltaPitch) {

    yaw += deltaYaw;
    pitch += deltaPitch;

    limitarPitch();
}

// ============================================================
// GETTERS
// ============================================================

float obterCameraX() {

    return cameraX;
}

float obterCameraY() {

    return cameraY;
}

float obterCameraZ() {

    return cameraZ;
}

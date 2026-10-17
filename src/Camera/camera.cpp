#include "camera.h"

#include <GL/gl.h>
#include <cmath>


// ============================================================
// DADOS DA CAMERA
// ============================================================

static float cameraX = 0.0f;
static float cameraY = 1.65f;
static float cameraZ = 3.0f;

static float yaw = 0.0f;
static float pitch = 0.0f;

static const float PI = 3.14159265f;


// ============================================================
// LIMITES DA CAFETERIA
// ============================================================

static void limitarCamera() {

    if (cameraX < -5.7f) cameraX = -5.7f;
    if (cameraX >  5.7f) cameraX =  5.7f;

    if (cameraZ < -3.7f) cameraZ = -3.7f;
    if (cameraZ >  3.7f) cameraZ =  3.7f;
}


// ============================================================
// INICIALIZACAO
// ============================================================

void inicializarCamera() {

    cameraX = 0.0f;
    cameraY = 1.65f;
    cameraZ = 3.0f;

    // Comeca olhando para -Z,
    // ou seja, para dentro da cafeteria
    yaw = 0.0f;
    pitch = 0.0f;
}


// ============================================================
// APLICAR CAMERA
// ============================================================

void aplicarCamera() {

    glRotatef(
        -pitch,
        1.0f,
        0.0f,
        0.0f
    );

    glRotatef(
        -yaw,
        0.0f,
        1.0f,
        0.0f
    );

    glTranslatef(
        -cameraX,
        -cameraY,
        -cameraZ
    );
}


// ============================================================
// W - FRENTE
// ============================================================

void moverCameraFrente(float distancia) {

    float angulo =
        yaw * PI / 180.0f;

    // Movimento acompanha exatamente
    // a direcao para onde a camera olha
    cameraX -=
        sinf(angulo) * distancia;

    cameraZ -=
        cosf(angulo) * distancia;

    limitarCamera();
}


// ============================================================
// S - TRAS
// ============================================================

void moverCameraTras(float distancia) {

    float angulo =
        yaw * PI / 180.0f;

    cameraX +=
        sinf(angulo) * distancia;

    cameraZ +=
        cosf(angulo) * distancia;

    limitarCamera();
}


// ============================================================
// A - ESQUERDA
// ============================================================

void moverCameraEsquerda(float distancia) {

    float angulo =
        yaw * PI / 180.0f;

    cameraX -=
        cosf(angulo) * distancia;

    cameraZ +=
        sinf(angulo) * distancia;

    limitarCamera();
}


// ============================================================
// D - DIREITA
// ============================================================

void moverCameraDireita(float distancia) {

    float angulo =
        yaw * PI / 180.0f;

    cameraX +=
        cosf(angulo) * distancia;

    cameraZ -=
        sinf(angulo) * distancia;

    limitarCamera();
}


// ============================================================
// MOUSE
// ============================================================

void rotacionarCamera(
    float deltaX,
    float deltaY
) {

    const float sensibilidade = 0.10f;

    // Mouse direita = olha direita
    // Mouse esquerda = olha esquerda
    yaw -=
        deltaX * sensibilidade;

    // Mouse cima = olha cima
    // Mouse baixo = olha baixo
    pitch -=
        deltaY * sensibilidade;


    if (pitch > 85.0f) {
        pitch = 85.0f;
    }

    if (pitch < -85.0f) {
        pitch = -85.0f;
    }
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
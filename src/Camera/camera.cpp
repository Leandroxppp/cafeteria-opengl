#include "camera.h"

#include "../Colisoes/colisoes.h"

#include <GL/gl.h>
#include <cmath>


// ============================================================
// DADOS DA CAMERA
// ============================================================

// Comeca em um corredor livre,
// evitando nascer encostado em cadeira/mesa.
static float cameraX = 1.50f;
static float cameraY = 1.65f;
static float cameraZ = 3.0f;

static float yaw = 0.0f;
static float pitch = 0.0f;

static const float PI = 3.14159265f;


// ============================================================
// MOVIMENTO COM COLISAO
//
// Primeiro tenta mover normalmente.
//
// Se houver colisao:
// tenta mover apenas em X
// e depois apenas em Z.
//
// Isso permite deslizar pelas paredes e objetos.
// ============================================================

static void tentarMover(
    float deslocamentoX,
    float deslocamentoZ
) {

    float novoX =
        cameraX + deslocamentoX;

    float novoZ =
        cameraZ + deslocamentoZ;


    // ========================================================
    // TENTA MOVIMENTO COMPLETO
    // ========================================================

    if (posicaoCameraValida(
        novoX,
        novoZ
    )) {

        cameraX = novoX;
        cameraZ = novoZ;

        return;
    }


    // ========================================================
    // TENTA APENAS X
    // ========================================================

    if (posicaoCameraValida(
        novoX,
        cameraZ
    )) {

        cameraX = novoX;
    }


    // ========================================================
    // TENTA APENAS Z
    // ========================================================

    if (posicaoCameraValida(
        cameraX,
        novoZ
    )) {

        cameraZ = novoZ;
    }
}


// ============================================================
// INICIALIZACAO
// ============================================================

void inicializarCamera() {

    // Posicao inicial em area livre
    cameraX = 1.50f;
    cameraY = 1.65f;
    cameraZ = 3.0f;


    // Comeca olhando para dentro da cafeteria
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

void moverCameraFrente(
    float distancia
) {

    float angulo =
        yaw * PI / 180.0f;


    float deslocamentoX =
        -sinf(angulo) *
        distancia;

    float deslocamentoZ =
        -cosf(angulo) *
        distancia;


    tentarMover(
        deslocamentoX,
        deslocamentoZ
    );
}


// ============================================================
// S - TRAS
// ============================================================

void moverCameraTras(
    float distancia
) {

    float angulo =
        yaw * PI / 180.0f;


    float deslocamentoX =
        sinf(angulo) *
        distancia;

    float deslocamentoZ =
        cosf(angulo) *
        distancia;


    tentarMover(
        deslocamentoX,
        deslocamentoZ
    );
}


// ============================================================
// A - ESQUERDA
// ============================================================

void moverCameraEsquerda(
    float distancia
) {

    float angulo =
        yaw * PI / 180.0f;


    float deslocamentoX =
        -cosf(angulo) *
        distancia;

    float deslocamentoZ =
        sinf(angulo) *
        distancia;


    tentarMover(
        deslocamentoX,
        deslocamentoZ
    );
}


// ============================================================
// D - DIREITA
// ============================================================

void moverCameraDireita(
    float distancia
) {

    float angulo =
        yaw * PI / 180.0f;


    float deslocamentoX =
        cosf(angulo) *
        distancia;

    float deslocamentoZ =
        -sinf(angulo) *
        distancia;


    tentarMover(
        deslocamentoX,
        deslocamentoZ
    );
}


// ============================================================
// MOUSE
// ============================================================

void rotacionarCamera(
    float deltaX,
    float deltaY
) {

    const float sensibilidade =
        0.10f;


    // Mouse para direita
    yaw -=
        deltaX *
        sensibilidade;


    // Mouse para cima/baixo
    pitch -=
        deltaY *
        sensibilidade;


    // ========================================================
    // LIMITAR VISAO VERTICAL
    // ========================================================

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
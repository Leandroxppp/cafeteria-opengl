#include "controles.h"
#include "../Camera/camera.h"

// Guarda o estado das teclas
static bool teclas[256] = { false };


// Inicializa os controles
void inicializarControles() {

    for (int i = 0; i < 256; i++) {
        teclas[i] = false;
    }
}


// Registra uma tecla pressionada
void teclaPressionada(int tecla) {

    if (tecla >= 0 && tecla < 256) {
        teclas[tecla] = true;
    }
}


// Registra uma tecla solta
void teclaSolta(int tecla) {

    if (tecla >= 0 && tecla < 256) {
        teclas[tecla] = false;
    }
}


// Atualiza a movimentacao WASD
void atualizarControles() {

    const float velocidade = 0.060f;


    // W = frente
    if (teclas['W']) {
        moverCameraFrente(velocidade);
    }


    // S = tras
    if (teclas['S']) {
        moverCameraTras(velocidade);
    }


    // A = esquerda
    if (teclas['A']) {
        moverCameraEsquerda(velocidade);
    }


    // D = direita
    if (teclas['D']) {
        moverCameraDireita(velocidade);
    }
}


// Envia o movimento do mouse para a camera
void moverMouse(int deltaX, int deltaY) {

    rotacionarCamera(
        static_cast<float>(deltaX),
        static_cast<float>(deltaY)
    );
}
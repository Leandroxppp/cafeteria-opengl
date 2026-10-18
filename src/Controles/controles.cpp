#include "controles.h"

#include "../Camera/camera.h"
#include "../Interacoes/interacoes.h"

static bool teclas[256] = { false };


void inicializarControles() {

    for (int i = 0; i < 256; i++) {
        teclas[i] = false;
    }
}


void teclaPressionada(int tecla) {

    if (tecla >= 0 && tecla < 256) {

        // E executa apenas uma vez por pressionamento
        if (tecla == 'E' && !teclas[tecla]) {
            tentarInteragir();
        }

        teclas[tecla] = true;
    }
}


void teclaSolta(int tecla) {

    if (tecla >= 0 && tecla < 256) {
        teclas[tecla] = false;
    }
}


void atualizarControles() {

    const float velocidade = 0.060f;

    if (teclas['W']) {
        moverCameraFrente(velocidade);
    }

    if (teclas['S']) {
        moverCameraTras(velocidade);
    }

    if (teclas['A']) {
        moverCameraEsquerda(velocidade);
    }

    if (teclas['D']) {
        moverCameraDireita(velocidade);
    }
}


void moverMouse(int deltaX, int deltaY) {

    rotacionarCamera(
        static_cast<float>(deltaX),
        static_cast<float>(deltaY)
    );
}
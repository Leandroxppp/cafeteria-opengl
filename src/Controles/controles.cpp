#include "controles.h"

#include <GLFW/glfw3.h>

#include "../Camera/camera.h"
#include "../Interacoes/interacoes.h"

static bool teclas[GLFW_KEY_LAST + 1] = { false };

// Ultima posicao recebida do mouse.
// O primeiro evento apenas registra a referencia.
static double ultimoX = 0.0;
static double ultimoY = 0.0;
static bool temUltimo = false;

void teclaPressionada(int tecla) {

    if (tecla < 0 || tecla > GLFW_KEY_LAST) {

        return;
    }

    // E executa apenas uma vez por pressionamento.
    if (tecla == GLFW_KEY_E && !teclas[tecla]) {

        tentarInteragir();
    }

    teclas[tecla] = true;
}

void teclaSolta(int tecla) {

    if (tecla < 0 || tecla > GLFW_KEY_LAST) {

        return;
    }

    teclas[tecla] = false;
}

void soltarTodasAsTeclas() {

    for (
        int i = 0;
        i <= GLFW_KEY_LAST;
        i++
    ) {

        teclas[i] = false;
    }
}

void redefinirMouse() {

    temUltimo = false;
}

void moverMouse(double x, double y) {

    if (!temUltimo) {

        ultimoX = x;
        ultimoY = y;
        temUltimo = true;

        return;
    }

    rotacionarCamera(
        static_cast<float>(x - ultimoX),
        static_cast<float>(y - ultimoY)
    );

    ultimoX = x;
    ultimoY = y;
}

void atualizarControles(float deltaTempo) {

    if (deltaTempo <= 0.0f) {

        return;
    }

    // ========================================================
    // MOVIMENTO (unidades por segundo)
    // ========================================================

    const float velocidade =
        3.6f;

    const float passo =
        velocidade * deltaTempo;


    if (teclas[GLFW_KEY_W]) {

        moverCameraFrente(passo);
    }

    if (teclas[GLFW_KEY_S]) {

        moverCameraTras(passo);
    }

    if (teclas[GLFW_KEY_A]) {

        moverCameraEsquerda(passo);
    }

    if (teclas[GLFW_KEY_D]) {

        moverCameraDireita(passo);
    }


    // ========================================================
    // ROTACAO PELAS SETAS (graus por segundo)
    //
    // Fallback que funciona em qualquer sessao, inclusive
    // Wayland, onde nao ha captura absoluta do ponteiro.
    // ========================================================

    const float giro =
        90.0f * deltaTempo;


    if (teclas[GLFW_KEY_LEFT]) {

        girarCamera(giro, 0.0f);
    }

    if (teclas[GLFW_KEY_RIGHT]) {

        girarCamera(-giro, 0.0f);
    }

    if (teclas[GLFW_KEY_UP]) {

        girarCamera(0.0f, giro);
    }

    if (teclas[GLFW_KEY_DOWN]) {

        girarCamera(0.0f, -giro);
    }
}

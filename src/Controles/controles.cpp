#include "controles.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <iterator>

#include "../Camera/camera.h"
#include "../Interacoes/interacoes.h"

namespace { 

    const float VELOCIDADE_MOVIMENTO = 2.0f;  // unidades por segundo
    const float VELOCIDADE_ROTACAO = 90.0f;   // graus por segundo

    bool teclas[GLFW_KEY_LAST + 1] = { false };

    // Ultima posicao recebida do mouse. O primeiro evento apenas
    // registra a referencia para calcular o proximo delta.
    double ultimoX = 0.0;
    double ultimoY = 0.0;
    bool temUltimo = false;

    bool teclaAtiva(int tecla) {

        return
            tecla >= 0 &&
            tecla <= GLFW_KEY_LAST &&
            teclas[tecla];
    }
}


// TECLADO
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

    std::fill(
        std::begin(teclas),
        std::end(teclas),
        false
    );
}



// MOUSE
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



// ATUALIZACAO CONTINUA
void atualizarControles(float deltaTempo) {

    if (deltaTempo <= 0.0f) {

        return;
    }

    const float passo = VELOCIDADE_MOVIMENTO * deltaTempo;

    if (teclaAtiva(GLFW_KEY_W)) moverCameraFrente(passo);
    if (teclaAtiva(GLFW_KEY_S)) moverCameraTras(passo);
    if (teclaAtiva(GLFW_KEY_A)) moverCameraEsquerda(passo);
    if (teclaAtiva(GLFW_KEY_D)) moverCameraDireita(passo);

    // Setas como alternativa ao mouse (funcionam no Wayland).
    const float giro = VELOCIDADE_ROTACAO * deltaTempo;

    if (teclaAtiva(GLFW_KEY_LEFT))  girarCamera( giro, 0.0f);
    if (teclaAtiva(GLFW_KEY_RIGHT)) girarCamera(-giro, 0.0f);
    if (teclaAtiva(GLFW_KEY_UP))    girarCamera(0.0f,  giro);
    if (teclaAtiva(GLFW_KEY_DOWN))  girarCamera(0.0f, -giro);
}

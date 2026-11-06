#include <GLFW/glfw3.h>

#include "Janela/janela.h"
#include "Camera/camera.h"
#include "Controles/controles.h"
#include "Interacoes/interacoes.h"
#include "Renderizacao/renderizador.h"

// ============================================================
// TECLADO
// ============================================================

static void callbackTecla(
    GLFWwindow* janela,
    int tecla,
    int,
    int acao,
    int
) {

    if (
        tecla == GLFW_KEY_ESCAPE &&
        acao == GLFW_PRESS
    ) {

        glfwSetWindowShouldClose(
            janela,
            GLFW_TRUE
        );

        return;
    }

    if (acao == GLFW_PRESS) {

        teclaPressionada(tecla);
    }

    else if (acao == GLFW_RELEASE) {

        teclaSolta(tecla);
    }
}

// ============================================================
// MOUSE
//
// Com GLFW_CURSOR_DISABLED o GLFW entrega a posicao virtual
// do cursor, sem limite de tela. Funciona no Wayland atraves
// do protocolo relative-pointer.
// ============================================================

static void callbackMouse(
    GLFWwindow*,
    double x,
    double y
) {

    moverMouse(x, y);
}

// ============================================================
// FOCO
// ============================================================

static void callbackFoco(
    GLFWwindow*,
    int focado
) {

    // Evita teclas "presas" ao trocar de janela.
    if (!focado) {

        soltarTodasAsTeclas();
    }

    redefinirMouse();
}

// ============================================================
// MAIN
// ============================================================

int main() {

    if (!criarJanela(800, 600, "Cafeteria")) {

        return 1;
    }

    GLFWwindow* janela = obterJanela();

    glfwSetKeyCallback(
        janela,
        callbackTecla
    );

    glfwSetCursorPosCallback(
        janela,
        callbackMouse
    );

    glfwSetWindowFocusCallback(
        janela,
        callbackFoco
    );

    // Captura o cursor: movimento relativo continuo.
    glfwSetInputMode(
        janela,
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED
    );

    redefinirMouse();

    glEnable(GL_DEPTH_TEST);

    inicializarCamera();
    inicializarInteracoes();

    // ========================================================
    // LOOP PRINCIPAL
    // ========================================================

    double instanteAnterior =
        glfwGetTime();

    while (!janelaDeveFechar()) {

        double instanteAtual =
            glfwGetTime();

        float deltaTempo =
            static_cast<float>(
                instanteAtual -
                instanteAnterior
            );

        instanteAnterior =
            instanteAtual;

        // Evita passos grandes depois de uma pausa,
        // que poderiam atravessar a colisao.
        if (deltaTempo > 0.05f) {

            deltaTempo = 0.05f;
        }

        processarEventos();

        atualizarControles(deltaTempo);

        atualizarInteracoes();

        renderizarCena();

        trocarBuffers();
    }

    destruirJanela();

    return 0;
}

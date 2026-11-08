#include <GLFW/glfw3.h>

#include <algorithm>

#include "Janela/janela.h"
#include "Camera/camera.h"
#include "Controles/controles.h"
#include "Interacoes/interacoes.h"
#include "Renderizacao/renderizador.h"

namespace {

const float DELTA_MAXIMO = 0.05f;

void callbackTecla(
    GLFWwindow* janela, int tecla, int, int acao, int) 
{

    if (tecla == GLFW_KEY_ESCAPE && acao == GLFW_PRESS) {

        glfwSetWindowShouldClose(janela, GLFW_TRUE);
        return;
    }

    if (acao == GLFW_PRESS) {

        teclaPressionada(tecla);
    }

    else if (acao == GLFW_RELEASE) {

        teclaSolta(tecla);
    }
}

// Com GLFW_CURSOR_DISABLED o GLFW entrega a posicao virtual do cursor
void callbackMouse(GLFWwindow*, double x, double y) {

    moverMouse(x, y);
}

void callbackFoco(GLFWwindow*, int focado) {

    // Evita teclas "presas" ao trocar de janela.
    if (!focado) { // 0 se perdeu o foco

        soltarTodasAsTeclas();
    }

    redefinirMouse();
}

void configurarEntrada(GLFWwindow* janela) {

    glfwSetKeyCallback(janela, callbackTecla);
    glfwSetCursorPosCallback(janela, callbackMouse);
    glfwSetWindowFocusCallback(janela, callbackFoco);

    glfwSetInputMode(janela, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ocultar o cursor

    redefinirMouse();
}

float calcularDeltaTempo(double& instanteAnterior) {

    const double instanteAtual = glfwGetTime();

    const float delta =
        static_cast<float>(instanteAtual - instanteAnterior);

    instanteAnterior = instanteAtual;

    // Evita passos grandes depois de uma pausa, que poderiam
    // atravessar a colisao.
    return std::min(delta, DELTA_MAXIMO);
}

} // namespace

int main() {

    if (!criarJanela(800, 600, "Cafeteria")) {
        return 1;
    }

    GLFWwindow* janela = obterJanela();

    configurarEntrada(janela);

    glEnable(GL_DEPTH_TEST); // habilita o eixo z

    inicializarCamera();
    inicializarInteracoes();

    double instanteAnterior = glfwGetTime();

    while (!janelaDeveFechar()) {

        const float deltaTempo = calcularDeltaTempo(instanteAnterior);

        glfwPollEvents(); //processarEventos

        atualizarControles(deltaTempo);
        atualizarInteracoes(deltaTempo);

        renderizarCena();
        glfwSwapBuffers(janela);
    }

    glfwDestroyWindow(janela); // destroe a janela
    glfwTerminate(); 

    return 0;
}

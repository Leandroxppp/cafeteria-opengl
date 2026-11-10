#include "janela.h"

#include <GLFW/glfw3.h>

#include <cstdio>

static GLFWwindow* janela = nullptr;

bool criarJanela(int largura, int altura, const char* titulo) {

    if (!glfwInit()) {
        return false;
    }

    // 2.1 e suficiente e funciona no X11 e no Wayland.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    janela = glfwCreateWindow(largura, altura, titulo, nullptr, nullptr); // 4 = monitor, 5 = compartilhamento de contexto

    if (!janela) {
        glfwTerminate(); // finalizar o glfwInit iniciou

        return false;
    }

    glfwMakeContextCurrent(janela);

    // VSync: o swap passa a limitar a taxa de quadros. Apenas realiza o swap no mesmo momento que a atualizacao de tela do monitor
    glfwSwapInterval(1);

    return true;
}

GLFWwindow* obterJanela() {

    return janela;
}

void obterTamanhoJanela(int* largura, int* altura) {

    if (!janela) { // a janela não existe

        *largura = 1; // valor de seguranca
        *altura = 1; // valor de seguranca

        return;
    }

    glfwGetFramebufferSize(
        janela,
        largura,
        altura
    );

    if (*largura <= 0) { // a janela está minimizada

        *largura = 1;
    }

    if (*altura <= 0) {

        *altura = 1;
    }
}

bool janelaDeveFechar() {

    return !janela || glfwWindowShouldClose(janela);
}

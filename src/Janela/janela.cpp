#include "janela.h"

#include <GLFW/glfw3.h>

#include <cstdio>

static GLFWwindow* janela = nullptr;

bool criarJanela(int largura, int altura, const char* titulo) {

    if (!glfwInit()) {

        std::fprintf(
            stderr,
            "Falha ao inicializar o GLFW\n"
        );

        return false;
    }

    // A cena usa OpenGL de funcao fixa (glBegin/glEnd,
    // glFrustum, glLightfv). Um contexto de compatibilidade
    // 2.1 e suficiente e funciona no X11 e no Wayland.
    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        2
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        1
    );

    janela = glfwCreateWindow(
        largura,
        altura,
        titulo,
        nullptr,
        nullptr
    );

    if (!janela) {

        std::fprintf(
            stderr,
            "Falha ao criar a janela GLFW\n"
        );

        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(janela);

    // VSync: o swap passa a limitar a taxa de quadros.
    glfwSwapInterval(1);

    return true;
}

GLFWwindow* obterJanela() {

    return janela;
}

void obterTamanhoJanela(int* largura, int* altura) {

    if (!janela) {

        *largura = 1;
        *altura = 1;

        return;
    }

    glfwGetFramebufferSize(
        janela,
        largura,
        altura
    );

    if (*largura <= 0) {

        *largura = 1;
    }

    if (*altura <= 0) {

        *altura = 1;
    }
}

void trocarBuffers() {

    if (janela) {

        glfwSwapBuffers(janela);
    }
}

void processarEventos() {

    glfwPollEvents();
}

bool janelaDeveFechar() {

    return !janela || glfwWindowShouldClose(janela);
}

void destruirJanela() {

    if (janela) {

        glfwDestroyWindow(janela);

        janela = nullptr;
    }

    glfwTerminate();
}

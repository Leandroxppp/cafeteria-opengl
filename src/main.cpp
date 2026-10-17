#include <windows.h>

#include "Janela/janela.h"
#include "Camera/camera.h"
#include "Controles/controles.h"
#include "Renderizacao/renderizador.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow
) {

    // Inicializa teclado
    inicializarControles();

    // Coloca a camera na posicao inicial
    inicializarCamera();

    // Cria a janela e inicia o OpenGL
    if (!criarJanela(hInstance, nCmdShow)) {
        return 1;
    }


    bool executando = true;


    // Loop principal do programa
    while (executando) {

        // Processa teclado, fechamento da janela etc.
        executando = processarEventos();


        // Se o programa recebeu ordem para fechar,
        // sai do loop imediatamente
        if (!executando) {
            break;
        }


        // Atualiza W A S D
        atualizarControles();


        // Desenha a cafeteria
        renderizarCena();


        // Exibe o frame
        atualizarJanela();


        // Limita aproximadamente a 60 FPS.
        // Isso também evita a movimentacao ficar absurdamente rapida.
        Sleep(16);
    }


    // Libera OpenGL e a janela
    destruirJanela();


    return 0;
}
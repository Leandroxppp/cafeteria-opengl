#include <windows.h>

#include "Janela/janela.h"
#include "Camera/camera.h"
#include "Controles/controles.h"
#include "Interacoes/interacoes.h"
#include "Renderizacao/renderizador.h"


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow
) {

    // ========================================================
    // INICIALIZACAO
    // ========================================================

    // Inicializa teclado e controles
    inicializarControles();


    // Coloca a camera na posicao inicial
    inicializarCamera();


    // Inicializa as interacoes
    // Porta começa fechada
    inicializarInteracoes();


    // Cria a janela e inicia o OpenGL
    if (!criarJanela(
        hInstance,
        nCmdShow
    )) {

        return 1;
    }


    // ========================================================
    // LOOP PRINCIPAL
    // ========================================================

    bool executando = true;


    while (executando) {

        // ----------------------------------------------------
        // EVENTOS
        // ----------------------------------------------------

        executando =
            processarEventos();


        if (!executando) {
            break;
        }


        // ----------------------------------------------------
        // CONTROLES
        // ----------------------------------------------------

        atualizarControles();


        // ----------------------------------------------------
        // INTERACOES
        //
        // Atualiza a animacao da porta.
        // ----------------------------------------------------

        atualizarInteracoes();


        // ----------------------------------------------------
        // DESENHAR CENA
        // ----------------------------------------------------

        renderizarCena();


        // ----------------------------------------------------
        // MOSTRAR FRAME
        // ----------------------------------------------------

        atualizarJanela();


        // Aproximadamente 60 FPS
        Sleep(16);
    }


    // ========================================================
    // FINALIZACAO
    // ========================================================

    destruirJanela();


    return 0;
}
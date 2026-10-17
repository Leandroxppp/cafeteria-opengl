#include "janela.h"
#include "../Controles/controles.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// DADOS DA JANELA
// ============================================================

static HWND janela = nullptr;
static HDC dispositivo = nullptr;
static HGLRC contextoOpenGL = nullptr;

static int larguraJanela = 1280;
static int alturaJanela = 720;


// ============================================================
// CENTRALIZA O MOUSE
// ============================================================

static void centralizarMouse(HWND hwnd) {

    RECT area;

    GetClientRect(
        hwnd,
        &area
    );


    POINT centro;

    centro.x =
        (area.right - area.left) / 2;

    centro.y =
        (area.bottom - area.top) / 2;


    ClientToScreen(
        hwnd,
        &centro
    );


    SetCursorPos(
        centro.x,
        centro.y
    );
}


// ============================================================
// CONFIGURACAO DO OPENGL
// ============================================================

static bool configurarPixelFormat(HDC hdc) {

    PIXELFORMATDESCRIPTOR pfd = {};

    pfd.nSize =
        sizeof(PIXELFORMATDESCRIPTOR);

    pfd.nVersion = 1;


    pfd.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;


    pfd.iPixelType =
        PFD_TYPE_RGBA;


    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;


    pfd.iLayerType =
        PFD_MAIN_PLANE;


    int pixelFormat =
        ChoosePixelFormat(
            hdc,
            &pfd
        );


    if (pixelFormat == 0) {
        return false;
    }


    return SetPixelFormat(
        hdc,
        pixelFormat,
        &pfd
    ) == TRUE;
}


// ============================================================
// EVENTOS
// ============================================================

static LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT mensagem,
    WPARAM wParam,
    LPARAM lParam
) {

    switch (mensagem) {


        // Tecla pressionada
        case WM_KEYDOWN:

            teclaPressionada(
                static_cast<int>(wParam)
            );


            if (wParam == VK_ESCAPE) {
                DestroyWindow(hwnd);
            }


            return 0;


        // Tecla solta
        case WM_KEYUP:

            teclaSolta(
                static_cast<int>(wParam)
            );

            return 0;


        // ====================================================
        // MOUSE
        // ====================================================

        case WM_MOUSEMOVE: {

            RECT area;

            GetClientRect(
                hwnd,
                &area
            );


            int centroX =
                (area.right - area.left) / 2;

            int centroY =
                (area.bottom - area.top) / 2;


            int mouseX =
                static_cast<short>(
                    LOWORD(lParam)
                );

            int mouseY =
                static_cast<short>(
                    HIWORD(lParam)
                );


            int deltaX =
                mouseX - centroX;

            int deltaY =
                mouseY - centroY;


            // Só movimenta se o mouse saiu do centro
            if (
                deltaX != 0 ||
                deltaY != 0
            ) {

                moverMouse(
                    deltaX,
                    deltaY
                );


                // Retorna o mouse para o centro
                centralizarMouse(hwnd);
            }


            return 0;
        }


        // Janela redimensionada
        case WM_SIZE:

            larguraJanela =
                LOWORD(lParam);

            alturaJanela =
                HIWORD(lParam);


            if (larguraJanela <= 0) {
                larguraJanela = 1;
            }


            if (alturaJanela <= 0) {
                alturaJanela = 1;
            }


            return 0;


        // Fechar janela
        case WM_CLOSE:

            DestroyWindow(hwnd);

            return 0;


        case WM_DESTROY:

            PostQuitMessage(0);

            return 0;
    }


    return DefWindowProc(
        hwnd,
        mensagem,
        wParam,
        lParam
    );
}


// ============================================================
// CRIAR JANELA
// ============================================================

bool criarJanela(
    HINSTANCE hInstance,
    int nCmdShow
) {

    WNDCLASS wc = {};

    wc.style =
        CS_OWNDC;

    wc.lpfnWndProc =
        WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        "CafeteriaOpenGLWindow";

    wc.hCursor =
        LoadCursor(
            nullptr,
            IDC_ARROW
        );


    if (!RegisterClass(&wc)) {
        return false;
    }


    janela =
        CreateWindowEx(
            0,

            wc.lpszClassName,

            "Cafeteria 3D",

            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,
            CW_USEDEFAULT,

            larguraJanela,
            alturaJanela,

            nullptr,
            nullptr,

            hInstance,

            nullptr
        );


    if (!janela) {
        return false;
    }


    dispositivo =
        GetDC(janela);


    if (!configurarPixelFormat(dispositivo)) {
        return false;
    }


    contextoOpenGL =
        wglCreateContext(
            dispositivo
        );


    if (!contextoOpenGL) {
        return false;
    }


    wglMakeCurrent(
        dispositivo,
        contextoOpenGL
    );


    glEnable(
        GL_DEPTH_TEST
    );


    glDisable(
        GL_CULL_FACE
    );


    ShowWindow(
        janela,
        nCmdShow
    );


    UpdateWindow(
        janela
    );


    // Esconde o cursor
    ShowCursor(FALSE);


    // Coloca o mouse no centro
    centralizarMouse(janela);


    return true;
}


// ============================================================
// PROCESSAR EVENTOS
// ============================================================

bool processarEventos() {

    MSG mensagem;


    while (
        PeekMessage(
            &mensagem,
            nullptr,
            0,
            0,
            PM_REMOVE
        )
    ) {

        if (
            mensagem.message ==
            WM_QUIT
        ) {

            return false;
        }


        TranslateMessage(
            &mensagem
        );


        DispatchMessage(
            &mensagem
        );
    }


    return true;
}


// ============================================================
// MOSTRAR FRAME
// ============================================================

void atualizarJanela() {

    if (dispositivo) {

        SwapBuffers(
            dispositivo
        );
    }
}


// ============================================================
// ENCERRAR
// ============================================================

void destruirJanela() {

    // Cursor volta a aparecer
    ShowCursor(TRUE);


    wglMakeCurrent(
        nullptr,
        nullptr
    );


    if (contextoOpenGL) {

        wglDeleteContext(
            contextoOpenGL
        );

        contextoOpenGL = nullptr;
    }


    if (
        dispositivo &&
        janela
    ) {

        ReleaseDC(
            janela,
            dispositivo
        );

        dispositivo = nullptr;
    }


    if (janela) {

        DestroyWindow(
            janela
        );

        janela = nullptr;
    }
}


// ============================================================
// TAMANHO
// ============================================================

int obterLarguraJanela() {

    return larguraJanela;
}


int obterAlturaJanela() {

    return alturaJanela;
}
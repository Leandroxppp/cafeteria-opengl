#include "renderizador.h"

#include "../Camera/camera.h"
#include "../Janela/janela.h"
#include "../Sala/sala.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


// ============================================================
// PERSPECTIVA 3D
// ============================================================

// Configura a perspectiva da camera.
//
// fovY   = campo de visao
// aspect = proporcao largura / altura
// zNear  = distancia minima visivel
// zFar   = distancia maxima visivel

static void configurarPerspectiva(
    double fovY,
    double aspect,
    double zNear,
    double zFar
) {

    const double PI =
        3.14159265358979323846;


    double altura =
        tan(
            fovY / 360.0 * PI
        ) * zNear;


    double largura =
        altura * aspect;


    glFrustum(
        -largura,
         largura,
        -altura,
         altura,
         zNear,
         zFar
    );
}


// ============================================================
// RENDERIZAR CENA
// ============================================================

void renderizarCena() {

    // --------------------------------------------------------
    // TAMANHO DA JANELA
    // --------------------------------------------------------

    int largura =
        obterLarguraJanela();

    int altura =
        obterAlturaJanela();


    if (altura <= 0) {
        altura = 1;
    }


    // --------------------------------------------------------
    // AREA DE DESENHO
    // --------------------------------------------------------

    glViewport(
        0,
        0,
        largura,
        altura
    );


    // --------------------------------------------------------
    // COR DO FUNDO
    // --------------------------------------------------------

    glClearColor(
        0.08f,
        0.08f,
        0.09f,
        1.0f
    );


    // --------------------------------------------------------
    // LIMPAR FRAME ANTERIOR
    // --------------------------------------------------------

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );


    // ========================================================
    // PROJECAO
    // ========================================================

    glMatrixMode(
        GL_PROJECTION
    );


    glLoadIdentity();


    configurarPerspectiva(
        70.0,
        static_cast<double>(largura) /
        static_cast<double>(altura),
        0.1,
        100.0
    );


    // ========================================================
    // VISAO / CAMERA
    // ========================================================

    glMatrixMode(
        GL_MODELVIEW
    );


    glLoadIdentity();


    aplicarCamera();


    // ========================================================
    // CENA
    // ========================================================

    desenharSala();


    // Depois adicionaremos:
    //
    // desenharMesas();
    // desenharCadeiras();
    // desenharPorta();
    // desenharMenu();
    // desenharBalcao();
    // desenharVitrine();
    // etc.
}
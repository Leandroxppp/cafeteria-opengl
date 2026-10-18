#include "renderizador.h"

#include "../Interacoes/interacoes.h"
#include "../Objetos/Menu/menu.h"
#include "../Objetos/Porta/porta.h"
#include "../Objetos/Interruptor/interruptor.h"
#include "../Objetos/PortaGuardanapos/porta_guardanapos.h"
#include "../Objetos/Xicara/xicara.h"
#include "../Objetos/Vasinho/vasinho.h"
#include "../Camera/camera.h"
#include "../Janela/janela.h"
#include "../Sala/sala.h"
#include "../Objetos/Mesa/mesa.h"
#include "../Objetos/Cadeira/cadeira.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


// ============================================================
// PERSPECTIVA 3D
// ============================================================

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
// ILUMINACAO
// ============================================================

static void configurarIluminacao() {

    // ========================================================
    // SISTEMA DE ILUMINACAO
    // ========================================================

    glEnable(GL_LIGHTING);

    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );


    glLightModeli(
        GL_LIGHT_MODEL_TWO_SIDE,
        GL_TRUE
    );


    // ========================================================
    // LUZ LIGADA
    // ========================================================

    if (luzEstaLigada()) {

        GLfloat ambiente[] = {
            0.40f,
            0.37f,
            0.32f,
            1.0f
        };


        glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT,
            ambiente
        );


        glEnable(GL_LIGHT0);


        GLfloat posicao[] = {
            0.0f,
            2.8f,
            0.5f,
            1.0f
        };


        GLfloat difusa[] = {
            1.0f,
            0.95f,
            0.85f,
            1.0f
        };


        GLfloat especular[] = {
            0.35f,
            0.30f,
            0.25f,
            1.0f
        };


        glLightfv(
            GL_LIGHT0,
            GL_POSITION,
            posicao
        );


        glLightfv(
            GL_LIGHT0,
            GL_DIFFUSE,
            difusa
        );


        glLightfv(
            GL_LIGHT0,
            GL_SPECULAR,
            especular
        );
    }


    // ========================================================
    // LUZ DESLIGADA
    // ========================================================

    else {

        glDisable(GL_LIGHT0);


        GLfloat ambienteEscuro[] = {
            0.06f,
            0.06f,
            0.07f,
            1.0f
        };


        glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT,
            ambienteEscuro
        );
    }
}


// ============================================================
// DESENHAR MESAS
// ============================================================

static void desenharMesas() {

    // Mesa esquerda
    desenharMesa(
        -3.0f,
         0.5f,
         0.0f
    );


    // Mesa central
    desenharMesa(
         0.0f,
         0.5f,
         0.0f
    );


    // Mesa direita
    desenharMesa(
         3.0f,
         0.5f,
         0.0f
    );
}


// ============================================================
// DECORACOES DAS MESAS
// ============================================================

static void desenharDecoracoesMesas() {

    // Altura do topo do tampo.
    //
    // Todos os objetos foram modelados com a base
    // iniciando em Y = 0 local.
    //
    // Portanto, usando esta altura eles ficam apoiados
    // diretamente sobre a mesa e nao flutuam.
    const float alturaTampo = 0.766f;


    // --------------------------------------------------------
    // MESA ESQUERDA -> VASINHO
    // --------------------------------------------------------

    desenharVasinho(
        -3.0f,
         alturaTampo,
         0.50f
    );


    // --------------------------------------------------------
    // MESA CENTRAL -> PORTA-GUARDANAPOS
    // --------------------------------------------------------

    desenharPortaGuardanapos(
         0.0f,
         alturaTampo,
         0.50f
    );


    // --------------------------------------------------------
    // MESA DIREITA -> XICARA
    // --------------------------------------------------------

    desenharXicara(
         3.15f,
         alturaTampo,
         0.50f
    );
}


// ============================================================
// DESENHAR CADEIRAS
//
// Indices:
//
// 0 = mesa esquerda / lado positivo de Z
// 1 = mesa esquerda / lado negativo de Z
//
// 2 = mesa central / lado positivo de Z
// 3 = mesa central / lado negativo de Z
//
// 4 = mesa direita / lado positivo de Z
// 5 = mesa direita / lado negativo de Z
// ============================================================

static void desenharCadeiras() {

    // ========================================================
    // MESA ESQUERDA
    // ========================================================

    // Cadeira 0
    desenharCadeira(
        -3.0f,
         1.2f + obterDeslocamentoCadeira(0),
         180.0f
    );


    // Cadeira 1
    desenharCadeira(
        -3.0f,
        -0.2f + obterDeslocamentoCadeira(1),
         0.0f
    );


    // ========================================================
    // MESA CENTRAL
    // ========================================================

    // Cadeira 2
    desenharCadeira(
         0.0f,
         1.2f + obterDeslocamentoCadeira(2),
         180.0f
    );


    // Cadeira 3
    desenharCadeira(
         0.0f,
        -0.2f + obterDeslocamentoCadeira(3),
         0.0f
    );


    // ========================================================
    // MESA DIREITA
    // ========================================================

    // Cadeira 4
    desenharCadeira(
         3.0f,
         1.2f + obterDeslocamentoCadeira(4),
         180.0f
    );


    // Cadeira 5
    desenharCadeira(
         3.0f,
        -0.2f + obterDeslocamentoCadeira(5),
         0.0f
    );
}


// ============================================================
// RENDERIZAR CENA
// ============================================================

void renderizarCena() {

    // ========================================================
    // TAMANHO DA JANELA
    // ========================================================

    int largura =
        obterLarguraJanela();

    int altura =
        obterAlturaJanela();


    if (altura <= 0) {
        altura = 1;
    }


    // ========================================================
    // AREA DE DESENHO
    // ========================================================

    glViewport(
        0,
        0,
        largura,
        altura
    );


    // ========================================================
    // COR DO FUNDO
    // ========================================================

    glClearColor(
        0.08f,
        0.08f,
        0.09f,
        1.0f
    );


    // ========================================================
    // LIMPAR FRAME ANTERIOR
    // ========================================================

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
    // CAMERA
    // ========================================================

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();


    aplicarCamera();


    // ========================================================
    // ILUMINACAO
    // ========================================================

    configurarIluminacao();


    // ========================================================
    // SALA
    // ========================================================

    desenharSala();


    // ========================================================
    // MESAS
    // ========================================================

    desenharMesas();


    // ========================================================
    // DECORACOES DAS MESAS
    // ========================================================

    desenharDecoracoesMesas();


    // ========================================================
    // CADEIRAS
    // ========================================================

    desenharCadeiras();


    // ========================================================
    // PORTA PRINCIPAL
    // ========================================================

    desenharPorta(
        obterAnguloPorta()
    );


    // ========================================================
    // QUADRO DE MENU
    // ========================================================

    desenharMenu();


    // ========================================================
    // INTERRUPTOR
    // ========================================================

    desenharInterruptor(
        luzEstaLigada()
    );
}
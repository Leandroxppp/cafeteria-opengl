#include "renderizador.h"

#include "../Interacoes/interacoes.h"

#include "../Objetos/PortaBanheiro/porta_banheiro.h"
#include "../Objetos/Menu/menu.h"
#include "../Objetos/Porta/porta.h"
#include "../Objetos/Interruptor/interruptor.h"
#include "../Objetos/PortaGuardanapos/porta_guardanapos.h"
#include "../Objetos/Xicara/xicara.h"
#include "../Objetos/Vasinho/vasinho.h"
#include "../Objetos/Balcao/balcao.h"
#include "../Objetos/Vitrine/vitrine.h"
#include "../Objetos/Registradora/registradora.h"
#include "../Objetos/MaquinaCafe/maquina_cafe.h"
#include "../Objetos/Luminaria/luminaria.h"
#include "../Objetos/JanelaCafe/janela_cafe.h"
#include "../Objetos/Prateleira/prateleira.h"

#include "../Objetos/VasoSanitario/vaso_sanitario.h"
#include "../Objetos/PiaBanheiro/pia_banheiro.h"
#include "../Objetos/EspelhoBanheiro/espelho_banheiro.h"

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
// CONFIGURAR LUZ DE UMA LUMINARIA
// ============================================================

static void configurarLuzLuminaria(
    GLenum luz,
    float x,
    float y,
    float z
) {

    GLfloat posicao[] = {
        x,
        y,
        z,
        1.0f
    };


    GLfloat direcao[] = {
         0.0f,
        -1.0f,
         0.0f
    };


    GLfloat ambiente[] = {
        0.025f,
        0.022f,
        0.018f,
        1.0f
    };


    GLfloat difusa[] = {
        1.00f,
        0.90f,
        0.65f,
        1.0f
    };


    GLfloat especular[] = {
        0.55f,
        0.45f,
        0.30f,
        1.0f
    };


    glEnable(luz);


    glLightfv(
        luz,
        GL_POSITION,
        posicao
    );


    glLightfv(
        luz,
        GL_SPOT_DIRECTION,
        direcao
    );


    glLightfv(
        luz,
        GL_AMBIENT,
        ambiente
    );


    glLightfv(
        luz,
        GL_DIFFUSE,
        difusa
    );


    glLightfv(
        luz,
        GL_SPECULAR,
        especular
    );


    glLightf(
        luz,
        GL_SPOT_CUTOFF,
        48.0f
    );


    glLightf(
        luz,
        GL_SPOT_EXPONENT,
        8.0f
    );


    glLightf(
        luz,
        GL_CONSTANT_ATTENUATION,
        1.0f
    );


    glLightf(
        luz,
        GL_LINEAR_ATTENUATION,
        0.10f
    );


    glLightf(
        luz,
        GL_QUADRATIC_ATTENUATION,
        0.025f
    );
}


// ============================================================
// ILUMINACAO
// ============================================================

static void configurarIluminacao() {

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

        GLfloat ambienteGlobal[] = {
            0.23f,
            0.21f,
            0.18f,
            1.0f
        };


        glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT,
            ambienteGlobal
        );


        // ====================================================
        // LUZ GERAL
        // ====================================================

        glEnable(GL_LIGHT0);


        GLfloat posicaoGeral[] = {
            0.0f,
            2.85f,
            0.0f,
            1.0f
        };


        GLfloat ambienteGeral[] = {
            0.0f,
            0.0f,
            0.0f,
            1.0f
        };


        GLfloat difusaGeral[] = {
            0.28f,
            0.26f,
            0.22f,
            1.0f
        };


        GLfloat especularGeral[] = {
            0.10f,
            0.09f,
            0.075f,
            1.0f
        };


        glLightfv(
            GL_LIGHT0,
            GL_POSITION,
            posicaoGeral
        );


        glLightfv(
            GL_LIGHT0,
            GL_AMBIENT,
            ambienteGeral
        );


        glLightfv(
            GL_LIGHT0,
            GL_DIFFUSE,
            difusaGeral
        );


        glLightfv(
            GL_LIGHT0,
            GL_SPECULAR,
            especularGeral
        );


        // ====================================================
        // LUMINARIA ESQUERDA
        // ====================================================

        configurarLuzLuminaria(
            GL_LIGHT1,
            -3.0f,
             2.43f,
             0.50f
        );


        // ====================================================
        // LUMINARIA CENTRAL
        // ====================================================

        configurarLuzLuminaria(
            GL_LIGHT2,
             0.0f,
             2.43f,
             0.50f
        );


        // ====================================================
        // LUMINARIA DIREITA
        // ====================================================

        configurarLuzLuminaria(
            GL_LIGHT3,
             3.0f,
             2.43f,
             0.50f
        );
    }


    // ========================================================
    // LUZ DESLIGADA
    // ========================================================

    else {

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);


        GLfloat ambienteEscuro[] = {
            0.045f,
            0.045f,
            0.055f,
            1.0f
        };


        glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT,
            ambienteEscuro
        );
    }
}


// ============================================================
// JANELA DA CAFETERIA
// ============================================================

static void desenharJanelaDaCafeteria() {

    desenharJanelaCafe(
        -5.94f,
         1.70f,
         2.00f
    );
}


// ============================================================
// LUMINARIAS
// ============================================================

static void desenharLuminarias() {

    bool ligada =
        luzEstaLigada();


    desenharLuminaria(
        -3.0f,
         2.98f,
         0.50f,
         ligada
    );


    desenharLuminaria(
         0.0f,
         2.98f,
         0.50f,
         ligada
    );


    desenharLuminaria(
         3.0f,
         2.98f,
         0.50f,
         ligada
    );
}


// ============================================================
// PRATELEIRA ATRAS DO BALCAO
// ============================================================

static void desenharPrateleiraBalcao() {

    desenharPrateleira(
        -3.85f,
         1.95f,
        -3.86f,
         0.0f
    );
}


// ============================================================
// BANHEIRO
//
// Area aproximada:
//
// X = 3.6 ate 6.0
// Z = -4.0 ate -2.2
// ============================================================

static void desenharObjetosBanheiro() {

    // ========================================================
    // VASO SANITARIO
    // ========================================================

    desenharVasoSanitario(
        4.25f,
        0.0f,
       -3.48f,
        0.0f
    );


    // ========================================================
    // PIA
    // ========================================================

    desenharPiaBanheiro(
         5.62f,
         0.0f,
        -3.05f,
        -90.0f
    );


    // ========================================================
    // ESPELHO
    // ========================================================

    desenharEspelhoBanheiro(
         5.91f,
         1.72f,
        -3.05f,
        -90.0f
    );
}


// ============================================================
// PORTA DO BANHEIRO
// ============================================================

static void desenharPortaDoBanheiro() {

    glPushMatrix();


    // ========================================================
    // POSICIONAR NO CENTRO DO VAO
    //
    // O modelo da porta usa coordenadas locais.
    // O centro aproximado do vao fica em X = 4.79.
    // ========================================================

    glTranslatef(
         4.79f,
         0.0f,
        -2.10f
    );


    // ========================================================
    // DESENHAR PORTA
    // ========================================================

    desenharPortaBanheiro(
        obterAnguloPortaBanheiro()
    );


    glPopMatrix();
}


// ============================================================
// MESAS
// ============================================================

static void desenharMesas() {

    desenharMesa(
        -3.0f,
         0.5f,
         0.0f
    );


    desenharMesa(
         0.0f,
         0.5f,
         0.0f
    );


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

    const float alturaTampo =
        0.766f;


    // Mesa esquerda
    desenharVasinho(
        -3.0f,
         alturaTampo,
         0.50f
    );


    // Mesa central
    desenharPortaGuardanapos(
         0.0f,
         alturaTampo,
         0.50f
    );


    // Mesa direita
    desenharXicara(
         3.0f,
         alturaTampo,
         0.50f
    );
}


// ============================================================
// BALCAO PRINCIPAL
// ============================================================

static void desenharBalcaoPrincipal() {

    desenharBalcao(
        -3.60f,
         0.0f,
        -2.65f,
         0.0f
    );
}


// ============================================================
// VITRINE
// ============================================================

static void desenharVitrineDoces() {

    desenharVitrine(
        -4.25f,
         1.07f,
        -2.65f
    );
}


// ============================================================
// REGISTRADORA
// ============================================================

static void desenharCaixaRegistradora() {

    desenharRegistradora(
        -3.25f,
         1.07f,
        -2.60f,
         180.0f
    );
}


// ============================================================
// MAQUINA DE CAFE
// ============================================================

static void desenharMaquinaCafeBalcao() {

    desenharMaquinaCafe(
        -2.55f,
         1.07f,
        -2.65f,
         180.0f
    );
}


// ============================================================
// CADEIRAS
// ============================================================

static void desenharCadeiras() {

    // ========================================================
    // MESA ESQUERDA
    // ========================================================

    desenharCadeira(
        -3.0f,
         1.2f + obterDeslocamentoCadeira(0),
         180.0f
    );


    desenharCadeira(
        -3.0f,
        -0.2f + obterDeslocamentoCadeira(1),
         0.0f
    );


    // ========================================================
    // MESA CENTRAL
    // ========================================================

    desenharCadeira(
         0.0f,
         1.2f + obterDeslocamentoCadeira(2),
         180.0f
    );


    desenharCadeira(
         0.0f,
        -0.2f + obterDeslocamentoCadeira(3),
         0.0f
    );


    // ========================================================
    // MESA DIREITA
    // ========================================================

    desenharCadeira(
         3.0f,
         1.2f + obterDeslocamentoCadeira(4),
         180.0f
    );


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
    // VIEWPORT
    // ========================================================

    glViewport(
        0,
        0,
        largura,
        altura
    );


    // ========================================================
    // FUNDO
    // ========================================================

    glClearColor(
        0.08f,
        0.08f,
        0.09f,
        1.0f
    );


    // ========================================================
    // LIMPAR FRAME
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
    // JANELA
    // ========================================================

    desenharJanelaDaCafeteria();


    // ========================================================
    // LUMINARIAS
    // ========================================================

    desenharLuminarias();


    // ========================================================
    // PRATELEIRA
    // ========================================================

    desenharPrateleiraBalcao();


    // ========================================================
    // OBJETOS DO BANHEIRO
    // ========================================================

    desenharObjetosBanheiro();


    // ========================================================
    // PORTA DO BANHEIRO
    // ========================================================

    desenharPortaDoBanheiro();


    // ========================================================
    // BALCAO
    // ========================================================

    desenharBalcaoPrincipal();


    // ========================================================
    // VITRINE
    // ========================================================

    desenharVitrineDoces();


    // ========================================================
    // REGISTRADORA
    // ========================================================

    desenharCaixaRegistradora();


    // ========================================================
    // MAQUINA DE CAFE
    // ========================================================

    desenharMaquinaCafeBalcao();


    // ========================================================
    // MESAS
    // ========================================================

    desenharMesas();


    // ========================================================
    // DECORACOES
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
    // CARDAPIO
    // ========================================================

    desenharMenu();


    // ========================================================
    // INTERRUPTOR
    // ========================================================

    desenharInterruptor(
        luzEstaLigada()
    );
}
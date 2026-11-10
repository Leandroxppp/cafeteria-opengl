#include <GL/gl.h>

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

    const double PI = 3.14159265358979323846;

    double altura = 
        tan((fovY / 2) * (PI / 180)) * zNear;

    double largura = altura * aspect;

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
// CONFIGURAR LUZ DE UMA LUMINARIA (setando propriedades)
// ============================================================

static void configurarLuzLuminaria(
    GLenum luz,
    float x,
    float y,
    float z
) {

    GLfloat posicao[] = { // ONDE ela está
        x,
        y,
        z,
        1.0f // w = 1
        // w = 1: é uma posição (os valores anteriores indicam a coordenadas da luz) (variados angulos)
        // w = 0: é uma direção (os valores anteriores indicam que a luz vem dessa direcao, os raios de luz seriam paralelos) (mesmo angulo, incidencia)
    };


    GLfloat direcao[] = {   // PARA ONDE aponta (para baixo)
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

    GLfloat difusa[] = { // a COR da luz (amarelada)
        1.00f,
        0.90f,
        0.65f,
        1.0f
    };


    GLfloat especular[] = { // a cor do brilho em superfícies polidas
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

    // abertura do cone
    glLightf(luz, GL_SPOT_CUTOFF,   38.0f);   // o cone abre 48° para cada lado do eixo
    glLightf(luz, GL_SPOT_EXPONENT,  2.0f);   // o centro do cone é mais forte que a borda


    // a luz enfraquece com a distância: 1 / (1 + 0,10·d + 0,025·d²)
    glLightf(luz, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(luz, GL_LINEAR_ATTENUATION,    0.10f);
    glLightf(luz, GL_QUADRATIC_ATTENUATION, 0.025f);
}


// ============================================================
// ILUMINACAO
// ============================================================

static void configurarIluminacao() {

    glEnable(GL_LIGHTING); // habilita o cálculo de iluminação

    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);


    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );


    // glLightModeli(
    //     GL_LIGHT_MODEL_TWO_SIDE,
    //     GL_TRUE
    // );


    // ========================================================
    // LUZ LIGADA
    // ========================================================

    if (luzEstaLigada()) {

        // GLfloat ambienteGlobal[] = {0.15f, 0.105f, 0.09f, 1.0f}; // R G B A
        GLfloat ambienteGlobal[] = {0.23f, 0.21f, 0.18f, 1.0f};
        // GLfloat ambienteGlobal[] = { 0.42f, 0.43f, 0.45f, 1.0f };


        glLightModelfv(
            GL_LIGHT_MODEL_AMBIENT,
            ambienteGlobal
        ); // configura luz ambiente global


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


        GLfloat ambienteGeral[] = { // chega a todos os pontos de todas as superfícies, com a mesma intensidade
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

    const float posicoesX[] = { -3.0f, 0.0f, 3.0f };
    const bool ligada = luzEstaLigada();

    for (float x : posicoesX) {

        desenharLuminaria(x, 2.98f, 0.50f, ligada);
    }
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

    const float posicoesX[] = { -3.0f, 0.0f, 3.0f };

    for (float x : posicoesX) {

        desenharMesa(x, 0.5f, 0.0f);
    }
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

    for (int i = 0; i < quantidadeCadeiras(); i++) {

        desenharCadeira(
            obterCadeiraX(i),
            obterCadeiraZ(i),
            obterAnguloCadeira(i)
        );
    }
}

// RENDERIZAR CENA
void renderizarCena() {

    // TAMANHO DA JANELA
    int largura = 1;
    int altura = 1;

    // obterTamanhoJanela ja garante valores maiores que zero
    obterTamanhoJanela(&largura, &altura);

    glViewport(
        0,
        0,
        largura,
        altura
    );

    glClearColor(
        0.08f,
        0.08f,
        0.09f,
        1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    configurarPerspectiva(
        70.0,
        static_cast<double>(largura) /
        static_cast<double>(altura),
        0.1,
        14.0
    );
    // ========================================================

    // CAMERA
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    aplicarCamera();
    // ========================================================

    // ILUMINACAO
    configurarIluminacao();

    // SALA
    desenharSala();

    // JANELA
    desenharJanelaDaCafeteria();

    // LUMINARIAS
    desenharLuminarias();

    // PRATELEIRA
    desenharPrateleiraBalcao();

    // OBJETOS DO BANHEIRO
    desenharObjetosBanheiro();

    // PORTA DO BANHEIRO
    desenharPortaDoBanheiro();

    // BALCAO
    desenharBalcaoPrincipal();

    // VITRINE
    desenharVitrineDoces();

    // REGISTRADORA
    desenharCaixaRegistradora();

    // MAQUINA DE CAFE
    desenharMaquinaCafeBalcao();
    
    // MESAS
    desenharMesas();

    // DECORACOES
    desenharDecoracoesMesas(); 

    // CADEIRAS
    desenharCadeiras();

    // PORTA PRINCIPAL
    desenharPorta(obterAnguloPorta());

    // CARDAPIO
    desenharMenu();

    // INTERRUPTOR
    desenharInterruptor(luzEstaLigada());
}

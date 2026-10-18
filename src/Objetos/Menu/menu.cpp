#include "menu.h"

#include "../../Renderizacao/primitivas.h"
#include "../../Texturas/texturas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// TEXTURA DO CARDAPIO
// ============================================================

static GLuint texturaMenu = 0;


// ============================================================
// MATERIAL DA MOLDURA
// ============================================================

static void aplicarMaterialMadeira() {

    GLfloat especular[] = {
        0.14f,
        0.10f,
        0.06f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especular
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        16.0f
    );
}


// ============================================================
// MATERIAL PADRAO
// ============================================================

static void restaurarMaterialPadrao() {

    GLfloat especular[] = {
        0.05f,
        0.05f,
        0.05f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especular
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        8.0f
    );
}


// ============================================================
// QUADRO DE MENU
//
// menu.bmp = proporcao 2:1
//
// O quadro foi aumentado mantendo a mesma proporcao:
// largura = 3.60 m
// altura  = 1.80 m
// ============================================================

void desenharMenu() {

    // ========================================================
    // CARREGAR TEXTURA
    // ========================================================

    if (texturaMenu == 0) {

        texturaMenu =
            carregarTexturaBMP(
                "assets/texturas/menu.bmp"
            );
    }


    // ========================================================
    // FUNDO PRETO ATRAS DO CARDAPIO
    //
    // Cria apenas uma borda interna fina.
    // ========================================================

    desenharCaixa(
        0.0f,
        2.00f,
       -3.94f,

        3.70f,
        1.90f,
        0.05f,

        0.025f,
        0.025f,
        0.022f
    );


    // ========================================================
    // TEXTURA DO CARDAPIO
    // ========================================================

    if (texturaMenu != 0) {

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaMenu
        );


        glColor3f(
            1.0f,
            1.0f,
            1.0f
        );


        glBegin(GL_QUADS);


            glNormal3f(
                0.0f,
                0.0f,
                1.0f
            );


            // Inferior esquerda
            glTexCoord2f(0.0f, 0.0f);

            glVertex3f(
                -1.80f,
                 1.10f,
                -3.90f
            );


            // Inferior direita
            glTexCoord2f(1.0f, 0.0f);

            glVertex3f(
                 1.80f,
                 1.10f,
                -3.90f
            );


            // Superior direita
            glTexCoord2f(1.0f, 1.0f);

            glVertex3f(
                 1.80f,
                 2.90f,
                -3.90f
            );


            // Superior esquerda
            glTexCoord2f(0.0f, 1.0f);

            glVertex3f(
                -1.80f,
                 2.90f,
                -3.90f
            );


        glEnd();


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glDisable(GL_TEXTURE_2D);
    }


    // ========================================================
    // MOLDURA DE MADEIRA
    // ========================================================

    aplicarMaterialMadeira();


    const float madeiraR = 0.28f;
    const float madeiraG = 0.13f;
    const float madeiraB = 0.05f;


    // --------------------------------------------------------
    // SUPERIOR
    // --------------------------------------------------------

    desenharCaixa(
        0.0f,
        2.96f,
       -3.88f,

        3.88f,
        0.08f,
        0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // --------------------------------------------------------
    // INFERIOR
    // --------------------------------------------------------

    desenharCaixa(
        0.0f,
        1.04f,
       -3.88f,

        3.88f,
        0.08f,
        0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // --------------------------------------------------------
    // ESQUERDA
    // --------------------------------------------------------

    desenharCaixa(
        -1.90f,
         2.00f,
        -3.88f,

        0.08f,
        1.98f,
        0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // --------------------------------------------------------
    // DIREITA
    // --------------------------------------------------------

    desenharCaixa(
         1.90f,
         2.00f,
        -3.88f,

        0.08f,
        1.98f,
        0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    restaurarMaterialPadrao();
}
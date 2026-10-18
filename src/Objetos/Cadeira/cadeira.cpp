#include "cadeira.h"

#include "../../Renderizacao/primitivas.h"
#include "../../Texturas/texturas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// TEXTURA DO ESTOFADO
// ============================================================

static GLuint texturaCadeira = 0;


// ============================================================
// COR DA MADEIRA
// ============================================================

static const float madeiraR = 0.40f;
static const float madeiraG = 0.22f;
static const float madeiraB = 0.10f;


// ============================================================
// MATERIAL DA MADEIRA
//
// Madeira possui um pequeno brilho,
// mas continua sendo relativamente fosca.
// ============================================================

static void aplicarMaterialMadeira() {

    GLfloat especular[] = {
        0.18f,
        0.14f,
        0.10f,
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
        18.0f
    );
}


// ============================================================
// MATERIAL DO TECIDO
//
// Tecido praticamente nao possui brilho especular.
// ============================================================

static void aplicarMaterialTecido() {

    GLfloat especular[] = {
        0.02f,
        0.02f,
        0.02f,
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
        2.0f
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
// ASSENTO
// ============================================================

static void desenharAssento() {

    // ========================================================
    // ESTRUTURA DE MADEIRA
    // ========================================================

    aplicarMaterialMadeira();

    desenharCaixa(
        0.0f,
        0.45f,
        0.0f,

        0.50f,
        0.08f,
        0.50f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // CARREGAR TEXTURA
    // ========================================================

    if (texturaCadeira == 0) {

        texturaCadeira =
            carregarTexturaBMP(
                "assets/texturas/cadeira.bmp"
            );
    }


    // ========================================================
    // ESTOFADO
    // ========================================================

    if (texturaCadeira != 0) {

        aplicarMaterialTecido();

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaCadeira
        );


        glColor3f(
            1.0f,
            1.0f,
            1.0f
        );


        glBegin(GL_QUADS);


            glNormal3f(
                0.0f,
                1.0f,
                0.0f
            );


            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(
                -0.23f,
                 0.495f,
                -0.23f
            );


            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(
                 0.23f,
                 0.495f,
                -0.23f
            );


            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(
                 0.23f,
                 0.495f,
                 0.23f
            );


            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(
                -0.23f,
                 0.495f,
                 0.23f
            );


        glEnd();


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glDisable(GL_TEXTURE_2D);
    }
}


// ============================================================
// ENCOSTO
// ============================================================

static void desenharEncosto() {

    // ========================================================
    // ESTRUTURA DE MADEIRA
    // ========================================================

    aplicarMaterialMadeira();

    desenharCaixa(
        0.0f,
        0.82f,
       -0.20f,

        0.46f,
        0.22f,
        0.06f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // ESTOFADO
    // ========================================================

    if (texturaCadeira != 0) {

        aplicarMaterialTecido();

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaCadeira
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


            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(
                -0.20f,
                 0.73f,
                -0.165f
            );


            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(
                 0.20f,
                 0.73f,
                -0.165f
            );


            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(
                 0.20f,
                 0.91f,
                -0.165f
            );


            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(
                -0.20f,
                 0.91f,
                -0.165f
            );


        glEnd();


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glDisable(GL_TEXTURE_2D);
    }
}


// ============================================================
// CADEIRA
// ============================================================

void desenharCadeira(
    float x,
    float z,
    float rotacao
) {

    glPushMatrix();


    // Posicao
    glTranslatef(
        x,
        0.0f,
        z
    );


    // Orientacao
    glRotatef(
        rotacao,
        0.0f,
        1.0f,
        0.0f
    );


    // ========================================================
    // ASSENTO
    // ========================================================

    desenharAssento();


    // ========================================================
    // ESTRUTURA DE MADEIRA
    // ========================================================

    aplicarMaterialMadeira();


    // ========================================================
    // PES
    // ========================================================

    desenharCaixa(
        -0.20f, 0.22f,  0.20f,
         0.06f, 0.44f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );

    desenharCaixa(
         0.20f, 0.22f,  0.20f,
         0.06f, 0.44f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );

    desenharCaixa(
        -0.20f, 0.22f, -0.20f,
         0.06f, 0.44f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );

    desenharCaixa(
         0.20f, 0.22f, -0.20f,
         0.06f, 0.44f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );


    // ========================================================
    // SUPORTES DO ENCOSTO
    // ========================================================

    desenharCaixa(
        -0.20f, 0.68f, -0.20f,
         0.06f, 0.46f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );

    desenharCaixa(
         0.20f, 0.68f, -0.20f,
         0.06f, 0.46f,  0.06f,
         madeiraR, madeiraG, madeiraB
    );


    // ========================================================
    // ENCOSTO
    // ========================================================

    desenharEncosto();


    // Evita que o material da cadeira afete
    // os objetos desenhados posteriormente.
    restaurarMaterialPadrao();


    glPopMatrix();
}
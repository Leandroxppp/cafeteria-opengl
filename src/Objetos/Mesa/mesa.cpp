#include "mesa.h"

#include "../../Renderizacao/primitivas.h"
#include "../../Texturas/texturas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// TEXTURA DA MESA
// ============================================================

static GLuint texturaMadeiraMesa = 0;


// ============================================================
// MATERIAL DO TAMPO
//
// Madeira levemente polida.
// ============================================================

static void aplicarMaterialTampo() {

    GLfloat especular[] = {
        0.22f,
        0.17f,
        0.11f,
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
        28.0f
    );
}


// ============================================================
// MATERIAL DOS PES
//
// Madeira mais fosca.
// ============================================================

static void aplicarMaterialPes() {

    GLfloat especular[] = {
        0.10f,
        0.07f,
        0.04f,
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
        10.0f
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
// TAMPO COM TEXTURA
// ============================================================

static void desenharTampoTexturizado() {

    if (texturaMadeiraMesa == 0) {

        texturaMadeiraMesa =
            carregarTexturaBMP(
                "assets/texturas/mesa.bmp"
            );
    }


    // Material da madeira do tampo
    aplicarMaterialTampo();


    // Base 3D do tampo
    desenharCaixa(
        0.0f,
        0.72f,
        0.0f,

        1.20f,
        0.08f,
        0.80f,

        0.30f,
        0.14f,
        0.05f
    );


    // ========================================================
    // SUPERFICIE SUPERIOR TEXTURIZADA
    // ========================================================

    if (texturaMadeiraMesa != 0) {

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaMadeiraMesa
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
                -0.60f,
                 0.765f,
                -0.40f
            );


            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(
                 0.60f,
                 0.765f,
                -0.40f
            );


            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(
                 0.60f,
                 0.765f,
                 0.40f
            );


            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(
                -0.60f,
                 0.765f,
                 0.40f
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
// MESA
// ============================================================

void desenharMesa(
    float x,
    float z,
    float rotacao
) {

    glPushMatrix();


    // Translacao
    glTranslatef(
        x,
        0.0f,
        z
    );


    // Rotacao
    glRotatef(
        rotacao,
        0.0f,
        1.0f,
        0.0f
    );


    // ========================================================
    // TAMPO
    // ========================================================

    desenharTampoTexturizado();


    // ========================================================
    // PES
    // ========================================================

    aplicarMaterialPes();


    const float corR = 0.20f;
    const float corG = 0.09f;
    const float corB = 0.03f;


    desenharCaixa(
        -0.50f, 0.35f,  0.30f,
         0.08f, 0.70f,  0.08f,
         corR, corG, corB
    );


    desenharCaixa(
         0.50f, 0.35f,  0.30f,
         0.08f, 0.70f,  0.08f,
         corR, corG, corB
    );


    desenharCaixa(
        -0.50f, 0.35f, -0.30f,
         0.08f, 0.70f,  0.08f,
         corR, corG, corB
    );


    desenharCaixa(
         0.50f, 0.35f, -0.30f,
         0.08f, 0.70f,  0.08f,
         corR, corG, corB
    );


    // Evita que o material da mesa afete
    // os objetos seguintes.
    restaurarMaterialPadrao();


    glPopMatrix();
}
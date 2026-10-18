#include "espelho_banheiro.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL DA MOLDURA
// ============================================================

static void aplicarMaterialMoldura() {

    GLfloat especular[] = {
        0.20f,
        0.14f,
        0.09f,
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
        20.0f
    );
}


// ============================================================
// MATERIAL DO ESPELHO
// ============================================================

static void aplicarMaterialEspelho() {

    GLfloat ambiente[] = {
        0.32f,
        0.34f,
        0.34f,
        1.0f
    };

    GLfloat difusa[] = {
        0.62f,
        0.64f,
        0.63f,
        1.0f
    };

    GLfloat especular[] = {
        0.90f,
        0.90f,
        0.92f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT,
        ambiente
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_DIFFUSE,
        difusa
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especular
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        90.0f
    );
}


// ============================================================
// RESTAURAR MATERIAL
// ============================================================

static void restaurarMaterial() {

    GLfloat ambiente[] = {
        0.20f,
        0.20f,
        0.20f,
        1.0f
    };

    GLfloat difusa[] = {
        0.80f,
        0.80f,
        0.80f,
        1.0f
    };

    GLfloat especular[] = {
        0.05f,
        0.05f,
        0.05f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT,
        ambiente
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_DIFFUSE,
        difusa
    );

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
// ESPELHO DO BANHEIRO
// ============================================================

void desenharEspelhoBanheiro(
    float x,
    float y,
    float z,
    float rotacao
) {

    glPushMatrix();


    // ========================================================
    // POSICAO / ROTACAO
    // ========================================================

    glTranslatef(
        x,
        y,
        z
    );

    glRotatef(
        rotacao,
        0.0f,
        1.0f,
        0.0f
    );


    // ========================================================
    // SUPERFICIE DO ESPELHO
    // ========================================================

    aplicarMaterialEspelho();

    glDisable(
        GL_COLOR_MATERIAL
    );


    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        0.78f,
        0.72f,
        0.035f,

        0.62f,
        0.64f,
        0.63f
    );


    glEnable(
        GL_COLOR_MATERIAL
    );


    // ========================================================
    // MOLDURA
    // ========================================================

    aplicarMaterialMoldura();


    const float madeiraR = 0.24f;
    const float madeiraG = 0.11f;
    const float madeiraB = 0.045f;


    // Parte superior
    desenharCaixa(
        0.0f,
        0.395f,
        0.0f,

        0.90f,
        0.07f,
        0.07f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // Parte inferior
    desenharCaixa(
        0.0f,
       -0.395f,
        0.0f,

        0.90f,
        0.07f,
        0.07f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // Lado esquerdo
    desenharCaixa(
        -0.415f,
         0.0f,
         0.0f,

         0.07f,
         0.72f,
         0.07f,

         madeiraR,
         madeiraG,
         madeiraB
    );


    // Lado direito
    desenharCaixa(
         0.415f,
         0.0f,
         0.0f,

         0.07f,
         0.72f,
         0.07f,

         madeiraR,
         madeiraG,
         madeiraB
    );


    // ========================================================
    // RESTAURAR
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
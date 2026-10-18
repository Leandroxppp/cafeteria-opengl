#include "prateleira.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL DA MADEIRA
// ============================================================

static void aplicarMaterialMadeira() {

    GLfloat especular[] = {
        0.18f,
        0.12f,
        0.07f,
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
// MATERIAL DOS OBJETOS
// ============================================================

static void aplicarMaterialObjetos() {

    GLfloat especular[] = {
        0.20f,
        0.20f,
        0.20f,
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
// RESTAURAR MATERIAL
// ============================================================

static void restaurarMaterial() {

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
// PRATELEIRA
// ============================================================

void desenharPrateleira(
    float x,
    float y,
    float z,
    float rotacao
) {

    glPushMatrix();


    // ========================================================
    // POSICAO
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
    // SUPORTES LATERAIS
    // ========================================================

    aplicarMaterialMadeira();


    // Esquerdo
    desenharCaixa(
        -0.82f,
         0.0f,
         0.0f,

         0.08f,
         1.20f,
         0.28f,

         0.27f,
         0.11f,
         0.035f
    );


    // Direito
    desenharCaixa(
         0.82f,
         0.0f,
         0.0f,

         0.08f,
         1.20f,
         0.28f,

         0.27f,
         0.11f,
         0.035f
    );


    // ========================================================
    // PRATELEIRA SUPERIOR
    // ========================================================

    desenharCaixa(
        0.0f,
        0.48f,
        0.0f,

        1.75f,
        0.08f,
        0.34f,

        0.30f,
        0.13f,
        0.045f
    );


    // ========================================================
    // PRATELEIRA CENTRAL
    // ========================================================

    desenharCaixa(
        0.0f,
        0.05f,
        0.0f,

        1.75f,
        0.08f,
        0.34f,

        0.30f,
        0.13f,
        0.045f
    );


    // ========================================================
    // PRATELEIRA INFERIOR
    // ========================================================

    desenharCaixa(
        0.0f,
       -0.38f,
        0.0f,

        1.75f,
        0.08f,
        0.34f,

        0.30f,
        0.13f,
        0.045f
    );


    // ========================================================
    // OBJETOS DA PRATELEIRA SUPERIOR
    // ========================================================

    aplicarMaterialObjetos();


    desenharCaixa(
        -0.52f,
         0.61f,
         0.0f,

         0.22f,
         0.22f,
         0.20f,

         0.08f,
         0.07f,
         0.06f
    );


    desenharCaixa(
        -0.18f,
         0.61f,
         0.0f,

         0.22f,
         0.22f,
         0.20f,

         0.12f,
         0.08f,
         0.055f
    );


    desenharCaixa(
         0.18f,
         0.61f,
         0.0f,

         0.22f,
         0.22f,
         0.20f,

         0.035f,
         0.08f,
         0.075f
    );


    desenharCaixa(
         0.52f,
         0.61f,
         0.0f,

         0.22f,
         0.22f,
         0.20f,

         0.16f,
         0.09f,
         0.055f
    );


    // ========================================================
    // OBJETOS DA PRATELEIRA CENTRAL
    // ========================================================

    desenharCaixa(
        -0.48f,
         0.20f,
         0.0f,

         0.26f,
         0.22f,
         0.16f,

         0.22f,
         0.07f,
         0.035f
    );


    desenharCaixa(
        -0.15f,
         0.20f,
         0.0f,

         0.26f,
         0.22f,
         0.16f,

         0.28f,
         0.10f,
         0.035f
    );


    desenharCaixa(
         0.18f,
         0.20f,
         0.0f,

         0.26f,
         0.22f,
         0.16f,

         0.18f,
         0.055f,
         0.030f
    );


    // ========================================================
    // OBJETOS DA PRATELEIRA INFERIOR
    // ========================================================

    desenharCaixa(
        -0.48f,
        -0.25f,
         0.0f,

         0.16f,
         0.18f,
         0.16f,

         0.72f,
         0.66f,
         0.48f
    );


    desenharCaixa(
        -0.22f,
        -0.25f,
         0.0f,

         0.16f,
         0.18f,
         0.16f,

         0.64f,
         0.59f,
         0.44f
    );


    desenharCaixa(
         0.04f,
        -0.25f,
         0.0f,

         0.16f,
         0.18f,
         0.16f,

         0.70f,
         0.66f,
         0.50f
    );


    // ========================================================
    // POTE MARROM DO LADO DIREITO
    //
    // Agora fica apoiado diretamente na prateleira
    // e sem nenhuma peca cinza por cima.
    // ========================================================

    desenharCaixa(
         0.48f,
        -0.24f,
         0.0f,

         0.28f,
         0.20f,
         0.18f,

         0.20f,
         0.075f,
         0.035f
    );


    // ========================================================
    // RESTAURAR
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
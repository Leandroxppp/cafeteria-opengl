#include "balcao.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL DE MADEIRA
// ============================================================

static void aplicarMaterialMadeira() {

    GLfloat especular[] = {
        0.16f,
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
        14.0f
    );
}


// ============================================================
// MATERIAL DO TAMPO
// ============================================================

static void aplicarMaterialTampo() {

    GLfloat especular[] = {
        0.35f,
        0.35f,
        0.35f,
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
        35.0f
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
// BALCAO
// ============================================================

void desenharBalcao(
    float x,
    float y,
    float z,
    float rotacao
) {

    glPushMatrix();


    // ========================================================
    // TRANSFORMACOES
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
    // CORPO PRINCIPAL
    // ========================================================

    aplicarMaterialMadeira();

    desenharCaixa(
        0.0f,
        0.48f,
        0.0f,

        2.60f,
        0.96f,
        0.65f,

        0.30f,
        0.15f,
        0.07f
    );


    // ========================================================
    // PAINEL FRONTAL CENTRAL
    // ========================================================

    desenharCaixa(
        0.0f,
        0.50f,
        0.335f,

        1.45f,
        0.72f,
        0.04f,

        0.22f,
        0.095f,
        0.04f
    );


    // ========================================================
    // PAINEL FRONTAL ESQUERDO
    // ========================================================

    desenharCaixa(
        -0.93f,
         0.50f,
         0.335f,

         0.32f,
         0.72f,
         0.04f,

         0.38f,
         0.20f,
         0.09f
    );


    // ========================================================
    // PAINEL FRONTAL DIREITO
    // ========================================================

    desenharCaixa(
         0.93f,
         0.50f,
         0.335f,

         0.32f,
         0.72f,
         0.04f,

         0.38f,
         0.20f,
         0.09f
    );


    // ========================================================
    // RODAPE
    // ========================================================

    desenharCaixa(
        0.0f,
        0.07f,
        0.0f,

        2.68f,
        0.14f,
        0.70f,

        0.16f,
        0.075f,
        0.035f
    );


    // ========================================================
    // TAMPO SUPERIOR
    // ========================================================

    aplicarMaterialTampo();

    desenharCaixa(
        0.0f,
        1.02f,
        0.0f,

        2.78f,
        0.10f,
        0.78f,

        0.11f,
        0.10f,
        0.09f
    );


    // ========================================================
    // FAIXA DECORATIVA
    // ========================================================

    aplicarMaterialMadeira();

    desenharCaixa(
        0.0f,
        0.87f,
        0.345f,

        2.48f,
        0.07f,
        0.035f,

        0.50f,
        0.27f,
        0.11f
    );


    // ========================================================
    // RESTAURAR MATERIAL
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
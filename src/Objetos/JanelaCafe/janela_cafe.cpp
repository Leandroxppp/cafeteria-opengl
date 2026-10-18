#include "janela_cafe.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL DA MOLDURA
// ============================================================

static void aplicarMaterialMoldura() {

    GLfloat especular[] = {
        0.18f,
        0.12f,
        0.08f,
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
// MATERIAL DO VIDRO
// ============================================================

static void aplicarMaterialVidro() {

    GLfloat especular[] = {
        0.70f,
        0.75f,
        0.80f,
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
        80.0f
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
// JANELA DA CAFETERIA
//
// A janela fica na parede esquerda.
//
// Como essa parede esta no eixo X,
// a largura da janela acontece no eixo Z.
// ============================================================

void desenharJanelaCafe(
    float x,
    float y,
    float z
) {

    glPushMatrix();


    glTranslatef(
        x,
        y,
        z
    );


    // ========================================================
    // DIMENSOES
    // ========================================================

    const float largura =
        3.0f;

    const float altura =
        1.80f;

    const float espessuraMoldura =
        0.09f;


    // ========================================================
    // FUNDO / VIDRO
    //
    // Usamos uma tonalidade azul acinzentada para evitar
    // aquele aspecto de buraco preto na parede.
    // ========================================================

    aplicarMaterialVidro();


    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        0.035f,
        altura - 0.16f,
        largura - 0.16f,

        0.22f,
        0.32f,
        0.36f
    );


    // ========================================================
    // REFLEXO LEVE NO VIDRO
    // ========================================================

    desenharCaixa(
        -0.022f,
         0.28f,
        -0.55f,

         0.012f,
         0.42f,
         0.90f,

         0.38f,
         0.50f,
         0.54f
    );


    // ========================================================
    // MOLDURA
    // ========================================================

    aplicarMaterialMoldura();


    const float madeiraR =
        0.28f;

    const float madeiraG =
        0.13f;

    const float madeiraB =
        0.055f;


    // ========================================================
    // MOLDURA SUPERIOR
    // ========================================================

    desenharCaixa(
        0.0f,
        altura / 2.0f,
        0.0f,

        0.12f,
        espessuraMoldura,
        largura + 0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // MOLDURA INFERIOR
    // ========================================================

    desenharCaixa(
        0.0f,
       -altura / 2.0f,
        0.0f,

        0.12f,
        espessuraMoldura,
        largura + 0.10f,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // MOLDURA ESQUERDA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.0f,
       -largura / 2.0f,

        0.12f,
        altura,
        espessuraMoldura,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // MOLDURA DIREITA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.0f,
        largura / 2.0f,

        0.12f,
        altura,
        espessuraMoldura,

        madeiraR,
        madeiraG,
        madeiraB
    );


    // ========================================================
    // DIVISAO CENTRAL VERTICAL
    //
    // Divide a janela em duas folhas.
    // ========================================================

    desenharCaixa(
        -0.025f,
         0.0f,
         0.0f,

         0.13f,
         altura - 0.08f,
         0.065f,

         madeiraR,
         madeiraG,
         madeiraB
    );


    // ========================================================
    // TRAVESSA HORIZONTAL
    // ========================================================

    desenharCaixa(
        -0.025f,
         0.0f,
         0.0f,

         0.13f,
         0.065f,
         largura - 0.08f,

         madeiraR,
         madeiraG,
         madeiraB
    );


    // ========================================================
    // PARAPEITO
    // ========================================================

    desenharCaixa(
        0.05f,
       -0.96f,
        0.0f,

        0.30f,
        0.10f,
        largura + 0.22f,

        0.34f,
        0.17f,
        0.07f
    );


    // ========================================================
    // RESTAURAR
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
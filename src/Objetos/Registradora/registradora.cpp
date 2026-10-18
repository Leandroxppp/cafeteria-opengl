#include "registradora.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL PLASTICO
// ============================================================

static void aplicarMaterialPlastico() {

    GLfloat especular[] = {
        0.28f,
        0.28f,
        0.28f,
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
// MATERIAL DA TELA
// ============================================================

static void aplicarMaterialTela() {

    GLfloat especular[] = {
        0.45f,
        0.45f,
        0.48f,
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
        55.0f
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
// REGISTRADORA
// ============================================================

void desenharRegistradora(
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
    // BASE
    // ========================================================

    aplicarMaterialPlastico();

    desenharCaixa(
        0.0f,
        0.05f,
        0.0f,

        0.42f,
        0.10f,
        0.32f,

        0.16f,
        0.16f,
        0.16f
    );


    // ========================================================
    // FRENTE DA GAVETA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.045f,
        0.162f,

        0.30f,
        0.05f,
        0.012f,

        0.11f,
        0.11f,
        0.11f
    );


    // ========================================================
    // PUXADOR DA GAVETA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.050f,
        0.172f,

        0.08f,
        0.012f,
        0.010f,

        0.32f,
        0.32f,
        0.32f
    );


    // ========================================================
    // SUPORTE DA TELA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.18f,
        0.03f,

        0.08f,
        0.24f,
        0.08f,

        0.18f,
        0.18f,
        0.18f
    );


    // ========================================================
    // TELA EXTERNA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.31f,
        0.02f,

        0.36f,
        0.25f,
        0.07f,

        0.12f,
        0.12f,
        0.13f
    );


    // ========================================================
    // DISPLAY
    // ========================================================

    aplicarMaterialTela();

    desenharCaixa(
        0.0f,
        0.31f,
        0.061f,

        0.29f,
        0.18f,
        0.01f,

        0.10f,
        0.36f,
        0.40f
    );


    // ========================================================
    // TECLADO / PAINEL
    // ========================================================

    aplicarMaterialPlastico();

    desenharCaixa(
        0.0f,
        0.085f,
        0.18f,

        0.34f,
        0.035f,
        0.16f,

        0.18f,
        0.18f,
        0.18f
    );


    // ========================================================
    // TECLAS
    // ========================================================

    const float inicioX = -0.105f;
    const float inicioZ = 0.135f;

    const float espacamentoX = 0.07f;
    const float espacamentoZ = 0.055f;


    for (int linha = 0; linha < 2; linha++) {

        for (int coluna = 0; coluna < 4; coluna++) {

            float r = 0.34f;
            float g = 0.34f;
            float b = 0.34f;

            if (linha == 0) {
                r = 0.38f;
                g = 0.38f;
                b = 0.38f;
            }

            desenharCaixa(
                inicioX + coluna * espacamentoX,
                0.108f,
                inicioZ + linha * espacamentoZ,

                0.045f,
                0.015f,
                0.035f,

                r,
                g,
                b
            );
        }
    }


    // ========================================================
    // BOTAO DE CONFIRMACAO
    // ========================================================

    desenharCaixa(
        0.105f,
        0.110f,
        0.245f,

        0.055f,
        0.018f,
        0.040f,

        0.20f,
        0.58f,
        0.22f
    );


    // ========================================================
    // RESTAURAR MATERIAL
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
#include "vitrine.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL DA MADEIRA
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
        16.0f
    );
}


// ============================================================
// MATERIAL METALICO
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.50f,
        0.50f,
        0.52f,
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
        60.0f
    );
}


// ============================================================
// MATERIAL DOS DOCES
// ============================================================

static void aplicarMaterialDoce() {

    GLfloat especular[] = {
        0.14f,
        0.09f,
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
        12.0f
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
// BANDEJA
// ============================================================

static void desenharBandeja(
    float x,
    float y,
    float z,
    float largura,
    float profundidade
) {

    aplicarMaterialMetal();

    desenharCaixa(
        x,
        y,
        z,

        largura,
        0.018f,
        profundidade,

        0.10f,
        0.09f,
        0.08f
    );
}


// ============================================================
// BROWNIE
// ============================================================

static void desenharBrownie(
    float x,
    float y,
    float z
) {

    aplicarMaterialDoce();


    // Corpo
    desenharCaixa(
        x,
        y + 0.035f,
        z,

        0.18f,
        0.07f,
        0.16f,

        0.20f,
        0.055f,
        0.025f
    );


    // Cobertura de chocolate
    desenharCaixa(
        x,
        y + 0.078f,
        z,

        0.185f,
        0.018f,
        0.165f,

        0.10f,
        0.025f,
        0.012f
    );
}


// ============================================================
// FATIA DE BOLO CLARO
// ============================================================

static void desenharBoloClaro(
    float x,
    float y,
    float z
) {

    aplicarMaterialDoce();


    // Primeira camada
    desenharCaixa(
        x,
        y + 0.025f,
        z,

        0.20f,
        0.05f,
        0.18f,

        0.78f,
        0.58f,
        0.30f
    );


    // Recheio
    desenharCaixa(
        x,
        y + 0.057f,
        z,

        0.202f,
        0.015f,
        0.182f,

        0.95f,
        0.87f,
        0.70f
    );


    // Segunda camada
    desenharCaixa(
        x,
        y + 0.092f,
        z,

        0.20f,
        0.055f,
        0.18f,

        0.74f,
        0.52f,
        0.27f
    );


    // Cobertura
    desenharCaixa(
        x,
        y + 0.126f,
        z,

        0.21f,
        0.018f,
        0.19f,

        0.96f,
        0.88f,
        0.72f
    );
}


// ============================================================
// BOLO DE CHOCOLATE
// ============================================================

static void desenharBoloChocolate(
    float x,
    float y,
    float z
) {

    aplicarMaterialDoce();


    // Camada inferior
    desenharCaixa(
        x,
        y + 0.028f,
        z,

        0.19f,
        0.056f,
        0.18f,

        0.27f,
        0.065f,
        0.028f
    );


    // Recheio
    desenharCaixa(
        x,
        y + 0.063f,
        z,

        0.192f,
        0.015f,
        0.182f,

        0.68f,
        0.38f,
        0.22f
    );


    // Camada superior
    desenharCaixa(
        x,
        y + 0.097f,
        z,

        0.19f,
        0.052f,
        0.18f,

        0.24f,
        0.055f,
        0.025f
    );


    // Cobertura
    desenharCaixa(
        x,
        y + 0.130f,
        z,

        0.205f,
        0.018f,
        0.19f,

        0.12f,
        0.025f,
        0.015f
    );
}


// ============================================================
// CROISSANT
//
// Feito com pequenos segmentos rotacionados,
// criando uma forma curva.
// ============================================================

static void desenharCroissant(
    float x,
    float y,
    float z
) {

    aplicarMaterialDoce();


    glPushMatrix();

    glTranslatef(
        x,
        y,
        z
    );


    // ========================================================
    // PARTE ESQUERDA
    // ========================================================

    glPushMatrix();

    glTranslatef(
        -0.075f,
         0.030f,
         0.0f
    );

    glRotatef(
        -18.0f,
        0.0f,
        1.0f,
        0.0f
    );

    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        0.11f,
        0.060f,
        0.085f,

        0.80f,
        0.46f,
        0.16f
    );

    glPopMatrix();


    // ========================================================
    // CENTRO
    // ========================================================

    desenharCaixa(
        0.0f,
        0.035f,
        0.0f,

        0.12f,
        0.075f,
        0.095f,

        0.88f,
        0.55f,
        0.20f
    );


    // ========================================================
    // PARTE DIREITA
    // ========================================================

    glPushMatrix();

    glTranslatef(
         0.075f,
         0.030f,
         0.0f
    );

    glRotatef(
        18.0f,
        0.0f,
        1.0f,
        0.0f
    );

    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        0.11f,
        0.060f,
        0.085f,

        0.80f,
        0.46f,
        0.16f
    );

    glPopMatrix();


    glPopMatrix();
}


// ============================================================
// DOCES
// ============================================================

static void desenharDoces() {

    // ========================================================
    // PRATELEIRA INFERIOR
    //
    // A superficie superior da prateleira fica aproximadamente
    // em Y = 0.229.
    // ========================================================

    const float baseInferior =
        0.240f;


    // Bandeja inferior
    desenharBandeja(
        0.0f,
        0.234f,
        0.0f,

        0.78f,
        0.40f
    );


    // Brownie
    desenharBrownie(
        -0.27f,
         baseInferior,
         0.0f
    );


    // Bolo claro
    desenharBoloClaro(
         0.0f,
         baseInferior,
         0.0f
    );


    // Bolo chocolate
    desenharBoloChocolate(
         0.27f,
         baseInferior,
         0.0f
    );


    // ========================================================
    // PRATELEIRA SUPERIOR
    //
    // Agora os croissants realmente ficam apoiados
    // sobre a prateleira.
    // ========================================================

    const float baseSuperior =
        0.500f;


    // Bandeja superior
    desenharBandeja(
        0.0f,
        0.494f,
        0.0f,

        0.78f,
        0.40f
    );


    // Croissant esquerdo
    desenharCroissant(
        -0.25f,
         baseSuperior,
         0.0f
    );


    // Croissant central
    desenharCroissant(
         0.0f,
         baseSuperior,
         0.0f
    );


    // Pequena fatia de bolo na direita
    aplicarMaterialDoce();

    desenharCaixa(
         0.27f,
         0.535f,
         0.0f,

         0.18f,
         0.07f,
         0.16f,

         0.68f,
         0.38f,
         0.26f
    );


    // Cobertura
    desenharCaixa(
         0.27f,
         0.580f,
         0.0f,

         0.19f,
         0.020f,
         0.17f,

         0.95f,
         0.78f,
         0.66f
    );
}


// ============================================================
// VIDROS
// ============================================================

static void desenharVidros() {

    // ========================================================
    // TRANSPARENCIA
    // ========================================================

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    glDepthMask(
        GL_FALSE
    );


    glDisable(
        GL_COLOR_MATERIAL
    );


    GLfloat ambienteVidro[] = {
        0.20f,
        0.23f,
        0.24f,
        0.12f
    };


    GLfloat difusaVidro[] = {
        0.70f,
        0.78f,
        0.80f,
        0.12f
    };


    GLfloat especularVidro[] = {
        0.90f,
        0.90f,
        0.95f,
        1.0f
    };


    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT,
        ambienteVidro
    );


    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_DIFFUSE,
        difusaVidro
    );


    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especularVidro
    );


    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        90.0f
    );


    glColor4f(
        0.82f,
        0.90f,
        0.92f,
        0.12f
    );


    // ========================================================
    // VIDRO FRONTAL
    // ========================================================

    desenharCaixa(
        0.0f,
        0.36f,
        0.275f,

        0.92f,
        0.60f,
        0.010f,

        0.82f,
        0.90f,
        0.92f
    );


    // ========================================================
    // VIDRO TRASEIRO
    // ========================================================

    desenharCaixa(
        0.0f,
        0.36f,
       -0.275f,

        0.92f,
        0.60f,
        0.010f,

        0.82f,
        0.90f,
        0.92f
    );


    // ========================================================
    // VIDRO ESQUERDO
    // ========================================================

    desenharCaixa(
        -0.465f,
         0.36f,
         0.0f,

         0.010f,
         0.60f,
         0.54f,

         0.82f,
         0.90f,
         0.92f
    );


    // ========================================================
    // VIDRO DIREITO
    // ========================================================

    desenharCaixa(
         0.465f,
         0.36f,
         0.0f,

         0.010f,
         0.60f,
         0.54f,

         0.82f,
         0.90f,
         0.92f
    );


    // ========================================================
    // RESTAURAR
    // ========================================================

    glDepthMask(
        GL_TRUE
    );

    glDisable(
        GL_BLEND
    );

    glEnable(
        GL_COLOR_MATERIAL
    );
}


// ============================================================
// VITRINE
// ============================================================

void desenharVitrine(
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
    // BASE
    // ========================================================

    aplicarMaterialMadeira();


    desenharCaixa(
        0.0f,
        0.025f,
        0.0f,

        1.02f,
        0.05f,
        0.60f,

        0.22f,
        0.10f,
        0.04f
    );


    // ========================================================
    // TOPO
    // ========================================================

    desenharCaixa(
        0.0f,
        0.69f,
        0.0f,

        1.02f,
        0.05f,
        0.60f,

        0.20f,
        0.09f,
        0.04f
    );


    // ========================================================
    // ESTRUTURA
    // ========================================================

    aplicarMaterialMetal();


    const float espessura =
        0.022f;


    // Frente esquerda
    desenharCaixa(
        -0.48f,
         0.36f,
         0.28f,

         espessura,
         0.66f,
         espessura,

         0.10f,
         0.10f,
         0.10f
    );


    // Frente direita
    desenharCaixa(
         0.48f,
         0.36f,
         0.28f,

         espessura,
         0.66f,
         espessura,

         0.10f,
         0.10f,
         0.10f
    );


    // Tras esquerda
    desenharCaixa(
        -0.48f,
         0.36f,
        -0.28f,

         espessura,
         0.66f,
         espessura,

         0.10f,
         0.10f,
         0.10f
    );


    // Tras direita
    desenharCaixa(
         0.48f,
         0.36f,
        -0.28f,

         espessura,
         0.66f,
         espessura,

         0.10f,
         0.10f,
         0.10f
    );


    // ========================================================
    // PRATELEIRA INFERIOR
    //
    // Foi abaixada.
    // Agora os doces ficam realmente apoiados.
    // ========================================================

    desenharCaixa(
        0.0f,
        0.22f,
        0.0f,

        0.90f,
        0.018f,
        0.48f,

        0.38f,
        0.38f,
        0.36f
    );


    // ========================================================
    // PRATELEIRA SUPERIOR
    // ========================================================

    desenharCaixa(
        0.0f,
        0.48f,
        0.0f,

        0.90f,
        0.018f,
        0.48f,

        0.38f,
        0.38f,
        0.36f
    );


    // ========================================================
    // DOCES
    // ========================================================

    desenharDoces();


    // ========================================================
    // VIDROS
    // ========================================================

    desenharVidros();


    // ========================================================
    // RESTAURAR MATERIAL
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
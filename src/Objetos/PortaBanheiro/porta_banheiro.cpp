#include "porta_banheiro.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>


// ============================================================
// MATERIAL MADEIRA
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
// MATERIAL METAL
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.72f,
        0.68f,
        0.50f,
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
        70.0f
    );
}


// ============================================================
// RESTAURAR
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
// MACANETA
// ============================================================

static void desenharMacaneta(
    float x,
    float y,
    float z,
    bool ladoInterno
) {

    aplicarMaterialMetal();


    // Base
    desenharCaixa(
        x,
        y,
        z,

        0.085f,
        0.14f,
        0.025f,

        0.52f,
        0.42f,
        0.12f
    );


    float direcaoZ =
        ladoInterno ? -1.0f : 1.0f;


    // Haste
    desenharCaixa(
        x,
        y,
        z + direcaoZ * 0.030f,

        0.035f,
        0.035f,
        0.070f,

        0.72f,
        0.60f,
        0.18f
    );


    float deslocamentoX =
        ladoInterno ? -0.065f : 0.065f;


    // Puxador
    desenharCaixa(
        x + deslocamentoX,
        y,
        z + direcaoZ * 0.065f,

        0.15f,
        0.030f,
        0.030f,

        0.78f,
        0.65f,
        0.20f
    );
}


// ============================================================
// PORTA DO BANHEIRO
// ============================================================

void desenharPortaBanheiro(
    float angulo
) {

    glPushMatrix();


    const float alturaVao =
        2.20f;

    const float larguraFolha =
        0.985f;

    const float alturaFolha =
        2.18f;

    const float espessuraFolha =
        0.070f;


    // ========================================================
    // BATENTE
    // ========================================================

    aplicarMaterialMadeira();


    // Esquerdo
    desenharCaixa(
        -0.56f,
         1.10f,
         0.0f,

         0.12f,
         alturaVao,
         0.12f,

         0.29f,
         0.12f,
         0.045f
    );


    // Direito
    desenharCaixa(
         0.56f,
         1.10f,
         0.0f,

         0.12f,
         alturaVao,
         0.12f,

         0.29f,
         0.12f,
         0.045f
    );


    // Superior
    desenharCaixa(
         0.0f,
         2.26f,
         0.0f,

         1.24f,
         0.12f,
         0.12f,

         0.29f,
         0.12f,
         0.045f
    );


    // ========================================================
    // GUARNICAO EXTERNA
    // ========================================================

    desenharCaixa(
        -0.505f,
         1.10f,
         0.075f,

         0.045f,
         2.20f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    desenharCaixa(
         0.505f,
         1.10f,
         0.075f,

         0.045f,
         2.20f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    desenharCaixa(
         0.0f,
         2.205f,
         0.075f,

         1.055f,
         0.045f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    // ========================================================
    // GUARNICAO INTERNA
    // ========================================================

    desenharCaixa(
        -0.505f,
         1.10f,
        -0.075f,

         0.045f,
         2.20f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    desenharCaixa(
         0.505f,
         1.10f,
        -0.075f,

         0.045f,
         2.20f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    desenharCaixa(
         0.0f,
         2.205f,
        -0.075f,

         1.055f,
         0.045f,
         0.030f,

         0.36f,
         0.16f,
         0.055f
    );


    // ========================================================
    // FOLHA DA PORTA
    // ========================================================

    glPushMatrix();


    glTranslatef(
        -0.492f,
         0.0f,
         0.0f
    );


    glRotatef(
        -angulo,
        0.0f,
        1.0f,
        0.0f
    );


    aplicarMaterialMadeira();


    desenharCaixa(
        larguraFolha * 0.5f,
        1.095f,
        0.0f,

        larguraFolha,
        alturaFolha,
        espessuraFolha,

        0.24f,
        0.075f,
        0.025f
    );


    // ========================================================
    // PAINEIS EXTERNOS
    // ========================================================

    desenharCaixa(
        larguraFolha * 0.5f,
        1.55f,
        0.041f,

        0.58f,
        0.61f,
        0.012f,

        0.18f,
        0.050f,
        0.018f
    );


    desenharCaixa(
        larguraFolha * 0.5f,
        0.63f,
        0.041f,

        0.58f,
        0.69f,
        0.012f,

        0.18f,
        0.050f,
        0.018f
    );


    // ========================================================
    // PAINEIS INTERNOS
    // ========================================================

    desenharCaixa(
        larguraFolha * 0.5f,
        1.55f,
       -0.041f,

        0.58f,
        0.61f,
        0.012f,

        0.18f,
        0.050f,
        0.018f
    );


    desenharCaixa(
        larguraFolha * 0.5f,
        0.63f,
       -0.041f,

        0.58f,
        0.69f,
        0.012f,

        0.18f,
        0.050f,
        0.018f
    );


    // ========================================================
    // MACANETA EXTERNA
    // ========================================================

    desenharMacaneta(
        larguraFolha - 0.105f,
        1.02f,
        0.055f,
        false
    );


    // ========================================================
    // MACANETA INTERNA
    // ========================================================

    desenharMacaneta(
        larguraFolha - 0.105f,
        1.02f,
       -0.055f,
        true
    );


    // Sem dobradicas visiveis.
    // O movimento continua acontecendo normalmente
    // pela rotacao da folha em torno da origem.


    glPopMatrix();


    restaurarMaterial();


    glPopMatrix();
}
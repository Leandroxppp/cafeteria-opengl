#include "pia_banheiro.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>
#include <cmath>


static const float PI = 3.14159265f;


// ============================================================
// DISCO OVAL
// ============================================================

static void desenharDiscoOval(
    float raioX,
    float raioZ,
    int segmentos
) {

    glBegin(GL_TRIANGLE_FAN);


    glNormal3f(
        0.0f,
        1.0f,
        0.0f
    );


    glVertex3f(
        0.0f,
        0.0f,
        0.0f
    );


    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);


        glVertex3f(
            cosf(angulo) * raioX,
            0.0f,
            sinf(angulo) * raioZ
        );
    }


    glEnd();
}


// ============================================================
// FAIXA OVAL
// ============================================================

static void desenharFaixaOval(
    float externoX,
    float externoZ,
    float yExterno,

    float internoX,
    float internoZ,
    float yInterno,

    int segmentos
) {

    glBegin(GL_QUAD_STRIP);


    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);


        float c =
            cosf(angulo);

        float s =
            sinf(angulo);


        glNormal3f(
            c * 0.35f,
            0.90f,
            s * 0.35f
        );


        glVertex3f(
            c * externoX,
            yExterno,
            s * externoZ
        );


        glVertex3f(
            c * internoX,
            yInterno,
            s * internoZ
        );
    }


    glEnd();
}


// ============================================================
// PAREDE OVAL
// ============================================================

static void desenharParedeOval(
    float raioX,
    float raioZ,
    float yInferior,
    float ySuperior,
    int segmentos
) {

    glBegin(GL_QUAD_STRIP);


    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);


        float c =
            cosf(angulo);

        float s =
            sinf(angulo);


        glNormal3f(
            c,
            0.0f,
            s
        );


        glVertex3f(
            c * raioX,
            yInferior,
            s * raioZ
        );


        glVertex3f(
            c * raioX,
            ySuperior,
            s * raioZ
        );
    }


    glEnd();
}


// ============================================================
// MATERIAL PORCELANA
// ============================================================

static void aplicarMaterialPorcelana() {

    GLfloat especular[] = {
        0.60f,
        0.60f,
        0.62f,
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
        58.0f
    );


    glColor3f(
        0.96f,
        0.95f,
        0.91f
    );
}


// ============================================================
// MATERIAL METAL
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.85f,
        0.85f,
        0.88f,
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
        90.0f
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


    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );
}


// ============================================================
// CUBA
// ============================================================

static void desenharCuba() {

    const int segmentos =
        40;


    aplicarMaterialPorcelana();


    // Parede externa
    desenharParedeOval(
        0.31f,
        0.21f,

        0.870f,
        0.965f,

        segmentos
    );


    // Borda
    desenharFaixaOval(
        0.31f,
        0.21f,
        0.965f,

        0.255f,
        0.165f,
        0.960f,

        segmentos
    );


    // Interior superior
    glColor3f(
        0.91f,
        0.91f,
        0.88f
    );


    desenharFaixaOval(
        0.255f,
        0.165f,
        0.960f,

        0.175f,
        0.105f,
        0.920f,

        segmentos
    );


    // Interior inferior
    glColor3f(
        0.84f,
        0.85f,
        0.83f
    );


    desenharFaixaOval(
        0.175f,
        0.105f,
        0.920f,

        0.085f,
        0.050f,
        0.895f,

        segmentos
    );


    // Fundo
    glPushMatrix();


    glTranslatef(
        0.0f,
        0.895f,
        0.0f
    );


    glColor3f(
        0.78f,
        0.80f,
        0.79f
    );


    desenharDiscoOval(
        0.085f,
        0.050f,
        segmentos
    );


    glPopMatrix();


    // Ralo
    aplicarMaterialMetal();


    glPushMatrix();


    glTranslatef(
        0.0f,
        0.899f,
        0.0f
    );


    glColor3f(
        0.24f,
        0.24f,
        0.25f
    );


    desenharDiscoOval(
        0.025f,
        0.025f,
        24
    );


    glPopMatrix();
}


// ============================================================
// PIA DO BANHEIRO
// ============================================================

void desenharPiaBanheiro(
    float x,
    float y,
    float z,
    float rotacao
) {

    glPushMatrix();


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


    aplicarMaterialPorcelana();


    // ========================================================
    // PEDESTAL
    // ========================================================

    desenharCaixa(
        0.0f,
        0.40f,
       -0.03f,

        0.30f,
        0.80f,
        0.28f,

        0.95f,
        0.94f,
        0.90f
    );


    // ========================================================
    // BANCADA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.82f,
        0.0f,

        0.90f,
        0.10f,
        0.50f,

        0.96f,
        0.95f,
        0.91f
    );


    // ========================================================
    // CUBA
    // ========================================================

    glPushMatrix();


    glTranslatef(
        0.0f,
        0.0f,
        0.035f
    );


    desenharCuba();


    glPopMatrix();


    // ========================================================
    // TORNEIRA
    // ========================================================

    aplicarMaterialMetal();


    // Base
    desenharCaixa(
        0.0f,
        0.925f,
       -0.175f,

        0.11f,
        0.06f,
        0.10f,

        0.62f,
        0.62f,
        0.65f
    );


    // Haste
    desenharCaixa(
        0.0f,
        1.055f,
       -0.175f,

        0.055f,
        0.26f,
        0.055f,

        0.70f,
        0.70f,
        0.73f
    );


    // Parte horizontal
    desenharCaixa(
        0.0f,
        1.17f,
       -0.095f,

        0.055f,
        0.055f,
        0.20f,

        0.70f,
        0.70f,
        0.73f
    );


    // Bico
    desenharCaixa(
        0.0f,
        1.115f,
       -0.005f,

        0.055f,
        0.11f,
        0.055f,

        0.70f,
        0.70f,
        0.73f
    );


    // ========================================================
    // REGISTRO ESQUERDO
    // ========================================================

    desenharCaixa(
        -0.16f,
         0.925f,
        -0.175f,

         0.12f,
         0.045f,
         0.08f,

         0.62f,
         0.62f,
         0.65f
    );


    // ========================================================
    // REGISTRO DIREITO
    // ========================================================

    desenharCaixa(
         0.16f,
         0.925f,
        -0.175f,

         0.12f,
         0.045f,
         0.08f,

         0.62f,
         0.62f,
         0.65f
    );


    restaurarMaterial();


    glPopMatrix();
}
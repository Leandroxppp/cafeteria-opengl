#include "vaso_sanitario.h"

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
// ANEL OVAL
// ============================================================

static void desenharAnelOval(
    float externoX,
    float externoZ,
    float internoX,
    float internoZ,
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
            0.0f,
            1.0f,
            0.0f
        );


        glVertex3f(
            c * externoX,
            0.0f,
            s * externoZ
        );


        glVertex3f(
            c * internoX,
            0.0f,
            s * internoZ
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


    // Branco levemente quente
    glColor3f(
        0.96f,
        0.95f,
        0.91f
    );
}


// ============================================================
// MATERIAL DA AGUA
// ============================================================

static void aplicarMaterialAgua() {

    GLfloat especular[] = {
        0.55f,
        0.65f,
        0.70f,
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


    glColor3f(
        0.16f,
        0.23f,
        0.25f
    );
}


// ============================================================
// MATERIAL METAL
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.80f,
        0.80f,
        0.82f,
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
        85.0f
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
// VASO SANITARIO
// ============================================================

void desenharVasoSanitario(
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
    // BASE
    // ========================================================

    desenharCaixa(
        0.0f,
        0.11f,
        0.02f,

        0.30f,
        0.22f,
        0.34f,

        0.96f,
        0.95f,
        0.91f
    );


    // ========================================================
    // CORPO DA BACIA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.27f,
        0.06f,

        0.42f,
        0.22f,
        0.52f,

        0.95f,
        0.94f,
        0.90f
    );


    // ========================================================
    // AGUA
    // ========================================================

    aplicarMaterialAgua();


    glPushMatrix();

    glTranslatef(
        0.0f,
        0.395f,
        0.075f
    );


    desenharDiscoOval(
        0.145f,
        0.205f,
        40
    );

    glPopMatrix();


    // ========================================================
    // ASSENTO
    // ========================================================

    aplicarMaterialPorcelana();


    glPushMatrix();

    glTranslatef(
        0.0f,
        0.425f,
        0.075f
    );


    desenharAnelOval(
        0.245f,
        0.305f,

        0.145f,
        0.205f,

        40
    );

    glPopMatrix();


    // ========================================================
    // CAIXA ACOPLADA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.68f,
       -0.215f,

        0.46f,
        0.50f,
        0.20f,

        0.96f,
        0.95f,
        0.91f
    );


    // ========================================================
    // TAMPA DA CAIXA
    // ========================================================

    desenharCaixa(
        0.0f,
        0.95f,
       -0.215f,

        0.50f,
        0.055f,
        0.23f,

        0.98f,
        0.97f,
        0.93f
    );


    // ========================================================
    // BOTAO DA DESCARGA
    // ========================================================

    aplicarMaterialMetal();


    desenharCaixa(
        0.0f,
        0.985f,
       -0.215f,

        0.10f,
        0.018f,
        0.065f,

        0.52f,
        0.52f,
        0.54f
    );


    // ========================================================
    // TAMPA DO VASO LEVANTADA
    // ========================================================

    aplicarMaterialPorcelana();


    glPushMatrix();


    glTranslatef(
        0.0f,
        0.69f,
       -0.105f
    );


    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );


    desenharDiscoOval(
        0.215f,
        0.270f,
        40
    );


    glPopMatrix();


    // Segunda face para dar espessura
    glPushMatrix();


    glTranslatef(
        0.0f,
        0.69f,
       -0.120f
    );


    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );


    desenharDiscoOval(
        0.215f,
        0.270f,
        40
    );


    glPopMatrix();


    // ========================================================
    // SUPORTES DA TAMPA
    // ========================================================

    aplicarMaterialMetal();


    desenharCaixa(
        -0.075f,
         0.445f,
        -0.165f,

         0.055f,
         0.030f,
         0.045f,

         0.62f,
         0.62f,
         0.64f
    );


    desenharCaixa(
         0.075f,
         0.445f,
        -0.165f,

         0.055f,
         0.030f,
         0.045f,

         0.62f,
         0.62f,
         0.64f
    );


    restaurarMaterial();


    glPopMatrix();
}
#include "luminaria.h"

#include "../../Renderizacao/primitivas.h"

#include <GL/gl.h>
#include <cmath>


static const float PI = 3.14159265f;


// ============================================================
// CILINDRO VERTICAL PARA BAIXO
// ============================================================

static void desenharCilindro(
    float raio,
    float altura,
    int segmentos
) {

    // ========================================================
    // LATERAL
    // ========================================================

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);


        float c = cosf(angulo);
        float s = sinf(angulo);


        glNormal3f(
            c,
            0.0f,
            s
        );


        // topo
        glVertex3f(
            c * raio,
            0.0f,
            s * raio
        );


        // parte inferior
        glVertex3f(
            c * raio,
            -altura,
            s * raio
        );
    }

    glEnd();


    // ========================================================
    // TAMPA SUPERIOR
    // ========================================================

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
            cosf(angulo) * raio,
            0.0f,
            sinf(angulo) * raio
        );
    }

    glEnd();


    // ========================================================
    // TAMPA INFERIOR
    // ========================================================

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(
        0.0f,
        -1.0f,
        0.0f
    );

    glVertex3f(
        0.0f,
        -altura,
        0.0f
    );


    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        glVertex3f(
            cosf(angulo) * raio,
            -altura,
            sinf(angulo) * raio
        );
    }

    glEnd();
}


// ============================================================
// CUPULA
//
// Comeca pequena em cima e abre para baixo.
// ============================================================

static void desenharCupula(
    float raioSuperior,
    float raioInferior,
    float altura,
    int segmentos
) {

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);


        float c = cosf(angulo);
        float s = sinf(angulo);


        glNormal3f(
            c,
            0.30f,
            s
        );


        // topo da cupula
        glVertex3f(
            c * raioSuperior,
            0.0f,
            s * raioSuperior
        );


        // abertura inferior
        glVertex3f(
            c * raioInferior,
            -altura,
            s * raioInferior
        );
    }

    glEnd();
}


// ============================================================
// MATERIAL DO METAL
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.25f,
        0.25f,
        0.27f,
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
        30.0f
    );
}


// ============================================================
// MATERIAL DA LAMPADA
// ============================================================

static void aplicarMaterialLampada(
    bool ligada
) {

    GLfloat especular[] = {
        0.30f,
        0.28f,
        0.22f,
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


    if (ligada) {

        GLfloat emissao[] = {
            0.75f,
            0.62f,
            0.30f,
            1.0f
        };


        glMaterialfv(
            GL_FRONT_AND_BACK,
            GL_EMISSION,
            emissao
        );
    }
    else {

        GLfloat emissao[] = {
            0.0f,
            0.0f,
            0.0f,
            1.0f
        };


        glMaterialfv(
            GL_FRONT_AND_BACK,
            GL_EMISSION,
            emissao
        );
    }
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


    GLfloat emissao[] = {
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };


    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especular
    );


    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_EMISSION,
        emissao
    );


    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        8.0f
    );
}


// ============================================================
// LUMINARIA
// ============================================================

void desenharLuminaria(
    float x,
    float y,
    float z,
    bool ligada
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


    aplicarMaterialMetal();


    // ========================================================
    // BASE PRESA NO TETO
    // ========================================================

    desenharCaixa(
        0.0f,
        -0.025f,
        0.0f,

        0.14f,
        0.05f,
        0.14f,

        0.07f,
        0.065f,
        0.06f
    );


    // ========================================================
    // CABO
    //
    // Agora menor.
    // ========================================================

    desenharCaixa(
        0.0f,
        -0.18f,
        0.0f,

        0.018f,
        0.28f,
        0.018f,

        0.025f,
        0.025f,
        0.025f
    );


    // ========================================================
    // ENCAIXE ENTRE CABO E CUPULA
    // ========================================================

    glColor3f(
        0.08f,
        0.075f,
        0.07f
    );


    glPushMatrix();

    glTranslatef(
        0.0f,
        -0.34f,
        0.0f
    );


    desenharCilindro(
        0.045f,
        0.055f,
        20
    );

    glPopMatrix();


    // ========================================================
    // CUPULA
    //
    // Bem menor que a anterior.
    // ========================================================

    glColor3f(
        0.09f,
        0.085f,
        0.075f
    );


    glPushMatrix();

    glTranslatef(
        0.0f,
        -0.385f,
        0.0f
    );


    desenharCupula(
        0.045f,
        0.145f,
        0.115f,
        28
    );

    glPopMatrix();


    // ========================================================
    // BORDA INFERIOR DA CUPULA
    // ========================================================

    glColor3f(
        0.14f,
        0.12f,
        0.095f
    );


    glPushMatrix();

    glTranslatef(
        0.0f,
        -0.495f,
        0.0f
    );


    desenharCilindro(
        0.147f,
        0.018f,
        28
    );

    glPopMatrix();


    // ========================================================
    // LAMPADA
    //
    // Agora:
    //
    // - menor
    // - centralizada
    // - aparece somente abaixo da cupula
    // ========================================================

    aplicarMaterialLampada(
        ligada
    );


    if (ligada) {

        glColor3f(
            1.0f,
            0.88f,
            0.50f
        );
    }
    else {

        glColor3f(
            0.45f,
            0.42f,
            0.34f
        );
    }


    glPushMatrix();

    glTranslatef(
        0.0f,
        -0.485f,
        0.0f
    );


    desenharCilindro(
        0.032f,
        0.065f,
        22
    );

    glPopMatrix();


    // ========================================================
    // RESTAURAR
    // ========================================================

    restaurarMaterial();


    glPopMatrix();
}
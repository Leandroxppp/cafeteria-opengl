#include "vasinho.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

static const float PI = 3.14159265f;


// ============================================================
// CILINDRO FECHADO
// ============================================================

static void desenharCilindroFechado(
    float raio,
    float altura,
    int segmentos
) {

    // lateral
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        float c = cosf(angulo);
        float s = sinf(angulo);

        glNormal3f(c, 0.0f, s);

        glVertex3f(c * raio, 0.0f, s * raio);
        glVertex3f(c * raio, altura, s * raio);
    }

    glEnd();

    // base
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

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

    // topo
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, altura, 0.0f);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        glVertex3f(
            cosf(angulo) * raio,
            altura,
            sinf(angulo) * raio
        );
    }

    glEnd();
}


// ============================================================
// TRONCO DE CONE
// ============================================================

static void desenharTroncoCone(
    float raioBase,
    float raioTopo,
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

        float nx = c;
        float nz = s;

        glNormal3f(nx, 0.35f, nz);

        glVertex3f(c * raioBase, 0.0f, s * raioBase);
        glVertex3f(c * raioTopo, altura, s * raioTopo);
    }

    glEnd();
}


// ============================================================
// DISCO
// ============================================================

static void desenharDisco(
    float raio,
    float y,
    int segmentos
) {

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, y, 0.0f);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            2.0f * PI *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        glVertex3f(
            cosf(angulo) * raio,
            y,
            sinf(angulo) * raio
        );
    }

    glEnd();
}


// ============================================================
// FOLHA
// ============================================================

static void desenharFolha(
    float anguloY,
    float inclinacaoX,
    float escala
) {

    glPushMatrix();

    glRotatef(
        anguloY,
        0.0f,
        1.0f,
        0.0f
    );

    glRotatef(
        inclinacaoX,
        1.0f,
        0.0f,
        0.0f
    );

    glScalef(
        escala,
        escala,
        escala
    );

    glColor3f(
        0.12f,
        0.48f,
        0.15f
    );

    glBegin(GL_TRIANGLES);

    // frente
    glNormal3f(0.0f, 0.0f, 1.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.030f, 0.10f, 0.0f);
    glVertex3f( 0.000f, 0.18f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f( 0.030f, 0.10f, 0.0f);
    glVertex3f( 0.000f, 0.18f, 0.0f);

    glEnd();

    glPopMatrix();
}


// ============================================================
// VASINHO
// ============================================================

void desenharVasinho(
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
    // MATERIAL
    // ========================================================

    GLfloat especular[] = {
        0.20f,
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

    // ========================================================
    // VASO
    // ========================================================

    glColor3f(
        0.58f,
        0.30f,
        0.16f
    );

    // base mais fechada
    desenharTroncoCone(
        0.060f,
        0.085f,
        0.10f,
        24
    );

    // borda superior
    glPushMatrix();
    glTranslatef(0.0f, 0.10f, 0.0f);

    glColor3f(
        0.65f,
        0.34f,
        0.18f
    );

    desenharCilindroFechado(
        0.090f,
        0.018f,
        24
    );

    glPopMatrix();

    // terra
    glColor3f(
        0.18f,
        0.10f,
        0.05f
    );

    desenharDisco(
        0.075f,
        0.112f,
        24
    );

    // ========================================================
    // CAULE
    // ========================================================

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.115f,
        0.0f
    );

    glColor3f(
        0.20f,
        0.40f,
        0.12f
    );

    desenharCilindroFechado(
        0.010f,
        0.12f,
        18
    );

    glPopMatrix();

    // ========================================================
    // FOLHAS
    // ========================================================

    glPushMatrix();
    glTranslatef(0.0f, 0.18f, 0.0f);

    desenharFolha(0.0f,   -20.0f, 1.0f);
    desenharFolha(70.0f,   10.0f, 0.9f);
    desenharFolha(140.0f, -10.0f, 0.95f);
    desenharFolha(220.0f,  20.0f, 0.85f);
    desenharFolha(300.0f,   5.0f, 0.90f);

    glPopMatrix();

    // ========================================================
    // RESTAURAR MATERIAL
    // ========================================================

    GLfloat especularPadrao[] = {
        0.05f,
        0.05f,
        0.05f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        especularPadrao
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        8.0f
    );

    glPopMatrix();
}
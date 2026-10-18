#include "xicara.h"

#include <GL/gl.h>
#include <cmath>


static const float PI = 3.14159265f;


// ============================================================
// CORPO DA XICARA
// ============================================================

static void desenharCorpoXicara(
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

        glNormal3f(
            c,
            0.08f,
            s
        );

        glVertex3f(
            c * raioBase,
            0.0f,
            s * raioBase
        );

        glVertex3f(
            c * raioTopo,
            altura,
            s * raioTopo
        );
    }

    glEnd();
}


// ============================================================
// DISCO
// ============================================================

static void desenharDisco(
    float raio,
    float y,
    int segmentos,
    float normalY
) {

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(
        0.0f,
        normalY,
        0.0f
    );

    glVertex3f(
        0.0f,
        y,
        0.0f
    );

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
// BORDA SUPERIOR
// ============================================================

static void desenharBorda(
    float raioExterno,
    float raioInterno,
    float y,
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
            0.0f,
            1.0f,
            0.0f
        );

        glVertex3f(
            c * raioExterno,
            y,
            s * raioExterno
        );

        glVertex3f(
            c * raioInterno,
            y,
            s * raioInterno
        );
    }

    glEnd();
}


// ============================================================
// ALCA
//
// Pequena, fina e colada ao corpo.
// ============================================================

static void desenharAlca() {

    const int segmentos = 22;

    const float raioExterno = 0.028f;
    const float raioInterno = 0.017f;

    const float metadeEspessura = 0.009f;

    // Mais proxima da xicara
    const float centroX = 0.062f;
    const float centroY = 0.060f;


    // ========================================================
    // FACE FRONTAL
    // ========================================================

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            -PI * 0.72f +
             PI * 1.44f *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        float c = cosf(angulo);
        float s = sinf(angulo);

        glNormal3f(
            0.0f,
            0.0f,
            1.0f
        );

        glVertex3f(
            centroX + c * raioExterno,
            centroY + s * raioExterno,
            metadeEspessura
        );

        glVertex3f(
            centroX + c * raioInterno,
            centroY + s * raioInterno,
            metadeEspessura
        );
    }

    glEnd();


    // ========================================================
    // FACE TRASEIRA
    // ========================================================

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            -PI * 0.72f +
             PI * 1.44f *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        float c = cosf(angulo);
        float s = sinf(angulo);

        glNormal3f(
            0.0f,
            0.0f,
           -1.0f
        );

        glVertex3f(
            centroX + c * raioInterno,
            centroY + s * raioInterno,
           -metadeEspessura
        );

        glVertex3f(
            centroX + c * raioExterno,
            centroY + s * raioExterno,
           -metadeEspessura
        );
    }

    glEnd();


    // ========================================================
    // LADO EXTERNO
    // ========================================================

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            -PI * 0.72f +
             PI * 1.44f *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        float c = cosf(angulo);
        float s = sinf(angulo);

        glNormal3f(
            c,
            s,
            0.0f
        );

        float px =
            centroX +
            c * raioExterno;

        float py =
            centroY +
            s * raioExterno;

        glVertex3f(
            px,
            py,
           -metadeEspessura
        );

        glVertex3f(
            px,
            py,
            metadeEspessura
        );
    }

    glEnd();


    // ========================================================
    // LADO INTERNO
    // ========================================================

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segmentos; i++) {

        float angulo =
            -PI * 0.72f +
             PI * 1.44f *
            static_cast<float>(i) /
            static_cast<float>(segmentos);

        float c = cosf(angulo);
        float s = sinf(angulo);

        glNormal3f(
           -c,
           -s,
            0.0f
        );

        float px =
            centroX +
            c * raioInterno;

        float py =
            centroY +
            s * raioInterno;

        glVertex3f(
            px,
            py,
            metadeEspessura
        );

        glVertex3f(
            px,
            py,
           -metadeEspessura
        );
    }

    glEnd();


    // ========================================================
    // FECHAMENTOS DA ALCA
    // ========================================================

    glBegin(GL_QUADS);


    // Superior
    glNormal3f(
        0.0f,
        1.0f,
        0.0f
    );

    glVertex3f(
        centroX,
        centroY + raioInterno,
       -metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY + raioInterno,
        metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY + raioExterno,
        metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY + raioExterno,
       -metadeEspessura
    );


    // Inferior
    glNormal3f(
        0.0f,
       -1.0f,
        0.0f
    );

    glVertex3f(
        centroX,
        centroY - raioExterno,
       -metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY - raioExterno,
        metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY - raioInterno,
        metadeEspessura
    );

    glVertex3f(
        centroX,
        centroY - raioInterno,
       -metadeEspessura
    );


    glEnd();
}


// ============================================================
// XICARA
// ============================================================

void desenharXicara(
    float x,
    float y,
    float z
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


    // ========================================================
    // MATERIAL
    // ========================================================

    GLfloat especular[] = {
        0.50f,
        0.46f,
        0.40f,
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
        38.0f
    );


    // ========================================================
    // DIMENSOES
    // ========================================================

    const float raioBase = 0.050f;
    const float raioTopo = 0.060f;
    const float altura   = 0.110f;

    const int segmentos = 28;


    // ========================================================
    // CORPO
    // ========================================================

    glColor3f(
        0.92f,
        0.88f,
        0.78f
    );


    desenharCorpoXicara(
        raioBase,
        raioTopo,
        altura,
        segmentos
    );


    // Fundo
    desenharDisco(
        raioBase,
        0.0f,
        segmentos,
       -1.0f
    );


    // ========================================================
    // BORDA
    // ========================================================

    desenharBorda(
        raioTopo,
        0.048f,
        altura,
        segmentos
    );


    // ========================================================
    // CAFE
    // ========================================================

    glColor3f(
        0.10f,
        0.035f,
        0.012f
    );


    desenharDisco(
        0.045f,
        altura - 0.005f,
        segmentos,
        1.0f
    );


    // ========================================================
    // ALCA
    // ========================================================

    glColor3f(
        0.92f,
        0.88f,
        0.78f
    );


    desenharAlca();


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
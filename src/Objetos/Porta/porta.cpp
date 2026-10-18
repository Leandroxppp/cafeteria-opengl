#include "porta.h"

#include "../../Renderizacao/primitivas.h"
#include "../../Texturas/texturas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// TEXTURA DA PORTA
// ============================================================

static GLuint texturaPorta = 0;


// ============================================================
// MATERIAL METALICO
//
// Usado na macaneta.
// Possui reflexo especular maior e brilho concentrado.
// ============================================================

static void aplicarMaterialMetal() {

    GLfloat especular[] = {
        0.75f,
        0.55f,
        0.20f,
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
// MATERIAL PADRAO
//
// Depois de desenhar a macaneta, voltamos para um
// material mais fosco para nao passar o brilho do metal
// para os outros objetos.
// ============================================================

static void restaurarMaterialPadrao() {

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
// BATENTE / MOLDURA
//
// O batente fica fixo na parede.
// Apenas a folha da porta gira.
// ============================================================

static void desenharBatente() {

    const float r = 0.32f;
    const float g = 0.15f;
    const float b = 0.06f;


    // Lado esquerdo
    desenharCaixa(
        -0.75f,
         1.12f,
         3.91f,

         0.10f,
         2.30f,
         0.14f,

         r, g, b
    );


    // Lado direito
    desenharCaixa(
         0.75f,
         1.12f,
         3.91f,

         0.10f,
         2.30f,
         0.14f,

         r, g, b
    );


    // Parte superior
    desenharCaixa(
         0.0f,
         2.25f,
         3.91f,

         1.60f,
         0.10f,
         0.14f,

         r, g, b
    );
}


// ============================================================
// MACANETA
//
// T = Translacao
// S = Escala
//
// A macaneta e modelada usando cubos unitarios.
// Tambem recebe material metalico com reflexo especular.
// ============================================================

static void desenharMacaneta() {

    // Ativa o material metalico
    aplicarMaterialMetal();


    // ========================================================
    // BASE METALICA
    // ========================================================

    glPushMatrix();


    // T - posiciona a base
    glTranslatef(
        1.18f,
        1.05f,
       -0.075f
    );


    // S - deixa a base pequena e fina
    glScalef(
        0.055f,
        0.11f,
        0.030f
    );


    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        1.0f,
        1.0f,
        1.0f,

        0.48f,
        0.34f,
        0.08f
    );


    glPopMatrix();


    // ========================================================
    // ALAVANCA
    // ========================================================

    glPushMatrix();


    // T - posiciona a alavanca
    glTranslatef(
        1.11f,
        1.05f,
       -0.105f
    );


    // S - deixa a alavanca comprida e fina
    glScalef(
        0.13f,
        0.025f,
        0.025f
    );


    desenharCaixa(
        0.0f,
        0.0f,
        0.0f,

        1.0f,
        1.0f,
        1.0f,

        0.52f,
        0.37f,
        0.09f
    );


    glPopMatrix();


    // Volta para um material mais fosco
    restaurarMaterialPadrao();
}


// ============================================================
// PORTA PRINCIPAL
// ============================================================

void desenharPorta(float angulo) {

    // ========================================================
    // BATENTE
    // ========================================================

    desenharBatente();


    // ========================================================
    // CARREGAR TEXTURA
    // ========================================================

    if (texturaPorta == 0) {

        texturaPorta =
            carregarTexturaBMP(
                "assets/texturas/porta.bmp"
            );
    }


    // ========================================================
    // FOLHA DA PORTA
    // ========================================================

    glPushMatrix();


    // ========================================================
    // T - TRANSLACAO
    //
    // Move o sistema de coordenadas para a dobradica.
    // ========================================================

    glTranslatef(
        -0.70f,
         0.0f,
         3.96f
    );


    // ========================================================
    // R - ROTACAO
    //
    // O angulo e controlado pela interacao com E.
    // ========================================================

    glRotatef(
        angulo,
        0.0f,
        1.0f,
        0.0f
    );


    // ========================================================
    // CORPO 3D DA PORTA
    // ========================================================

    desenharCaixa(
        0.70f,
        1.10f,
        0.0f,

        1.40f,
        2.20f,
        0.08f,

        0.13f,
        0.07f,
        0.035f
    );


    // ========================================================
    // TEXTURA
    // ========================================================

    if (texturaPorta != 0) {

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaPorta
        );


        glColor3f(
            1.0f,
            1.0f,
            1.0f
        );


        // ====================================================
        // FACE INTERNA
        // ====================================================

        glBegin(GL_QUADS);


            glNormal3f(
                0.0f,
                0.0f,
               -1.0f
            );


            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(
                0.0f,
                0.0f,
               -0.045f
            );


            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(
                1.40f,
                0.0f,
               -0.045f
            );


            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(
                1.40f,
                2.20f,
               -0.045f
            );


            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(
                0.0f,
                2.20f,
               -0.045f
            );


        glEnd();


        // ====================================================
        // FACE EXTERNA
        // ====================================================

        glBegin(GL_QUADS);


            glNormal3f(
                0.0f,
                0.0f,
                1.0f
            );


            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(
                0.0f,
                0.0f,
                0.045f
            );


            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(
                1.40f,
                0.0f,
                0.045f
            );


            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(
                1.40f,
                2.20f,
                0.045f
            );


            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(
                0.0f,
                2.20f,
                0.045f
            );


        glEnd();


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glDisable(GL_TEXTURE_2D);
    }


    // ========================================================
    // MACANETA
    //
    // Possui:
    //
    // - translacao
    // - escala
    // - material metalico
    // - reflexo especular
    //
    // Como esta dentro da transformacao da porta,
    // acompanha a rotacao automaticamente.
    // ========================================================

    desenharMacaneta();


    glPopMatrix();
}
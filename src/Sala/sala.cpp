#include "sala.h"

#include "../Renderizacao/primitivas.h"
#include "../Texturas/texturas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// TEXTURA DO PISO
// ============================================================

static GLuint texturaPiso = 0;


// ============================================================
// CHAO
// ============================================================

static void desenharChao() {

    // Carrega a textura apenas uma vez
    if (texturaPiso == 0) {

        texturaPiso =
            carregarTexturaBMP(
                "assets/texturas/piso.bmp"
            );
    }


    // ========================================================
    // PISO COM TEXTURA
    // ========================================================

    if (texturaPiso != 0) {

        glEnable(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            texturaPiso
        );


        // Faz a textura repetir pelo piso
        // em vez de esticar uma unica imagem.
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT
        );


        // Branco para preservar as cores
        // originais da textura.
        glColor3f(
            1.0f,
            1.0f,
            1.0f
        );


        glBegin(GL_QUADS);


            // Normal apontando para cima
            glNormal3f(
                0.0f,
                1.0f,
                0.0f
            );


            // Canto traseiro esquerdo
            glTexCoord2f(
                0.0f,
                0.0f
            );

            glVertex3f(
                -6.0f,
                 0.0f,
                -4.0f
            );


            // Canto traseiro direito
            //
            // 6 repeticoes no eixo X
            glTexCoord2f(
                6.0f,
                0.0f
            );

            glVertex3f(
                 6.0f,
                 0.0f,
                -4.0f
            );


            // Canto frontal direito
            //
            // 4 repeticoes no eixo Z
            glTexCoord2f(
                6.0f,
                4.0f
            );

            glVertex3f(
                 6.0f,
                 0.0f,
                 4.0f
            );


            // Canto frontal esquerdo
            glTexCoord2f(
                0.0f,
                4.0f
            );

            glVertex3f(
                -6.0f,
                 0.0f,
                 4.0f
            );


        glEnd();


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glDisable(GL_TEXTURE_2D);
    }


    // ========================================================
    // PISO SEM TEXTURA
    //
    // Caso o arquivo piso.bmp nao seja encontrado,
    // usa a cor antiga como seguranca.
    // ========================================================

    else {

        desenharQuad(
            -6.0f, 0.0f, -4.0f,
             6.0f, 0.0f, -4.0f,
             6.0f, 0.0f,  4.0f,
            -6.0f, 0.0f,  4.0f,

            0.42f,
            0.30f,
            0.20f
        );
    }
}


// ============================================================
// TETO
// ============================================================

static void desenharTeto() {

    desenharQuad(
        -6.0f, 3.0f,  4.0f,
         6.0f, 3.0f,  4.0f,
         6.0f, 3.0f, -4.0f,
        -6.0f, 3.0f, -4.0f,

        0.90f, 0.88f, 0.82f
    );
}


// ============================================================
// PAREDE DO FUNDO
// Z = -4
// ============================================================

static void desenharParedeFundo() {

    desenharQuad(
        -6.0f, 0.0f, -4.0f,
         6.0f, 0.0f, -4.0f,
         6.0f, 3.0f, -4.0f,
        -6.0f, 3.0f, -4.0f,

        0.72f, 0.64f, 0.54f
    );
}


// ============================================================
// PAREDE DIREITA
// X = +6
// ============================================================

static void desenharParedeDireita() {

    desenharQuad(
        6.0f, 0.0f, -4.0f,
        6.0f, 0.0f,  4.0f,
        6.0f, 3.0f,  4.0f,
        6.0f, 3.0f, -4.0f,

        0.76f, 0.68f, 0.57f
    );
}


// ============================================================
// PAREDE ESQUERDA
//
// Possui abertura para a janela.
//
// Janela:
// Z = 0.5 ate 3.5
// Y = 0.8 ate 2.6
// ============================================================

static void desenharParedeEsquerda() {

    // Parte antes da janela
    desenharQuad(
        -6.0f, 0.0f, -4.0f,
        -6.0f, 0.0f,  0.5f,
        -6.0f, 3.0f,  0.5f,
        -6.0f, 3.0f, -4.0f,

        0.76f, 0.68f, 0.57f
    );


    // Parte abaixo da janela
    desenharQuad(
        -6.0f, 0.0f, 0.5f,
        -6.0f, 0.0f, 3.5f,
        -6.0f, 0.8f, 3.5f,
        -6.0f, 0.8f, 0.5f,

        0.76f, 0.68f, 0.57f
    );


    // Parte acima da janela
    desenharQuad(
        -6.0f, 2.6f, 0.5f,
        -6.0f, 2.6f, 3.5f,
        -6.0f, 3.0f, 3.5f,
        -6.0f, 3.0f, 0.5f,

        0.76f, 0.68f, 0.57f
    );


    // Parte depois da janela
    desenharQuad(
        -6.0f, 0.0f, 3.5f,
        -6.0f, 0.0f, 4.0f,
        -6.0f, 3.0f, 4.0f,
        -6.0f, 3.0f, 3.5f,

        0.76f, 0.68f, 0.57f
    );
}


// ============================================================
// PAREDE DA FRENTE
//
// Porta principal:
// largura = 1.4 m
// altura = 2.2 m
// centro = X 0
// ============================================================

static void desenharParedeFrente() {

    // Lado esquerdo da porta
    desenharQuad(
        -6.0f, 0.0f, 4.0f,
        -0.7f, 0.0f, 4.0f,
        -0.7f, 3.0f, 4.0f,
        -6.0f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );


    // Lado direito da porta
    desenharQuad(
         0.7f, 0.0f, 4.0f,
         6.0f, 0.0f, 4.0f,
         6.0f, 3.0f, 4.0f,
         0.7f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );


    // Parte acima da porta
    desenharQuad(
        -0.7f, 2.2f, 4.0f,
         0.7f, 2.2f, 4.0f,
         0.7f, 3.0f, 4.0f,
        -0.7f, 3.0f, 4.0f,

        0.70f, 0.62f, 0.52f
    );
}


// ============================================================
// BANHEIRO
//
// Canto traseiro direito.
//
// X = 3.6 ate 6.0
// Z = -4.0 ate -2.2
// ============================================================

static void desenharBanheiro() {

    const float corR = 0.62f;
    const float corG = 0.58f;
    const float corB = 0.52f;


    // Parede lateral esquerda
    desenharCaixa(
        3.60f,
        1.50f,
       -3.10f,

        0.10f,
        3.00f,
        1.80f,

        corR,
        corG,
        corB
    );


    // Parte esquerda da porta
    desenharCaixa(
        3.975f,
        1.50f,
       -2.20f,

        0.75f,
        3.00f,
        0.10f,

        corR,
        corG,
        corB
    );


    // Parte direita da porta
    desenharCaixa(
        5.625f,
        1.50f,
       -2.20f,

        0.75f,
        3.00f,
        0.10f,

        corR,
        corG,
        corB
    );


    // Parte acima da porta
    desenharCaixa(
        4.80f,
        2.55f,
       -2.20f,

        0.90f,
        0.90f,
        0.10f,

        corR,
        corG,
        corB
    );
}


// ============================================================
// SALA COMPLETA
// ============================================================

void desenharSala() {

    desenharChao();

    desenharTeto();

    desenharParedeFundo();

    desenharParedeDireita();

    desenharParedeEsquerda();

    desenharParedeFrente();

    desenharBanheiro();
}
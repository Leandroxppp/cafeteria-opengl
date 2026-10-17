#include "primitivas.h"

#include <windows.h>
#include <GL/gl.h>


// Desenha uma superficie usando 4 pontos
void desenharQuad(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4,
    float r, float g, float b
) {

    // Define a cor
    glColor3f(r, g, b);

    glBegin(GL_QUADS);

        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x3, y3, z3);
        glVertex3f(x4, y4, z4);

    glEnd();
}


// Desenha uma caixa 3D
void desenharCaixa(
    float centroX,
    float centroY,
    float centroZ,
    float tamanhoX,
    float tamanhoY,
    float tamanhoZ,
    float r,
    float g,
    float b
) {

    float x0 = centroX - tamanhoX / 2.0f;
    float x1 = centroX + tamanhoX / 2.0f;

    float y0 = centroY - tamanhoY / 2.0f;
    float y1 = centroY + tamanhoY / 2.0f;

    float z0 = centroZ - tamanhoZ / 2.0f;
    float z1 = centroZ + tamanhoZ / 2.0f;

    glColor3f(r, g, b);

    glBegin(GL_QUADS);

        // Frente
        glVertex3f(x0, y0, z1);
        glVertex3f(x1, y0, z1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x0, y1, z1);

        // Tras
        glVertex3f(x1, y0, z0);
        glVertex3f(x0, y0, z0);
        glVertex3f(x0, y1, z0);
        glVertex3f(x1, y1, z0);

        // Esquerda
        glVertex3f(x0, y0, z0);
        glVertex3f(x0, y0, z1);
        glVertex3f(x0, y1, z1);
        glVertex3f(x0, y1, z0);

        // Direita
        glVertex3f(x1, y0, z1);
        glVertex3f(x1, y0, z0);
        glVertex3f(x1, y1, z0);
        glVertex3f(x1, y1, z1);

        // Topo
        glVertex3f(x0, y1, z1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z0);
        glVertex3f(x0, y1, z0);

        // Base
        glVertex3f(x0, y0, z0);
        glVertex3f(x1, y0, z0);
        glVertex3f(x1, y0, z1);
        glVertex3f(x0, y0, z1);

    glEnd();
}
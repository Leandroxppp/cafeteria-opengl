#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

// Desenha uma superficie formada por 4 pontos
void desenharQuad(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4,
    float r, float g, float b
);

// Desenha uma caixa 3D a partir do centro, tamanho e cor
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
);

#endif
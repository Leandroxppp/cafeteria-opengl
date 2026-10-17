#ifndef CAMERA_H
#define CAMERA_H

// Inicializacao
void inicializarCamera();

// Aplica a camera na cena
void aplicarCamera();

// Movimentacao
void moverCameraFrente(float distancia);
void moverCameraTras(float distancia);
void moverCameraEsquerda(float distancia);
void moverCameraDireita(float distancia);

// Rotacao pelo mouse
void rotacionarCamera(float deltaX, float deltaY);

// Posicao atual
float obterCameraX();
float obterCameraY();
float obterCameraZ();

#endif
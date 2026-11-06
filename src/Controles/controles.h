#ifndef CONTROLES_H
#define CONTROLES_H

// Callback de teclado do GLFW.
void teclaPressionada(int tecla);
void teclaSolta(int tecla);

// Callback de mouse do GLFW (posicao virtual com cursor capturado).
void moverMouse(double x, double y);

// Descarta a ultima posicao do mouse (ao capturar/liberar o cursor).
void redefinirMouse();

// Libera todas as teclas (por exemplo, ao perder o foco).
void soltarTodasAsTeclas();

// Atualiza o movimento continuo (WASD e setas).
void atualizarControles(float deltaTempo);

#endif

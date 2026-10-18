#ifndef TEXTURAS_H
#define TEXTURAS_H

#include <windows.h>
#include <GL/gl.h>

// Carrega uma imagem BMP e cria uma textura OpenGL.
// Retorna 0 caso nao consiga carregar.
GLuint carregarTexturaBMP(const char* caminho);

// Libera uma textura da memoria.
void liberarTextura(GLuint textura);

#endif
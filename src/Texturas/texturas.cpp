#include "texturas.h"

#include <windows.h>
#include <GL/gl.h>


// Alguns headers antigos do OpenGL nao possuem
// essas constantes.
#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif

#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif


// ============================================================
// CARREGAR TEXTURA BMP
// ============================================================

GLuint carregarTexturaBMP(
    const char* caminho
) {

    // Carrega o BMP usando o proprio Windows.
    HBITMAP imagem =
        (HBITMAP)LoadImageA(
            NULL,
            caminho,
            IMAGE_BITMAP,
            0,
            0,
            LR_LOADFROMFILE |
            LR_CREATEDIBSECTION
        );


    // Se nao encontrou a imagem.
    if (imagem == NULL) {
        return 0;
    }


    // Informacoes da imagem.
    BITMAP bitmap;

    GetObject(
        imagem,
        sizeof(BITMAP),
        &bitmap
    );


    // Aceitamos BMP de 24 ou 32 bits.
    if (
        bitmap.bmBitsPixel != 24 &&
        bitmap.bmBitsPixel != 32
    ) {

        DeleteObject(imagem);

        return 0;
    }


    // ========================================================
    // CRIAR TEXTURA OPENGL
    // ========================================================

    GLuint textura = 0;

    glGenTextures(
        1,
        &textura
    );


    glBindTexture(
        GL_TEXTURE_2D,
        textura
    );


    // Filtro quando a textura estiver pequena.
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );


    // Filtro quando a textura estiver ampliada.
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );


    // Impede repeticao nas bordas.
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP
    );


    // BMP usa alinhamento de 4 bytes.
    glPixelStorei(
        GL_UNPACK_ALIGNMENT,
        4
    );


    // ========================================================
    // ENVIAR IMAGEM PARA A PLACA DE VIDEO
    // ========================================================

    if (bitmap.bmBitsPixel == 24) {

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            bitmap.bmWidth,
            bitmap.bmHeight,
            0,
            GL_BGR_EXT,
            GL_UNSIGNED_BYTE,
            bitmap.bmBits
        );
    }

    else {

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            bitmap.bmWidth,
            bitmap.bmHeight,
            0,
            GL_BGRA_EXT,
            GL_UNSIGNED_BYTE,
            bitmap.bmBits
        );
    }


    // O OpenGL ja recebeu os pixels.
    DeleteObject(imagem);


    return textura;
}


// ============================================================
// LIBERAR TEXTURA
// ============================================================

void liberarTextura(
    GLuint textura
) {

    if (textura != 0) {

        glDeleteTextures(
            1,
            &textura
        );
    }
}
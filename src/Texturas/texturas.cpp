#include "texturas.h"

#include <GL/gl.h>

// Alguns headers antigos do OpenGL nao possuem
// essas constantes.
#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif

#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// ============================================================
// CARREGAR TEXTURA BMP
// ============================================================

GLuint carregarTexturaBMP(
    const char* caminho
) {

    


   

    


   

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

#include "texturas.h"

#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Funcao para carregar a textura
GLuint carregarTexturaBMP(const char* caminho) {

    int largura;
    int altura;
    int canaisDeCor;

    // Voce passa o caminho da imagem e ele retorna o local dos pixel e preeche a largura, altura e quantidade de canais da imagem passada
    unsigned char* dados = stbi_load(caminho, &largura, &altura, &canaisDeCor, 0);

    if (!dados) {
        return 0;
    }
   


    // configuracao de textura

    GLuint textura = 0;

    // gera uma quantidade X de identificador(es), nesse caso, gera apenas 1
    glGenTextures(
        1,
        &textura
    );

    // a textura que estamos lidando, textura, é do tipo 2d
    glBindTexture(
        GL_TEXTURE_2D,
        textura
    );


    // filtro quando for necessario mapear a textura para um tamanho inferior ao dela
    // filtro de interpolacao linear
    // textura do tipo 2d
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );


    // filtro quando for necessario mapear a textura para um tamanho superior ao dela
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );


    // impede repeticao da textura quando esta ultrapassar as bordas
    // eixo x
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP
    );

    // eixo y
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP
    );

    // como o OpenGL deve interpretar a organização dos dados na memória
    glPixelStorei(
        GL_UNPACK_ALIGNMENT, // como os dados dos pixels serao organizados na memoria
        1                    // leia os pixels exatamente como eles estão organizados
    );


    // pega os pixels da imagem e cria uma textura 2d opengl
    // passam da ram para o gerenciamento de texturas do opengl 
    if (canaisDeCor == 3) {
        glTexImage2D(
            GL_TEXTURE_2D, // tipo/alvo da textura
            0, // nivel principal da imagem, 0 = nivel original
            GL_RGB, // formato interno que queremos que o OpenGL use para armazenar a textura
            largura,
            altura,
            0, // espessura de borda, 0 = sem borda
            GL_RGB, // formato dos dados que estamos entregando
            GL_UNSIGNED_BYTE, // tipo de cada componente dos pixels, 1 byte por componente
            dados // ponteiro para os pixels que o stbi_load() carregou na RAM
        );
    } else if (canaisDeCor == 4) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            largura,
            altura,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            dados
        );
    } else {
        stbi_image_free(dados);
        glDeleteTextures(1, &textura);

        return 0;
    }

    // libera a imagem da ram
    stbi_image_free(dados);

    return textura;
}


// liberando textura

void liberarTextura(GLuint textura) {
    glDeleteTextures(1, &textura);
}

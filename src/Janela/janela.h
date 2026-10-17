#ifndef JANELA_H
#define JANELA_H

#include <windows.h>

// Cria a janela e inicializa o contexto OpenGL
bool criarJanela(
    HINSTANCE hInstance,
    int nCmdShow
);

// Processa os eventos do Windows
// Retorna false quando o programa deve fechar
bool processarEventos();

// Atualiza o conteúdo exibido na tela
void atualizarJanela();

// Libera os recursos da janela e do OpenGL
void destruirJanela();

// Retorna o tamanho atual da janela
int obterLarguraJanela();
int obterAlturaJanela();

#endif
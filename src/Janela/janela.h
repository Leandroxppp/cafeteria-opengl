#ifndef JANELA_H
#define JANELA_H

// Declaracao antecipada para nao expor o GLFW nos demais modulos.
struct GLFWwindow;

// Cria a janela e o contexto OpenGL. Retorna false em caso de erro.
bool criarJanela(int largura, int altura, const char* titulo);

// Janela GLFW atual.
GLFWwindow* obterJanela();

// Tamanho do framebuffer, usado por glViewport e pela projecao.
void obterTamanhoJanela(int* largura, int* altura);

// Apresenta o frame (double buffering).
void trocarBuffers();

// Processa os eventos pendentes (teclado, mouse, fechar janela).
void processarEventos();

// Verdadeiro quando o usuario pediu para fechar a janela.
bool janelaDeveFechar();

// Libera janela, contexto e o GLFW.
void destruirJanela();

#endif

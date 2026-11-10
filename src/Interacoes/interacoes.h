#ifndef INTERACOES_H
#define INTERACOES_H

// Inicializa portas, cadeiras e iluminacao.
void inicializarInteracoes();

// Atualiza as animacoes de portas e cadeiras.
// deltaTempo esta em segundos.
void atualizarInteracoes(float deltaTempo);

// Executa a interacao quando o jogador aperta E.
void tentarInteragir();


// ============================================================
// PORTA PRINCIPAL
// ============================================================

float obterAnguloPorta();


// ============================================================
// CADEIRAS
//
// O layout de cada cadeira fica em interacoes.cpp. Renderizacao
// e colisao consultam estes getters para nao duplicar posicoes.
// ============================================================

int quantidadeCadeiras();

float obterCadeiraX(int indice);

// Posicao Z atual (posicao original + deslocamento da animacao).
float obterCadeiraZ(int indice);

float obterAnguloCadeira(int indice);


// ============================================================
// PORTA DO BANHEIRO
// ============================================================

float obterAnguloPortaBanheiro();


// ============================================================
// ILUMINACAO
// ============================================================

bool luzEstaLigada();

#endif

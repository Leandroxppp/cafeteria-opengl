#ifndef INTERACOES_H
#define INTERACOES_H


// Inicializa porta, cadeiras e iluminacao.
void inicializarInteracoes();


// Atualiza as animacoes.
void atualizarInteracoes();


// Executa a interacao quando o jogador aperta E.
void tentarInteragir();


// ============================================================
// PORTA
// ============================================================

float obterAnguloPorta();


// ============================================================
// CADEIRAS
// ============================================================

float obterDeslocamentoCadeira(
    int indice
);


// ============================================================
// ILUMINACAO
// ============================================================

bool luzEstaLigada();


#endif
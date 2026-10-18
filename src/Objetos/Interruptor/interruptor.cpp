#include "interruptor.h"
#include "../../Renderizacao/primitivas.h"

#include <windows.h>
#include <GL/gl.h>


// ============================================================
// INTERRUPTOR DA CAFETERIA
//
// Fica na parede direita, proximo da entrada.
//
// Parede direita:
// X = 6
//
// O interruptor fica levemente para dentro da sala.
// ============================================================

void desenharInterruptor(bool ligado) {

    // ========================================================
    // PLACA DO INTERRUPTOR
    // ========================================================

    desenharCaixa(
        5.94f,     // X
        1.30f,     // Y
        2.80f,     // Z

        0.05f,     // espessura
        0.30f,     // altura
        0.22f,     // largura

        0.85f,
        0.85f,
        0.80f
    );


    // ========================================================
    // BOTAO
    // ========================================================

    float posicaoBotaoY;

    if (ligado) {
        posicaoBotaoY = 1.35f;
    }
    else {
        posicaoBotaoY = 1.25f;
    }


    desenharCaixa(
        5.90f,
        posicaoBotaoY,
        2.80f,

        0.05f,
        0.12f,
        0.10f,

        0.30f,
        0.30f,
        0.28f
    );
}
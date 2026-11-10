# Guia de Estudo do Código — Cafeteria 3D

> Material didático sobre a **versão atual** do projeto `cafeteria-opengl`.
> Explica a arquitetura, o fluxo de execução e as principais decisões técnicas
> do código em C++ com OpenGL de função fixa e GLFW.

---

## Sumário

1. [Visão geral](#1-visão-geral)
2. [Como o programa inicia e executa](#2-como-o-programa-inicia-e-executa)
3. [Janela e contexto OpenGL](#3-janela-e-contexto-opengl)
4. [Entrada: teclado e mouse](#4-entrada-teclado-e-mouse)
5. [Câmera em primeira pessoa](#5-câmera-em-primeira-pessoa)
6. [Sistema de colisões](#6-sistema-de-colisões)
7. [Interações e animações](#7-interações-e-animações)
8. [Renderização](#8-renderização)
9. [Iluminação e materiais](#9-iluminação-e-materiais)
10. [Primitivas e modelagem dos objetos](#10-primitivas-e-modelagem-dos-objetos)
11. [Texturas](#11-texturas)
12. [Cenário: sala, paredes e banheiro](#12-cenário-sala-paredes-e-banheiro)
13. [Build, execução e diagnóstico](#13-build-execução-e-diagnóstico)
14. [Decisões de projeto e limitações](#14-decisões-de-projeto-e-limitações)
15. [Roteiro de leitura e exercícios](#15-roteiro-de-leitura-e-exercícios)
16. [Apêndices](#16-apêndices)

---

## 1. Visão geral

### 1.1 O que o programa faz

A aplicação renderiza uma cafeteria 3D em primeira pessoa. O jogador pode:

- andar com `W`, `A`, `S`, `D`;
- olhar ao redor com o mouse;
- girar a câmera com as setas;
- interagir com portas, cadeiras e com o interruptor de luz usando `E`;
- sair com `Esc`.

Não há motor gráfico, engine de física ou biblioteca de cena. Toda a geometria é
desenhada com primitivas do OpenGL de função fixa (`glBegin`, `glEnd`, `glVertex3f`,
`glTranslatef`, `glRotatef`, `glScalef`).

### 1.2 Tecnologias usadas

| Tecnologia | Papel |
|---|---|
| C++14 | Linguagem do projeto |
| OpenGL 2.1+ (compatibilidade) | Renderização, transformações, iluminação |
| GLU | Apenas linkada; a cena usa funções básicas do OpenGL |
| GLFW 3.4 | Janela, contexto OpenGL, teclado, mouse e foco |
| stb_image | Decodificação das imagens BMP |
| CMake 3.20+ | Configuração e compilação |
| GCC/g++ (ou MinGW-w64 no Windows) | Compilador |

> **Por que GLFW e não GLUT?**
> O GLUT/freeglut não oferece captura relativa confiável do mouse no Wayland.
> O GLFW 3.4 usa o protocolo `zwp_relative_pointer_v1`, permitindo que a câmera
> continue funcionando com `GLFW_CURSOR_DISABLED`.

### 1.3 Arquitetura em camadas

```text
┌──────────────────────────────────────────────────────────┐
│ main.cpp                                                 │
│  loop principal, callbacks do GLFW, delta-time            │
└───────────────┬──────────────────────────────┬───────────┘
                │                              │
        ┌───────▼────────┐            ┌────────▼─────────┐
        │ Janela         │            │ Controles        │
        │ janela.cpp/.h  │            │ controles.cpp/.h │
        │ GLFW + OpenGL  │            │ teclado + mouse  │
        └───────┬────────┘            └────────┬─────────┘
                │                              │
                │                     ┌────────▼─────────┐
                │                     │ Câmera           │
                │                     │ camera.cpp/.h    │
                │                     └────────┬─────────┘
                │                              │
                │                     ┌────────▼─────────┐
                │                     │ Colisões         │
                │                     │ colisoes.cpp/.h  │
                │                     └──────────────────┘
                │
        ┌───────▼────────┐   ┌──────────────────┐
        │ Renderização   │──▶│ Interações       │
        │ renderizador   │   │ interacoes.cpp   │
        └───────┬────────┘   └──────────────────┘
                │
    ┌───────────┼──────────────┬────────────────┐
    │           │              │                │
┌───▼────┐ ┌────▼─────┐ ┌──────▼──────┐ ┌───────▼──────┐
│ Sala   │ │ Primitivas│ │ Objetos     │ │ Texturas     │
│ sala   │ │ primitivas│ │ src/Objetos │ │ texturas     │
└────────┘ └───────────┘ └─────────────┘ └──────────────┘
```

### 1.4 Responsabilidade de cada pasta

| Caminho | Responsabilidade |
|---|---|
| `src/main.cpp` | Inicializa tudo, registra callbacks e mantém o loop |
| `src/Janela/` | Cria a janela GLFW, contexto, VSync, tamanho e swap |
| `src/Controles/` | Estado das teclas, delta do mouse, atualização contínua |
| `src/Camera/` | Posição, orientação, movimento e aplicação da câmera |
| `src/Colisoes/` | Testes de colisão no plano XZ |
| `src/Interacoes/` | Estado das portas, cadeiras, luz e animações |
| `src/Renderizacao/` | Monta o frame, iluminação, câmera e primitivas |
| `src/Sala/` | Piso, teto, paredes, janela e banheiro |
| `src/Objetos/` | Modelagem de cada objeto da cafeteria |
| `src/Texturas/` | Carregamento de imagens e criação de texturas OpenGL |
| `assets/texturas/` | Arquivos de imagem usados pela cena |

### 1.5 Fluxo de um frame

```text
main()
  │
  ├─ processarEventos()          → glfwPollEvents()
  │
  ├─ atualizarControles(dt)      → WASD, setas, mouse
  │
  ├─ atualizarInteracoes(dt)     → portas e cadeiras
  │
  ├─ renderizarCena()            → desenha a cena inteira
  │
  └─ trocarBuffers()             → glfwSwapBuffers()
```

O swap é feito **uma única vez**, no `main`. `renderizarCena()` apenas desenha;
ela não apresenta o frame.

---

## 2. Como o programa inicia e executa

### 2.1 `main.cpp` em etapas

```cpp
int main() {
    if (!criarJanela(800, 600, "Cafeteria")) {
        return 1;
    }

    GLFWwindow* janela = obterJanela();

    configurarEntrada(janela);

    glEnable(GL_DEPTH_TEST);

    inicializarCamera();
    inicializarInteracoes();

    double instanteAnterior = glfwGetTime();

    while (!janelaDeveFechar()) {
        const float deltaTempo = calcularDeltaTempo(instanteAnterior);

        processarEventos();
        atualizarControles(deltaTempo);
        atualizarInteracoes(deltaTempo);
        renderizarCena();
        trocarBuffers();
    }

    destruirJanela();
    return 0;
}
```

A ordem importa:

1. **Eventos primeiro**: o GLFW atualiza o estado de teclas e mouse.
2. **Controles depois**: o estado atual é convertido em movimento/rotação.
3. **Interações**: portas e cadeiras avançam suas animações.
4. **Renderização**: o frame é desenhado com o estado mais recente.
5. **Swap**: o frame pronto aparece na tela.

### 2.2 Delta-time

`calcularDeltaTempo()` mede o tempo entre frames:

```cpp
const float delta = static_cast<float>(instanteAtual - instanteAnterior);
return std::min(delta, DELTA_MAXIMO); // DELTA_MAXIMO = 0.05f
```

O limite de `0.05 s` evita que uma pausa longa (janela minimizada, travamento)
gere um passo gigante e faça a câmera atravessar paredes.

A velocidade é expressa em **unidades por segundo** (câmera e cadeiras) ou
**graus por segundo** (portas e setas). Por isso o movimento é multiplicado por
`deltaTempo`.

### 2.3 Callbacks

| Callback | Quando dispara | O que faz |
|---|---|---|
| `callbackTecla` | Tecla pressionada/solta | Encaminha para `teclaPressionada`/`teclaSolta`; `Esc` fecha |
| `callbackMouse` | Cursor se move | Chama `moverMouse(x, y)` |
| `callbackFoco` | Janela ganha/perde foco | Libera teclas e redefine a referência do mouse |

O GLFW trabalha com callbacks: o programa não fica consultando o teclado o tempo
todo. O estado é acumulado em `controles.cpp` e consultado no loop.

---

## 3. Janela e contexto OpenGL

### 3.1 API de `janela.h`

| Função | Responsabilidade |
|---|---|
| `criarJanela(largura, altura, titulo)` | Inicializa GLFW, cria janela e contexto |
| `obterJanela()` | Retorna o `GLFWwindow*` atual |
| `obterTamanhoJanela(&l, &a)` | Tamanho real do framebuffer, nunca menor que 1 |
| `trocarBuffers()` | `glfwSwapBuffers` (double buffering) |
| `processarEventos()` | `glfwPollEvents` |
| `janelaDeveFechar()` | Fechamento pedido pelo usuário |
| `destruirJanela()` | Destrói janela e finaliza GLFW |

O header usa `struct GLFWwindow;` como declaração antecipada. Assim, os demais
módulos não precisam incluir `GLFW/glfw3.h`.

### 3.2 Contexto de compatibilidade

```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
```

A cena usa apenas funções antigas do OpenGL. Um contexto de compatibilidade 2.1
é suficiente. No Mesa atual pode ser entregue um contexto de compatibilidade
mais novo, mas o código continua usando o mesmo subconjunto fixo.

### 3.3 VSync e double buffering

```cpp
glfwSwapInterval(1);
```

Com VSync ligado, o programa **solicita** ao sistema que `trocarBuffers()`
espere o monitor para evitar tearing e limitar a taxa de quadros. O desenho
acontece no buffer de trás; o swap troca os buffers. No Wayland, a taxa efetiva
também pode ser controlada pelo compositor.

> **Cuidado:** chamar `trocarBuffers()` duas vezes no mesmo frame descarta um
> frame e pode reduzir a taxa efetiva. Atualmente o swap existe apenas no
> `main`.

### 3.4 Wayland e X11

| Situação | Comportamento |
|---|---|
| X11 | Funciona com GLX; mouse relativo via `GLFW_CURSOR_DISABLED` |
| Wayland | GLFW usa `zwp_relative_pointer_v1`; funciona com o cursor capturado |
| GLUT no Wayland | `glutWarpPointer` não funciona; por isso foi substituído |

---

## 4. Entrada: teclado e mouse

### 4.1 Teclado

`controles.cpp` mantém um vetor de estados indexado pelas constantes do GLFW:

```cpp
bool teclas[GLFW_KEY_LAST + 1] = { false };
```

- `teclaPressionada(tecla)` marca `true`.
- `teclaSolta(tecla)` marca `false`.
- `teclaAtiva(tecla)` valida o índice e consulta o estado.

A tecla `E` é tratada na **borda de descida**:

```cpp
if (tecla == GLFW_KEY_E && !teclas[tecla]) {
    tentarInteragir();
}
```

Assim, segurar `E` não alterna a porta várias vezes por segundo.

### 4.2 Mouse relativo

O cursor é capturado em `main`:

```cpp
glfwSetInputMode(janela, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
```

Com isso, o GLFW entrega uma posição virtual do cursor que pode sair dos limites
da janela. O código não usa posição absoluta; usa o **delta**:

```cpp
if (!temUltimo) {
    ultimoX = x;
    ultimoY = y;
    temUltimo = true;
    return; // primeiro evento apenas cria a referência
}

rotacionarCamera(x - ultimoX, y - ultimoY);
ultimoX = x;
ultimoY = y;
```

Essa abordagem dispensa `glutWarpPointer` e funciona no Wayland.

### 4.3 Perda de foco

```cpp
void callbackFoco(GLFWwindow*, int focado) {
    if (!focado) {
        soltarTodasAsTeclas();
    }
    redefinirMouse();
}
```

Sem isso, uma tecla pressionada ao trocar de janela poderia ficar "presa".
`redefinirMouse()` descarta a última posição para evitar um salto no próximo foco.

### 4.4 Controles atuais

| Entrada | Efeito |
|---|---|
| `W` / `S` | Frente / trás |
| `A` / `D` | Esquerda / direita |
| Mouse | Rotação horizontal e vertical |
| `←` / `→` | Rotação horizontal |
| `↑` / `↓` | Rotação vertical |
| `E` | Interagir |
| `Esc` | Fechar |

### 4.5 Atualização contínua

```cpp
const float passo = VELOCIDADE_MOVIMENTO * deltaTempo;
if (teclaAtiva(GLFW_KEY_W)) moverCameraFrente(passo);
if (teclaAtiva(GLFW_KEY_S)) moverCameraTras(passo);
if (teclaAtiva(GLFW_KEY_A)) moverCameraEsquerda(passo);
if (teclaAtiva(GLFW_KEY_D)) moverCameraDireita(passo);
```

As setas usam `VELOCIDADE_ROTACAO` em graus por segundo. Isso mantém a
velocidade constante independentemente do FPS.

---

## 5. Câmera em primeira pessoa

### 5.1 Estado

```cpp
float cameraX = 1.50f;
float cameraY = 1.65f;
float cameraZ = 3.00f;

float yaw = 0.0f;    // rotação horizontal
float pitch = 0.0f;  // rotação vertical
```

- A câmera começa em `(1.5, 1.65, 3.0)`.
- `cameraY = 1.65` representa a altura dos olhos.
- `yaw = 0` olha para `-Z` (para dentro da cafeteria, já que a entrada fica em `+Z`).

### 5.2 Aplicação da câmera

```cpp
glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
glRotatef(-yaw,   0.0f, 1.0f, 0.0f);
glTranslatef(-cameraX, -cameraY, -cameraZ);
```

Em OpenGL, a matriz de modelview transforma coordenadas do mundo para o espaço
da câmera. Para "mover a câmera", aplica-se a transformação inversa ao mundo:

1. transladar o mundo pelo negativo da posição da câmera;
2. rotacionar pelo negativo de `yaw`;
3. rotacionar pelo negativo de `pitch`.

A última operação aplicada ao código é a primeira aplicada aos vértices.

### 5.3 Movimento relativo à direção

A função central é:

```cpp
void moverCamera(float frente, float lateral, float distancia) {
    const float radianos = yaw * PI / 180.0f;

    const float deslocamentoX = (
        -std::sin(radianos) * frente +
         std::cos(radianos) * lateral
    ) * distancia;

    const float deslocamentoZ = (
        -std::cos(radianos) * frente -
         std::sin(radianos) * lateral
    ) * distancia;

    tentarMover(deslocamentoX, deslocamentoZ);
}
```

Com `yaw = 0`:

- frente (`frente = 1`) → `dx = 0`, `dz = -distancia` (anda para `-Z`);
- direita (`lateral = 1`) → `dx = +distancia`, `dz = 0` (anda para `+X`);
- esquerda (`lateral = -1`) → `dx = -distancia`, `dz = 0`;
- trás (`frente = -1`) → `dz = +distancia`.

As funções `moverCameraFrente`, `moverCameraTras`, `moverCameraEsquerda` e
`moverCameraDireita` são apenas atalhos para essa função.

### 5.4 Rotação

```cpp
void rotacionarCamera(float deltaX, float deltaY) {
    yaw -= deltaX * SENSIBILIDADE_MOUSE;
    pitch -= deltaY * SENSIBILIDADE_MOUSE;
    limitarPitch();
}
```

- `SENSIBILIDADE_MOUSE = 0.10f`.
- `limitarPitch()` mantém o ângulo entre `-85°` e `+85°`, evitando que a câmera
  "vire de cabeça para baixo".

As setas usam `girarCamera(deltaYaw, deltaPitch)`, que soma diretamente em graus
e aplica o mesmo limite.

### 5.5 Deslizamento nas colisões

```cpp
static void tentarMover(float deslocamentoX, float deslocamentoZ) {
    const float novoX = cameraX + deslocamentoX;
    const float novoZ = cameraZ + deslocamentoZ;

    if (posicaoCameraValida(novoX, novoZ)) {
        cameraX = novoX;
        cameraZ = novoZ;
        return;
    }

    if (posicaoCameraValida(novoX, cameraZ)) {
        cameraX = novoX;
    }

    if (posicaoCameraValida(cameraX, novoZ)) {
        cameraZ = novoZ;
    }
}
```

Se o movimento diagonal for bloqueado, o código tenta cada eixo separadamente.
Isso permite deslizar ao longo de paredes e móveis em vez de parar completamente.

> **Limitação:** não há resposta física nem velocidade; a posição é apenas
> aceita ou rejeitada. O deslizamento é uma aproximação simples e adequada ao
> escopo da disciplina.

---

## 6. Sistema de colisões

### 6.1 Representação no plano XZ

O jogador é tratado como uma caixa de raio `RAIO_CAMERA = 0.20f`. Cada obstáculo
é um retângulo no plano XZ:

```cpp
struct RetanguloXZ {
    float minX;
    float maxX;
    float minZ;
    float maxZ;
};
```

O teste é:

```cpp
bool colideComRetangulo(float x, float z, const RetanguloXZ& area) {
    return
        x + RAIO_CAMERA > area.minX &&
        x - RAIO_CAMERA < area.maxX &&
        z + RAIO_CAMERA > area.minZ &&
        z - RAIO_CAMERA < area.maxZ;
}
```

Isso equivale a expandir o retângulo pelo raio do jogador e testar sobreposição
de caixas. É uma aproximação conservadora: nos cantos, a área efetiva é
ligeiramente maior que um círculo.

### 6.2 Paredes externas

A sala tem limites:

```text
X = -5.75 .. +5.75
Z = -3.75 .. +3.75
```

A parede da frente (`Z > 3.75`) só permite passagem pelo vão central:

```text
-0.45 < X < 0.45
```

Além disso:

- a porta principal precisa estar com ângulo `>= 70°`;
- o jogador pode sair até `Z <= 4.80`, mas não infinitamente.

### 6.3 Portas como segmentos

Uma folha de porta não é um retângulo alinhado aos eixos; ela gira. Por isso é
representada por um segmento entre a dobradiça e a ponta:

```cpp
const float pontaX = dobradicaX + std::cos(radianos) * largura;
const float pontaZ = dobradicaZ - std::sin(radianos) * largura;
```

O algoritmo calcula o ponto do segmento mais próximo do jogador:

1. projeta o vetor jogador→dobradiça sobre o vetor da folha;
2. limita o parâmetro `t` entre 0 e 1;
3. calcula a distância até esse ponto;
4. compara com `RAIO_CAMERA + meiaEspessura`.

Dados principais:

| Porta | Dobradiça | Largura | Meia espessura | Ângulo usado |
|---|---|---|---|---|
| Principal | `(-0.70, 3.96)` | `1.40` | `0.04` | `obterAnguloPorta()` |
| Banheiro | `(4.298, -2.10)` | `0.985` | `0.035` | `-obterAnguloPortaBanheiro()` |

O sinal negativo da porta do banheiro acompanha o `glRotatef` usado no modelo.

### 6.4 Caixas fixas

As mesas usam uma tabela de três retângulos:

```cpp
const RetanguloXZ MESAS[] = {
    { -3.65f, -2.35f, 0.05f, 0.95f },
    { -0.65f,  0.65f, 0.05f, 0.95f },
    {  2.35f,  3.65f, 0.05f, 0.95f }
};
```

Também são caixas fixas:

- balcão;
- vaso sanitário;
- pia do banheiro;
- paredes do banheiro (três blocos, deixando o vão da porta).

### 6.5 Cadeiras dinâmicas

As cadeiras não têm posições duplicadas no código de colisão. Elas consultam o
layout de `interacoes.cpp`:

```cpp
for (int i = 0; i < quantidadeCadeiras(); i++) {
    const float cadeiraX = obterCadeiraX(i);
    const float cadeiraZ = obterCadeiraZ(i);
    // monta o retângulo e testa
}
```

`obterCadeiraZ(i)` já inclui o deslocamento da animação. Assim, quando a cadeira
é afastada da mesa, a colisão acompanha automaticamente.

### 6.6 Ordem de verificação

`posicaoCameraValida()` testa, nesta ordem:

1. paredes externas;
2. folha da porta principal;
3. paredes do banheiro;
4. porta do banheiro;
5. balcão;
6. mesas;
7. cadeiras;
8. vaso sanitário;
9. pia.

Se qualquer teste indicar colisão, a posição é inválida.

> **Limitação:** não há colisão vertical (telhado, pulo) nem objetos rotacionados
> além das portas. O sistema é 2D no plano XZ, adequado a uma câmera que anda
> sempre na mesma altura.

---

## 7. Interações e animações

### 7.1 Modelo de estado

Cada elemento interativo guarda um valor atual e um alvo:

```cpp
float anguloPorta;          // valor atual
float anguloAlvoPorta;      // 0 ou 90
bool portaAberta;

float deslocamentoCadeira[6];
float deslocamentoAlvoCadeira[6];
bool cadeiraPuxada[6];

bool luzLigada;
```

A cada frame, `atualizarInteracoes(deltaTempo)` aproxima o valor atual do alvo.
Isso produz animações suaves sem bibliotecas externas.

### 7.2 Função `aproximar`

```cpp
void aproximar(float& valor, float alvo, float passo) {
    if (valor < alvo) {
        valor = std::min(valor + passo, alvo);
    } else if (valor > alvo) {
        valor = std::max(valor - passo, alvo);
    }
}
```

O `passo` já vem multiplicado por `deltaTempo`, então a animação é independente
de FPS:

```cpp
const float passoPorta = VELOCIDADE_PORTA * deltaTempo;    // 150°/s
const float passoCadeira = VELOCIDADE_CADEIRA * deltaTempo; // 1.5 un/s
```

### 7.3 Portas

- Fechada: ângulo `0°`.
- Aberta: ângulo `90°`.
- `alternarPorta()` troca o booleano e define o alvo.

A porta principal usa o ângulo atual na colisão e no desenho. A porta do
banheiro faz o mesmo, mas o modelo gira no sentido oposto (daí o sinal negativo
na colisão).

### 7.4 Cadeiras

O layout completo fica em uma única tabela:

```cpp
struct LayoutCadeira {
    float x;       // posição X
    float z;       // posição Z original
    float direcao; // +1 afasta para +Z; -1 para -Z
    float angulo;  // rotação usada ao desenhar
};

const LayoutCadeira CADEIRAS[6] = {
    { -3.0f,  1.2f,  1.0f, 180.0f },
    { -3.0f, -0.2f, -1.0f,   0.0f },
    {  0.0f,  1.2f,  1.0f, 180.0f },
    {  0.0f, -0.2f, -1.0f,   0.0f },
    {  3.0f,  1.2f,  1.0f, 180.0f },
    {  3.0f, -0.2f, -1.0f,   0.0f }
};
```

Ao interagir:

- a cadeira é marcada como puxada ou não;
- o alvo é `direcao * 0.60` ou `0`;
- a animação move `deslocamentoCadeira[i]` até o alvo.

A renderização e a colisão consultam `obterCadeiraX(i)`, `obterCadeiraZ(i)` e
`obterAnguloCadeira(i)`. Essa é a **fonte única de verdade** do layout.

### 7.5 Interruptor de luz

A interação apenas alterna `luzLigada`. O renderizador consulta esse estado para:

- ligar ou desligar `GL_LIGHT0`–`GL_LIGHT3`;
- mudar a luz ambiente global;
- desenhar o interruptor na posição visual correta.

### 7.6 Zonas de interação

`tentarInteragir()` testa nesta ordem:

| Alvo | Condição |
|---|---|
| Porta do banheiro | Distância até `(4.80, -2.05)` ≤ `1.15` |
| Porta principal | `-1.8 < X < 1.8` e `Z > 2.0` |
| Interruptor | `X > 4.6`, `1.8 < Z < 3.7` |
| Cadeira | Mais próxima, a até `1.10` de distância |

A porta do banheiro é verificada primeiro porque o jogador pode estar exatamente
na entrada, dentro da zona da porta principal.

Se nenhuma condição for satisfeita, `E` não faz nada.

---

## 8. Renderização

### 8.1 `renderizarCena()` passo a passo

```cpp
void renderizarCena() {
    int largura = 1;
    int altura = 1;
    obterTamanhoJanela(&largura, &altura);

    glViewport(0, 0, largura, altura);
    glClearColor(0.08f, 0.08f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const double aspecto =
        static_cast<double>(largura) / static_cast<double>(altura);
    configurarPerspectiva(70.0, aspecto, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    aplicarCamera();

    configurarIluminacao();

    desenharSala();
    desenharJanelaDaCafeteria();
    desenharLuminarias();
    // ... demais objetos ...
}
```

A função **não** chama `trocarBuffers()`. Quem apresenta o frame é o `main`.

### 8.2 Projeção perspectiva

```cpp
const double altura = tan(fovY / 360.0 * PI) * zNear;
const double largura = altura * aspect;

glFrustum(-largura, largura, -altura, altura, zNear, zFar);
```

- `fovY = 70°`;
- `near = 0.1`, `far = 100.0`;
- `aspect = largura / altura`.

`glFrustum` define um tronco de pirâmide. Objetos entre `near` e `far` são
projetados; o resto é recortado.

### 8.3 Ordem de desenho

A ordem atual é:

1. sala (piso, teto, paredes, banheiro);
2. janela da cafeteria;
3. luminárias;
4. prateleira;
5. objetos do banheiro (vaso, pia, espelho);
6. porta do banheiro;
7. balcão;
8. vitrine;
9. registradora;
10. máquina de café;
11. mesas;
12. decorações das mesas;
13. cadeiras;
14. porta principal;
15. cardápio;
16. interruptor.

O depth test garante que a ordem não cause sobreposição errada, mas desenhar
objetos opacos primeiro e translúcidos depois (caso da vitrine) continua sendo
boa prática.

### 8.4 Matrizes e transformações locais

Cada objeto normalmente segue o padrão:

```cpp
glPushMatrix();
glTranslatef(x, y, z);      // posiciona no mundo
glRotatef(rotacao, 0, 1, 0); // orienta
// desenha o objeto em coordenadas locais
glPopMatrix();
```

`glPushMatrix`/`glPopMatrix` isolam a transformação. Sem eles, a posição de um
objeto contaminaria todos os seguintes.

### 8.5 Estado global do OpenGL

O OpenGL de função fixa é uma máquina de estados. Alguns cuidados aparecem no
código:

- texturas são habilitadas com `glEnable(GL_TEXTURE_2D)` e desabilitadas depois;
- materiais são restaurados com `restaurarMaterialPadrao()`;
- a vitrine usa blending e `glDepthMask` para o vidro;
- o depth test é habilitado uma vez no `main`.

---

## 9. Iluminação e materiais

### 9.1 Fontes de luz

| Luz | Papel | Posição |
|---|---|---|
| `GL_LIGHT0` | Luz geral | `(0, 2.85, 0)` |
| `GL_LIGHT1` | Luminária esquerda | `(-3, 2.43, 0.50)` |
| `GL_LIGHT2` | Luminária central | `(0, 2.43, 0.50)` |
| `GL_LIGHT3` | Luminária direita | `(3, 2.43, 0.50)` |

As três luminárias são spotlights apontando para baixo:

```cpp
GLfloat direcao[] = { 0.0f, -1.0f, 0.0f };
glLightf(luz, GL_SPOT_CUTOFF, 48.0f);
glLightf(luz, GL_SPOT_EXPONENT, 8.0f);
```

A atenuação usa:

```cpp
GL_CONSTANT_ATTENUATION  = 1.0
GL_LINEAR_ATTENUATION    = 0.10
GL_QUADRATIC_ATTENUATION = 0.025
```

Isso faz a luz perder intensidade com a distância.

### 9.2 Luz ligada e desligada

Com a luz ligada:

- ambiente global `(0.23, 0.21, 0.18)`;
- `GL_LIGHT0`–`GL_LIGHT3` habilitadas;
- luz geral difusa suave;
- spotlights quentes sobre as mesas.

Com a luz desligada:

- todas as quatro luzes são desabilitadas;
- ambiente global cai para `(0.045, 0.045, 0.055)`;
- a cena continua parcialmente visível.

### 9.3 Materiais

O código usa:

```cpp
glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glEnable(GL_NORMALIZE);
glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
```

- `GL_COLOR_MATERIAL` permite que `glColor3f` defina as propriedades do material.
- `GL_NORMALIZE` renormaliza normais após transformações de escala.
- `GL_LIGHT_MODEL_TWO_SIDE` ilumina as duas faces, importante para superfícies
  vistas por dentro.

Alguns objetos definem materiais específicos, como madeira e tecido, com
`glMaterialfv` para refletância e brilho (`GL_SHININESS`).

---

## 10. Primitivas e modelagem dos objetos

### 10.1 `desenharQuad`

Desenha um quadrilátero com normal calculada por produto vetorial:

```cpp
// vetores u = p2 - p1 e v = p3 - p1
// normal = u × v, normalizada
glNormal3f(nx, ny, nz);

glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
glEnd();
```

A normal é essencial para a iluminação: sem ela, o OpenGL não sabe como a
superfície reflete a luz.

### 10.2 `desenharCaixa`

Desenha uma caixa a partir do centro e do tamanho, com seis faces e normais
explícitas:

- frente (`+Z`);
- trás (`-Z`);
- esquerda (`-X`);
- direita (`+X`);
- topo (`+Y`);
- base (`-Y`).

Essa primitiva é a base de quase todos os objetos: pés de mesa, balcão, porta,
máquina de café, vaso etc.

### 10.3 Padrão dos objetos

Cada objeto em `src/Objetos/` segue o mesmo contrato:

```cpp
void desenharAlgo(float x, float y, float z, float rotacao);
```

Dentro da função:

1. `glPushMatrix()`;
2. `glTranslatef(x, y, z)`;
3. `glRotatef(rotacao, 0, 1, 0)` quando aplicável;
4. desenha partes com `desenharCaixa`, `desenharQuad`, texturas e materiais;
5. `glPopMatrix()`.

As coordenadas internas são locais. Isso permite reutilizar o mesmo modelo em
posições diferentes.

### 10.4 Objetos e assinaturas

| Objeto | Função |
|---|---|
| Balcão | `desenharBalcao(x, y, z, rotacao)` |
| Cadeira | `desenharCadeira(x, z, rotacao)` |
| Espelho | `desenharEspelhoBanheiro(x, y, z, rotacao)` |
| Interruptor | `desenharInterruptor(ligado)` |
| Janela | `desenharJanelaCafe(x, y, z)` |
| Luminária | `desenharLuminaria(x, y, z, ligada)` |
| Máquina de café | `desenharMaquinaCafe(x, y, z, rotacao)` |
| Menu | `desenharMenu()` |
| Mesa | `desenharMesa(x, z, rotacao)` |
| Pia | `desenharPiaBanheiro(x, y, z, rotacao)` |
| Porta principal | `desenharPorta(angulo)` |
| Porta do banheiro | `desenharPortaBanheiro(angulo)` |
| Porta-guardanapos | `desenharPortaGuardanapos(x, y, z)` |
| Prateleira | `desenharPrateleira(x, y, z, rotacao)` |
| Registradora | `desenharRegistradora(x, y, z, rotacao)` |
| Vasinho | `desenharVasinho(x, y, z)` |
| Vaso sanitário | `desenharVasoSanitario(x, y, z, rotacao)` |
| Vitrine | `desenharVitrine(x, y, z)` |
| Xícara | `desenharXicara(x, y, z)` |

### 10.5 Por que os arquivos de objetos são grandes

A modelagem é procedural e detalhista: cada objeto é composto por várias caixas,
quads, materiais e, às vezes, texturas. Isso gera arquivos longos, mas com uma
estrutura repetitiva e previsível:

```text
material
  → parte 1 (caixa/quad)
  → parte 2
  → ...
  → restauração do material
```

Essa repetição é aceitável no escopo do projeto e mantém cada objeto
independente. Uma abstração genérica de modelagem reduziria linhas, mas
aumentaria o risco de alterar a geometria e dificultaria a leitura por partes.

---

## 11. Texturas

### 11.1 Carregamento

`texturas.cpp` usa `stb_image`:

```cpp
unsigned char* dados = stbi_load(caminho, &largura, &altura, &canais, 0);
```

Depois:

1. `glGenTextures` cria o identificador;
2. `glBindTexture` ativa a textura;
3. filtros `GL_LINEAR` para minificação e magnificação;
4. `GL_CLAMP` para não repetir fora das bordas;
5. `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)`;
6. `glTexImage2D` envia os pixels para a GPU;
7. `stbi_image_free` libera a memória RAM.

Formatos aceitos:

- 3 canais → `GL_RGB`;
- 4 canais → `GL_RGBA`;
- qualquer outro → retorna `0` (falha).

### 11.2 Texturas em cache

Cada módulo guarda um `static GLuint`:

```cpp
static GLuint texturaPiso = 0;

if (texturaPiso == 0) {
    texturaPiso = carregarTexturaBMP("assets/texturas/piso.bmp");
}
```

Isso evita recarregar a imagem a cada frame. Se o arquivo não existir, o código
usa a versão sem textura (cor sólida) como fallback.

### 11.3 Texturas usadas

| Arquivo | Onde aparece |
|---|---|
| `piso.bmp` | Piso da cafeteria |
| `mesa.bmp` | Tampo das mesas |
| `cadeira.bmp` | Estofado das cadeiras |
| `porta.bmp` | Folha da porta principal |
| `menu.bmp` | Quadro de cardápio |

O piso usa `GL_REPEAT` para repetir a textura em vez de esticá-la. As demais
usam o padrão do carregador (`GL_CLAMP`).

### 11.4 Caminho dos arquivos

Os caminhos são relativos ao diretório de trabalho:

```text
assets/texturas/piso.bmp
```

Por isso, rodar a partir da raiz do projeto funciona. O CMake também copia
`assets/` para junto do executável, permitindo rodar de dentro de `build/`.

---

## 12. Cenário: sala, paredes e banheiro

### 12.1 Dimensões

```text
Sala: 12 m × 8 m × 3 m
X: -6.0 .. +6.0
Y:  0.0 .. +3.0
Z: -4.0 .. +4.0
1 unidade OpenGL ≈ 1 metro
```

A entrada principal fica em `Z = +4.0`, com 1.4 m de largura e 2.2 m de altura.

### 12.2 Piso e teto

- Piso em `Y = 0`, texturizado e repetido (`6 × 4` repetições).
- Teto em `Y = 3`, cor clara.

### 12.3 Paredes

| Parede | Coordenada | Observação |
|---|---|---|
| Fundo | `Z = -4` | Fecha a sala atrás do balcão |
| Direita | `X = +6` | Parede do banheiro |
| Esquerda | `X = -6` | Possui abertura para a janela |
| Frente | `Z = +4` | Possui o vão da porta principal |

A parede esquerda é dividida em quatro quads para deixar o vão da janela:

```text
Z = 0.5 .. 3.5
Y = 0.8 .. 2.6
```

A parede da frente é dividida em três partes: esquerda, direita e acima da porta.

### 12.4 Banheiro

O banheiro ocupa o canto traseiro direito:

```text
X = 3.6 .. 6.0
Z = -4.0 .. -2.2
```

É montado com caixas:

- parede lateral esquerda;
- parte esquerda da parede frontal;
- parte direita da parede frontal;
- parte acima da porta.

O vão da porta do banheiro fica na parede frontal, em torno de `X = 4.80`.

---

## 13. Build, execução e diagnóstico

### 13.1 Instalação das dependências

A compilação é feita exclusivamente com CMake. O projeto exige **GLFW 3.4**.

**Linux — Fedora**

```bash
sudo dnf install gcc-c++ make cmake glfw-devel mesa-libGL-devel mesa-libGLU-devel
```

**Linux — Ubuntu / Debian (24.04 ou superior)**

```bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```

**Linux — Arch Linux**

```bash
sudo pacman -S --needed base-devel cmake glfw mesa glu
```

**Windows — MSYS2 (terminal UCRT64)**

```bash
pacman -S --needed \
    mingw-w64-ucrt-x86_64-toolchain \
    mingw-w64-ucrt-x86_64-cmake \
    mingw-w64-ucrt-x86_64-glfw \
    mingw-w64-ucrt-x86_64-glu \
    mingw-w64-ucrt-x86_64-ninja
```

> O README traz o passo a passo completo, incluindo a configuração do `PATH` no Windows e as dependências de execução.

### 13.2 CMake

O `CMakeLists.txt` atual:

- exige C++14;
- procura `OpenGL`, `GLU` e `glfw3 3.4`;
- coleta automaticamente todos os `.cpp` e `.h` de `src/`;
- adiciona `src/` aos includes;
- linka `OpenGL::GL`, `OpenGL::GLU` e `glfw`;
- copia `assets/` para o diretório do executável após o build.

```cmake
file(GLOB_RECURSE CAFETERIA_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(cafeteria_opengl ${CAFETERIA_SOURCES})
```

### 13.3 Compilar e executar

A compilação é feita exclusivamente com CMake.

**Linux**

```bash
cmake -S . -B build
cmake --build build
./build/cafeteria_opengl
```

**Windows (terminal MSYS2 UCRT64)**

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/cafeteria_opengl.exe
```

Também é possível executar de dentro de `build/`:

```bash
cd build
./cafeteria_opengl
```

### 13.4 Diagnóstico rápido

| Sintoma | Causa provável | Solução |
|---|---|---|
| Tela preta | Sem `glEnable(GL_DEPTH_TEST)` ou sem swap | Verifique `main.cpp` e o swap único |
| Texturas ausentes | Executou fora da raiz e sem assets no build | Rode da raiz ou de `build/` após o CMake copiar |
| Mouse não gira | Janela sem foco ou cursor não capturado | Clique na janela; verifique `GLFW_CURSOR_DISABLED` |
| Mouse não gira no Wayland | GLUT antigo | Use o binário GLFW atual |
| Erro de link `glfw` | Pacote de desenvolvimento ausente | Instale `glfw-devel` |
| Build desatualizado | Arquivos antigos no `build/` | `rm -rf build` e reconfigure |
| Contexto OpenGL falha | Driver/Mesa incompatível | Verifique `glxinfo -B` e o suporte a OpenGL 2.1 |

### 13.5 Verificação de dependências

```bash
pkg-config --modversion glfw3
ldd build/cafeteria_opengl | grep glfw
glxinfo -B | grep "OpenGL version"
```

---

## 14. Decisões de projeto e limitações

### 14.1 Separação de responsabilidades

O código evita que a renderização conheça detalhes de entrada e que a câmera
conheça detalhes de desenho:

- `Controles` só traduz eventos em chamadas de movimento;
- `Camera` só guarda posição/orientação e aplica a transformação;
- `Colisoes` só responde "esta posição é válida?";
- `Interacoes` só guarda estado e anima alvos;
- `Renderizacao` só desenha;
- `Objetos` só modelam geometria local.

### 14.2 Fonte única de verdade

O layout das cadeiras existe apenas em `interacoes.cpp`. A renderização e a
colisão consultam os mesmos getters. Isso evita o problema clássico de mover uma
cadeira no desenho e esquecer a colisão (ou vice-versa).

### 14.3 Animações independentes de FPS

Portas e cadeiras usam velocidade em unidades por segundo, multiplicada por
`deltaTempo`. O comportamento é o mesmo em 30, 60 ou 144 Hz.

### 14.4 OpenGL de função fixa

A escolha é adequada à disciplina:

- mostra transformações, projeção, iluminação e textura explicitamente;
- não exige shaders, VAOs/VBOs nem bibliotecas externas de matemática;
- é simples de depurar.

Como contrapartida:

- é um modelo legado;
- não escala para muitas luzes/objetos;
- o estado global exige cuidado com `glPushMatrix`, texturas e materiais.

### 14.5 Limitações conhecidas

- Colisão apenas no plano XZ.
- Portas são os únicos obstáculos rotacionados.
- Não há física, gravidade ou salto.
- Não há carregamento assíncrono de texturas.
- Os objetos são desenhados imediatamente, sem instancing ou culling.
- O layout da cena é codificado em constantes; não há editor ou arquivo de cena.

---

## 15. Roteiro de leitura e exercícios

### 15.1 Ordem sugerida de leitura

Para entender o projeto de ponta a ponta:

1. `src/main.cpp` — visão do loop;
2. `src/Janela/janela.h` e `janela.cpp` — plataforma;
3. `src/Controles/controles.cpp` — entrada;
4. `src/Camera/camera.cpp` — movimento e orientação;
5. `src/Colisoes/colisoes.cpp` — regras do mundo;
6. `src/Interacoes/interacoes.cpp` — estado e animações;
7. `src/Renderizacao/renderizador.cpp` — montagem do frame;
8. `src/Renderizacao/primitivas.cpp` — blocos de geometria;
9. `src/Sala/sala.cpp` — cenário;
10. `src/Objetos/...` — modelagem;
11. `src/Texturas/texturas.cpp` — imagens.

### 15.2 Perguntas para revisar

1. Por que o `trocarBuffers()` fica no `main` e não em `renderizarCena()`?
2. O que aconteceria se o delta-time não fosse limitado a `0.05 s`?
3. Por que o mouse usa delta em vez de posição absoluta?
4. Por que a colisão das cadeiras consulta `interacoes.cpp`?
5. Qual é a diferença entre a colisão de uma mesa e a de uma porta?
6. Por que `glPushMatrix`/`glPopMatrix` são necessários nos objetos?
7. O que `GL_NORMALIZE` faz e por que ele importa?
8. Por que a textura do piso usa `GL_REPEAT` e as outras usam `GL_CLAMP`?
9. O que muda na cena quando `luzLigada` é falso?
10. Por que o contexto 2.1 de compatibilidade é suficiente?

### 15.3 Exercícios práticos

**Iniciante**

- Altere a velocidade de caminhada em `controles.cpp`.
- Mude o campo de visão de `70°` para `60°` em `renderizador.cpp`.
- Troque a cor de fundo em `renderizarCena()`.

**Intermediário**

- Adicione uma nova cadeira ao layout e ajuste a tabela de `CADEIRAS`.
- Crie uma nova caixa de colisão para um objeto existente.
- Faça o interruptor também mudar a cor da luz ambiente.

**Avançado**

- Adicione uma tecla para agachar, mudando `cameraY` temporariamente.
- Implemente uma porta que abre apenas até `45°` e ajuste a colisão.
- Separe a cena em um arquivo de configuração (posições e tipos de objeto).

---

## 16. Apêndices

### 16.1 Constantes principais

| Constante | Valor | Onde |
|---|---:|---|
| Janela | `800 × 600` | `main.cpp` |
| Altura dos olhos | `1.65` | `camera.cpp` |
| Posição inicial | `(1.50, 1.65, 3.00)` | `camera.cpp` |
| Velocidade de caminhada | `3.6 un/s` | `controles.cpp` |
| Velocidade das setas | `90 °/s` | `controles.cpp` |
| Sensibilidade do mouse | `0.10` | `camera.cpp` |
| Limite de pitch | `±85°` | `camera.cpp` |
| Delta máximo | `0.05 s` | `main.cpp` |
| FOV vertical | `70°` | `renderizador.cpp` |
| Near / far | `0.1 / 100.0` | `renderizador.cpp` |
| Raio de colisão | `0.20` | `colisoes.cpp` |
| Porta aberta | `90°` | `interacoes.cpp` |
| Velocidade da porta | `150 °/s` | `interacoes.cpp` |
| Deslocamento da cadeira | `0.60` | `interacoes.cpp` |
| Velocidade da cadeira | `1.5 un/s` | `interacoes.cpp` |
| Distância de interação com cadeira | `1.10` | `interacoes.cpp` |
| Distância da porta do banheiro | `1.15` | `interacoes.cpp` |

### 16.2 Mapa de coordenadas

```text
Sala:
  X: -6.0 .. +6.0
  Y:  0.0 .. +3.0
  Z: -4.0 .. +4.0

Porta principal:
  parede: Z = +4.0
  vão físico: X = -0.7 .. +0.7
  centro da câmera no vão: X = -0.45 .. +0.45 (por causa do raio)
  altura: 2.2
  dobradiça: (-0.70, 3.96)

Janela:
  parede: X = -6.0
  Z: 0.5 .. 3.5
  Y: 0.8 .. 2.6

Banheiro:
  X: 3.6 .. 6.0
  Z: -4.0 .. -2.2
  porta: X ≈ 4.80, Z ≈ -2.10

Mesas:
  X: -3.0, 0.0, +3.0
  Z: 0.0
  tampo: Y = 0.5

Cadeiras:
  X: -3.0, 0.0, +3.0
  Z: +1.2 (rotacionadas 180°) e -0.2 (rotacionadas 0°)

Luminárias:
  X: -3.0, 0.0, +3.0
  Y: 2.98
  Z: 0.50
```

> Este mapa reflete o código atual (`renderizador.cpp`, `interacoes.cpp` e
> `sala.cpp`). O arquivo `COORDENADAS.txt` contém as dimensões da sala e
> referências antigas de placeholders; em caso de divergência, vale o código.

### 16.3 Glossário

| Termo | Significado |
|---|---|
| **Yaw** | Rotação horizontal (em torno do eixo Y) |
| **Pitch** | Rotação vertical (em torno do eixo X) |
| **Framebuffer** | Buffer onde o frame é desenhado |
| **Double buffering** | Desenhar no buffer de trás e trocar com o da frente |
| **VSync** | Sincronização com a taxa do monitor |
| **Modelview** | Matriz que combina câmera e transformações dos objetos |
| **Projeção** | Matriz que define o volume visível (perspectiva) |
| **Normal** | Vetor perpendicular à superfície, usado na iluminação |
| **AABB** | Caixa alinhada aos eixos (*axis-aligned bounding box*) |
| **Spotlight** | Luz em forma de cone |
| **Immediate mode** | Desenho com `glBegin`/`glEnd` (OpenGL legado) |
| **Delta-time** | Tempo entre frames consecutivos |

### 16.4 Checklist dos requisitos da disciplina

| Requisito | Onde aparece |
|---|---|
| Pelo menos 8 objetos modelados | `src/Objetos/` (mais de 15 tipos) |
| Translação | `glTranslatef` nos objetos e na câmera |
| Rotação | `glRotatef` nas portas, cadeiras e orientações |
| Escala | `glScalef` em objetos como porta e vaso |
| Navegação | `W/A/S/D` + mouse + setas |
| Pelo menos 3 interações | Portas, cadeiras e interruptor |
| Iluminação | `GL_LIGHT0`–`GL_LIGHT3` |
| Materiais distintos | Madeira, tecido, metal, porcelana, vidro |
| Mapeamento de textura | Piso, mesas, cadeiras, porta e menu |
| Sem motor gráfico | OpenGL de função fixa direto |

---

## Resumo final

O projeto é organizado em torno de um loop simples e explícito:

```text
eventos → controles → interações → renderização → swap
```

Cada módulo tem uma responsabilidade clara. A câmera e a colisão compartilham o
mesmo espaço XZ; as interações guardam estado e animam alvos; a renderização
consulta esse estado e desenha a cena com OpenGL de função fixa. As posições das
cadeiras ficam em um único lugar, e as animações usam delta-time. Essas escolhas
mantêm o código didático sem abrir mão de um resultado visual completo.

# Cafeteria 3D - OpenGL

Projeto desenvolvido para a disciplina de Computação Gráfica.

A aplicação apresenta uma cafeteria 3D explorável, desenvolvida diretamente em C++ com OpenGL. O usuário pode caminhar pelo ambiente utilizando teclado e mouse, interagir com objetos e explorar diferentes áreas da cafeteria.

O projeto foi desenvolvido sem o uso de motores gráficos ou frameworks como Unity, Godot ou Three.js.

---

## Cenário

A cena representa o interior de uma cafeteria e possui uma área destinada aos clientes, um balcão de atendimento e um banheiro.

Os objetos principais foram modelados pela equipe utilizando primitivas geométricas e transformações do OpenGL.

Entre os elementos presentes na cena estão:

- mesas;
- cadeiras;
- balcão;
- vitrine de doces;
- máquina de café;
- registradora;
- prateleira;
- cardápio;
- luminárias;
- janela;
- porta principal;
- porta do banheiro;
- vaso sanitário;
- pia;
- espelho;
- xícara;
- vaso decorativo;
- porta-guardanapos;
- interruptor.

Não foram utilizados modelos 3D externos na composição dos objetos principais da cena.

---

## Funcionalidades

O projeto possui:

- navegação em primeira pessoa;
- movimentação utilizando W, A, S e D;
- controle da câmera utilizando o mouse;
- rotação da câmera pelas setas do teclado (alternativa ao mouse);
- sistema próprio de colisões;
- abertura e fechamento da porta principal;
- abertura e fechamento da porta do banheiro;
- movimentação individual das cadeiras;
- interruptor para ligar e desligar a iluminação;
- iluminação geral do ambiente;
- três luminárias com iluminação localizada;
- materiais diferentes para os objetos;
- mapeamento de texturas;
- animações suaves nas interações.

---

## Controles

| Tecla / Controle | Função |
|---|---|
| `W` | Mover para frente |
| `S` | Mover para trás |
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `Mouse` | Controlar a direção da câmera |
| `↑` / `↓` | Olhar para cima / para baixo |
| `←` / `→` | Girar a câmera para a esquerda / direita |
| `E` | Interagir com objetos próximos |
| `Esc` | Fechar a aplicação |

O cursor é capturado pela janela enquanto ela está em foco. Ao perder o foco, as teclas são liberadas automaticamente.

---

## Interações

### Porta principal

Ao se aproximar da porta principal e pressionar `E`, a porta abre ou fecha através de uma animação de rotação.

Quando a porta está fechada, a colisão impede que o jogador atravesse a entrada.

---

### Porta do banheiro

A porta do banheiro também pode ser aberta e fechada utilizando `E`.

A porta possui animação própria e colisão independente da porta principal.

Quando fechada, a passagem é bloqueada. Quando aberta, o jogador pode entrar no banheiro.

---

### Cadeiras

As seis cadeiras da cafeteria podem ser movimentadas individualmente.

Ao se aproximar de uma cadeira e pressionar `E`, ela é afastada da mesa.

Pressionando `E` novamente, a cadeira retorna à posição original.

A colisão acompanha o deslocamento de cada cadeira.

---

### Iluminação

A cafeteria possui um interruptor interativo.

Ao se aproximar dele e pressionar `E`, a iluminação pode ser ligada ou desligada.

Com a iluminação ligada, a cena utiliza uma iluminação geral combinada com três fontes de luz localizadas próximas às luminárias.

Quando a iluminação é desligada, permanece apenas uma iluminação ambiente muito fraca, permitindo que o usuário ainda consiga visualizar parcialmente o cenário.

---

## Técnicas utilizadas

### Modelagem

Os objetos foram modelados a partir da combinação de primitivas geométricas.

Objetos mais complexos foram construídos utilizando várias formas simples.

Alguns exemplos:

- a máquina de café utiliza corpo, painel frontal, display, botões, grupos, bandeja e vaporizador;
- a registradora possui base, tela, suporte, teclado e botão de confirmação;
- a vitrine possui estrutura, vidro, prateleiras e produtos;
- o vaso sanitário possui base, bacia, assento, caixa acoplada e tampa;
- a pia possui bancada, pedestal, cuba, ralo, torneira e registros;
- a porta do banheiro possui folha, batente, guarnições e maçanetas dos dois lados.

---

## Transformações geométricas

O projeto utiliza as três transformações exigidas:

### Translação

Utilizada para posicionar objetos no ambiente.

Exemplo:

```cpp
glTranslatef(x, y, z);
```

### Rotação

Utilizada na orientação dos objetos e também nas animações das portas.

Exemplo:

```cpp
glRotatef(
    angulo,
    0.0f,
    1.0f,
    0.0f
);
```

### Escala

Utilizada na modelagem de objetos como a porta e o vaso decorativo.

Exemplo:

```cpp
glScalef(
    escalaX,
    escalaY,
    escalaZ
);
```

---

## Iluminação

A iluminação foi implementada utilizando o sistema de iluminação do OpenGL.

A cena possui:

- iluminação ambiente;
- iluminação difusa;
- iluminação especular;
- atenuação da intensidade da luz;
- iluminação localizada;
- spotlights sobre as mesas.

São utilizadas as fontes:

```text
GL_LIGHT0
GL_LIGHT1
GL_LIGHT2
GL_LIGHT3
```

`GL_LIGHT0` funciona como iluminação geral do ambiente.

`GL_LIGHT1`, `GL_LIGHT2` e `GL_LIGHT3` representam as três luminárias posicionadas sobre as mesas.

---

## Materiais

Os objetos possuem diferentes propriedades de material.

Foram utilizados materiais para representar superfícies como:

- madeira;
- metal;
- plástico;
- vidro;
- porcelana;
- telas e displays.

São utilizadas propriedades como reflexão especular e `GL_SHININESS` para produzir diferentes respostas à iluminação.

---

## Texturas

O projeto utiliza mapeamento de textura em diferentes elementos da cena.

As texturas utilizadas estão armazenadas em:

```text
assets/texturas/
```

Arquivos:

```text
cadeira.bmp
menu.bmp
mesa.bmp
piso.bmp
porta.bmp
```

As texturas são carregadas através de um carregador BMP implementado no próprio projeto.

---

## Sistema de colisões

Foi desenvolvido um sistema próprio de colisões para impedir que a câmera atravesse determinados objetos.

Existem colisões com:

- paredes externas;
- paredes do banheiro;
- porta principal;
- porta do banheiro;
- mesas;
- cadeiras;
- balcão;
- vaso sanitário;
- pia.

As cadeiras possuem colisão dinâmica, ou seja, a região de colisão acompanha a posição da cadeira quando ela é movimentada.

---

## Câmera

A câmera utiliza navegação em primeira pessoa.

A posição do jogador é controlada pelas teclas `W`, `A`, `S` e `D`.

O mouse controla a rotação horizontal e vertical da câmera. Como a janela utiliza GLFW com o cursor capturado (`GLFW_CURSOR_DISABLED`), o movimento relativo funciona tanto em X11 quanto em Wayland.

As setas `←`, `→`, `↑` e `↓` também rotacionam a câmera e servem como alternativa caso o mouse não esteja disponível.

Também foi implementado deslizamento durante colisões. Dessa forma, quando o jogador tenta andar diagonalmente contra uma parede ou objeto, ainda é possível continuar o movimento pelo eixo que estiver livre.

---

## Estrutura do projeto

```text
cafeteria-opengl/
│
├── assets/
│   └── texturas/
│       ├── cadeira.bmp
│       ├── menu.bmp
│       ├── mesa.bmp
│       ├── piso.bmp
│       └── porta.bmp
│
├── src/
│   │
│   ├── Camera/
│   ├── Colisoes/
│   ├── Controles/
│   ├── Interacoes/
│   ├── Janela/
│   ├── Renderizacao/
│   ├── Sala/
│   ├── Texturas/
│   │
│   └── Objetos/
│       ├── Balcao/
│       ├── Cadeira/
│       ├── EspelhoBanheiro/
│       ├── Interruptor/
│       ├── JanelaCafe/
│       ├── Luminaria/
│       ├── MaquinaCafe/
│       ├── Menu/
│       ├── Mesa/
│       ├── PiaBanheiro/
│       ├── Porta/
│       ├── PortaBanheiro/
│       ├── PortaGuardanapos/
│       ├── Prateleira/
│       ├── Registradora/
│       ├── Vasinho/
│       ├── VasoSanitario/
│       ├── Vitrine/
│       └── Xicara/
│
├── CMakeLists.txt          # Opcional: compilação via CMake
├── Cafeteria3D.exe
└── README.md
```

---

## Requisitos para compilação

O projeto utiliza:

- C++ (C++14);
- OpenGL;
- GLFW 3.4 (camada de janela, entrada e contexto OpenGL);
- stb_image para carregamento de imagens;
- CMake;
- GCC / g++.

No Fedora, as dependências podem ser instaladas com:

```bash
sudo dnf install gcc-c++ cmake glfw-devel mesa-libGL-devel mesa-libGLU-devel
```

Em outras distribuições, instale os pacotes equivalentes de desenvolvimento de GLFW 3.4, OpenGL e GLU.

O compilador `g++` deve estar configurado no PATH de variáveis do seu SO.

Para verificar:

```powershell
g++ --version
```

---

## Como compilar com CMake (alternativa)

Além do método manual com `g++` apresentado abaixo, o projeto também pode ser compilado com **CMake**. Os dois métodos ficam disponíveis; escolha o que preferir.

### Requisitos para CMake

- CMake 3.20 ou superior;
- GCC / g++;
- OpenGL;
- GLFW 3.4 (o CMake procura com `find_package(glfw3 3.4 REQUIRED)`);
- Ninja (opcional).

Verifique as ferramentas:

```powershell
cmake --version
g++ --version
```

### Configurar e compilar com CMake

Execute os comandos a partir da pasta raiz do projeto:

```powershell
cmake -S . -B build 
cmake --build build
```

Para uma compilação Release:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Executar

No Windows:

```powershell
.\build\cafeteria_opengl.exe
```

No Linux:

```bash
./build/cafeteria_opengl
```

> Execute a partir da raiz do projeto: os caminhos de textura (`assets/texturas/...`) são relativos ao diretório de trabalho.

### Usar no CLion

1. Abra a pasta raiz do projeto no CLion.
2. Certifique-se de que o `CMakeLists.txt` esteja na raiz.
3. Configure um toolchain com MinGW ou outro compilador C++ compatível.
4. Aguarde a configuração do CMake e compile/executa o alvo `Cafeteria3D`.

> **Observação:** este método é adicional. O comando manual com `g++` continua disponível na seção seguinte. O CMake também precisa que os caminhos e nomes dos arquivos correspondam à estrutura real do projeto.

---

## Como compilar manualmente com g++

Na pasta raiz do projeto, no Linux:

```bash
mkdir -p build
g++ -std=c++14 $(find src -name '*.cpp') \
    -o build/cafeteria_opengl \
    $(pkg-config --cflags --libs glfw3) \
    -lGL -lGLU
```

Se a compilação terminar sem erros, o executável será criado em:

```text
build/cafeteria_opengl
```

---

## Como executar

No Linux, a partir da raiz do projeto:

```bash
./build/cafeteria_opengl
```

---

## Organização do código

### `Camera`

Responsável pela posição, movimentação e orientação da câmera.

### `Controles`

Responsável pela leitura das teclas e do movimento do mouse.

### `Interacoes`

Responsável pelo estado e pelas animações dos objetos interativos.

### `Colisoes`

Implementa as verificações de colisão da câmera com paredes e objetos.

### `Renderizacao`

Coordena a renderização da cena e contém primitivas utilizadas na modelagem.

### `Texturas`

Realiza o carregamento e gerenciamento das texturas BMP.

### `Sala`

Contém a estrutura principal da cafeteria.

### `Objetos`

Contém os diferentes objetos modelados para compor a cena.

---

## Requisitos atendidos

| Requisito | Implementação |
|---|---|
| Mínimo de 8 objetos modelados | Mais de 15 tipos de objetos modelados |
| Translação | `glTranslatef()` |
| Rotação | `glRotatef()` |
| Escala | `glScalef()` |
| Navegação | W/A/S/D + mouse (setas como alternativa) |
| Pelo menos 3 interações | Portas, cadeiras e iluminação |
| Iluminação | Luz geral + três luminárias |
| Materiais distintos | Madeira, metal, porcelana, plástico, vidro etc. |
| Mapeamento de textura | Piso, mesas, cadeiras, porta e cardápio |
| Sem motor gráfico | OpenGL utilizado diretamente |

---

## Equipe

- Leandro Marcio Elias da Silva
- Daniel de Araujo Albuquerque
- Guilherme Alessander da Silva Fernandes 

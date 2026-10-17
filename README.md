# ☕ Cafeteria 3D Interativa — OpenGL

Projeto desenvolvido para a atividade prática de **Modelagem 3D Interativa com OpenGL**.

A proposta é construir uma **cafeteria 3D explorável em primeira pessoa**, com ambiente realista, objetos modelados pela equipe, texturas, iluminação e interações simples com elementos da cena.

---

## 📌 Informações da atividade

**Disciplina:** Computação Gráfica / OpenGL  
**Equipe:** até 3 integrantes  
**Tema:** Livre  
**Tipo de projeto:** Ambiente 3D interativo / mini-experiência  
**Tecnologia principal:** OpenGL

### Requisitos obrigatórios

- [ ] No mínimo 8 objetos modelados pela equipe
- [ ] Translação
- [ ] Rotação
- [ ] Escala
- [ ] Navegação com W/A/S/D
- [ ] Controle de câmera com mouse
- [ ] Pelo menos 3 interações com objetos
- [ ] Iluminação
- [ ] Materiais distintos
- [ ] Mapeamento de textura
- [ ] README com instruções de compilação
- [ ] Relatório curto
- [ ] Vídeo de 2 a 4 minutos

---

# 🎯 Objetivo do projeto

Criar uma cafeteria 3D pequena e realista em que o usuário possa caminhar livremente pelo ambiente e interagir com alguns objetos.

A prioridade do projeto é:

- manter o código compreensível;
- facilitar a divisão do trabalho entre 3 pessoas;
- cumprir todos os requisitos da atividade;
- apresentar um ambiente visualmente bem acabado;
- evitar sistemas complexos desnecessários.

---

# 🏠 Dimensões da cafeteria

Escala adotada:

```text
1.0 unidade OpenGL = aproximadamente 1 metro
```

Dimensões principais:

```text
Largura:       12 m
Profundidade:   8 m
Altura:         3 m
```

Sistema de coordenadas sugerido:

```text
X = esquerda / direita
Y = altura
Z = frente / fundo
```

Limites aproximados da sala:

```text
X: -6 até +6
Y:  0 até +3
Z: -4 até +4
```

A origem `(0, 0, 0)` fica aproximadamente no centro da cafeteria.

---

# 🗺️ Organização do ambiente

Layout planejado:

```text
                         PAREDE DO FUNDO
┌────────────────────────────────────────────────────────────┐
│                     QUADRO / MENU                         │
│                                                          │
│ Máquina      Moedor       Pia       Geladeira  Banheiro  │
│                                                          │
│ BALCÃO DE ATENDIMENTO | VITRINE | CAIXA                 │
│                                                          │
│   ○      ○      ○      ○      ○      ○                   │
│                 Bancos altos                             │
│                                                          │
│       Mesa            Mesa            Mesa               │
│                                                          │
│ Mesa                                             Bancada │
│ janela                                            alta   │
│                                                          │
│ Mesa                                      Sofá           │
│ janela                                                   │
│                                                          │
│                       Entrada                            │
└────────────────────────────────────────────────────────────┘
```

---

# 📐 Medidas aproximadas dos objetos

| Objeto | Dimensão aproximada |
|---|---|
| Sala | 12 × 8 × 3 m |
| Porta principal | 1,4 × 2,2 m |
| Porta do banheiro | 0,8 × 2,1 m |
| Mesa | 1,2 × 0,8 × 0,75 m |
| Cadeira | 0,50 × 0,50 × 0,90 m |
| Balcão | 4,0 × 0,80 × 1,10 m |
| Vitrine | 1,5 × 0,80 × 1,20 m |
| Caixa | 1,0 × 0,80 × 1,10 m |
| Sofá | 2,0 × 0,80 × 0,90 m |
| Janela | aproximadamente 3 × 1,8 m |
| Quadro/Menu | aproximadamente 2,5 × 1,2 m |

Essas medidas são apenas referências e podem ser ajustadas durante o desenvolvimento.

---

# 🧱 Objetos planejados

Objetos que podem ser modelados pela equipe:

- [ ] Sala
- [ ] Balcão
- [ ] Vitrine
- [ ] Caixa
- [ ] Máquina de café
- [ ] Moedor
- [ ] Pia
- [ ] Geladeira
- [ ] Mesas
- [ ] Cadeiras
- [ ] Bancos altos
- [ ] Sofá
- [ ] Bancada alta
- [ ] Porta principal
- [ ] Porta do banheiro
- [ ] Quadro/Menu
- [ ] Janelas
- [ ] Luminárias
- [ ] Xícaras
- [ ] Objetos decorativos

> Objetos repetidos, como mesas e cadeiras, devem ser modelados uma única vez e reutilizados com diferentes transformações.

---

# 🕹️ Interações planejadas

O projeto deverá possuir pelo menos 3 interações.

### Porta principal

Ao se aproximar da porta e pressionar:

```text
E
```

A porta deverá abrir ou fechar através de uma **rotação**.

### Iluminação

O usuário poderá ligar ou desligar a iluminação principal da cafeteria.

```text
E → ligar/desligar luz
```

### Máquina de café

Ao se aproximar da máquina:

```text
E → ativar máquina
```

A interação pode:

- acender uma luz indicadora;
- alterar a cor de um LED;
- simular preparo de café;
- reproduzir uma pequena animação.

### Interações opcionais

- abrir/fechar porta do banheiro;
- ligar/desligar quadro luminoso;
- mover uma cadeira;
- abrir a geladeira;
- acender luz da vitrine.

---

# 🔄 Transformações

## Translação

Usada para:

- posicionar móveis;
- mover cadeiras;
- deslocar objetos interativos.

## Rotação

Usada para:

- abrir e fechar portas;
- orientar cadeiras;
- posicionar objetos em diferentes direções.

## Escala

Usada para:

- adaptar cubos e primitivas para formar mesas;
- criar paredes;
- criar balcões;
- ajustar móveis e objetos.

---

# 💡 Iluminação

A cafeteria deverá utilizar diferentes fontes de luz.

Sugestão:

- luz principal no teto;
- luzes pendentes sobre o balcão;
- iluminação da vitrine;
- iluminação ambiente;
- luz mais fraca próxima ao sofá.

Objetivo visual:

```text
Ambiente aconchegante
+
tons quentes
+
madeira
+
luz suave
+
contraste entre áreas claras e escuras
```

---

# 🎨 Materiais e texturas

Materiais planejados:

- madeira;
- metal;
- vidro;
- plástico;
- cerâmica;
- tecido.

Texturas sugeridas:

```text
parede
piso
madeira
metal
menu
vitrine
tecido
```

O quadro/menu poderá utilizar uma textura contendo os produtos da cafeteria.

---

# 👥 Divisão inicial da equipe

## Integrante 1

Responsabilidades:

- quadro/menu;
- mesas;
- cadeiras;
- porta;
- estrutura inicial da sala.

## Integrante 2

Responsabilidades sugeridas:

- balcão;
- vitrine;
- caixa;
- área do barista;
- objetos do balcão.

## Integrante 3

Responsabilidades sugeridas:

- iluminação;
- câmera;
- movimentação;
- interações;
- integração geral.

> A divisão pode ser alterada conforme o andamento do projeto.

Todos os integrantes devem entender o funcionamento geral da aplicação para a apresentação individual.

---

# 📁 Estrutura sugerida do projeto

```text
cafeteria-opengl/
│
├── README.md
├── .gitignore
│
├── src/
│   ├── main.cpp
│   │
│   ├── camera/
│   │   ├── Camera.cpp
│   │   └── Camera.h
│   │
│   ├── scene/
│   │   ├── Cafeteria.cpp
│   │   └── Cafeteria.h
│   │
│   ├── objects/
│   │   ├── Table.cpp
│   │   ├── Table.h
│   │   ├── Chair.cpp
│   │   ├── Chair.h
│   │   ├── Door.cpp
│   │   ├── Door.h
│   │   ├── Counter.cpp
│   │   └── Counter.h
│   │
│   ├── rendering/
│   │   ├── Texture.cpp
│   │   ├── Texture.h
│   │   ├── Lighting.cpp
│   │   └── Lighting.h
│   │
│   └── interactions/
│       ├── Interaction.cpp
│       └── Interaction.h
│
├── assets/
│   ├── textures/
│   │   ├── floor/
│   │   ├── walls/
│   │   ├── wood/
│   │   ├── metal/
│   │   └── menu/
│   │
│   └── models/
│
├── docs/
│   ├── relatorio/
│   ├── imagens/
│   └── referencias/
│
├── shaders/
│   ├── vertex_shader.glsl
│   └── fragment_shader.glsl
│
└── build/
```

> Se a implementação inicial utilizar OpenGL clássico/fixed pipeline, a pasta `shaders/` pode ser removida.

---

# 📍 Coordenadas da cena

As posições dos objetos serão definidas antes da integração.

Exemplo inicial:

```text
Mesa 1   = (-3.5, 0.0, 0.5)
Mesa 2   = ( 0.0, 0.0, 0.5)
Mesa 3   = ( 3.5, 0.0, 0.5)

Sofá     = ( 3.5, 0.0, 2.7)

Vitrine  = ( 2.9, 0.0,-2.7)
Caixa    = ( 4.3, 0.0,-2.7)
```

Essas coordenadas ainda poderão ser alteradas durante o desenvolvimento.

---

# ⌨️ Controles

| Tecla | Ação |
|---|---|
| W | mover para frente |
| S | mover para trás |
| A | mover para esquerda |
| D | mover para direita |
| Mouse | movimentar câmera |
| E | interagir |
| ESC | sair |

Controles adicionais poderão ser adicionados posteriormente.

---

# 🛠️ Compilação

As instruções definitivas serão atualizadas conforme a configuração das bibliotecas utilizadas.

Exemplo inicial para MinGW/Windows:

```bash
g++ src/main.cpp -o Cafeteria3D.exe -lopengl32 -lgdi32 -mwindows
```

Caso sejam utilizadas bibliotecas adicionais, como GLFW, GLUT, FreeGLUT, GLEW ou GLAD, o comando será atualizado.

---

# ▶️ Execução

Após compilar:

```bash
./Cafeteria3D.exe
```

No PowerShell:

```powershell
.\Cafeteria3D.exe
```

---

# 🌿 Organização das branches

Sugestão:

```text
main
│
├── develop
│
├── feature/sala
├── feature/mesas
├── feature/cadeiras
├── feature/porta
├── feature/menu
├── feature/balcao
├── feature/iluminacao
└── feature/interacoes
```

Fluxo recomendado:

```text
feature → develop → main
```

A branch `main` deve conter apenas versões estáveis.

---

# 📝 Padrão de commits

Sugestão de padrão:

```text
feat: adiciona modelo da mesa
feat: implementa abertura da porta
feat: adiciona textura de madeira

fix: corrige posição da cadeira
fix: corrige rotação da porta

refactor: reorganiza código da cafeteria

docs: atualiza README
```

---

# ✅ Checklist do projeto

## Ambiente

- [ ] Criar chão
- [ ] Criar paredes
- [ ] Criar teto
- [ ] Criar entrada
- [ ] Criar banheiro
- [ ] Criar janela

## Modelagem

- [ ] Mesa
- [ ] Cadeira
- [ ] Porta
- [ ] Quadro/Menu
- [ ] Balcão
- [ ] Vitrine
- [ ] Caixa
- [ ] Máquina de café
- [ ] Geladeira
- [ ] Sofá

## OpenGL

- [ ] Câmera
- [ ] WASD
- [ ] Mouse
- [ ] Texturas
- [ ] Iluminação
- [ ] Materiais
- [ ] Translação
- [ ] Rotação
- [ ] Escala

## Interações

- [ ] Porta
- [ ] Luz
- [ ] Máquina de café
- [ ] Interação extra

## Entrega

- [ ] Repositório organizado
- [ ] README
- [ ] Relatório
- [ ] Vídeo
- [ ] Teste final
- [ ] Preparar apresentação

---

# 📷 Screenshots

Adicionar imagens conforme o projeto evoluir em:

```text
docs/imagens/
```

Sugestões de nomes:

```text
cafeteria-inicial.png
cafeteria-iluminada.png
balcao.png
mesas.png
porta.png
```

---

# 🚧 Status

```text
Projeto em desenvolvimento.
```

### Etapa atual

- definição da planta;
- definição das dimensões;
- divisão inicial dos objetos;
- preparação da estrutura do repositório.

---

# 👨‍💻 Equipe

Adicionar nomes:

```text
Integrante 1:
Integrante 2:
Integrante 3:
```

---

# 📚 Observações

O projeto será desenvolvido sem motores gráficos como:

- Unity;
- Godot;
- Unreal Engine;
- Three.js.

A implementação será realizada diretamente com OpenGL e bibliotecas auxiliares permitidas pela disciplina.

Modelos externos, caso sejam utilizados, respeitarão o limite definido pela atividade e não serão contabilizados como objetos modelados pela equipe.

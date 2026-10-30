cmake_minimum_required(VERSION 3.20)
project(cafeteria_opengl)

set(CMAKE_CXX_STANDARD 14)

# Localiza as bibliotecas do OpenGL no sistema
find_package(OpenGL REQUIRED)

# Diretorios de inclusao
include_directories(src/Camera)
include_directories(src/Colisoes)
include_directories(src/Controles)
include_directories(src/Interacoes)
include_directories(src/Janela)
include_directories(src/Objetos/Balcao)
include_directories(src/Objetos/Cadeira)
include_directories(src/Objetos/EspelhoBanheiro)
include_directories(src/Objetos/Interruptor)
include_directories(src/Objetos/JanelaCafe)
include_directories(src/Objetos/Luminaria)
include_directories(src/Objetos/MaquinaCafe)
include_directories(src/Objetos/Menu)
include_directories(src/Objetos/Mesa)
include_directories(src/Objetos/PiaBanheiro)
include_directories(src/Objetos/Porta)
include_directories(src/Objetos/PortaBanheiro)
include_directories(src/Objetos/PortaGuardanapos)
include_directories(src/Objetos/Prateleira)
include_directories(src/Objetos/Registradora)
include_directories(src/Objetos/Vasinho)
include_directories(src/Objetos/VasoSanitario)
include_directories(src/Objetos/Vitrine)
include_directories(src/Objetos/Xicara)
include_directories(src/Renderizacao)
include_directories(src/Sala)
include_directories(src/Texturas)

# Executavel e arquivos fonte
add_executable(cafeteria_opengl
        src/Camera/camera.cpp
        src/Camera/camera.h
        src/Colisoes/colisoes.cpp
        src/Colisoes/colisoes.h
        src/Controles/controles.cpp
        src/Controles/controles.h
        src/Interacoes/interacoes.cpp
        src/Interacoes/interacoes.h
        src/Janela/janela.cpp
        src/Janela/janela.h
        src/Objetos/Balcao/balcao.cpp
        src/Objetos/Balcao/balcao.h
        src/Objetos/Cadeira/cadeira.cpp
        src/Objetos/Cadeira/cadeira.h
        src/Objetos/EspelhoBanheiro/espelho_banheiro.cpp
        src/Objetos/EspelhoBanheiro/espelho_banheiro.h
        src/Objetos/Interruptor/interruptor.cpp
        src/Objetos/Interruptor/interruptor.h
        src/Objetos/JanelaCafe/janela_cafe.cpp
        src/Objetos/JanelaCafe/janela_cafe.h
        src/Objetos/Luminaria/luminaria.cpp
        src/Objetos/Luminaria/luminaria.h
        src/Objetos/MaquinaCafe/maquina_cafe.cpp
        src/Objetos/MaquinaCafe/maquina_cafe.h
        src/Objetos/Menu/menu.cpp
        src/Objetos/Menu/menu.h
        src/Objetos/Mesa/mesa.cpp
        src/Objetos/Mesa/mesa.h
        src/Objetos/PiaBanheiro/pia_banheiro.cpp
        src/Objetos/PiaBanheiro/pia_banheiro.h
        src/Objetos/Porta/porta.cpp
        src/Objetos/Porta/porta.h
        src/Objetos/PortaBanheiro/porta_banheiro.cpp
        src/Objetos/PortaBanheiro/porta_banheiro.h
        src/Objetos/PortaGuardanapos/porta_guardanapos.cpp
        src/Objetos/PortaGuardanapos/porta_guardanapos.h
        src/Objetos/Prateleira/prateleira.cpp
        src/Objetos/Prateleira/prateleira.h
        src/Objetos/Registradora/registradora.cpp
        src/Objetos/Registradora/registradora.h
        src/Objetos/Vasinho/vasinho.cpp
        src/Objetos/Vasinho/vasinho.h
        src/Objetos/VasoSanitario/vaso_sanitario.cpp
        src/Objetos/VasoSanitario/vaso_sanitario.h
        src/Objetos/Vitrine/vitrine.cpp
        src/Objetos/Vitrine/vitrine.h
        src/Objetos/Xicara/xicara.cpp
        src/Objetos/Xicara/xicara.h
        src/Renderizacao/primitivas.cpp
        src/Renderizacao/primitivas.h
        src/Renderizacao/renderizador.cpp
        src/Renderizacao/renderizador.h
        src/Sala/sala.cpp
        src/Sala/sala.h
        src/Texturas/texturas.cpp
        src/Texturas/texturas.h
        src/main.cpp)

# Linkagem das bibliotecas OpenGL e GLU
target_link_libraries(cafeteria_opengl PRIVATE OpenGL::GL OpenGL::GLU)

# Copia a pasta assets para o diretorio onde o executavel e rodado (cmake-build-debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

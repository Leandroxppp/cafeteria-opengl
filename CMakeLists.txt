cmake_minimum_required(VERSION 3.20)
project(cafeteria_opengl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Localiza OpenGL e a camada de janela.
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)

# Inclui automaticamente todos os fontes de src/.
file(GLOB_RECURSE CAFETERIA_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(cafeteria_opengl ${CAFETERIA_SOURCES})

# Permite incluir arquivos como "Camera/camera.h" a partir de src/.
target_include_directories(cafeteria_opengl PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(cafeteria_opengl PRIVATE
        OpenGL::GL
        OpenGL::GLU
        glfw)

# Copia assets/ para junto do executavel, permitindo rodar de build/.
add_custom_command(TARGET cafeteria_opengl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                "$<TARGET_FILE_DIR:cafeteria_opengl>/assets")

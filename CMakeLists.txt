cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto
project(caso_final_integrador_3)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)

# Incluir directorios
include_directories(helper)

# Archivos fuente
add_executable(caso_final_integrador_3
        main.cpp
        helper/helper.cpp

)
add_executable(new_target
        main.cpp
        helper/helper.cpp
)

#include <iostream>
#include <string>
#include <cstdio>
#include "helper.h"

// Función para cargar un script desde un archivo
void load_script(const char *filename, bool show_script) {
    std::string script;
    FILE *file = nullptr;

    try {
        // Intentar abrir el archivo
        file = fopen(filename, "rb");
        if (!file) {
            std::perror("Error al abrir el archivo"); // Diagnóstico detallado
            return;
        }

        // Leer contenido del archivo
        char buffer[4001];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, 4000, file)) > 0) {
            buffer[bytesRead] = '\0';
            script.append(buffer);
        }

        // Verificar si ocurrió un error durante la lectura
        if (ferror(file)) {
            throw std::runtime_error("Error durante la lectura del archivo.");
        }

        fclose(file); // Cerrar archivo
        file = nullptr;

        // Mostrar el contenido del archivo si se solicita
        if (show_script) {
            std::cout << "\033[34m\033[47m"; // Color azul sobre fondo blanco
            std::cout << script << std::endl;
            std::cout << "\033[0m";         // Reset de colores
        }

        std::cout << "[INFO] El archivo fue cargado correctamente." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
        if (file) fclose(file); // Cerrar el archivo si está abierto
    } catch (...) {
        std::cerr << "Error desconocido durante la carga del archivo." << std::endl;
        if (file) fclose(file); // Cerrar el archivo si está abierto
    }
}

// Función para solicitar un archivo y cargarlo
void load_script() {
    char filename[500];

    std::cout << "Ingrese el nombre del archivo (con extensión): ";
    if (std::scanf("%499s", filename) != 1) {
        std::cerr << "Error al leer el nombre del archivo." << std::endl;
        return;
    }

    load_script(filename, true);
}

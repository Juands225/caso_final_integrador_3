#include <iostream>
#include <string>
#include <cstdio>
#include "helper.h"

using namespace std;

// Función para cargar un script desde un archivo
void load_script(const char *filename, bool show_script) {
    string script;
    FILE *file = nullptr;

    try {
        file = fopen(filename, "rb");
        if (!file) {
            cerr << "Error: No se pudo abrir el archivo '" << filename << "'." << endl;
            return;
        }

        char buffer[4001];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, 4000, file)) > 0) {
            buffer[bytesRead] = '\0';
            script.append(buffer);
        }

        if (ferror(file)) {
            throw runtime_error("Error durante la lectura del archivo.");
        }

        fclose(file);
        file = nullptr;

        if (show_script) {
            cout << "\033[34m\033[47m"; // Color azul sobre fondo blanco
            cout << script << endl;
            cout << "\033[0m";         // Reset de colores
        }

        cout << "[INFO] El archivo fue cargado correctamente." << endl;

    } catch (const exception &e) {
        cerr << "Excepción: " << e.what() << endl;
        if (file) fclose(file);
    } catch (...) {
        cerr << "Error desconocido durante la carga del archivo." << endl;
        if (file) fclose(file);
    }
}

// Función para solicitar un archivo y cargarlo
void load_script() {
    char filename[500];

    cout << "Ingrese el nombre del archivo: ";
    if (scanf("%499s", filename) != 1) {
        cerr << "Error al leer el nombre del archivo." << endl;
        return;
    }

    load_script(filename, true);
}

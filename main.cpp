#include <iostream>
#include "helper/helper.h"

int main() {
    try {
        std::cout << "=== Programa de Carga de Scripts ===" << std::endl;

        // Llamar a la función para cargar un script
        load_script();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido." << std::endl;
    }

    return 0;
}
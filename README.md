# caso_final_integrador_3
https://github.com/Juands225/caso_final_integrador_3.git
<details>
    <summary>TRABAJOS PRÁCTICOS</summary>
    
```
1. Carga de scripts en tiny-lisp
El módulo Labmain.cpp define la función load_script(), que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.

Implementa las funciones load_script() y load_script(filename, true) en CLion, de tal manera que puedas abrir y leer archivos de texto. El primer método toma el nombre de un archivo como entrada del usuario, mientras que el segundo muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.

void load_script(const char* filename, bool show_script = false);
void load_script();
2. Asegurando la robustez del código
Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada. Esto incluye, pero no se limita a:

El usuario proporciona un nombre de archivo que no existe.
El archivo proporcionado no se puede abrir por alguna razón.
Se produce un error de lectura durante la lectura del archivo.
Para manejar estos y otros errores potenciales, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.
```

</details>
<details>
    <summary>NOTAS</summary>

```
Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo _s). En cambio, deberías usar las funciones estándar de C/C++ 
disponibles en todas las plataformas y compiladores, como fopen, printf y scanf.
```

</details>
<details>
    <summary>RUBRICA</summary>
    
```
Carga de scripts (50 puntos)

Se proporciona una implementación correcta de load_script(const char* filename, bool show_script = false) que carga correctamente el archivo dado y muestra su contenido si show_script es verdadero. (25 puntos)
Se proporciona una implementación correcta de load_script() que solicita al usuario un nombre de archivo, llama a la función load_script(const char* filename, bool show_script = false) y maneja cualquier error de manera apropiada. (25 puntos)
Manejo de errores (50 puntos)

El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)
Total: 100 puntos
```

</details>
<details>
        <summary>PROPUESTA DE SOLUCION</summary>
    
```
## Propuesta de solución
En CLion, las funciones seguras de la biblioteca estándar de C (*_s funciones) generalmente no están disponibles porque estas son específicas de Microsoft y no son estándar de C/C++. Por lo tanto, en lugar de utilizar funciones como fopen_s, printf_s y scanf_s, puedes usar sus equivalentes no seguros, que son fopen, printf y scanf.

A continuación se muestra cómo se podría reescribir el código para CLion:

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
```

</details>
<details>
    <summary>FINAL</summary>
    
```
Este código debería compilar y funcionar en CLion sin necesidad de agregar la directiva _CRT_SECURE_NO_WARNINGS, ya que no se están utilizando las versiones seguras específicas de Microsoft de las funciones de la biblioteca estándar de C.

Por último, ten en cuenta que este código no realiza una comprobación completa de errores y no es robusto contra varios tipos de errores de entrada. Dependiendo de tu caso de uso específico, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.
```

</details>
<details>
    <summary>CORRECION DE GONZALO MULLER</summary>

```
1. Buffer Overflow en filename
Problema: La entrada para el nombre del archivo (scanf("%499s", filename)) podría desbordarse si el usuario introduce más de 499 caracteres.
Solución: Utilizar std::cin con std::string para manejar cadenas dinámicamente y evitar este riesgo.


2. Acceso fuera de límites en el buffer buf
Problema: El buffer buf de tamaño 4001 puede producir un acceso fuera de límites porque buf[c] = 0 no asegura que c esté dentro de los límites.
Solución: Asegurar que fread no lea más bytes de los esperados y usar script.append(buf, c) para evitar asignaciones incorrectas.


3. Colores no se restablecen
Problema: Los códigos de color ANSI (\033[34m y \033[47m) no se restablecen después de mostrar el script.
Solución: Añadir un código ANSI para restablecer los colores (\033[0m) al final del texto coloreado.


4. Fallo al cerrar el archivo
Problema: Si ocurre una excepción después de abrir el archivo, este podría no cerrarse debido a la falta de manejo adecuado de recursos.
Solución: Usar std::unique_ptr o try/finally para garantizar que el archivo se cierra.


5. Uso excesivo de catch genérico
Problema: El uso de catch (...) captura cualquier excepción, incluyendo las que no están relacionadas con la lectura del archivo, lo cual no siempre es deseado.
Solución: Manejar excepciones específicas, como std::ios_base::failure o errores relacionados con la E/S.


6. Duplicación de código para load_script
Problema: Hay dos funciones load_script, lo cual es redundante e innecesario.
Solución: Simplificar la lógica de load_script() para llamar internamente a la versión con argumentos.
```
</details>

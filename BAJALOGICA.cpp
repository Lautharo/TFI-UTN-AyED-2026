#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h> 
#include "BAJALOGICA.h"
#include "CAMPOS.h"
void realizarBajaLogica() {
    FILE *f;
    registro emp;
    int legajoBuscado;
    int encontrado = 0;
    char respuesta; 
    f = fopen("Campos.dat", "r+b");

    if (f == NULL) {
        printf("\nERROR: No se pudo abrir el archivo o no existen empleados cargados.\n");
        return;
    }

    printf("\n=== BAJA LOGICA DE EMPLEADO ===\n");
    printf("Ingrese el Legajo del empleado a dar de baja: ");
    scanf("%d", &legajoBuscado);

    // 2. Recorremos el archivo leyendo registro por registro
    while (fread(&emp, sizeof(registro), 1, f) == 1) {
        
        // Si el legajo coincide Y el empleado está activo
        if (emp.legajo == legajoBuscado && emp.activo == true) {
            
            // 3. Mostramos a quién encontramos (por seguridad)
            printf("\n--- Empleado Encontrado ---\n");
            printf("Nombre y apellido: %s\n", emp.nombreapell);
            printf("Area ID: %d\n", emp.area);
            
            printf("\nEsta seguro de darlo de baja? (s/n): ");
            fflush(stdin); // Limpiar buffer antes de leer char
            scanf("%c", &respuesta);

            if (respuesta == 's' || respuesta == 'S') {
                // 4. EL TRUCO: Retroceder el puntero
                // Como el fread avanzó, tenemos que volver 1 registro atrás
                // para escribir ENCIMA del que acabamos de leer.
                fseek(f, -((long)sizeof(registro)), SEEK_CUR);

                // 5. Modificamos el campo en memoria
                emp.activo = false; 

                // 6. Escribimos el registro modificado en el archivo
                fwrite(&emp, sizeof(registro), 1, f);
                
                printf("\n>>> El empleado fue dado de baja exitosamente.\n");
            } else {
                printf("\nOperacion cancelada por el usuario.\n");
            }
            encontrado = 1;
            break; // Ya lo encontramos, salimos del while
        }
    }
    if (encontrado == 0) {
        printf("\nNo se encontro ningun empleado activo con el Legajo %d.\n", legajoBuscado);
    }

    fclose(f);
    system("pause");
}

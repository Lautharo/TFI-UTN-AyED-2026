#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h> 
#include "BAJALOGICA.h"
#include "CAMPOS.h"
void realizarBajaLogica() {
    FILE *m;
    reg r;
    int legajoBuscado;
    int encontrado = 0;
    char respuesta; 
    m = fopen("Campos.dat", "r+b");

    if (m == NULL) {
        printf("\nERROR: No se pudo abrir el archivo o no existen empleados cargados.\n");
        return;
    }

    printf("\n=== BAJA LOGICA DE EMPLEADO ===\n");
    printf("Ingrese el Legajo del empleado a dar de baja: ");
    scanf("%d", &legajoBuscado);

    // 2. Recorremos el archivo leyendo registro por registro
    while (fread(&r, sizeof(reg), 1, m) == 1) {
        
        // Si el legajo coincide Y el empleado está activo
        if (r.legajo == legajoBuscado && r.activo == true) {
            
            // 3. Mostramos a quién encontramos (por seguridad)
            printf("\n--- Empleado Encontrado ---\n");
            printf("Nombre y apellido: %s\n", r.nombreapell);
            printf("Area ID: %d\n", r.area);
            
            printf("\nEsta seguro de darlo de baja? (s/n): ");
            fflush(stdin); // Limpiar buffer antes de leer char
            scanf("%c", &respuesta);

            if (respuesta == 's' || respuesta == 'S') {
                // Como el fread avanzó, tenemos que volver 1 registro atrás
                // para escribir ENCIMA del que acabamos de leer.
                fseek(m, -((long)sizeof(reg)), SEEK_CUR);

                // 5. Modificamos el campo en memoria
                r.activo = false; 

                // 6. Escribimos el registro modificado en el archivo
                fwrite(&r, sizeof(reg), 1, m);
                
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

    fclose(m);
    system("pause");
}

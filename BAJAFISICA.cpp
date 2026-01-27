#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h> 
#include <string.h>
#include "BAJAFISICA.h"
#include "CAMPOS.h"

void realizarBajaFisica()
{
	struct registro r;
    FILE *archivoOriginal;
    FILE *archivoTemporal;
    
    int legajoBuscado;
    int encontrado =0;
    char confirmacion;

   
    archivoOriginal = fopen("campos.dat", "rb");
    
    archivoTemporal = fopen("temp.dat", "wb");

    if (archivoOriginal == NULL || archivoTemporal == NULL)
    {
        printf("Error: No se pudo abrir el archivo original o crear el temporal.");
        if (archivoOriginal != NULL) fclose(archivoOriginal); 
        return;
    }

    system("CLS");
    printf("==================== BAJA FISICA DE EMPLEADO (IRREVERSIBLE) ====================\n\n");
    
    printf("Ingrese el Legajo a eliminar: ");
    scanf("%d", &legajoBuscado);

    fread(&r, sizeof(struct registro), 1, archivoOriginal);

    while (!feof(archivoOriginal))
    {
        if (r.legajo == legajoBuscado)
        {
            printf("\n--- Empleado a eliminar ---\n");
            printf("Nombre: %s\n", r.nombreapell);
            printf("Sueldo: %d\n", r.sueldo);
            
            printf("\nEsta seguro? Se borrara definitivamente (s/n): ");
            _flushall();
            confirmacion = getch();

            if (confirmacion == 's' || confirmacion == 'S')
            {
                printf("\n>>> Registro eliminado del nuevo archivo.\n");
                encontrado = 1; 
            }
            else
            {
                fwrite(&r, sizeof(struct registro), 1, archivoTemporal);
                printf("\nOperacion cancelada. El registro se mantiene.\n");
            }
        }
        else
        {
            fwrite(&r, sizeof(struct registro), 1, archivoTemporal);
        }

        fread(&r, sizeof(struct registro), 1, archivoOriginal);
    }

    fclose(archivoOriginal);
    fclose(archivoTemporal);

    if (encontrado == 1)
    {
        if (remove("campos.dat") == 0) 
        {
            rename("temp.dat", "campos.dat");
            printf("\nEXITO: Archivo actualizado correctamente.");
        }
        else
        {
            printf("\nERROR: No se pudo borrar el original. Revise permisos.");
        }
    }
    else
    {
        remove("temp.dat");
        if (confirmacion != 'n' && confirmacion != 'N')
             printf("\nNo se encontro el legajo ingresado.");
    }

    getch();
}
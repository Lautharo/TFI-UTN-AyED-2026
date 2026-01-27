#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h>
#include "ALTA.h"
#include "CAMPOS.h" // Necesario para reconocer 'struct registro'

void grabarInformacion()
{
    struct registro r;
    FILE *archivo;
    
    // IMPORTANTE: "ab" significa Append Binary (Agregar al final)
    // Si usas "w+b" aquí, borrarías todo cada vez que agregues uno nuevo.
    archivo = fopen("campos.dat", "ab"); 
    
    if (archivo == NULL)
    {
        printf("\n[X] Error: No se pudo abrir el archivo de empleados.\n");
        return; // Salimos si falla
    }
    
    char opcion = 's';
    
    while (opcion == 's' || opcion == 'S')
    {
        system("cls");
        printf("=== ALTA DE NUEVO EMPLEADO (AGREGAR) ===\n\n");

        printf("Ingrese Nombre y Apellido: ");
        _flushall(); 
        gets(r.nombreapell);

        printf("Ingrese Edad: ");
        scanf("%d", &r.edad);

        printf("Ingrese Sueldo: ");
        scanf("%d", &r.sueldo);

        printf("Ingrese Puesto: ");
        _flushall();
        gets(r.puesto);

        printf("Ingrese Turno: ");
        _flushall();
        gets(r.turno);

        printf("Ingrese Sexo: ");
        _flushall();
        gets(r.sexo);

        printf("Ingrese Area: ");
        _flushall();
        gets(r.area); 
    
        // Guardamos el registro al final del archivo
        fwrite(&r, sizeof(struct registro), 1, archivo);
        
        printf("\n[!] Empleado agregado exitosamente.\n");
        printf("Desea agregar otro? (s/n): ");
        opcion = getch();
    }
    
    fclose(archivo);
}
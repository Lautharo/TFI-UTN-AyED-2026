#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h>
#include "CAMPOS.h"

void carga_empleados()
{
	reg r;
	FILE*m;
	m =fopen("campos.dat","wb");
	
	char opcion='s';
	
	if (m == NULL)
    {
        printf("Error: No se pudo crear el archivo.");
    }
    
    while (opcion == 's'||opcion == 'S')
    {
    	printf("=== INGRESO DE DATOS DE EMPLEADO ===\n\n");

        // Ingreso de Nombre y Apellido (Cadena con espacios)
        printf("Ingrese Nombre y Apellido: ");
        _flushall(); 
        gets(r.nombreapell);
        // Ingreso de Legajo)
        printf("Ingrese Legajo: ");
        scanf("%d", &r.legajo);
        // Ingreso de Edad)
        printf("Ingrese Edad: ");
        scanf("%d", &r.edad);

        // Ingreso de Sueldo
        printf("Ingrese Sueldo: ");
        scanf("%d", &r.sueldo);

        // Ingreso de Puesto
        printf("Ingrese Puesto: ");
        _flushall();
        gets(r.puesto);

        // Ingreso de Turno
        printf("Ingrese Turno: ");
        _flushall();
        gets(r.turno);

        // Ingreso de Sexo
        printf("Ingrese Sexo: ");
        _flushall();
        gets(r.sexo);

        // Ingreso de Area
        printf("Ingrese Area: ");
        _flushall();
        gets(r.area); 
    
	
	    
        fwrite(&r, sizeof(struct reg), 1, m);
        printf("\nregistro guardado exitosamente.\n");
        printf("Desea ingresar otro empleado? (s/n): ");
        opcion = getch();
	}
	fclose(m);
	printf("\n\nCarga finalizada.");
    getch();

	
}
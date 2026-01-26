#ifndef CAMPOS_H
#define CAMPOS_H

// Estructura para guardar en el archivo
struct registro
{
   char nombreapell[60];
	char puesto[10];
	int sueldo, edad;
	char turno[10];
	char sexo[10];
	char area[10];
};
void carga_empleados();
#endif
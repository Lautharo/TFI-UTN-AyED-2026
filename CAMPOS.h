#ifndef CAMPOS_H
#define CAMPOS_H

struct registro
{
    char nombreapell[60];
    int legajo;
	char puesto[10];
    int sueldo, edad;
    char turno[10];
    char sexo[10];
    char area[10];    
    bool activo; // true = visible, false = borrado logicamente
};
void carga_empleados();
void modificarEmpleado();
#endif
#ifndef CAMPOS_H
#define CAMPOS_H

struct registro
{
    char nombreapell[60];
    char puesto[10];
    int sueldo, edad;
    char turno[10];
    char sexo[10];
    char area[10];
    
    // CAMBIO IMPORTANTE: Agregamos este campo
    bool activo; // true = visible, false = borrado logicamente
};

void carga_empleados();

#endif
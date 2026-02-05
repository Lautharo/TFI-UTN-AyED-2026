#ifndef CAMPOS_H
#define CAMPOS_H

struct reg {
    char nombreapell[60];
    int legajo;
    char puesto[20]; // Aumente un poco por si acaso
    int sueldo, edad;
    char turno[10];
    char sexo[15];
    char area[20];    
    bool activo; 
};

void carga_empleados();
// void modificarEmpleado(); // Descomenta cuando lo tengas
#endif
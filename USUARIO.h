#ifndef USUARIO_H
#define USUARIO_H

// Estructura para guardar en el archivo
struct User {
    char usuario[11];       // 10 chars
    char contrasenia[35];   // 32 chars
    char apeNom[61];        // Nombre y Apellido
    int rol;                // 1:Admin, 2: Supervisor. 
    bool activo;            // Para dar de baja sin borrar
};

// Prototipos de funciones
void regUser(); 
bool UserVal(char u[]);
bool ContraVal(char c[]);
void capContra(char pass[]);
bool iniciarSesion(char usuarioLogueado[]);
#endif
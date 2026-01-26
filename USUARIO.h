#ifndef USUARIO_H
#define USUARIO_H

// Estructura para guardar en el archivo
struct Usuario {
    char usuario[11];       // 10 chars
    char contrasenia[35];   // 32 chars
    char apeNom[61];        // Nombre y Apellido
    int rol;                // 1:Admin, 2: Supervisor. 
    bool activo;            // Para dar de baja sin borrar
};

// Prototipos de funciones
void registrarUsuario(); 
bool esUsuarioValido(char u[]);
bool esContraseniaValida(char c[]);
void capturarContrasenia(char pass[]);

#endif
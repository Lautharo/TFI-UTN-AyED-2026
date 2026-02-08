#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h> 
#include "USUARIO.h"
#include "MENU.h"

// --- FUNCION 1: Validar el Nombre de Usuario ---
// Reglas: Min 6, Max 10. Comienza minúscula. Min 2 Mayúsculas. Max 3 Digitos.
bool UserVal(char u[]) {
    int len = strlen(u);
    int mayusculas = 0;
    int digitos = 0;

    // 1. Validar longitud
    if (len < 6 || len > 10) {
        printf("\n[X] Error: El usuario debe tener entre 6 y 10 caracteres.\n");
        return false;
    }

    // 2. Validar que comience con minúscula
    if (!islower(u[0])) {
        printf("\n[X] Error: El usuario debe comenzar con una letra minuscula.\n");
        return false;
    }

    // 3. Contar mayúsculas y dígitos
    for (int i = 0; i < len; i++) {
        if (isupper(u[i])) mayusculas++;
        if (isdigit(u[i])) digitos++;
        
        // Validar que solo sean letras o números (opcional pero recomendado)
        if (!isalnum(u[i])) {
            printf("\n[X] Error: Solo se permiten letras y numeros.\n");
            return false;
        }
    }

    if (mayusculas < 2) {
        printf("\n[X] Error: Debe tener al menos 2 mayusculas.\n");
        return false;
    }
    if (digitos > 3) {
        printf("\n[X] Error: No puede tener mas de 3 digitos.\n");
        return false;
    }

    return true; // Si pasó todo, es válido
}

// --- FUNCION 2: Validar la Contraseña ---
// Reglas: Min 6 chars. Al menos 1 mayus, 1 minus, 1 digito.
// NO puede tener caracteres consecutivos ascendentes (ej: abc, 123, BCD).
bool ContraVal(char c[]) {
    int len = strlen(c);
    bool tieneMay = false;
    bool tieneMin = false;
    bool tieneDig = false;

    // 1. Longitud
    if (len < 6 || len > 32) {
        printf("\n[X] Error: La contrasenia debe tener entre 6 y 32 caracteres.\n");
        return false;
    }

    // 2. Verificación de contenido y Consecutivos
    for (int i = 0; i < len; i++) {
        if (isupper(c[i])) tieneMay = true;
        if (islower(c[i])) tieneMin = true;
        if (isdigit(c[i])) tieneDig = true;

        // VERIFICACION DE CONSECUTIVOS
        // Comparamos el caracter actual con el siguiente
        if (i < len - 1) {
            // Si el siguiente es igual al actual + 1 (ej: 'b' es 'a'+1)
            if (c[i+1] == c[i] + 1) {
                printf("\n[X] Error: No se permiten caracteres consecutivos (ej: abc, 123).\n");
                return false;
            }
        }
    }

    if (!tieneMay || !tieneMin || !tieneDig) {
        printf("\n[X] Error: Debe tener al menos 1 Mayuscula, 1 Minuscula y 1 Numero.\n");
        return false;
    }

    return true;
}

// --- FUNCION 3: Captura con asteriscos ---
void capContra(char pass[]) {
    char caracter;
    int i = 0;
    
    while (true) {
        caracter = getch(); // Captura tecla sin mostrarla
        
        if (caracter == 13) { // Si es ENTER
            pass[i] = '\0';
            break;
        } 
        else if (caracter == 8) { // Si es BACKSPACE (borrar)
            if (i > 0) {
                i--;
                printf("\b \b"); // Borra visualmente el asterisco
            }
        }
        else {
            if (i < 32) {
                pass[i] = caracter;
                printf("*"); // Muestra asterisco
                i++;
            }
        }
    }
}

// --- FUNCION PRINCIPAL DE REGISTRO ---
void regUser() {
    User r;
    FILE *m;

    system("cls");
    printf("=== REGISTRO DE NUEVO USUARIO ===\n");

    // 1. Pedir Usuario
    do {
        printf("\nUsuario (Min 6-10, Inicio minuscula, 2 Mayus, Max 3 num): ");
        _flushall();
        gets(r.usuario);
    } while (!UserVal(r.usuario));

    // 2. Pedir Contraseña
    do {
        printf("\nContrasenia (Min 6, Mayus+Minus+Num, No consecutivos): ");
        capContra(r.contrasenia);
        printf("\n");
    } while (!ContraVal(r.contrasenia));

    // 3. Pedir Nombre Real
    printf("\nNombre y Apellido del empleado: ");
    _flushall();
    gets(r.apeNom);
    
    setUsuarioActual(r.apeNom);
    
    r.rol = 2; // Por defecto rol normal
    r.activo = true;

    // 4. Guardar en archivo
    m = fopen("Usuarios.dat", "ab"); // "ab" para agregar al final
    if (m == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(&r, sizeof(User), 1, m	);
    fclose(m);

    printf("\n[!] Usuario registrado con exito!\n");
    system("pause");
}
// --- FUNCION 4: Iniciar Sesion ---
bool iniciarSesion(char usuarioLogueado[]) {
    FILE *f;
    User u; 
    char userIngresado[11];
    char passIngresado[35];
    bool encontrado = false;

    // 1. Verificamos si existe el archivo. Si no, creamos un admin por defecto.
    f = fopen("Usuarios.dat", "rb");
    if (f == NULL) {
        printf("\n[!] Archivo de usuarios no encontrado.\n");
        printf("[!] Creando usuario administrador por defecto...\n");
        
        f = fopen("Usuarios.dat", "wb");
        User admin;
        // OJO: Este admin quizas no cumpla tus reglas de validacion (mayusculas etc)
        // pero como lo grabamos directo, funciona igual.
        strcpy(admin.usuario, "admin01"); 
        strcpy(admin.contrasenia, "Admin123"); 
        strcpy(admin.apeNom, "Administrador Sistema");
        admin.rol = 1; // Rol de Admin
        admin.activo = true;
        
        fwrite(&admin, sizeof(User), 1, f);
        fclose(f);
        
        printf("[!] Usuario 'admin01' creado. Clave: 'Admin123'\n");
        system("pause");
        
        f = fopen("Usuarios.dat", "rb"); // Lo volvemos a abrir para leer
    }

    system("cls");
    printf("========================================\n");
    printf("         INICIO DE SESION YPF           \n");
    printf("========================================\n");

    // 2. Pedimos los datos
    printf("Usuario: ");
    _flushall();
    gets(userIngresado);

    printf("Contrasenia: ");
    capContra(passIngresado); // Usamos tu funcion de asteriscos
    printf("\n");

    // 3. Buscamos en el archivo
    rewind(f);
    while (fread(&u, sizeof(User), 1, f) == 1) {
        // Comparamos Usuario, Contraseña y que esté Activo
        if (strcmp(userIngresado, u.usuario) == 0 && 
            strcmp(passIngresado, u.contrasenia) == 0 && 
            u.activo == true) {
            
            encontrado = true;
            strcpy(usuarioLogueado, u.usuario); // Devolvemos el nombre de usuario
            // Opcional: Si necesitas el nombre real en el main, copia u.apeNom
            break; 
        }
    }

    fclose(f);

    if (encontrado) {
        printf("\n>>> Bienvenido al sistema!\n");
        system("pause");
        return true;
    } else {
        printf("\n[X] Error: Usuario o clave incorrectos.\n");
        system("pause");
        return false;
    }
}




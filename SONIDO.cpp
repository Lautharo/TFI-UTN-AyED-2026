#include <windows.h>
#include <mmsystem.h> // Librería multimedia de Windows
#include <stdio.h>
#include "SONIDO.h"

// Variable interna para saber si ya cargamos la cancion
int musicaCargada = 0;

void iniciarMusica() {
    // Comando MCI para abrir y reproducir en loop
    // "fondo.mp3" es el nombre del archivo. "Alias musica" es el nombre clave para controlarla.
    mciSendString("open \"fondo.mp3\" type mpegvideo alias musica", NULL, 0, NULL);
    mciSendString("play musica repeat", NULL, 0, NULL);
    musicaCargada = 1;
}

void detenerMusica() {
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);
    musicaCargada = 0;
}

// Función interruptor: Si está prendida la apaga, y viceversa
void toggleMusica(int *estado) {
    if (*estado == 1) {
        // Estaba prendida, la apagamos (Pausa)
        mciSendString("pause musica", NULL, 0, NULL);
        *estado = 0;
    } else {
        // Estaba apagada
        if (musicaCargada == 0) {
            iniciarMusica(); // Si nunca arrancó, cargarla
        } else {
            mciSendString("resume musica", NULL, 0, NULL); // Si estaba pausada, continuar
        }
        *estado = 1;
    }
}
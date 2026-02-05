// MENU.h
#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
using namespace std;

// Prototipo de la funcion
int mostrarMenuPrincipal();
int mostrarSubMenu(string titulo, const vector<string> &opciones);
#endif
#ifndef MENU_H
#define MENU_H

#include "estructuras.h"

int mostrarMenuPrincipal();
int mostrarMenuGestion();
int mostrarMenuUsuarios();
int mostrarMenuSitios();
int mostrarMenuEspacios();
int mostrarMenuEventos();
int mostrarMenuEstadoEvento();
int mostrarMenuFacturas();
int mostrarMenuEstadisticas();
void ObtenerDatosSitioManual(char *nombre, char *ubicacion, char *sitioWeb);

#endif

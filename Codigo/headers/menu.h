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

/*
 * loginAdmin
 * Objetivo:    Solicitar usuario y contraseña para acceder
 *              al menu administrativo. Reintenta hasta 3 veces.
 * Entrada:     void
 * Salida:      1 si el login es exitoso, 0 si falla 3 intentos
 */
int loginAdmin(void);

#endif

#ifndef MENU_H
#define MENU_H

#include "estructuras.h"

/*
 * mostrarMenuPrincipal
 * Objetivo:    Mostrar el menu raiz con opciones Administrativa/General/Salir.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuPrincipal();

/*
 * mostrarMenuGestion
 * Objetivo:    Menu administrativo con accesos a gestion de sitios, espacios,
 *              eventos, estado, facturas y estadisticas.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuGestion();

/*
 * mostrarMenuUsuarios
 * Objetivo:    Menu general para consultas y compra de boletos.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuUsuarios();

/*
 * mostrarMenuSitios
 * Objetivo:    Menu de acciones sobre sitios de eventos.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuSitios();

/*
 * mostrarMenuEspacios
 * Objetivo:    Menu para administrar sectores/asientos de un sitio.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuEspacios();

/*
 * mostrarMenuEventos
 * Objetivo:    Menu de creacion, listado y consulta de eventos.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuEventos();

/*
 * mostrarMenuEstadoEvento
 * Objetivo:    Menu para ver resumen, recaudacion y asientos de un evento.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuEstadoEvento();

/*
 * mostrarMenuFacturas
 * Objetivo:    Menu de listado y detalle de facturas.
 * Entrada:     nada
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuFacturas();

/*
 * mostrarMenuEstadisticas
 * Objetivo:    Menu para acceder a reportes estadisticos.
 * Entrada:     void
 * Salida:      opcion seleccionada (int)
 */
int mostrarMenuEstadisticas();

/*
 * ObtenerDatosSitioManual
 * Objetivo:    Pedir por consola los datos de un sitio (nombre, ubicacion, web).
 * Entrada:     buffers de salida nombre, ubicacion, sitioWeb
 * Salida:      nada (llena los buffers)
 */
void ObtenerDatosSitioManual(char *nombre, char *ubicacion, char *sitioWeb);

/*
 * loginAdmin
 * Objetivo:    Solicitar usuario y contraseña para acceder
 *              al menu administrativo. Reintenta hasta 3 veces.
 * Entrada:     nada
 * Salida:      1 si el login es exitoso, 0 si falla 3 intentos
 */
int loginAdmin(void);

#endif

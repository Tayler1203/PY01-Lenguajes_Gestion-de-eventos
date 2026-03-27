#ifndef ESPACIOS_H
#define ESPACIOS_H

#include "estructuras.h"

/*
 * mostrarSitiosConSectores
 * Objetivo:    Listar todos los sitios con sus sectores,
 *              cantidad de espacios y numeracion de asientos.
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      nada (imprime en consola)
 */
void mostrarSitiosConSectores(const AppData *app);

/*
 * agregarSector
 * Objetivo:    Solicitar nombre, cantidad de espacios e inicial,
 *              generar los asientos automaticamente con la forma
 *              Inicial# (ej. A1, A2...) y agregar el sector al
 *              sitio indicado.
 * Entrada:     sitio - puntero al SitioEvento a modificar
 * Salida:      nada (modifica sitio->sectores por referencia)
 * Restriccion: La inicial debe ser un caracter alfabetico
 */
void agregarSector(SitioEvento *sitio);

/*
 * resetEspaciosSitio
 * Objetivo:    Marcar todos los asientos de todos los sectores
 *              del sitio como DISPONIBLE.
 * Entrada:     sitio - puntero al SitioEvento a resetear
 * Salida:      nada (modifica asientos por referencia)
 * Restriccion: Solicita confirmacion antes de ejecutar
 */
void resetEspaciosSitio(SitioEvento *sitio);

/*
 * gestionarEspaciosSitio
 * Objetivo:    Flujo completo para seleccionar un sitio y
 *              administrar sus sectores.
 *              Muestra sitios, permite seleccionar uno, luego
 *              permite agregar sectores o hacer reset.
 * Entrada:     app - puntero a AppData
 * Salida:      nada
 */
void gestionarEspaciosSitio(AppData *app);

#endif

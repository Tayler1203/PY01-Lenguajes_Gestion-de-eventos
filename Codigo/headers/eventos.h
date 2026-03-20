#ifndef EVENTOS_H
#define EVENTOS_H

#include "estructuras.h"

/*
 * crearEvento
 * Objetivo:    Solicitar nombre, productora, fecha y sitio;
 *              luego pedir el monto por asiento para cada
 *              sector del sitio elegido.
 * Entrada:     app - puntero a AppData
 * Salida:      void (agrega evento a app->eventos)
 * Restriccion: El sitio debe existir previamente en el sistema
 */
void crearEvento(AppData *app);

/*
 * mostrarEstadoEvento
 * Objetivo:    Para un evento seleccionado mostrar: nombre,
 *              productora, sitio, fecha, monto por sector,
 *              monto recaudado por sector y estado de cada
 *              asiento.
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void mostrarEstadoEvento(const AppData *app);

/*
 * consultarEventosFuturos
 * Objetivo:    Solicitar una fecha inicial y listar los eventos
 *              cuya fecha sea mayor o igual, ordenados
 *              ascendentemente.
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void consultarEventosFuturos(const AppData *app);

/*
 * mostrarDetalleEvento
 * Objetivo:    Para un evento dado mostrar: nombre, productora,
 *              sitio web, fecha, monto por sector y cantidad de
 *              asientos disponibles por sector.
 * Entrada:     evento - puntero al Evento a mostrar
 * Salida:      void (imprime en consola)
 */
void mostrarDetalleEvento(const Evento *evento);

/*
 * seleccionarEvento
 * Objetivo:    Mostrar lista numerada de eventos y retornar
 *              el elegido por el usuario.
 * Entrada:     app - puntero a AppData
 * Salida:      puntero al Evento seleccionado,
 *              NULL si el usuario cancela
 */
Evento *seleccionarEvento(const AppData *app);

#endif

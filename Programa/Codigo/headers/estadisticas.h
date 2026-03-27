#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "estructuras.h"

/*
 * topMesesConMasEventos
 * Objetivo:    Agrupar eventos por mes-anio, ordenar de mayor
 *              a menor y mostrar el top 3 (RF-18).
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void topMesesConMasEventos(const AppData *app);

/*
 * topProductorasPorRecaudacion
 * Objetivo:    Acumular recaudacion por productora usando las
 *              facturas, ordenar de mayor a menor y mostrar
 *              el top 3 (RF-19).
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void topProductorasPorRecaudacion(const AppData *app);

/*
 * reporteSitiosPorRecaudacion
 * Objetivo:    Por cada sitio calcular cantidad de eventos y
 *              monto total recaudado; mostrar ordenado de mayor
 *              a menor recaudacion (RF-20).
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void reporteSitiosPorRecaudacion(const AppData *app);

#endif

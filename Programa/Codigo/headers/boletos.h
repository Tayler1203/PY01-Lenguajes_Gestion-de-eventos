#ifndef BOLETOS_H
#define BOLETOS_H

#include "estructuras.h"

/*
 * comprarBoletos
 * Objetivo:    Flujo completo de compra: seleccionar evento,
 *              mostrar asientos disponibles por sector, permitir
 *              seleccion multiple, verificar disponibilidad,
 *              solicitar cedula y nombre, generar y mostrar
 *              factura.
 * Entrada:     app - puntero a AppData
 * Salida:      nada (agrega factura a app->facturas y marca
 *              asientos como VENDIDO)
 */
void comprarBoletos(AppData *app);

/*
 * verificarDisponibilidad
 * Objetivo:    Comprobar que todos los asientos en el arreglo
 *              dado tienen estado DISPONIBLE.
 * Entrada:     asientos  - arreglo de punteros a Asiento
 *              cantidad  - numero de asientos a verificar
 * Salida:      1 si todos estan disponibles, 0 si alguno no
 */
int verificarDisponibilidad(Asiento **asientos, int cantidad);
#endif

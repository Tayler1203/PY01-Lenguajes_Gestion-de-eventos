#ifndef FACTURACION_H
#define FACTURACION_H

#include "estructuras.h"

/*
 * generarFactura
 * Objetivo:    Crear la Factura con todos sus campos, calcular
 *              subtotal, costo de servicio (5%) y total,
 *              marcar asientos como VENDIDO y agregar la
 *              factura a app->facturas.
 * Entrada:     app       - puntero a AppData
 *              evento    - puntero al Evento comprado
 *              asientos  - arreglo de punteros a Asiento
 *              sectores  - arreglo de punteros a SectorEvento
 *                          paralelo a asientos[]
 *              cantidad  - numero de asientos comprados
 *              cedula    - cedula del comprador
 *              nombre    - nombre del comprador
 * Salida:      void (modifica app->facturas y asientos)
 */
void generarFactura(AppData *app, Evento *evento,
                    Asiento **asientos, SectorEvento **sectores,
                    int cantidad,
                    const char *cedula, const char *nombre);

#endif

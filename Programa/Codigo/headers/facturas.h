#ifndef FACTURAS_H
#define FACTURAS_H

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
 * Salida:      nada (modifica app->facturas y asientos)
 */
void generarFactura(AppData *app, Evento *evento,
					Asiento **asientos, SectorEvento **sectores,
					int cantidad,
					const char *cedula, const char *nombre);

/*
 * listarFacturas
 * Objetivo:    Mostrar todas las facturas con columnas:
 *              ID | Evento | Fecha compra | Cliente | Subtotal        
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      nada (imprime en consola)
 */
void listarFacturas(const AppData *app);

/*
 * imprimirFactura
 * Objetivo:    Mostrar en pantalla el detalle completo de una
 *              factura: todos los campos.
 * Entrada:     factura - puntero a la Factura a imprimir
 * Salida:      nada (imprime en consola)
 */
void imprimirFactura(const Factura *factura);

#endif

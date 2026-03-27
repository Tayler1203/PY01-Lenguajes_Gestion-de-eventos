#ifndef FACTURAS_H
#define FACTURAS_H

#include "estructuras.h"

/*
 * listarFacturas
 * Objetivo:    Mostrar todas las facturas con columnas:
 *              ID | Evento | Fecha compra | Cliente | Subtotal        
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void listarFacturas(const AppData *app);

/*
 * imprimirFactura
 * Objetivo:    Mostrar en pantalla el detalle completo de una
 *              factura: todos los campos.
 * Entrada:     factura - puntero a la Factura a imprimir
 * Salida:      void (imprime en consola)
 */
void imprimirFactura(const Factura *factura);

#endif

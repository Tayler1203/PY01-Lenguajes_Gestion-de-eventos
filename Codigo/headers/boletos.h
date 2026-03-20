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
 * Salida:      void (agrega factura a app->facturas y marca
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

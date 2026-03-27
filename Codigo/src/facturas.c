#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/facturas.h"

void listarFacturas(const AppData *app) {
	if (app == NULL) {
		printf("Datos invalidos.\n");
		return;
	}

	if (app->cantidadFacturas == 0) {
		printf("\nNo hay facturas registradas.\n");
		return;
	}

	printf("\n");
	printf("============================================================================================================\n");
	printf("                                         LISTADO DE FACTURAS                                                \n");
	printf("============================================================================================================\n");
	printf(" ID  | Evento                              | Fecha Compra | Cliente               | Subtotal        | Total   \n");
	printf("============================================================================================================\n");

	for (int i = 0; i < app->cantidadFacturas; i++) {
		const Factura *factura = &app->facturas[i];
		printf(" %3d | %-35s | %12s | %-21s | $%13.2f | $%7.2f\n",
			factura->id,
			factura->nombreEvento,
			factura->fechaCompra,
			factura->nombreComprador,
			factura->subtotal,
			factura->total);
	}

	printf("============================================================================================================\n\n");
}

void imprimirFactura(const Factura *factura) {
	if (factura == NULL) {
		printf("Factura invalida.\n");
		return;
	}

	printf("\n");
	printf("====================================================================================================================\n");
	printf("                                    FACTURA DE COMPRA DE BOLETOS                                                \n");
	printf("====================================================================================================================\n\n");

	printf("Factura #%d\n", factura->id);
	printf("Fecha de compra: %s\n\n", factura->fechaCompra);

	printf("CLIENTE:\n");
	printf("  Nombre: %s\n", factura->nombreComprador);
	printf("  Cedula: %s\n\n", factura->cedula);

	printf("EVENTO:\n");
	printf("  Nombre: %s\n", factura->nombreEvento);
	printf("  Productora: %s\n", factura->productora);
	printf("  Sitio: %s\n", factura->nombreSitio);
	printf("  Fecha del evento: %s\n\n", factura->fechaEvento);

	printf("===================================================================================================================\n");
	printf("DETALLE DE ASIENTOS:\n");
	printf("===================================================================================================================\n\n");
	printf("%-15s | %-25s | %-15s\n", "ASIENTO", "SECTOR", "PRECIO");
	printf("--------------------+---------------------------------+---------------------\n");

	for (int i = 0; i < factura->cantidadAsientos; i++) {
		const DetalleAsiento *detalle = &factura->detalles[i];
		printf("%-15s | %-25s | $%13.2f\n",
			detalle->idAsiento,
			detalle->nombreSector,
			detalle->costo);
	}

	printf("\n");
	printf("===================================================================================================================\n");
	printf("TOTALES:\n");
	printf("===================================================================================================================\n\n");
	printf("Subtotal:                            $%13.2f\n", factura->subtotal);
	printf("Costo por servicio (5%%):            $%13.2f\n", factura->costoServicio);
	printf("------------------------------------------------------------\n");
	printf("TOTAL A PAGAR:                       $%13.2f\n", factura->total);
	printf("====================================================================================================================\n\n");
}

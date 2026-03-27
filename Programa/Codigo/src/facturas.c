#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/facturas.h"
#include "../headers/archivos.h"
#include "../headers/boletos.h"

static void marcarAsientosVendidos(Asiento **asientos, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		if (asientos[i] != NULL) {
			asientos[i]->estado = VENDIDO;
		}
	}
}

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

void generarFactura(AppData *app, Evento *evento, Asiento **asientos, SectorEvento **sectores, int cantidad, const char *cedula, const char *nombre) {
	if (app == NULL || evento == NULL || asientos == NULL || sectores == NULL || cantidad <= 0 || cedula == NULL || nombre == NULL) {
		printf("No se pudo generar la factura: datos incompletos.\n");
		return;
	}

	if (!verificarDisponibilidad(asientos, cantidad)) {
		printf("Algunos asientos ya no estan disponibles. Compra cancelada.\n");
		return;
	}

	Factura factura = {0};
	factura.cantidadAsientos = cantidad;

	time_t ahora = time(NULL);
	struct tm *infoTiempo = localtime(&ahora);
	if (infoTiempo != NULL) {
		strftime(factura.fechaCompra, MAX_FECHA, "%Y-%m-%d", infoTiempo);
	}

	strncpy(factura.cedula, cedula, MAX_CEDULA - 1);
	factura.cedula[MAX_CEDULA - 1] = '\0';
	strncpy(factura.nombreComprador, nombre, MAX_NOMBRE - 1);
	factura.nombreComprador[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.nombreEvento, evento->nombre, MAX_NOMBRE - 1);
	factura.nombreEvento[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.productora, evento->productora, MAX_NOMBRE - 1);
	factura.productora[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.nombreSitio, evento->sitio->nombre, MAX_NOMBRE - 1);
	factura.nombreSitio[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.fechaEvento, evento->fecha, MAX_FECHA - 1);
	factura.fechaEvento[MAX_FECHA - 1] = '\0';

	factura.detalles = malloc(cantidad * sizeof(DetalleAsiento));
	if (factura.detalles == NULL) {
		printf("Error de memoria al generar factura. Compra cancelada.\n");
		return;
	}

	double subtotal = 0.0;
	for (int i = 0; i < cantidad; i++) {
		DetalleAsiento *detalle = &factura.detalles[i];
		const Asiento *asiento = asientos[i];
		SectorEvento *sectorEv = sectores[i];
		if (asiento == NULL || sectorEv == NULL || sectorEv->sector == NULL) {
			printf("Datos de asiento invalidos. Compra cancelada.\n");
			free(factura.detalles);
			return;
		}

		strncpy(detalle->idAsiento, asiento->id, MAX_ID_ASIENTO - 1);
		detalle->idAsiento[MAX_ID_ASIENTO - 1] = '\0';
		strncpy(detalle->nombreSector, sectorEv->sector->nombre, MAX_NOMBRE - 1);
		detalle->nombreSector[MAX_NOMBRE - 1] = '\0';
		detalle->costo = sectorEv->montoPorAsiento;
		subtotal += detalle->costo;
	}

	factura.subtotal = subtotal;
	factura.costoServicio = subtotal * COSTO_SERVICIO;
	factura.total = factura.subtotal + factura.costoServicio;

	Factura *nuevoArreglo = realloc(app->facturas, (app->cantidadFacturas + 1) * sizeof(Factura));
	if (nuevoArreglo == NULL) {
		printf("No se pudo reservar espacio para la factura. Compra cancelada.\n");
		free(factura.detalles);
		return;
	}

	factura.id = app->contadorFacturas + 1;
	app->facturas = nuevoArreglo;
	app->facturas[app->cantidadFacturas] = factura;
	app->cantidadFacturas++;
	app->contadorFacturas = factura.id;

	marcarAsientosVendidos(asientos, cantidad);

	agregarFacturaAlArchivo(&app->facturas[app->cantidadFacturas - 1]);

	printf("\nCompra realizada exitosamente!\n");
	printf("Factura #%d - Fecha compra: %s\n", factura.id, factura.fechaCompra);
	printf("Cliente: %s (%s)\n", factura.nombreComprador, factura.cedula);
	printf("Evento: %s | Productora: %s | Fecha: %s | Sitio: %s\n", factura.nombreEvento, factura.productora, factura.fechaEvento, factura.nombreSitio);
	printf("Asientos comprados (%d): ", factura.cantidadAsientos);
	for (int i = 0; i < factura.cantidadAsientos; i++) {
		printf("%s%s", factura.detalles[i].idAsiento, (i < factura.cantidadAsientos - 1) ? ", " : "");
	}
	printf("\nSubtotal: $%.2f | Costo servicio (5%%): $%.2f | Total: $%.2f\n", factura.subtotal, factura.costoServicio, factura.total);
}

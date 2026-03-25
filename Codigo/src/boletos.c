#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/boletos.h"
#include "../headers/eventos.h"
#include "../headers/sitios.h"
#include "../headers/archivos.h"



int verificarDisponibilidad(Asiento **asientos, int cantidad) {
	if (asientos == NULL || cantidad <= 0) {
		return 0;
	}

	for (int i = 0; i < cantidad; i++) {
		if (asientos[i] == NULL || asientos[i]->estado != DISPONIBLE) {
			return 0;
		}
	}

	return 1;
}

void mostrarAsientosDisponibles(Evento *evento) {
	if (evento == NULL) {
		printf("Evento inválido.\n");
		return;
	}

	printf("\n=== Disponibilidad de asientos en %s ===\n", evento->nombre);
	printf("Productora: %s | Fecha: %s\n", evento->productora, evento->fecha);
	printf("Sitio: %s\n\n", evento->sitio->nombre);

	for (int s = 0; s < evento->cantidadSectores; s++) {
		SectorEvento *sectEv = &evento->sectoresEvento[s];
		Sector *sector = sectEv->sector;
		int disponibles = 0;

		for (int a = 0; a < sector->cantidadEspacios; a++) {
			if (sector->asientos[a].estado == DISPONIBLE) {
				disponibles++;
			}
		}

		printf("  Sector: %s (Inicial: %c)\n", sector->nombre, sector->inicial);
		printf("    Asientos disponibles: %d/%d\n", disponibles, sector->cantidadEspacios);
		printf("    Precio por asiento: $%.2f\n", sectEv->montoPorAsiento);
		printf("    Estado: ");
		for (int a = 0; a < sector->cantidadEspacios; a++) {
			if (sector->asientos[a].estado == DISPONIBLE) {
				printf("[%s] ", sector->asientos[a].id);
			} else {
				printf("(V) ");
			}
		}
		printf("\n\n");
	}
}

void marcarAsientosVendidos(Asiento **asientos, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		if (asientos[i] != NULL) {
			asientos[i]->estado = VENDIDO;
		}
	}
}

void comprarBoletos(AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("\nNo hay eventos disponibles.\n");
		return;
	}

	printf("\n=== Eventos disponibles ===");
	for (int i = 0; i < app->cantidadEventos; i++) {
		printf("\n%d. %s - %s (%s)", i + 1, app->eventos[i].nombre,
				app->eventos[i].productora, app->eventos[i].fecha);
	}
	printf("\nSeleccione evento (0 para cancelar): ");
	int opEvento;
	if (scanf("%d", &opEvento) != 1 || opEvento < 1 || opEvento > app->cantidadEventos) {
		limpiarBufferEntrada();
		printf("\nOpción inválida. Compra cancelada.\n");
		return;
	}
	limpiarBufferEntrada();

	Evento *evento = &app->eventos[opEvento - 1];

	// Mostrar asientos disponibles
	mostrarAsientosDisponibles(evento);

	// Seleccionar asientos 
	printf("\n*** Sistema de selección de asientos ***\n");
	printf("Para la compra completa, implementar:\n");
	printf("- Selección de asientos específicos\n");
	printf("- Validación de disponibilidad\n");
	printf("- Generación de factura\n\n");
}

void generarFactura(AppData *app, Evento *evento, Asiento **asientos, SectorEvento **sectores, int cantidad, const char *cedula, const char *nombre) {
	printf("\n*** Generación de factura ***\n");
	printf("Factura para: %s\n", nombre);
	printf("Cédula: %s\n", cedula);
	printf("Evento: %s\n", evento->nombre);
	printf("Asientos: %d\n", cantidad);
	printf("\nImplementar:\n");
	printf("- Creación de DetalleAsiento[]\n");
	printf("- Cálculo de subtotal\n");
	printf("- Cálculo de costo de servicio (5%%)\n");
	printf("- Cálculo de total\n");
	printf("- Guardado en app->facturas\n\n");
}

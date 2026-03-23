#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/eventos.h"
#include "../headers/archivos.h"

static void limpiarBufferEntrada(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void quitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

void mostrarDetalleEvento(const Evento *evento) {
	(void)evento;
}

void listarEventos(const AppData *app) {
	(void)app;
}

Evento *seleccionarEvento(const AppData *app) {
	(void)app;
	return NULL;
}

void mostrarEstadoEvento(const AppData *app) {
	(void)app;
}

void mostrarResumenEvento(const AppData *app) {
	(void)app;
}

void mostrarRecaudacionPorSector(const AppData *app) {
	(void)app;
}

void mostrarAsientosPorSector(const AppData *app) {
	(void)app;
}

void consultarEventosFuturos(const AppData *app) {
	(void)app;
}


void crearEvento(AppData *app) {
	if (app->cantidadSitios == 0) {
		printf("\nDebe crear al menos un sitio antes de crear un evento.\n");
		return;
	}

	printf("\n--- Crear Evento Manual ---\n");
	char nombre[MAX_NOMBRE];
	char productora[MAX_NOMBRE];
	char fecha[MAX_FECHA];

	limpiarBufferEntrada();
	printf("Nombre del evento: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	quitarSaltoDeLinea(nombre);

	printf("Productora: ");
	fgets(productora, MAX_NOMBRE, stdin);
	quitarSaltoDeLinea(productora);

	printf("Fecha (YYYY-MM-DD): ");
	fgets(fecha, MAX_FECHA, stdin);
	quitarSaltoDeLinea(fecha);

	printf("\nSeleccione el sitio para el evento:\n");
	for (int i = 0; i < app->cantidadSitios; i++) {
		printf("%d) %s (%s)\n", i + 1, app->sitios[i].nombre, app->sitios[i].ubicacion);
	}

	int indiceSitio = 0;
	printf("Opcion: ");
	if (scanf("%d", &indiceSitio) != 1) {
		printf("Entrada invalida. Operacion abortada.\n");
		limpiarBufferEntrada();
		return;
	}
	limpiarBufferEntrada();

	if (indiceSitio <= 0 || indiceSitio > app->cantidadSitios) {
		printf("Sitio seleccionado invalido. Operacion abortada.\n");
		return;
	}

	SitioEvento *sitioSeleccionado = &app->sitios[indiceSitio - 1];
	if (sitioSeleccionado->cantidadSectores == 0) {
		printf("El sitio seleccionado no tiene sectores definidos. Agregue sectores primero.\n");
		return;
	}

	Evento *nuevoArreglo = realloc(app->eventos, (app->cantidadEventos + 1) * sizeof(Evento));
	if (nuevoArreglo == NULL) {
		printf("No se pudo asignar memoria para el nuevo evento.\n");
		return;
	}

	app->eventos = nuevoArreglo;
	Evento *nuevoEvento = &app->eventos[app->cantidadEventos];

	strncpy(nuevoEvento->nombre, nombre, MAX_NOMBRE - 1);
	nuevoEvento->nombre[MAX_NOMBRE - 1] = '\0';
	strncpy(nuevoEvento->productora, productora, MAX_NOMBRE - 1);
	nuevoEvento->productora[MAX_NOMBRE - 1] = '\0';
	strncpy(nuevoEvento->fecha, fecha, MAX_FECHA - 1);
	nuevoEvento->fecha[MAX_FECHA - 1] = '\0';
	
	nuevoEvento->sitio = sitioSeleccionado;
	nuevoEvento->cantidadSectores = sitioSeleccionado->cantidadSectores;
	nuevoEvento->sectoresEvento = malloc(nuevoEvento->cantidadSectores * sizeof(SectorEvento));
	if (nuevoEvento->sectoresEvento == NULL) {
		printf("No se pudo asignar memoria para los sectores del evento.\n");
		return;
	}

	for (int i = 0; i < nuevoEvento->cantidadSectores; i++) {
		nuevoEvento->sectoresEvento[i].sector = &sitioSeleccionado->sectores[i];
		printf("Monto por asiento para sector '%s': ", sitioSeleccionado->sectores[i].nombre);
		if (scanf("%lf", &nuevoEvento->sectoresEvento[i].montoPorAsiento) != 1) {
			printf("Monto invalido. Operacion abortada.\n");
			limpiarBufferEntrada();
			free(nuevoEvento->sectoresEvento);
			return;
		}
		limpiarBufferEntrada();
	}

	app->cantidadEventos++;

	if (GuardarEventosEnArchivo(app, nuevoEvento)) {
		printf("Evento guardado correctamente en archivo.\n");
	} else {
		printf("Error al guardar evento en archivo.\n");
	}
}

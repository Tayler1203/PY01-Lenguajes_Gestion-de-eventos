#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sitios.h"
#include "../headers/menu.h"
#include "../headers/archivos.h"

void listarSitios(const AppData *app) {
	int i;
	
	if (app->cantidadSitios == 0) {
		printf("\nNo hay sitios registrados.\n");
		return;
	}
	
	printf("\n--- Sitios Registrados ---\n");
	for (i = 0; i < app->cantidadSitios; i++) {
		printf("\n%d. %s\n", i + 1, app->sitios[i].nombre);
		printf("   Ubicacion: %s\n", app->sitios[i].ubicacion);
		printf("   Sitio web: %s\n", app->sitios[i].sitioWeb);
	}
}

/*
 * Captura los datos desde el menú, reserva espacio para un nuevo sitio
 * en el arreglo dinámico y guarda el registro en memoria.
 */
void agregarSitioManual(AppData *app) {
	char nombre[MAX_NOMBRE];
	char ubicacion[MAX_UBICACION];
	char sitioWeb[MAX_URL];
	SitioEvento *nuevoArreglo;
	SitioEvento *nuevoSitio;
	int i;

	/* Solicita nombre, ubicación y sitio web por consola. */
	ObtenerDatosSitioManual(nombre, ubicacion, sitioWeb);

	/* Reserva un nuevo bloque y copia los sitios existentes. */
	nuevoArreglo = (SitioEvento *)malloc((app->cantidadSitios + 1) * sizeof(SitioEvento));

	for (i = 0; i < app->cantidadSitios; i++) {
		nuevoArreglo[i] = app->sitios[i];
	}

	free(app->sitios);
	app->sitios = nuevoArreglo;
	/* Toma la nueva posición disponible para escribir el sitio. */
	nuevoSitio = &app->sitios[app->cantidadSitios];

	/* Copia  del strings. */
	strncpy(nuevoSitio->nombre, nombre, MAX_NOMBRE - 1);
	nuevoSitio->nombre[MAX_NOMBRE - 1] = '\0';

	strncpy(nuevoSitio->ubicacion, ubicacion, MAX_UBICACION - 1);
	nuevoSitio->ubicacion[MAX_UBICACION - 1] = '\0';

	strncpy(nuevoSitio->sitioWeb, sitioWeb, MAX_URL - 1);
	nuevoSitio->sitioWeb[MAX_URL - 1] = '\0';

	nuevoSitio->cantidadSectores = 0;
	nuevoSitio->sectores = NULL;

	/* Actualiza el contador de sitios en memoria. */
	app->cantidadSitios++;
	GuardarSitiosEnArchivo(app, nuevoSitio->nombre, nuevoSitio->ubicacion, nuevoSitio->sitioWeb);

	printf("Nombre: %s\n", nuevoSitio->nombre);
	printf("Ubicacion: %s\n", nuevoSitio->ubicacion);
	printf("Sitio web: %s\n", nuevoSitio->sitioWeb);
}

void cargarSitiosDesdeArchivo(AppData *app, const char *ruta) {
}

SitioEvento *buscarSitioPorNombre(const AppData *app, const char *nombre) {
}

SitioEvento *seleccionarSitio(const AppData *app) {
}

void ValidarNombreSitio(const char *nombre) {
	
}
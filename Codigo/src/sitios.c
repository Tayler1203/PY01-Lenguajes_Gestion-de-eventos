#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sitios.h"
#include "../headers/menu.h"
#include "../headers/archivos.h"

static void quitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

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
void agregarSitioManual(AppData *app) {
	char nombre[MAX_NOMBRE];
	char ubicacion[MAX_UBICACION];
	char sitioWeb[MAX_URL];
	SitioEvento *nuevoArreglo;
	SitioEvento *nuevoSitio;

	ObtenerDatosSitioManual(nombre, ubicacion, sitioWeb);

	nuevoArreglo = realloc(app->sitios, (app->cantidadSitios + 1) * sizeof(SitioEvento));
	if (nuevoArreglo == NULL) {
		printf("No se pudo asignar memoria para el nuevo sitio.\n");
		return;
	}

	app->sitios = nuevoArreglo;
	nuevoSitio = &app->sitios[app->cantidadSitios];

	strncpy(nuevoSitio->nombre, nombre, MAX_NOMBRE - 1);
	nuevoSitio->nombre[MAX_NOMBRE - 1] = '\0';

	strncpy(nuevoSitio->ubicacion, ubicacion, MAX_UBICACION - 1);
	nuevoSitio->ubicacion[MAX_UBICACION - 1] = '\0';

	strncpy(nuevoSitio->sitioWeb, sitioWeb, MAX_URL - 1);
	nuevoSitio->sitioWeb[MAX_URL - 1] = '\0';

	nuevoSitio->cantidadSectores = 0;
	nuevoSitio->sectores = NULL;

	app->cantidadSitios++;
	GuardarSitiosEnArchivo(app, nuevoSitio->nombre, nuevoSitio->ubicacion, nuevoSitio->sitioWeb);

	printf("Nombre: %s\n", nuevoSitio->nombre);
	printf("Ubicacion: %s\n", nuevoSitio->ubicacion);
	printf("Sitio web: %s\n", nuevoSitio->sitioWeb);
}

void cargarSitiosDesdeArchivo(AppData *app, const char *ruta) {
	FILE *archivo = fopen(ruta, "r");
	if (archivo == NULL) {
		printf("Advertencia: no se pudo abrir el archivo de sitios %s.\n", ruta);
		return;
	}

	char linea[512];
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		quitarSaltoDeLinea(linea);

		if (linea[0] == '\0') continue;

		char nombre[MAX_NOMBRE];
		char ubicacion[MAX_UBICACION];
		char sitioWeb[MAX_URL];
		int campos = sscanf(linea, "%99[^,],%149[^,],%149[^\n]", nombre, ubicacion, sitioWeb);
		if (campos < 2) continue;

		if (buscarSitioPorNombre(app, nombre) != NULL) continue;

		SitioEvento *nuevoArreglo = realloc(app->sitios, (app->cantidadSitios + 1) * sizeof(SitioEvento));
		if (nuevoArreglo == NULL) {
			printf("Error: memoria insuficiente al cargar sitio %s.\n", nombre);
			break;
		}
		app->sitios = nuevoArreglo;

		SitioEvento *sitio = &app->sitios[app->cantidadSitios];
		strncpy(sitio->nombre, nombre, MAX_NOMBRE - 1);
		sitio->nombre[MAX_NOMBRE - 1] = '\0';
		strncpy(sitio->ubicacion, ubicacion, MAX_UBICACION - 1);
		sitio->ubicacion[MAX_UBICACION - 1] = '\0';

		if (campos == 3) {
			strncpy(sitio->sitioWeb, sitioWeb, MAX_URL - 1);
			sitio->sitioWeb[MAX_URL - 1] = '\0';
		} else {
			sitio->sitioWeb[0] = '\0';
		}

		sitio->cantidadSectores = 0;
		sitio->sectores = NULL;

		app->cantidadSitios++;
	}

	fclose(archivo);
}

SitioEvento *buscarSitioPorNombre(const AppData *app, const char *nombre) {
	for (int i = 0; i < app->cantidadSitios; i++) {
		if (strcmp(app->sitios[i].nombre, nombre) == 0) {
			return &app->sitios[i];
		}
	}
	return NULL;
}

SitioEvento *seleccionarSitio(const AppData *app) {
	if (app->cantidadSitios == 0) {
		return NULL;
	}

	for (int i = 0; i < app->cantidadSitios; i++) {
		printf("%d) %s (%s)\n", i + 1, app->sitios[i].nombre, app->sitios[i].ubicacion);
	}

	printf("Seleccione el sitio (0 para cancelar): ");
	int opcion;
	if (scanf("%d", &opcion) != 1) {
		limpiarBufferEntrada();
		return NULL;
	}
	if (opcion <= 0 || opcion > app->cantidadSitios) {
		return NULL;
	}
	return &app->sitios[opcion - 1];
}

void cargarSitiosDesdeArchivoConRuta(AppData *app) {
	char ruta[600];
	limpiarBufferEntrada();
	
	printf("\n--- Cargar Sitios desde Archivo ---\n");
	printf("Ingrese la ruta del archivo: ");
	
	if (fgets(ruta, sizeof(ruta), stdin) == NULL) {
		printf("Error al leer la ruta.\n");
		return;
	}
	
	quitarSaltoDeLinea(ruta);
	
	if (ruta[0] == '\0') {
		printf("Error: debe ingresar una ruta valida.\n");
		return;
	}
	
	printf("Cargando sitios desde: %s\n", ruta);
	cargarSitiosDesdeArchivo(app, ruta);
	printf("Carga completada. Total de sitios: %d\n", app->cantidadSitios);
}

void ValidarNombreSitio(const char *nombre) {
	
}
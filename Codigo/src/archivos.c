#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/archivos.h"
#include "../headers/sitios.h"
#include "../headers/sitios.h"

void inicializarApp(AppData *app) {
}

void liberarApp(AppData *app) {
	if (app == NULL) return;
	
	// Liberar sitios y sus sectores
	for (int i = 0; i < app->cantidadSitios; i++) {
		SitioEvento *sitio = &app->sitios[i];
		for (int j = 0; j < sitio->cantidadSectores; j++) {
			free(sitio->sectores[j].asientos);
		}
		free(sitio->sectores);
	}
	free(app->sitios);
	
	// Liberar eventos
	for (int i = 0; i < app->cantidadEventos; i++) {
		free(app->eventos[i].sectoresEvento);
	}
	free(app->eventos);
	
	// Liberar facturas
	for (int i = 0; i < app->cantidadFacturas; i++) {
		free(app->facturas[i].detalles);
	}
	free(app->facturas);
}

void asegurarDirectorioDatos() {
}

void cargarDatos(AppData *app) {
	if (app == NULL) return;
	app->cantidadSitios = 0;
	app->sitios = NULL;
	app->cantidadEventos = 0;
	app->eventos = NULL;
	app->cantidadFacturas = 0;
	app->facturas = NULL;

	cargarSitiosDesdeArchivo(app, ARCHIVO_SITIOS);
	cargarSectoresDesdeArchivo(app);
}

void guardarDatos(AppData *app) {
	if (app == NULL) return;
	
	// Guardar sectores
	guardarSectoresEnArchivo(app);
	
	// Aquí se pueden agregar guardado de eventos y facturas si es necesario
}

int verificarCredenciales(const char *usuario, const char *contrasena) {
	FILE *archivo;
	char linea[256];
	char usuarioArchivo[MAX_NOMBRE];
	char contrasenaArchivo[MAX_NOMBRE];
	
	archivo = fopen(ARCHIVO_CREDENCIALES, "r");
	if (archivo == NULL) {
		printf("ERROR: No se pudo abrir el archivo de credenciales.\n");
		return 0;
	}
	
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		linea[strcspn(linea, "\r\n")] = '\0';
		
		if (sscanf(linea, "%99[^,],%99s", usuarioArchivo, contrasenaArchivo) == 2) {
			if (strcmp(usuarioArchivo, usuario) == 0 && 
			    strcmp(contrasenaArchivo, contrasena) == 0) {
				fclose(archivo);
				return 1;
			}
		}
	}
	
	fclose(archivo);
	return 0;
}
int GuardarSitiosEnArchivo(const AppData *app, const char *nombre, const char *ubicacion, const char *sitioWeb) {
	FILE *archivo;
	
	(void)app;
	archivo = fopen(ARCHIVO_SITIOS, "a");
	if (archivo == NULL) {
		return 0;
	}

	fprintf(archivo, "%s,%s,%s\n", nombre, ubicacion, sitioWeb);
	fclose(archivo);
	return 1;
}

void cargarSectoresDesdeArchivo(AppData *app) {
	FILE *archivo = fopen(ARCHIVO_SECTORES, "r");
	if (archivo == NULL) {
		// No hay archivo de sectores, es normal
		return;
	}

	char linea[1024];
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		linea[strcspn(linea, "\r\n")] = '\0';

		if (linea[0] == '\0') continue;

		char *token = strtok(linea, ",");
		if (token == NULL) continue;
		char nombreSitio[MAX_NOMBRE];
		strncpy(nombreSitio, token, MAX_NOMBRE - 1);
		nombreSitio[MAX_NOMBRE - 1] = '\0';

		SitioEvento *sitio = buscarSitioPorNombre(app, nombreSitio);
		if (sitio == NULL) continue; // Sitio no encontrado, ignorar

		token = strtok(NULL, ",");
		if (token == NULL) continue;
		char nombreSector[MAX_NOMBRE];
		strncpy(nombreSector, token, MAX_NOMBRE - 1);
		nombreSector[MAX_NOMBRE - 1] = '\0';

		token = strtok(NULL, ",");
		if (token == NULL) continue;
		char inicial = token[0];

		token = strtok(NULL, ",");
		if (token == NULL) continue;
		int cantidadEspacios = atoi(token);

		// Agregar sector al sitio
		Sector *nuevoArreglo = realloc(sitio->sectores, (sitio->cantidadSectores + 1) * sizeof(Sector));
		if (nuevoArreglo == NULL) {
			printf("Error: memoria insuficiente para sector %s.\n", nombreSector);
			continue;
		}
		sitio->sectores = nuevoArreglo;

		Sector *sector = &sitio->sectores[sitio->cantidadSectores];
		strncpy(sector->nombre, nombreSector, MAX_NOMBRE - 1);
		sector->nombre[MAX_NOMBRE - 1] = '\0';
		sector->inicial = inicial;
		sector->cantidadEspacios = cantidadEspacios;

		// Generar asientos
		sector->asientos = malloc(cantidadEspacios * sizeof(Asiento));
		if (sector->asientos == NULL) {
			printf("Error: memoria insuficiente para asientos de sector %s.\n", nombreSector);
			sector->cantidadEspacios = 0;
			sitio->cantidadSectores++;
			continue;
		}
		for (int j = 0; j < cantidadEspacios; j++) {
			snprintf(sector->asientos[j].id, MAX_ID_ASIENTO, "%c%d", inicial, j + 1);
			sector->asientos[j].estado = DISPONIBLE;
		}

		sitio->cantidadSectores++;
	}

	fclose(archivo);
}

void guardarSectoresEnArchivo(const AppData *app) {
	FILE *archivo = fopen(ARCHIVO_SECTORES, "w");
	if (archivo == NULL) {
		printf("Error: no se pudo abrir el archivo de sectores para guardar.\n");
		return;
	}

	for (int i = 0; i < app->cantidadSitios; i++) {
		SitioEvento *sitio = &app->sitios[i];
		for (int j = 0; j < sitio->cantidadSectores; j++) {
			Sector *sector = &sitio->sectores[j];
			fprintf(archivo, "%s,%s,%c,%d\n", sitio->nombre, sector->nombre, sector->inicial, sector->cantidadEspacios);
		}
	}

	fclose(archivo);
}

int GuardarEventosEnArchivo(const AppData *app, const Evento *evento) {
	FILE *archivo;
	int i;

	(void)app;
	archivo = fopen(ARCHIVO_EVENTOS, "a");
	if (archivo == NULL) {
		return 0;
	}

	fprintf(archivo, "%s,%s,%s,%s,%d", evento->nombre, evento->productora, evento->fecha, evento->sitio->nombre, evento->cantidadSectores);
	for (i = 0; i < evento->cantidadSectores; i++) {
		fprintf(archivo, ",%.2f", evento->sectoresEvento[i].montoPorAsiento);
	}
	fprintf(archivo, "\n");
	fclose(archivo);
	return 1;
}

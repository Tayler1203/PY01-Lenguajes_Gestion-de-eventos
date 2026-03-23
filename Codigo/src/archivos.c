#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/archivos.h"
#include "../headers/sitios.h"

void inicializarApp(AppData *app) {
}

void liberarApp(AppData *app) {
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
}

void guardarDatos(AppData *app) {
	// Implementación pendiente: escribir sitios/eventos/facturas en archivos.
	(void)app;
}

int verificarCredenciales(const char *usuario, const char *contraseña) {
	FILE *archivo;
	char linea[256];
	char usuarioArchivo[MAX_NOMBRE];
	char contraseñaArchivo[MAX_NOMBRE];
	
	archivo = fopen(ARCHIVO_CREDENCIALES, "r");
	if (archivo == NULL) {
		printf("ERROR: No se pudo abrir el archivo de credenciales.\n");
		return 0;
	}
	
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		/* Eliminar salto de línea */
		linea[strcspn(linea, "\r\n")] = '\0';
		
		/* Parsear formato: usuario,contraseña */
		if (sscanf(linea, "%99[^,],%99s", usuarioArchivo, contraseñaArchivo) == 2) {
			if (strcmp(usuarioArchivo, usuario) == 0 && 
			    strcmp(contraseñaArchivo, contraseña) == 0) {
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

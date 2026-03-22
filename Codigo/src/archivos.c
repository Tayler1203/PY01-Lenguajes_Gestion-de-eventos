#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/archivos.h"

void inicializarApp(AppData *app) {
}

void liberarApp(AppData *app) {
}

void asegurarDirectorioDatos() {
}

void cargarDatos(AppData *app) {
}

void guardarDatos(AppData *app) {
}

int verificarCredenciales(const char *usuario, const char *contrasena) {
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

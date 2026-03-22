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

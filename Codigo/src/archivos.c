#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/archivos.h"
#include "../headers/sitios.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

void inicializarApp(AppData *app) {
    if (app == NULL) return;
    app->sitios = NULL;
    app->cantidadSitios = 0;
    app->eventos = NULL;
    app->cantidadEventos = 0;
    app->facturas = NULL;
    app->cantidadFacturas = 0;
    app->contadorFacturas = 0;
    app->sesionActiva = 0;
}

void liberarApp(AppData *app) {
	if (app == NULL) return;
	
	for (int i = 0; i < app->cantidadSitios; i++) {
		SitioEvento *sitio = &app->sitios[i];
		for (int j = 0; j < sitio->cantidadSectores; j++) {
			free(sitio->sectores[j].asientos);
		}
		free(sitio->sectores);
	}
	free(app->sitios);
	
	for (int i = 0; i < app->cantidadEventos; i++) {
		free(app->eventos[i].sectoresEvento);
	}
	free(app->eventos);
	
	for (int i = 0; i < app->cantidadFacturas; i++) {
		free(app->facturas[i].detalles);
	}
	free(app->facturas);
}

void asegurarDirectorioDatos() {
    int ret = MKDIR("../data");
    (void)ret; // Ignorar error si ya existe.
}

void cargarEventosDesdeArchivo(AppData *app) {
    if (app == NULL) return;

    FILE *archivo = fopen(ARCHIVO_EVENTOS, "r");
    if (archivo == NULL) {
        return;
    }

    char linea[2048];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';

        if (linea[0] == '\0') continue;

        char *token = strtok(linea, ",");
        if (token == NULL) continue;

        char nombre[MAX_NOMBRE];
        char productora[MAX_NOMBRE];
        char fecha[MAX_FECHA];
        char nombreSitio[MAX_NOMBRE];
        int cantidadSectores = 0;

        strncpy(nombre, token, MAX_NOMBRE - 1);
        nombre[MAX_NOMBRE - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(productora, token, MAX_NOMBRE - 1);
        productora[MAX_NOMBRE - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(fecha, token, MAX_FECHA - 1);
        fecha[MAX_FECHA - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(nombreSitio, token, MAX_NOMBRE - 1);
        nombreSitio[MAX_NOMBRE - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        cantidadSectores = atoi(token);

        SitioEvento *sitio = buscarSitioPorNombre(app, nombreSitio);
        if (sitio == NULL || sitio->cantidadSectores == 0) continue;

        int sectoresAUsar = cantidadSectores;
        if (sectoresAUsar > sitio->cantidadSectores) {
            sectoresAUsar = sitio->cantidadSectores;
        }

        Evento *nuevoArreglo = realloc(app->eventos, (app->cantidadEventos + 1) * sizeof(Evento));
        if (nuevoArreglo == NULL) {
            printf("Error: memoria insuficiente al cargar evento %s.\n", nombre);
            continue;
        }

        app->eventos = nuevoArreglo;
        Evento *evento = &app->eventos[app->cantidadEventos];

        strncpy(evento->nombre, nombre, MAX_NOMBRE - 1);
        evento->nombre[MAX_NOMBRE - 1] = '\0';
        strncpy(evento->productora, productora, MAX_NOMBRE - 1);
        evento->productora[MAX_NOMBRE - 1] = '\0';
        strncpy(evento->fecha, fecha, MAX_FECHA - 1);
        evento->fecha[MAX_FECHA - 1] = '\0';

        evento->sitio = sitio;
        evento->cantidadSectores = sectoresAUsar;
        evento->sectoresEvento = malloc(sectoresAUsar * sizeof(SectorEvento));

        if (evento->sectoresEvento == NULL) {
            printf("Error: memoria insuficiente para sectores de evento %s.\n", nombre);
            continue;
        }

        for (int i = 0; i < sectoresAUsar; i++) {
            evento->sectoresEvento[i].sector = &sitio->sectores[i];
            token = strtok(NULL, ",");
            if (token != NULL) {
                evento->sectoresEvento[i].montoPorAsiento = atof(token);
            } else {
                evento->sectoresEvento[i].montoPorAsiento = 0.0;
            }
        }

        app->cantidadEventos++;
    }

    fclose(archivo);
}

void cargarDatos(AppData *app) {
	if (app == NULL) return;

	inicializarApp(app);
	asegurarDirectorioDatos();

	cargarSitiosDesdeArchivo(app, ARCHIVO_SITIOS);
	cargarSectoresDesdeArchivo(app);
	cargarEventosDesdeArchivo(app);
	cargarEstadosAsientos(app);
}

void guardarDatos(AppData *app) {
	if (app == NULL) return;
	
	guardarSectoresEnArchivo(app);
	guardarEstadosAsientos(app);
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
		if (sitio == NULL) continue;

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

void cargarEstadosAsientos(AppData *app) {
	FILE *archivo = fopen(ARCHIVO_ASIENTOS, "r");
	if (archivo == NULL) {
		return;
	}

	char linea[256];
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		linea[strcspn(linea, "\r\n")] = '\0';
		if (linea[0] == '\0') continue;

		char nombreEvento[MAX_NOMBRE];
		char asientoId[MAX_ID_ASIENTO];
		int estado;

		if (sscanf(linea, "%99[^,],%9[^,],%d", nombreEvento, asientoId, &estado) != 3) {
			continue;
		}

		// Buscar el evento
		Evento *evento = NULL;
		for (int i = 0; i < app->cantidadEventos; i++) {
			if (strcmp(app->eventos[i].nombre, nombreEvento) == 0) {
				evento = &app->eventos[i];
				break;
			}
		}

		if (evento == NULL) continue;

		// Buscar el asiento en los sectores del evento
		for (int s = 0; s < evento->cantidadSectores; s++) {
			Sector *sector = evento->sectoresEvento[s].sector;
			for (int a = 0; a < sector->cantidadEspacios; a++) {
				if (strcmp(sector->asientos[a].id, asientoId) == 0) {
					sector->asientos[a].estado = (EstadoAsiento)estado;
					goto siguiente_linea;
				}
			}
		}
		siguiente_linea:;
	}

	fclose(archivo);
}

void guardarEstadosAsientos(const AppData *app) {
	FILE *archivo = fopen(ARCHIVO_ASIENTOS, "w");
	if (archivo == NULL) {
		printf("Error: no se pudo abrir archivo de asientos para guardar.\n");
		return;
	}

	for (int e = 0; e < app->cantidadEventos; e++) {
		Evento *evento = &app->eventos[e];
		for (int s = 0; s < evento->cantidadSectores; s++) {
			Sector *sector = evento->sectoresEvento[s].sector;
			for (int a = 0; a < sector->cantidadEspacios; a++) {
				fprintf(archivo, "%s,%s,%d\n", evento->nombre, sector->asientos[a].id, (int)sector->asientos[a].estado);
			}
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

void limpiarBufferEntrada(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

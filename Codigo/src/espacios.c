#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/espacios.h"
#include "../headers/sitios.h"

static void limpiarBufferEntrada(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void quitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

void mostrarSitiosConSectores(const AppData *app) {
	int i, j, k;
	
	if (app->cantidadSitios == 0) {
		printf("\nNo hay sitios registrados.\n");
		return;
	}
	
	printf("\n--- Sitios con Sectores y Asientos ---\n");
	for (i = 0; i < app->cantidadSitios; i++) {
		SitioEvento *sitio = &app->sitios[i];
		printf("\nSitio: %s\n", sitio->nombre);
		printf("Ubicacion: %s\n", sitio->ubicacion);
		printf("Sitio web: %s\n", sitio->sitioWeb);
		printf("Cantidad de sectores: %d\n", sitio->cantidadSectores);
		
		for (j = 0; j < sitio->cantidadSectores; j++) {
			Sector *sector = &sitio->sectores[j];
			printf("  Sector %d: %s (Inicial: %c, Asientos: %d)\n", 
				   j + 1, sector->nombre, sector->inicial, sector->cantidadEspacios);
			// Opcional: mostrar IDs de asientos
			// printf("    Asientos: ");
			// for (k = 0; k < sector->cantidadEspacios; k++) {
			//     printf("%s ", sector->asientos[k].id);
			// }
			// printf("\n");
		}
		if (sitio->cantidadSectores == 0) {
			printf("  No hay sectores definidos.\n");
		}
	}
}

void agregarSector(SitioEvento *sitio) {
	char Letras[26] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};

	int cantidadNuevosSectores;
	printf("\nCantidad de sectores a agregar: ");
	if (scanf("%d", &cantidadNuevosSectores) != 1) {
		printf("Entrada invalida.\n");
		limpiarBufferEntrada();
		return;
	}

	if (cantidadNuevosSectores <= 0) {
		printf("La cantidad debe ser mayor a cero.\n");
		return;
	}

	int totalSectores = sitio->cantidadSectores + cantidadNuevosSectores;
	Sector *nuevoArreglo = realloc(sitio->sectores, totalSectores * sizeof(Sector));

	sitio->sectores = nuevoArreglo;
	limpiarBufferEntrada();

	for (int i = 0; i < cantidadNuevosSectores; i++) {
		Sector *sector = &sitio->sectores[sitio->cantidadSectores + i];
		int numAsientos;
		int resultadoScanf;

		printf("Nombre del sector %d: ", i + 1);
		fgets(sector->nombre, MAX_NOMBRE, stdin);
		quitarSaltoDeLinea(sector->nombre);

		printf("Cantidad de asientos para %s: ", sector->nombre);
		scanf("%d", &numAsientos);
		limpiarBufferEntrada();

		if (numAsientos <= 0) {
			printf("Cantidad invalida. Se creara el sector scon 1 asiento.\n");
			numAsientos = 1;
		}

		sector->inicial = Letras[i];
		sector->cantidadEspacios = numAsientos;
		sector->asientos = NULL;

		if (numAsientos > 0) {
			sector->asientos = (Asiento *)realloc(sector->asientos, numAsientos * sizeof(Asiento));

			printf("Lista de asientos para %s (%c):\n", sector->nombre, sector->inicial);
			for (int j = 0; j < numAsientos; j++) {
				snprintf(sector->asientos[j].id, MAX_ID_ASIENTO, "%c%d", sector->inicial, j + 1);
				sector->asientos[j].estado = DISPONIBLE;
				printf("- %s\n", sector->asientos[j].id);
			}
		}
	}

	sitio->cantidadSectores = totalSectores;
	printf("Se agregaron %d sectores en el sitio '%s'.\n", cantidadNuevosSectores, sitio->nombre);
}

void resetEspaciosSitio(SitioEvento *sitio) {
	char confirmacion;
	printf("\n¿Esta seguro de resetear todos los asientos de '%s' a DISPONIBLE? (s/n): ", sitio->nombre);
	scanf(" %c", &confirmacion);
	if (confirmacion != 's' && confirmacion != 'S') {
		printf("Operacion cancelada.\n");
		return;
	}
	
	for (int i = 0; i < sitio->cantidadSectores; i++) {
		Sector *sector = &sitio->sectores[i];
		for (int j = 0; j < sector->cantidadEspacios; j++) {
			sector->asientos[j].estado = DISPONIBLE;
		}
	}
	printf("Todos los asientos de '%s' han sido reseteados a DISPONIBLE.\n", sitio->nombre);
}

void gestionarEspaciosSitio(AppData *app) {
	SitioEvento *sitioSeleccionado = seleccionarSitio(app);
	if (sitioSeleccionado == NULL) {
		printf("\nNo se selecciono sitio.\n");
		return;
	}
	
	int opcion;
	do {
		printf("\nGestionando sitio: %s\n", sitioSeleccionado->nombre);
		printf("1. Agregar sectores\n");
		printf("2. Reset espacios\n");
		printf("3. Ver sectores actuales\n");
		printf("4. Volver\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
			case 1:
				agregarSector(sitioSeleccionado);
				break;
			case 2:
				resetEspaciosSitio(sitioSeleccionado);
				break;
			case 3:
				// Mostrar sectores del sitio seleccionado
				printf("\nSectores de %s:\n", sitioSeleccionado->nombre);
				for (int i = 0; i < sitioSeleccionado->cantidadSectores; i++) {
					Sector *sector = &sitioSeleccionado->sectores[i];
					printf("  %s (Inicial: %c, Asientos: %d)\n", sector->nombre, sector->inicial, sector->cantidadEspacios);
				}
				if (sitioSeleccionado->cantidadSectores == 0) {
					printf("  No hay sectores.\n");
				}
				break;
			case 4:
				printf("\nRegresando...\n");
				break;
			default:
				printf("\nOpcion no valida.\n");
				break;
		}
	} while (opcion != 4);
}

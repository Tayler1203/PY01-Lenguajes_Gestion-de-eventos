#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/espacios.h"

static void limpiarBufferEntrada(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void quitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

void mostrarSitiosConSectores(const AppData *app) {
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
}

void gestionarEspaciosSitio(AppData *app) {
}

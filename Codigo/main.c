#include <stdio.h>
#include "headers/menu.h"

int main(void) {
	int opcionPrincipal;
	int opcionAdmin;
	int opcionGeneral;

	do {
		opcionPrincipal = mostrarMenuPrincipal();

		switch (opcionPrincipal) {
			case 1:
				do {
					opcionAdmin = mostrarMenuGestion();

					switch (opcionAdmin) {
						case 1:
							printf("\ntayeler\n");
							break;
						case 2:
							printf("\nchambeeee\n");
							break;
						case 3:
							printf("\naaaaaaa\n");
							break;
						case 4:
							printf("\naaaaaaa\n");
							break;
						case 5:
							printf("\naaaaaaa\n");
							break;
						case 6:
							printf("\naaaaaaaaa\n");
							break;
						case 7:
							printf("\naaaaaaa\n");
							break;
						default:
							printf("\naaaaaaaa\n");
							break;
					}
				} while (opcionAdmin != 7);
				break;

			case 2:
				do {
					opcionGeneral = mostrarMenuUsuarios();

					switch (opcionGeneral) {
						case 1:
							printf("\naaaaaaa\n");
							break;
						case 2:
							printf("\naaaaaaa\n");
							break;
						case 3:
							printf("\naaaaaaa\n");
							break;
						default:
							printf("\naaaaaaaa\n");
							break;
					}
				} while (opcionGeneral != 3);
				break;

			case 3:
				printf("\nSaliendo del sistema...\n");
				break;

			default:
				printf("\nOpcion no valida. Intente de nuevo.\n");
				break;
		}
	} while (opcionPrincipal != 3);

	return 0;
}

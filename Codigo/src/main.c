#include <stdio.h>
#include "../headers/menu.h"
#include "../headers/sitios.h"

int main(void) {
	int opcionPrincipal;
	int opcionAdmin;
	int opcionGeneral;
	int opcionSitios;
	int opcionEspacios;
	int opcionEventos;
	int opcionEstadoEvento;
	int opcionFacturas;
	int opcionEstadisticas;
	AppData app = {0};

	do {
		opcionPrincipal = mostrarMenuPrincipal();

		switch (opcionPrincipal) {
			case 1:
				do {
					opcionAdmin = mostrarMenuGestion();

					switch (opcionAdmin) {
						case 1:
							do {
								opcionSitios = mostrarMenuSitios();

								switch (opcionSitios) {
									case 1:
										printf("\n[Carga en lote de sitios]\n");
										break;
									case 2:
										printf("\n[Listar sitios]\n");
										break;
									case 3:
										agregarSitioManual(&app);
										break;
									case 4:
										printf("\n[Buscar sitio por nombre]\n");
										break;
									case 5:
										printf("\n[Modificar sitio]\n");
										break;
									case 6:
										printf("\n[Eliminar sitio]\n");
										break;
									case 7:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionSitios != 7);
							break;
						case 2:
							do {
								opcionEspacios = mostrarMenuEspacios();

								switch (opcionEspacios) {
									case 1:
										printf("\n[Mostrar sitios con sectores y asientos]\n");
										break;
									case 2:
										printf("\n[Seleccionar sitio para administrar]\n");
										break;
									case 3:
										printf("\n[Agregar sector a un sitio]\n");
										break;
									case 4:
										printf("\n[Reset de espacios por sitio]\n");
										break;
									case 5:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionEspacios != 5);
							break;
						case 3:
							do {
								opcionEventos = mostrarMenuEventos();

								switch (opcionEventos) {
									case 1:
										printf("\n[Crear evento]\n");
										break;
									case 2:
										printf("\n[Ver eventos]\n");
										break;
									case 3:
										printf("\n[Consultar evento]\n");
										break;
									case 4:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionEventos != 4);
							break;
						case 4:
							do {
								opcionEstadoEvento = mostrarMenuEstadoEvento();

								switch (opcionEstadoEvento) {
									case 1:
										printf("\n[Seleccionar evento y ver resumen]\n");
										break;
									case 2:
										printf("\n[Ver recaudacion por sector]\n");
										break;
									case 3:
										printf("\n[Ver asientos por sector]\n");
										break;
									case 4:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionEstadoEvento != 4);
							break;
						case 5:
							do {
								opcionFacturas = mostrarMenuFacturas();

								switch (opcionFacturas) {
									case 1:
										printf("\n[Mostrar todas las facturas]\n");
										break;
									case 2:
										printf("\n[Ver detalle de factura]\n");
										break;
									case 3:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionFacturas != 3);
							break;
						case 6:
							do {
								opcionEstadisticas = mostrarMenuEstadisticas();

								switch (opcionEstadisticas) {
									case 1:
										printf("\n[Top 3 mes-anio con mas eventos]\n");
										break;
									case 2:
										printf("\n[Top 3 productoras por recaudacion]\n");
										break;
									case 3:
										printf("\n[Sitios con eventos y total recaudado]\n");
										break;
									case 4:
										printf("\nRegresando al menu administrativo...\n");
										break;
									default:
										printf("\nOpcion no valida. Intente de nuevo.\n");
										break;
								}
							} while (opcionEstadisticas != 4);
							break;
						case 7:
							printf("\nRegresando al menu principal...\n");
							break;
						default:
							printf("\nOpcion no valida. Intente de nuevo.\n");
							break;
					}
				} while (opcionAdmin != 7);
				break;

			case 2:
				do {
					opcionGeneral = mostrarMenuUsuarios();

					switch (opcionGeneral) {
						case 1:
							printf("\n[Consulta por evento]\n");
							break;
						case 2:
							printf("\n[Compra de boletos]\n");
							break;
						case 3:
							printf("\nRegresando al menu principal...\n");
							break;
						default:
							printf("\nOpcion no valida. Intente de nuevo.\n");
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

#include <stdio.h>
#include "headers/menu.h"

int mostrarMenuPrincipal() {
	printf("\n====================================\n");
	printf("   SISTEMA DE GESTION DE EVENTOS\n");
	printf("====================================\n");
	printf("1. Administrativas\n");
	printf("2. Generales\n");
	printf("3. Salir\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuGestion() {
	printf("\n######## MENU ADMINISTRATIVO ########\n");
	printf("1. Gestion de Sitios de Eventos\n");
	printf("2. Gestion de espacios sitio de eventos\n");
	printf("3. Gestion de Eventos\n");
	printf("4. Estado de evento\n");
	printf("5. Lista de facturas\n");
	printf("6. Estadisticas\n");
	printf("7. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuUsuarios() {
	printf("\n######### MENU GENERALES #########\n");
	printf("1. Consulta por evento\n");
	printf("2. Compra de boletos\n");
	printf("3. Salir\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuSitios() {
	printf("\n#### GESTION DE SITIOS DE EVENTOS ####\n");
	printf("1. Carga en lote desde archivo\n");
	printf("2. Ver sitios\n");
	printf("3. Registrar sitio manual\n");
	printf("4. Buscar sitio por nombre\n");
	printf("5. Modificar sitio\n");
	printf("6. Eliminar sitio\n");
	printf("7. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuEspacios() {
	printf("\n### GESTION DE ESPACIOS DE LOS SITIOS ###\n");
	printf("1. Mostrar sitios con sectores y asientos\n");
	printf("2. Seleccionar sitio para administrar\n");
	printf("3. Agregar sector a un sitio\n");
	printf("4. Reset de espacios por sitio\n");
	printf("5. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuEventos() {
	printf("\n######## GESTION DE EVENTOS ########\n");
	printf("1. Crear evento\n");
	printf("2. Ver eventos\n");
	printf("3. Consultar evento\n");
	printf("4. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuEstadoEvento() {
	printf("\n######## ESTADO DE EVENTO #########\n");
	printf("1. Seleccionar evento y ver resumen\n");
	printf("2. Ver recaudacion por sector\n");
	printf("3. Ver asientos por sector (estado)\n");
	printf("4. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuFacturas() {
	printf("\n######## LISTA DE FACTURAS ########\n");
	printf("1. Mostrar todas las facturas\n");
	printf("2. Ver detalle de factura\n");
	printf("3. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuEstadisticas() {
	printf("\n######### ESTADISTICAS #########\n");
	printf("1. Top 3 mes-año con mas eventos\n");
	printf("2. Top 3 productoras por recaudacion\n");
	printf("3. Sitios con eventos y total recaudado\n");
	printf("4. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

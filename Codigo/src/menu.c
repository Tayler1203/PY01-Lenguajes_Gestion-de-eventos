#include <stdio.h>
#include <string.h>
#include "../headers/menu.h"
#include "../headers/archivos.h"

static void QuitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

int mostrarMenuPrincipal() {
	printf("\n====================================\n");
	printf("   SISTEMA DE GESTION DE EVENTOS\n");
	printf("====================================\n");
	printf("1. Administrativo\n");
	printf("2. General\n");
	printf("3. Salir\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuGestion() {
	printf("\n######## MENU ADMINISTRATIVO ########\n");
	printf("1. Gestion de sitios de eventos\n");
	printf("2. Gestion de espacios y sectores de sitios de eventos\n");
	printf("3. Gestion de eventos\n");
	printf("4. Estado de evento\n");
	printf("5. Registro de facturas\n");
	printf("6. Estadisticas\n");
	printf("7. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuUsuarios() {
	printf("\n######### MENU GENERAL #########\n");
	printf("1. Consulta por evento\n");
	printf("2. Compra de boletos\n");
	printf("3. Volver\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

int mostrarMenuSitios() {
	printf("\n#### GESTION DE SITIOS DE EVENTOS ####\n");
	printf("1. Cargar en lote desde archivo\n");
	printf("2. Ver sitios de eventos\n");
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
	printf("3. Ver estado de asientos por sector\n");
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

void ObtenerDatosSitioManual(char *nombre, char *ubicacion, char *sitioWeb) {
	limpiarBufferEntrada();

	printf("\nNombre del sitio: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	QuitarSaltoDeLinea(nombre);

	printf("Ubicacion del sitio: ");
	fgets(ubicacion, MAX_UBICACION, stdin);
	QuitarSaltoDeLinea(ubicacion);

	printf("Sitio web (opcional): ");
	fgets(sitioWeb, MAX_URL, stdin);
	QuitarSaltoDeLinea(sitioWeb);
}

int loginAdmin(void) {
	char usuario[MAX_NOMBRE];
	char contrasena[MAX_NOMBRE];
	int intentos = 3;
	
	printf("\n====================================\n");
	printf("   ACCESO AL MENU ADMINISTRATIVO\n");
	printf("====================================\n");
	
	while (intentos > 0) {
		limpiarBufferEntrada();
		
		printf("Usuario: ");
		fgets(usuario, MAX_NOMBRE, stdin);
		QuitarSaltoDeLinea(usuario);
		
		printf("Contraseña: ");
		fgets(contrasena, MAX_NOMBRE, stdin);
		QuitarSaltoDeLinea(contrasena);
		
		if (verificarCredenciales(usuario, contrasena)) {
			printf("\n✓ ¡Acceso concedido! Bienvenido.\n\n");
			return 1;
		} else {
			intentos--;
			if (intentos > 0) {
				printf("\n✗ Credenciales invalidas. Intentos restantes: %d\n\n", intentos);
			} else {
				printf("\n✗ Credenciales invalidas. Se agotaron los intentos.\n\n");
			}
		}
	}
	
	return 0;
}

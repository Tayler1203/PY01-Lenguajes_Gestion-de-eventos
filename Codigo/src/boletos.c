#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/boletos.h"
#include "../headers/eventos.h"
#include "../headers/sitios.h"
#include "../headers/archivos.h"

static void limpiarCadena(char *texto) {
	if (texto == NULL) return;
	texto[strcspn(texto, "\r\n")] = '\0';
}

static SectorEvento *buscarSectorEventoPorAsiento(Evento *evento, const char *asientoId, Asiento **asientoOut) {
	if (evento == NULL || asientoId == NULL) return NULL;

	for (int s = 0; s < evento->cantidadSectores; s++) {
		SectorEvento *sectEv = &evento->sectoresEvento[s];
		Sector *sector = sectEv->sector;
		for (int a = 0; a < sector->cantidadEspacios; a++) {
			if (strcmp(sector->asientos[a].id, asientoId) == 0) {
				if (asientoOut != NULL) {
					*asientoOut = &sector->asientos[a];
				}
				return sectEv;
			}
		}
	}

	return NULL;
}

static int esAsientoDuplicado(Asiento **seleccionados, int cantidad, const Asiento *asiento) {
	for (int i = 0; i < cantidad; i++) {
		if (seleccionados[i] == asiento) {
			return 1;
		}
	}
	return 0;
}

// Deja lista la persistencia de facturas en archivo CSV pero no se invoca todavía
static void guardarFacturaEnArchivo(const Factura *factura) {
	if (factura == NULL) return;

	FILE *archivo = fopen(ARCHIVO_FACTURAS, "a");
	if (archivo == NULL) {
		printf("Advertencia: no se pudo abrir archivo de facturas para guardar.\n");
		return;
	}

	// Formato: id,fechaCompra,cedula,nombreComprador,nombreEvento,productora,nombreSitio,fechaEvento,cantidadAsientos,subtotal,costoServicio,total,detalle1|detalle2...
	// detalle: asientoId;sector;costo
	fprintf(archivo, "%d,%s,%s,%s,%s,%s,%s,%s,%d,%.2f,%.2f,%.2f,",
		factura->id,
		factura->fechaCompra,
		factura->cedula,
		factura->nombreComprador,
		factura->nombreEvento,
		factura->productora,
		factura->nombreSitio,
		factura->fechaEvento,
		factura->cantidadAsientos,
		factura->subtotal,
		factura->costoServicio,
		factura->total);

	for (int i = 0; i < factura->cantidadAsientos; i++) {
		DetalleAsiento *d = &factura->detalles[i];
		fprintf(archivo, "%s;%s;%.2f", d->idAsiento, d->nombreSector, d->costo);
		if (i < factura->cantidadAsientos - 1) {
			fputc('|', archivo);
		}
	}

	fputc('\n', archivo);
	fclose(archivo);
}

int verificarDisponibilidad(Asiento **asientos, int cantidad) {
	if (asientos == NULL || cantidad <= 0) {
		return 0;
	}

	for (int i = 0; i < cantidad; i++) {
		if (asientos[i] == NULL || asientos[i]->estado != DISPONIBLE) {
			return 0;
		}
	}

	return 1;
}

static void mostrarAsientosDisponibles(Evento *evento) {
	if (evento == NULL) {
		printf("Evento inválido.\n");
		return;
	}

	printf("\n=== Disponibilidad de asientos en %s ===\n", evento->nombre);
	printf("Productora: %s | Fecha: %s\n", evento->productora, evento->fecha);
	printf("Sitio: %s\n\n", evento->sitio->nombre);

	for (int s = 0; s < evento->cantidadSectores; s++) {
		SectorEvento *sectEv = &evento->sectoresEvento[s];
		Sector *sector = sectEv->sector;
		int disponibles = 0;
		for (int a = 0; a < sector->cantidadEspacios; a++) {
			if (sector->asientos[a].estado == DISPONIBLE) {
				disponibles++;
			}
		}

		printf("  Sector: %s (Inicial: %c)\n", sector->nombre, sector->inicial);
		printf("    Asientos disponibles: %d/%d\n", disponibles, sector->cantidadEspacios);
		printf("    Precio por asiento: $%.2f\n", sectEv->montoPorAsiento);
		printf("    Asientos: ");
		for (int a = 0; a < sector->cantidadEspacios; a++) {
			if (sector->asientos[a].estado == DISPONIBLE) {
				printf("[%s] ", sector->asientos[a].id);
			} else {
				printf("(V) ");
			}
		}
		printf("\n\n");
	}
}

static void marcarAsientosVendidos(Asiento **asientos, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		if (asientos[i] != NULL) {
			asientos[i]->estado = VENDIDO;
		}
	}
}

void generarFactura(AppData *app, Evento *evento, Asiento **asientos, SectorEvento **sectores, int cantidad, const char *cedula, const char *nombre) {
	if (app == NULL || evento == NULL || asientos == NULL || sectores == NULL || cantidad <= 0 || cedula == NULL || nombre == NULL) {
		printf("No se pudo generar la factura: datos incompletos.\n");
		return;
	}

	if (!verificarDisponibilidad(asientos, cantidad)) {
		printf("Algunos asientos ya no estan disponibles. Compra cancelada.\n");
		return;
	}

	Factura factura = {0};
	factura.cantidadAsientos = cantidad;

	time_t ahora = time(NULL);
	struct tm *infoTiempo = localtime(&ahora);
	if (infoTiempo != NULL) {
		strftime(factura.fechaCompra, MAX_FECHA, "%Y-%m-%d", infoTiempo);
	}

	strncpy(factura.cedula, cedula, MAX_CEDULA - 1);
	factura.cedula[MAX_CEDULA - 1] = '\0';
	strncpy(factura.nombreComprador, nombre, MAX_NOMBRE - 1);
	factura.nombreComprador[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.nombreEvento, evento->nombre, MAX_NOMBRE - 1);
	factura.nombreEvento[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.productora, evento->productora, MAX_NOMBRE - 1);
	factura.productora[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.nombreSitio, evento->sitio->nombre, MAX_NOMBRE - 1);
	factura.nombreSitio[MAX_NOMBRE - 1] = '\0';
	strncpy(factura.fechaEvento, evento->fecha, MAX_FECHA - 1);
	factura.fechaEvento[MAX_FECHA - 1] = '\0';

	factura.detalles = malloc(cantidad * sizeof(DetalleAsiento));
	if (factura.detalles == NULL) {
		printf("Error de memoria al generar factura. Compra cancelada.\n");
		return;
	}

	double subtotal = 0.0;
	for (int i = 0; i < cantidad; i++) {
		DetalleAsiento *detalle = &factura.detalles[i];
		const Asiento *asiento = asientos[i];
		SectorEvento *sectorEv = sectores[i];
		if (asiento == NULL || sectorEv == NULL || sectorEv->sector == NULL) {
			printf("Datos de asiento invalidos. Compra cancelada.\n");
			free(factura.detalles);
			return;
		}

		strncpy(detalle->idAsiento, asiento->id, MAX_ID_ASIENTO - 1);
		detalle->idAsiento[MAX_ID_ASIENTO - 1] = '\0';
		strncpy(detalle->nombreSector, sectorEv->sector->nombre, MAX_NOMBRE - 1);
		detalle->nombreSector[MAX_NOMBRE - 1] = '\0';
		detalle->costo = sectorEv->montoPorAsiento;
		subtotal += detalle->costo;
	}

	factura.subtotal = subtotal;
	factura.costoServicio = subtotal * COSTO_SERVICIO;
	factura.total = factura.subtotal + factura.costoServicio;

	Factura *nuevoArreglo = realloc(app->facturas, (app->cantidadFacturas + 1) * sizeof(Factura));
	if (nuevoArreglo == NULL) {
		printf("No se pudo reservar espacio para la factura. Compra cancelada.\n");
		free(factura.detalles);
		return;
	}

	factura.id = app->contadorFacturas + 1;
	app->facturas = nuevoArreglo;
	app->facturas[app->cantidadFacturas] = factura;
	app->cantidadFacturas++;
	app->contadorFacturas = factura.id;

	marcarAsientosVendidos(asientos, cantidad);

	agregarFacturaAlArchivo(&app->facturas[app->cantidadFacturas - 1]);

	printf("\nCompra realizada exitosamente!\n");
	printf("Factura #%d - Fecha compra: %s\n", factura.id, factura.fechaCompra);
	printf("Cliente: %s (%s)\n", factura.nombreComprador, factura.cedula);
	printf("Evento: %s | Productora: %s | Fecha: %s | Sitio: %s\n", factura.nombreEvento, factura.productora, factura.fechaEvento, factura.nombreSitio);
	printf("Asientos comprados (%d): ", factura.cantidadAsientos);
	for (int i = 0; i < factura.cantidadAsientos; i++) {
		printf("%s%s", factura.detalles[i].idAsiento, (i < factura.cantidadAsientos - 1) ? ", " : "");
	}
	printf("\nSubtotal: $%.2f | Costo servicio (5%%): $%.2f | Total: $%.2f\n", factura.subtotal, factura.costoServicio, factura.total);
}

void comprarBoletos(AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("\nNo hay eventos disponibles.\n");
		return;
	}

	printf("\n=== Eventos disponibles ===\n");
	for (int i = 0; i < app->cantidadEventos; i++) {
		printf("%d. %s - %s (%s)\n", i + 1, app->eventos[i].nombre,
			app->eventos[i].productora, app->eventos[i].fecha);
	}

	printf("Seleccione evento (0 para cancelar): ");
	int opEvento;
	if (scanf("%d", &opEvento) != 1) {
		limpiarBufferEntrada();
		printf("Entrada invalida. Compra cancelada.\n");
		return;
	}

	if (opEvento == 0) {
		printf("Compra cancelada por usuario.\n");
		return;
	}

	if (opEvento < 1 || opEvento > app->cantidadEventos) {
		printf("Opción inválida. Compra cancelada.\n");
		return;
	}

	Evento *evento = &app->eventos[opEvento - 1];
	mostrarAsientosDisponibles(evento);

	char input[256];
	printf("\nIngrese asientos a comprar (separados por coma, ej: A1,B2): ");
	limpiarBufferEntrada();
	if (fgets(input, sizeof(input), stdin) == NULL) {
		printf("Error de entrada. Compra cancelada.\n");
		return;
	}
	limpiarCadena(input);
	if (input[0] == '\0') {
		printf("No se ingresaron asientos. Compra cancelada.\n");
		return;
	}

	// Contar asientos solicitados
	Asiento **seleccionados = NULL;
	SectorEvento **sectoresSeleccionados = NULL;
	int cantidadSeleccionados = 0;

	char *token = strtok(input, ",;");
	while (token != NULL) {
		char asientoId[MAX_ID_ASIENTO];
		sscanf(token, " %9[^\n]", asientoId);
		limpiarCadena(asientoId);

		if (asientoId[0] == '\0') {
			token = strtok(NULL, ",;");
			continue;
		}

		Asiento *asiento = NULL;
		SectorEvento *sectorEv = buscarSectorEventoPorAsiento(evento, asientoId, &asiento);
		if (sectorEv == NULL) {
			printf("Asiento %s no existe para el evento %s. Compra cancelada.\n", asientoId, evento->nombre);
			free(seleccionados);
			free(sectoresSeleccionados);
			return;
		}

		if (asiento->estado != DISPONIBLE) {
			printf("Asiento %s ya esta vendido. Compra cancelada.\n", asientoId);
			free(seleccionados);
			free(sectoresSeleccionados);
			return;
		}

		if (esAsientoDuplicado(seleccionados, cantidadSeleccionados, asiento)) {
			printf("Asiento %s ingresado mas de una vez. Compra cancelada.\n", asientoId);
			free(seleccionados);
			free(sectoresSeleccionados);
			return;
		}

		Asiento **temporalA = realloc(seleccionados, (cantidadSeleccionados + 1) * sizeof(Asiento *));
		SectorEvento **temporalS = realloc(sectoresSeleccionados, (cantidadSeleccionados + 1) * sizeof(SectorEvento *));
		if (temporalA == NULL || temporalS == NULL) {
			printf("Error de memoria al seleccionar asientos.\n");
			free(seleccionados);
			free(sectoresSeleccionados);
			return;
		}
		seleccionados = temporalA;
		sectoresSeleccionados = temporalS;
		seleccionados[cantidadSeleccionados] = asiento;
		sectoresSeleccionados[cantidadSeleccionados] = sectorEv;
		cantidadSeleccionados++;

		token = strtok(NULL, ",;");
	}

	if (cantidadSeleccionados == 0) {
		printf("No se seleccionaron asientos validos. Compra cancelada.\n");
		free(seleccionados);
		free(sectoresSeleccionados);
		return;
	}

	char cedula[MAX_CEDULA];
	char nombreComprador[MAX_NOMBRE];
	
	printf("\nCedula del comprador: ");
	if (fgets(cedula, sizeof(cedula), stdin) == NULL) {
		printf("Error de entrada. Compra cancelada.\n");
		free(seleccionados);
		free(sectoresSeleccionados);
		return;
	}
	limpiarCadena(cedula);
	if (cedula[0] == '\0') {
		printf("Cedula obligatoria. Compra cancelada.\n");
		free(seleccionados);
		free(sectoresSeleccionados);
		return;
	}

	printf("Nombre del comprador: ");
	if (fgets(nombreComprador, sizeof(nombreComprador), stdin) == NULL) {
		printf("Error de entrada. Compra cancelada.\n");
		free(seleccionados);
		free(sectoresSeleccionados);
		return;
	}
	limpiarCadena(nombreComprador);
	if (nombreComprador[0] == '\0') {
		printf("Nombre obligatorio. Compra cancelada.\n");
		free(seleccionados);
		free(sectoresSeleccionados);
		return;
	}

	generarFactura(app, evento, seleccionados, sectoresSeleccionados, cantidadSeleccionados, cedula, nombreComprador);

	free(seleccionados);
	free(sectoresSeleccionados);
}


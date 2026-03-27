#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/eventos.h"
#include "../headers/archivos.h"



static void quitarSaltoDeLinea(char *texto) {
	texto[strcspn(texto, "\r\n")] = '\0';
}

void mostrarDetalleEvento(const Evento *evento) {
	if (evento == NULL) {
		printf("Evento invalido.\n");
		return;
	}

	printf("\n--- Detalle de evento: %s ---\n", evento->nombre);
	printf("Productora : %s\n", evento->productora);
	printf("Fecha      : %s\n", evento->fecha);
	printf("Sitio      : %s\n", evento->sitio ? evento->sitio->nombre : "(sin sitio)");
	printf("Sectores   : %d\n", evento->cantidadSectores);
	for (int i = 0; i < evento->cantidadSectores; i++) {
		SectorEvento *se = &evento->sectoresEvento[i];
		Sector *s = se->sector;
		if (s == NULL) continue;
		printf("  %d. %s (inicial %c) - precio: %.2f - asientos: %d\n", 
			  i + 1, s->nombre, s->inicial, se->montoPorAsiento, s->cantidadEspacios);
	}
}

void listarEventos(const AppData *app) {
	if (app == NULL) {
		printf("Aplicacion no inicializada.\n");
		return;
	}

	if (app->cantidadEventos == 0) {
		printf("\nNo hay eventos registrados.\n");
		return;
	}

	printf("\n--- Eventos Registrados ---\n");
	for (int i = 0; i < app->cantidadEventos; i++) {
		Evento *evento = &app->eventos[i];
		printf("%d. %s | %s | %s | sitio: %s\n", 
			  i + 1, evento->nombre, evento->productora, evento->fecha,
			  evento->sitio ? evento->sitio->nombre : "(sin sitio)");
	}
}

Evento *seleccionarEvento(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos disponibles a seleccionar.\n");
		return NULL;
	}

	for (int i = 0; i < app->cantidadEventos; i++) {
		printf("%d) %s (%s)\n", i + 1, app->eventos[i].nombre, app->eventos[i].fecha);
	}

	printf("Seleccione un evento (0 para cancelar): ");
	int opcion;
	if (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > app->cantidadEventos) {
		limpiarBufferEntrada();
		printf("Seleccion invalida.\n");
		return NULL;
	}
	limpiarBufferEntrada();

	if (opcion == 0) {
		return NULL;
	}

	return &app->eventos[opcion - 1];
}

void mostrarEstadoEvento(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos para mostrar estado.\n");
		return;
	}

	Evento *evento = seleccionarEvento(app);
	if (evento == NULL) return;

	mostrarDetalleEvento(evento);
}

static void calcularEstadoSector(const Evento *evento, int indexSector, int *vendidos, int *disponibles, double *recaudacion) {
	*vendidos = *disponibles = 0;
	*recaudacion = 0.0;
	if (evento == NULL || indexSector < 0 || indexSector >= evento->cantidadSectores) return;

	SectorEvento *sectEv = (SectorEvento *)&evento->sectoresEvento[indexSector];
	Sector *sector = sectEv->sector;
	for (int i = 0; i < sector->cantidadEspacios; i++) {
		if (sector->asientos[i].estado == VENDIDO) {
			(*vendidos)++;
			*recaudacion += sectEv->montoPorAsiento;
		} else {
			(*disponibles)++;
		}
	}
}

void mostrarResumenEvento(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos para mostrar resumen.\n");
		return;
	}

	Evento *evento = seleccionarEvento(app);
	if (evento == NULL) return;

	printf("\n--- Resumen de evento: %s ---\n", evento->nombre);
	printf("Productora: %s | Fecha: %s | Sitio: %s\n", evento->productora, evento->fecha, evento->sitio->nombre);

	int totalVendidos = 0;
	int totalDisponibles = 0;
	double totalRecaudacion = 0.0;

	for (int i = 0; i < evento->cantidadSectores; i++) {
		int vendidos, disponibles;
		double recaud;
		calcularEstadoSector(evento, i, &vendidos, &disponibles, &recaud);
		totalVendidos += vendidos;
		totalDisponibles += disponibles;
		totalRecaudacion += recaud;
		Sector *sector = evento->sectoresEvento[i].sector;
		printf("Sector %s: vendidos %d, disponibles %d, recaudacion %.2f\n", sector->nombre, vendidos, disponibles, recaud);
	}

	printf("\nTotales: vendidos %d, disponibles %d, recaudacion total %.2f\n", totalVendidos, totalDisponibles, totalRecaudacion);
}

void mostrarRecaudacionPorSector(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos para mostrar recaudacion.\n");
		return;
	}

	Evento *evento = seleccionarEvento(app);
	if (evento == NULL) return;

	printf("\n--- Recaudacion por sector para %s ---\n", evento->nombre);

	for (int i = 0; i < evento->cantidadSectores; i++) {
		int vendidos, disponibles;
		double recaud;
		calcularEstadoSector(evento, i, &vendidos, &disponibles, &recaud);
		Sector *sector = evento->sectoresEvento[i].sector;
		printf("Sector %s -> vendidos %d, disponibles %d, recaudacion %.2f\n", sector->nombre, vendidos, disponibles, recaud);
	}
}

void mostrarAsientosPorSector(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos para mostrar asientos.\n");
		return;
	}

	Evento *evento = seleccionarEvento(app);
	if (evento == NULL) return;

	printf("\n--- Asientos por sector en %s ---\n", evento->nombre);

	for (int i = 0; i < evento->cantidadSectores; i++) {
		SectorEvento *sectorEvento = &evento->sectoresEvento[i];
		Sector *sector = sectorEvento->sector;
		printf("Sector %s (precio %.2f):\n", sector->nombre, sectorEvento->montoPorAsiento);
		for (int j = 0; j < sector->cantidadEspacios; j++) {
			printf("  %s -> %s\n", sector->asientos[j].id,
				sector->asientos[j].estado == DISPONIBLE ? "DISPONIBLE" : "VENDIDO");
		}
	}
}

void consultarEventosFuturos(const AppData *app) {
	if (app == NULL || app->cantidadEventos == 0) {
		printf("No hay eventos registrados.\n");
		return;
	}

	limpiarBufferEntrada();

	char fechaInicio[MAX_FECHA];
	printf("\nIngrese fecha inicial (YYYY-MM-DD): ");
	fgets(fechaInicio, sizeof(fechaInicio), stdin);
	fechaInicio[strcspn(fechaInicio, "\r\n")] = '\0';
	if (fechaInicio[0] == '\0') {
		printf("Fecha invalida.\n");
		return;
	}

	Evento **eventosFiltrados = malloc(app->cantidadEventos * sizeof(Evento *));
	if (eventosFiltrados == NULL) {
		printf("Error de memoria.\n");
		return;
	}

	int cantidadFiltrada = 0;
	for (int i = 0; i < app->cantidadEventos; i++) {
		if (strcmp(app->eventos[i].fecha, fechaInicio) >= 0) {
			eventosFiltrados[cantidadFiltrada++] = &app->eventos[i];
		}
	}

	if (cantidadFiltrada == 0) {
		printf("No hay eventos futuros a partir de esa fecha.\n");
		free(eventosFiltrados);
		return;
	}

	for (int i = 0; i < cantidadFiltrada - 1; i++) {
		for (int j = i + 1; j < cantidadFiltrada; j++) {
			if (strcmp(eventosFiltrados[i]->fecha, eventosFiltrados[j]->fecha) > 0) {
				Evento *tmp = eventosFiltrados[i];
				eventosFiltrados[i] = eventosFiltrados[j];
				eventosFiltrados[j] = tmp;
			}
		}
	}

	printf("\n--- Eventos a partir de %s ---\n", fechaInicio);
	for (int i = 0; i < cantidadFiltrada; i++) {
		printf("%d. %s - %s\n", i + 1, eventosFiltrados[i]->nombre, eventosFiltrados[i]->fecha);
	}

	int seleccion = -1;
	printf("\nSeleccione un evento (0 para cancelar): ");
	if (scanf("%d", &seleccion) != 1 || seleccion < 0 || seleccion > cantidadFiltrada) {
		printf("Seleccion invalida.\n");
		limpiarBufferEntrada();
		free(eventosFiltrados);
		return;
	}
	limpiarBufferEntrada();

	if (seleccion == 0) {
		printf("Consulta cancelada.\n");
		free(eventosFiltrados);
		return;
	}

	Evento *evento = eventosFiltrados[seleccion - 1];
	if (evento == NULL) {
		printf("Evento no encontrado.\n");
		free(eventosFiltrados);
		return;
	}

	printf("\n--- Detalle de evento seleccionado ---\n");
	printf("Nombre: %s\n", evento->nombre);
	printf("Productora: %s\n", evento->productora);
	printf("Sitio: %s\n", evento->sitio ? evento->sitio->nombre : "(sin sitio)");
	printf("Fecha: %s\n", evento->fecha);

	printf("\nSectores:\n");
	for (int i = 0; i < evento->cantidadSectores; i++) {
		SectorEvento *sectEv = &evento->sectoresEvento[i];
		Sector *sector = sectEv->sector;
		if (sector == NULL) continue;

		int vendidos, disponibles;
		double recaud;
		calcularEstadoSector(evento, i, &vendidos, &disponibles, &recaud);

		printf("  - %s | Precio: %.2f | Total: %d | Vendidos: %d | Disponibles: %d\n",
			sector->nombre, sectEv->montoPorAsiento, sector->cantidadEspacios, vendidos, disponibles);
	}

	free(eventosFiltrados);
}


static Sector *copiarSector(const Sector *sectorOrigen) {
	if (sectorOrigen == NULL) return NULL;

	Sector *sectorCopia = malloc(sizeof(Sector));
	if (sectorCopia == NULL) return NULL;

	*sectorCopia = *sectorOrigen;
	sectorCopia->asientos = malloc(sectorOrigen->cantidadEspacios * sizeof(Asiento));
	if (sectorCopia->asientos == NULL) {
		free(sectorCopia);
		return NULL;
	}
	for (int i = 0; i < sectorOrigen->cantidadEspacios; i++) {
		sectorCopia->asientos[i] = sectorOrigen->asientos[i];
	}
	return sectorCopia;
}

void crearEvento(AppData *app) {
	if (app->cantidadSitios == 0) {
		printf("\nDebe crear al menos un sitio antes de crear un evento.\n");
		return;
	}

	printf("\n--- Crear Evento Manual ---\n");
	char nombre[MAX_NOMBRE];
	char productora[MAX_NOMBRE];
	char fecha[MAX_FECHA];

	limpiarBufferEntrada();
	printf("Nombre del evento: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	quitarSaltoDeLinea(nombre);

	printf("Productora: ");
	fgets(productora, MAX_NOMBRE, stdin);
	quitarSaltoDeLinea(productora);

	printf("Fecha (YYYY-MM-DD): ");
	fgets(fecha, MAX_FECHA, stdin);
	quitarSaltoDeLinea(fecha);

	printf("\nSeleccione el sitio para el evento:\n");
	for (int i = 0; i < app->cantidadSitios; i++) {
		printf("%d) %s (%s)\n", i + 1, app->sitios[i].nombre, app->sitios[i].ubicacion);
	}

	int indiceSitio = 0;
	printf("Opcion: ");
	if (scanf("%d", &indiceSitio) != 1) {
		printf("Entrada invalida. Operacion abortada.\n");
		limpiarBufferEntrada();
		return;
	}
	limpiarBufferEntrada();

	if (indiceSitio <= 0 || indiceSitio > app->cantidadSitios) {
		printf("Sitio seleccionado invalido. Operacion abortada.\n");
		return;
	}

	SitioEvento *sitioSeleccionado = &app->sitios[indiceSitio - 1];
	if (sitioSeleccionado->cantidadSectores == 0) {
		printf("El sitio seleccionado no tiene sectores definidos. Agregue sectores primero.\n");
		return;
	}

	Evento *nuevoArreglo = realloc(app->eventos, (app->cantidadEventos + 1) * sizeof(Evento));
	if (nuevoArreglo == NULL) {
		printf("No se pudo asignar memoria para el nuevo evento.\n");
		return;
	}

	app->eventos = nuevoArreglo;
	Evento *nuevoEvento = &app->eventos[app->cantidadEventos];

	strncpy(nuevoEvento->nombre, nombre, MAX_NOMBRE - 1);
	nuevoEvento->nombre[MAX_NOMBRE - 1] = '\0';
	strncpy(nuevoEvento->productora, productora, MAX_NOMBRE - 1);
	nuevoEvento->productora[MAX_NOMBRE - 1] = '\0';
	strncpy(nuevoEvento->fecha, fecha, MAX_FECHA - 1);
	nuevoEvento->fecha[MAX_FECHA - 1] = '\0';

	nuevoEvento->sitio = sitioSeleccionado;
	nuevoEvento->cantidadSectores = sitioSeleccionado->cantidadSectores;
	nuevoEvento->sectoresEvento = malloc(nuevoEvento->cantidadSectores * sizeof(SectorEvento));
	if (nuevoEvento->sectoresEvento == NULL) {
		printf("No se pudo asignar memoria para los sectores del evento.\n");
		return;
	}

	for (int i = 0; i < nuevoEvento->cantidadSectores; i++) {
		Sector *sectorCopiado = copiarSector(&sitioSeleccionado->sectores[i]);
		if (sectorCopiado == NULL) {
			printf("No se pudo copiar sector %s para el evento.\n", sitioSeleccionado->sectores[i].nombre);
			for (int j = 0; j < i; j++) {
				free(nuevoEvento->sectoresEvento[j].sector->asientos);
				free(nuevoEvento->sectoresEvento[j].sector);
			}
			free(nuevoEvento->sectoresEvento);
			return;
		}
		nuevoEvento->sectoresEvento[i].sector = sectorCopiado;
		printf("Monto por asiento para sector '%s': ", sectorCopiado->nombre);
		if (scanf("%lf", &nuevoEvento->sectoresEvento[i].montoPorAsiento) != 1) {
			printf("Monto invalido. Operacion abortada.\n");
			limpiarBufferEntrada();
			for (int j = 0; j <= i; j++) {
				free(nuevoEvento->sectoresEvento[j].sector->asientos);
				free(nuevoEvento->sectoresEvento[j].sector);
			}
			free(nuevoEvento->sectoresEvento);
			return;
		}
		limpiarBufferEntrada();
	}

	app->cantidadEventos++;

	if (GuardarEventosEnArchivo(app, nuevoEvento)) {
		printf("Evento guardado correctamente en archivo.\n");
	} else {
		printf("Error al guardar evento en archivo.\n");
	}
}

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "estructuras.h"

/*
 * inicializarApp
 * Objetivo:    Poner todos los punteros en NULL y contadores en 0.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 * Restriccion: Debe llamarse antes que cualquier otra funcion
 */
void inicializarApp(AppData *app);

/*
 * liberarApp
 * Objetivo:    Liberar toda la memoria dinamica de AppData.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 */
void liberarApp(AppData *app);

/*
 * asegurarDirectorioDatos
 * Objetivo:    Crear el directorio "datos/" si no existe.
 * Entrada:     void
 * Salida:      void
 */
void asegurarDirectorioDatos();

/*
 * cargarDatos
 * Objetivo:    Leer sitios, eventos y facturas desde archivos
 *              txt al inicio del programa.
 * Entrada:     app - puntero a AppData
 * Salida:      void (llena los arreglos en app por referencia)
 */
void cargarDatos(AppData *app);

/*
 * guardarDatos
 * Objetivo:    Escribir toda la informacion en memoria a los
 *              archivos txt antes de salir.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 * Restriccion: Sobreescribe los archivos existentes
 */
void guardarDatos(AppData *app);

/*
 * verificarCredenciales
 * Objetivo:    Leer usuario y contraseña del archivo y
 *              comparar con la entrada del usuario.
 * Entrada:     usuario    - string ingresado por el usuario
 *              contrasena - string ingresado por el usuario
 * Salida:      1 si las credenciales son validas, 0 si no
 */
int verificarCredenciales(const char *usuario, const char *contrasena);

/*
 * GuardarSitiosEnArchivo
 * Objetivo:    Agregar un sitio al archivo de sitios en formato CSV.
 * Formato:     nombre,ubicacion,sitioWeb
 * Entrada:     app, nombre, ubicacion, sitioWeb
 * Salida:      1 si guarda correctamente, 0 si falla
 */
int GuardarSitiosEnArchivo(const AppData *app, const char *nombre, const char *ubicacion, const char *sitioWeb);

/*
 * reescribirArchivoSitios
 * Objetivo:    Sobrescribir el archivo de sitios con el contenido actual en memoria.
 * Entrada:     app - puntero a AppData
 * Salida:      1 si se pudo escribir, 0 en caso de error
 */
int reescribirArchivoSitios(const AppData *app);

/*
 * GuardarEventosEnArchivo
 * Objetivo:    Agregar un evento al archivo de eventos en formato CSV.
 * Formato:     nombre,productora,fecha,nombreSitio,cantidadSectores,monto1,monto2,...
 * Entrada:     app, evento
 * Salida:      1 si guarda correctamente, 0 si falla
 */
int GuardarEventosEnArchivo(const AppData *app, const Evento *evento);

/*
 * cargarEstadosAsientos
 * Objetivo:    Leer el estado de asientos desde archivo y aplicarlos a eventos.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica asientos por referencia)
 */
void cargarEstadosAsientos(AppData *app);

/*
 * guardarEstadosAsientos
 * Objetivo:    Guardar el estado actual de todos los asientos de todos los eventos.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 */
void guardarEstadosAsientos(const AppData *app);

/*
 * cargarSectoresDesdeArchivo
 * Objetivo:    Leer sectores desde archivo y asignarlos a los sitios.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica sitios por referencia)
 */
void cargarSectoresDesdeArchivo(AppData *app);

/*
 * cargarFacturasDesdeArchivo
 * Objetivo:    Leer facturas desde archivo y cargarlas en memoria.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica app->facturas y app->cantidadFacturas)
 */
void cargarFacturasDesdeArchivo(AppData *app);

/*
 * guardarFacturasEnArchivo
 * Objetivo:    Escribir todas las facturas en memoria al archivo.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 */
void guardarFacturasEnArchivo(const AppData *app);

/*
 * agregarFacturaAlArchivo
 * Objetivo:    Agregar una factura individual al archivo (append).
 * Entrada:     factura - puntero a la factura a guardar
 * Salida:      void
 */
void agregarFacturaAlArchivo(const Factura *factura);

void cargarEventosDesdeArchivo(AppData *app);

/*
 * guardarSectoresEnArchivo
 * Objetivo:    Guardar todos los sectores de todos los sitios.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 */
void guardarSectoresEnArchivo(const AppData *app);

/*
 * limpiarBufferEntrada
 * Objetivo:    Limpiar el buffer de entrada stdin eliminando
 *              caracteres residuales del ultima lectura.
 * Entrada:     void
 * Salida:      void
 */
void limpiarBufferEntrada(void);

#endif

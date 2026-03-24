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
 *              comparar con la entrada del usuario (RF-05).
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
 * GuardarEventosEnArchivo
 * Objetivo:    Agregar un evento al archivo de eventos en formato CSV.
 * Formato:     nombre,productora,fecha,nombreSitio,cantidadSectores,monto1,monto2,...
 * Entrada:     app, evento
 * Salida:      1 si guarda correctamente, 0 si falla
 */
int GuardarEventosEnArchivo(const AppData *app, const Evento *evento);

/*
 * cargarSectoresDesdeArchivo
 * Objetivo:    Leer sectores desde archivo y asignarlos a los sitios.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica sitios por referencia)
 */
void cargarSectoresDesdeArchivo(AppData *app);

/*
 * guardarSectoresEnArchivo
 * Objetivo:    Guardar todos los sectores de todos los sitios.
 * Entrada:     app - puntero a AppData
 * Salida:      void
 */
void guardarSectoresEnArchivo(const AppData *app);

#endif

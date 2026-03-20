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
 *              contraseña - string ingresado por el usuario
 * Salida:      1 si las credenciales son validas, 0 si no
 */
int verificarCredenciales(const char *usuario, const char *contraseña);

#endif

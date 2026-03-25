#ifndef SITIOS_H
#define SITIOS_H

#include "estructuras.h"

/*
 * listarSitios
 * Objetivo:    Mostrar todos los sitios registrados con su
 *              informacion basica.
 * Entrada:     app - puntero a AppData (solo lectura)
 * Salida:      void (imprime en consola)
 */
void listarSitios(const AppData *app);

/*
 * agregarSitioManual
 * Objetivo:    Solicitar nombre, ubicacion y sitio web por
 *              consola y agregar el sitio si el nombre no
 *              existe.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica app->sitios por referencia)
 * Restriccion: El nombre es unico; rechaza duplicados
 */
void agregarSitioManual(AppData *app);

/*
 * cargarSitiosDesdeArchivo
 * Objetivo:    Leer un archivo CSV con registros de sitios e
 *              insertar unicamente los nuevos.
 *              Formato de cada linea: nombre,ubicacion,sitioWeb
 *              El campo sitioWeb es opcional.
 * Entrada:     app  - puntero a AppData
 *              ruta - ruta del archivo a leer
 * Salida:      void (modifica app->sitios por referencia)
 * Restriccion: Ignora registros cuyo nombre ya existe
 */
void cargarSitiosDesdeArchivo(AppData *app, const char *ruta);

/*
 * cargarSitiosDesdeArchivoConRuta
 * Objetivo:    Solicitar al usuario la ruta de un archivo CSV
 *              e importar los sitios desde ese archivo.
 * Entrada:     app - puntero a AppData
 * Salida:      void (modifica app->sitios por referencia)
 * Restriccion: Ignora registros cuyo nombre ya existe
 */
void cargarSitiosDesdeArchivoConRuta(AppData *app);

/*
 * buscarSitioPorNombre
 * Objetivo:    Busqueda lineal de un sitio por nombre exacto.
 * Entrada:     app    - puntero a AppData
 *              nombre - string a buscar
 * Salida:      puntero al SitioEvento encontrado, NULL si no existe
 */
SitioEvento *buscarSitioPorNombre(const AppData *app, const char *nombre);

/*
 * seleccionarSitio
 * Objetivo:    Mostrar lista numerada de sitios y retornar el
 *              elegido por el usuario.
 * Entrada:     app - puntero a AppData
 * Salida:      puntero al SitioEvento seleccionado,
 *              NULL si el usuario cancela
 */
SitioEvento *seleccionarSitio(const AppData *app);

#endif

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>

/*
*   MACROS - Tamaños de campos y valores constantes
*   nombre sitio, ubicacion, sitio web
*   nombre sector, inicial
*   nombre evento, productora, fecha
*   cedula, nombre comprador, fecha compra
*   costo servicio = 5% del subtotal
 */
#define MAX_NOMBRE       100
#define MAX_UBICACION    150
#define MAX_URL          150
#define MAX_CEDULA        20
#define MAX_FECHA         20
#define MAX_ID_ASIENTO    10
#define COSTO_SERVICIO  0.05

#define ARCHIVO_CREDENCIALES  "../data/credenciales.txt"
#define ARCHIVO_SITIOS        "../data/sitios.txt"
#define ARCHIVO_EVENTOS       "../data/eventos.txt"
#define ARCHIVO_FACTURAS      "../data/facturas.txt"
#define ARCHIVO_SECTORES      "../data/sectores.txt"

/*
*   EstadoAsiento
*   Cada asiento tiene exactamente uno de estos dos estados.
*   Se usa int en archivos para no depender del valor del enum.
*/
typedef enum {
    DISPONIBLE = 0,
    VENDIDO    = 1
} EstadoAsiento;

/* 
*   Asiento
*   - id: generado automaticamente como inicial+numero 
*   - estado: DISPONIBLE o VENDIDO
*   Restriccion: id es de solo lectura una vez generado 
 */
typedef struct {
    char          id[MAX_ID_ASIENTO];
    EstadoAsiento estado;
} Asiento;

/*
*   Sector  
*   - nombre: identificador descriptivo del sector (ej. "VIP")
*   - inicial: caracter unico para generar IDs de asientos 
*   - cantidadEspacios: total de asientos en este sector
*   - asientos: arreglo dinamico de tamaño cantidadEspacios 
*   Restriccion: los asientos se generan automaticamente al crear
*   el sector, no se agregan uno a uno
 */
typedef struct {
    char     nombre[MAX_NOMBRE];
    char     inicial;
    int      cantidadEspacios;
    Asiento *asientos;
} Sector;

/*
*   SitioEvento  
*   - nombre: clave unica del sitio
*   - ubicacion, sitioWeb: informacion del lugar
*   - sectores: arreglo dinamico de sectores 
*   - cantidadSectores: tamaño actual del arreglo
*   Restriccion: no pueden existir dos sitios con el mismo nombre
 */
typedef struct {
    char    nombre[MAX_NOMBRE];
    char    ubicacion[MAX_UBICACION];
    char    sitioWeb[MAX_URL];
    int     cantidadSectores;
    Sector *sectores;
} SitioEvento;

/*
*   SectorEvento  
*   Vincula un Sector de un sitio con el monto definido para
*   ese sector en un evento concreto.
*   - sector: puntero al Sector original en el SitioEvento
*   - montoPorAsiento: precio fijado al crear el evento 
*   Razon de existencia: el mismo sector puede tener precios
*   distintos en eventos diferentes; no se puede guardar el
*   monto dentro de Sector porque Sector pertenece al sitio,
*   no al evento.
 */
typedef struct {
    Sector *sector;
    double  montoPorAsiento;
} SectorEvento;

/*
*   Evento
*   - nombre, productora, fecha: datos basicos del evento
*   - sitio: puntero al SitioEvento asociado
*             no se duplica la info del sitio
*   - sectoresEvento: arreglo dinamico de SectorEvento,
*             uno por cada sector del sitio
*   - cantidadSectores: tamaño del arreglo sectoresEvento,
*             debe coincidir con sitio->cantidadSectores
*/
typedef struct {
    char          nombre[MAX_NOMBRE];
    char          productora[MAX_NOMBRE];
    char          fecha[MAX_FECHA];
    SitioEvento  *sitio;
    SectorEvento *sectoresEvento;
    int           cantidadSectores;
} Evento;

/*
*   DetalleAsiento  
*   Una linea dentro de la factura por cada asiento comprado.
*   - idAsiento: copia del id del asiento (ej. "A1")
*   - nombreSector: copia del nombre del sector
*   - costo: montoPorAsiento del SectorEvento al momento
*             de la compra (se copia para persistencia)
*   Razon de copiar strings: la factura debe ser auto-contenida
*   para poder escribirse en archivo y recuperarse sin depender
*   de punteros a otras estructuras.
 */
typedef struct {
    char   idAsiento[MAX_ID_ASIENTO];
    char   nombreSector[MAX_NOMBRE];
    double costo;
} DetalleAsiento;

/* 
*   Factura  
*   Documento completo de una compra. Todos los campos de texto
*   son copias (no punteros) para garantizar persistencia.
*   - id: autogenerado con AppData.contadorFacturas 
*   - fechaCompra: fecha en que se realizo la compra
*   - cedula, nombreComprador: datos del cliente 
*   - nombreEvento, productora, nombreSitio, fechaEvento:
*             copias de los datos del evento al momento de compra
*   - detalles: arreglo dinamico de DetalleAsiento 
*   - cantidadAsientos: tamaño del arreglo detalles
*   - subtotal: suma de detalles[i].costo
*   - costoServicio: subtotal * COSTO_SERVICIO (5%) 
*   - total: subtotal + costoServicio
 */
typedef struct {
    int             id;
    char            fechaCompra[MAX_FECHA];
    char            cedula[MAX_CEDULA];
    char            nombreComprador[MAX_NOMBRE];
    char            nombreEvento[MAX_NOMBRE];
    char            productora[MAX_NOMBRE];
    char            nombreSitio[MAX_NOMBRE];
    char            fechaEvento[MAX_FECHA];
    int             cantidadAsientos;
    DetalleAsiento *detalles;
    double          subtotal;
    double          costoServicio;
    double          total;
} Factura;

/* 
*   AppData  
*   Contenedor global unico. Se pasa por referencia a todas las
*   funciones que necesiten leer o modificar datos.
*   - sitios, eventos, facturas: arreglos dinamicos principales
*   - cantidades: tamaño actual de cada arreglo
*   - contadorFacturas: se incrementa al generar cada factura,
*             nunca se resetea
*   - sesionActiva: 1 si el admin hizo login, 0 si no 
 */
typedef struct {
    SitioEvento *sitios;
    int          cantidadSitios;

    Evento      *eventos;
    int          cantidadEventos;

    Factura     *facturas;
    int          cantidadFacturas;

    int          contadorFacturas;
    int          sesionActiva;
} AppData;

#endif

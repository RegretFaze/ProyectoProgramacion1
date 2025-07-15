#ifndef FUNCIONES_PRINCIPALES_H
#define FUNCIONES_PRINCIPALES_H

#include "Validaciones_funciones_comunes.h" // Para constantes y la estructura Vehiculo

// Variables globales para veh�culos (definidas en Funciones_principales.c)
extern Vehiculo vehiculos[MAX_VEHICULOS];
extern int cantidadVehiculos;

// Funciones de gesti�n de veh�culos (solo las que se quedan aqu�)
void registrarVehiculo();
void registrarRevision();
void generarComprobante(const char *placaBuscar);
void buscarVehiculo();
void listarVehiculos();
void eliminarVehiculo();

#endif // FUNCIONES_PRINCIPALES_H

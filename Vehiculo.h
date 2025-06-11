#ifndef VEHICULO_H
#define VEHICULO_H

#include <stdio.h>
#include <stdbool.h> // Booleados (V,F)

#define MAX_VEHICULOS 100
#define ARCHIVO_DATOS "vehiculos.txt"

// Estructura para el vehículo
typedef struct {
	char placa[10];
	char cedula[15];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
} Vehiculo;

// Variables globales (definidas en .c)
extern Vehiculo vehiculos[MAX_VEHICULOS];
extern int cantidadVehiculos;

// Prototipos de funciones
void limpiarBuffer();
void limpiarPantalla();
void backupDatos();
void cargarDatos();
void guardarDatos();
void registrarVehiculo();
void calcularValorMatricula();
void ordenarVehiculos();
void registrarRevision();
void generarComprobante();
void exportarComprobante();
void buscarVehiculo();
void listarVehiculos();
void estadisticasVehiculares();
void editarVehiculo();
void eliminarVehiculo();

#endif // VEHICULO_H

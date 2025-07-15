#ifndef VALIDACIONES_FUNCIONES_COMUNES_H
#define VALIDACIONES_FUNCIONES_COMUNES_H

#include <stdio.h>
#include <stdbool.h> // Para usar bool

// Definiciones de constantes globales
#define MAX_VEHICULOS 100 // Ahora aquí
#define ARCHIVO_DATOS "vehiculos.txt"
#define ARCHIVO_USUARIOS "usuarios.txt"
#define MAX_USUARIOS 10

// Estructura para el vehículo (¡AHORA AQUÍ!)
typedef struct {
	char placa[10];
	char cedula[15];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3]; // 0: pendiente, 1: aprobada
} Vehiculo;


// Funciones de utilidad general
void limpiarBuffer();
void limpiarPantalla();

// Funciones de validación
bool validarPlaca(const char *placa);
bool validarCedula(const char *cedula);
bool validarAnio(int anio);
bool validarTipo(int tipoNum);
bool validarAvaluo(float avaluo);

#endif // VALIDACIONES_FUNCIONES_COMUNES_H

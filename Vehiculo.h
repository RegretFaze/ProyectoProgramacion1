#ifndef VEHICULO_H
#define VEHICULO_H

#include <stdio.h>
#include <stdbool.h> //Booleanos (V,F)

#define MAX_VEHICULOS 100
#define ARCHIVO_DATOS "vehiculos.txt"
#define ARCHIVO_USUARIOS "usuarios.txt" // Nuevo: Archivo para almacenar usuarios
#define MAX_USUARIOS 10 // Nuevo: Máximo de usuarios que se pueden registrar

//Estructura para el vehículo
typedef struct {
	char placa[10];
	char cedula[15];
	int anio;
	char tipo[20];
	float avaluo;
	int revisiones[3];
} Vehiculo;

// Nuevo: Estructura para el usuario
typedef struct {
	char username[50];
	char password[15];
} Usuario;

//Variables globales (definidas en .c)
extern Vehiculo vehiculos[MAX_VEHICULOS];
extern int cantidadVehiculos;

extern Usuario usuarios[MAX_USUARIOS]; // Nuevo: Array para almacenar usuarios
extern int cantidadUsuarios; // Nuevo: Cantidad de usuarios registrados

//Funciones
void limpiarBuffer();
void limpiarPantalla();
void guardarDatos();
void registrarVehiculo();
void registrarRevision();
void generarComprobante();
void buscarVehiculo();
void listarVehiculos();
void eliminarVehiculo();
bool login();
void calcularValorMatricula();

// Nuevas funciones para la gestión de usuarios
void cargarUsuarios();
void guardarUsuarios();
void registrarNuevoUsuario();

#endif //VEHICULO_H

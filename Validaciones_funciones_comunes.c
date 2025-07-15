#include "Validaciones_funciones_comunes.h"
#include <stdlib.h> // Para system()
#include <string.h> // Para strlen(), strcspn()
#include <ctype.h>  // Para isalpha(), isdigit()

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Función para limpiar la pantalla
void limpiarPantalla() {
#ifdef _WIN32
	system("cls"); // Para Windows
#else
	system("clear"); // Para sistemas Unix/Linux
#endif
}

// Implementaciones de las funciones de validación

// Validación de Placa
bool validarPlaca(const char *placa) {
	int len = strlen(placa);
	if (len != 7) return false;
	
	for (int i = 0; i < 3; i++) {
		if (!isalpha(placa[i])) return false;
	}
	
	for (int i = 3; i < 7; i++) {
		if (!isdigit(placa[i])) return false;
	}
	return true;
}

// Validación de Cedula
bool validarCedula(const char *cedula) {
	int len = strlen(cedula);
	if (len != 10) return false;
	
	for (int i = 0; i < len; i++) {
		if (!isdigit(cedula[i])) return false;
	}
	return true;
}

// Validación de Año (Límites)
bool validarAnio(int anio) {
	return anio >= 1900 && anio <= 2026;
}

// Validación de Tipo de Vehículo (ahora recibe un entero)
bool validarTipo(int tipoNum) {
	return tipoNum >= 1 && tipoNum <= 3; // Valida que sea 1, 2 o 3
}

// Validación de Avalúo
bool validarAvaluo(float avaluo) {
	return avaluo > 0 && avaluo <= 120000.0f;
}

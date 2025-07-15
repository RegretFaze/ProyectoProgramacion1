#include "Usuario.h"                 // Para cargarUsuarios, login, registrarNuevoUsuario
#include "Funciones_principales.h"   // Para las funciones de gestión de vehículos
#include "Gestion_archivos.h"        // ¡NUEVO! Para cargarDatos y guardarDatos
#include "Validaciones_funciones_comunes.h" // Para limpiarPantalla, limpiarBuffer, etc.

#include <stdio.h>   // Para printf, sscanf
#include <string.h>  // Para strcspn
#include <ctype.h>   // Para toupper

int main() {
	// Cargar usuarios al inicio del programa
	cargarUsuarios();
	// Cargar datos de vehículos al inicio del programa
	cargarDatos(); // Ahora llamada desde Gestion_archivos.h
	
	int opcionLogin;
	
	do {
		limpiarPantalla();
		printf("--- BIENVENIDO AL SISTEMA DE MATRICULACION VEHICULAR ---\n");
		printf("1. Iniciar Sesion\n");
		printf("2. Registrar Nuevo Usuario\n");
		printf("3. Salir\n");
		printf("Seleccione una opcion: ");
		
		char inputLogin[10];
		fgets(inputLogin, sizeof(inputLogin), stdin);
		inputLogin[strcspn(inputLogin, "\n")] = 0;
		
		if (sscanf(inputLogin, "%d", &opcionLogin) != 1) {
			opcionLogin = 0; // Si no es un número válido, establecer a una opción inválida
		}
		
		switch (opcionLogin) {
		case 1:
			if (login()) {
				opcionLogin = 0; // Para salir del bucle do-while de login si el login es exitoso
			}
			break;
		case 2:
			registrarNuevoUsuario();
			break;
		case 3:
			printf("Saliendo del programa...\n");
			return 0;
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			break;
		}
	} while (opcionLogin != 0); // Continúa hasta que el login sea exitoso o se elija salir
	
	// Menú principal
	int opcion;
	do {
		limpiarPantalla();
		printf("--- Sistema Integral de Matriculacion Vehicular ---\n");
		printf("1. Registrar Vehiculo\n");
		printf("2. Eliminar Vehiculo\n");
		printf("3. Buscar Vehiculo\n");
		printf("4. Listar Vehiculos\n");
		printf("5. Registrar Revision Tecnica\n");
		printf("6. Guardar y Salir\n");
		printf("Seleccione una opcion: ");
		
		char inputMenu[10];
		fgets(inputMenu, sizeof(inputMenu), stdin);
		inputMenu[strcspn(inputMenu, "\n")] = 0;
		
		if (sscanf(inputMenu, "%d", &opcion) != 1) {
			opcion = 0; // Si no es un número válido, establecer a una opción inválida
		}
		
		switch (opcion) {
		case 1: registrarVehiculo(); break;
		case 2: eliminarVehiculo(); break;
		case 3: buscarVehiculo(); break;
		case 4: listarVehiculos(); break;
		case 5: registrarRevision(); break;
		case 6: guardarDatos(); printf("Datos guardados. Saliendo...\n"); break; // Ahora llamada desde Gestion_archivos.h
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			break;
		}
		
	} while (opcion != 6); // La opción de salir ahora es 6
	
	return 0;
}

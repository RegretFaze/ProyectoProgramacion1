#include "vehiculo.h"
#include <stdio.h>

//Funcion de submenú
void gestionarVehiculos();

int main() {
	// Nuevo: Cargar usuarios al inicio del programa
	cargarUsuarios();
	
	// Realizar el inicio de sesión antes de entrar al bucle del menú principal
	if (!login()) {
		return 1; // Salir del programa si el inicio de sesión falla o el usuario decide no registrarse
	}
	limpiarPantalla();
	int opcion;
	do {
		printf("--- Sistema Integral de Matriculacion Vehicular ---\n");
		printf("1. Gestionar Vehiculos\n");
		printf("2. Generar Comprobante\n");
		printf("3. Guardar y Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		limpiarPantalla();
		
		switch (opcion) {
		case 1: gestionarVehiculos(); limpiarPantalla(); break;
		case 2: generarComprobante(); break;
		case 3: guardarDatos(); printf("Datos guardados. Saliendo...\n"); break;
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			break;
		}
		
	} while (opcion != 3);
	
	return 0;
}

void gestionarVehiculos() {
	int subOpcion;
	do {
		printf("--- Submenu de Gestion de Vehiculos ---\n");
		printf("1. Registrar Vehiculo\n");
		printf("2. Eliminar Vehiculo\n");
		printf("3. Buscar Vehiculo\n");
		printf("4. Listar Vehiculos\n");
		printf("5. Registrar Revision Tecnica\n");
		printf("6. Volver al Menu Principal\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &subOpcion);
		limpiarBuffer();
		limpiarPantalla();
		
		switch (subOpcion) {
		case 1: registrarVehiculo(); break;
		case 2: eliminarVehiculo(); break;
		case 3: buscarVehiculo(); break;
		case 4: listarVehiculos(); break;
		case 5: registrarRevision(); break;
		case 6: printf("Volviendo al menu principal...\n"); break;
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			break;
		}
	} while (subOpcion != 6); // Se cambió de 7 a 6 para salir correctamente del submenú
}

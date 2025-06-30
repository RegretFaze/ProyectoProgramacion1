#include "vehiculo.h"
#include <stdio.h>

//Funcion submenu
void gestionarVehiculos();

int main() {
	int opcion;
	do {
		printf("--- Sistema Integral de Matriculacion Vehicular ---\n");
		printf("1. Gestionar Vehiculos\n");
		printf("2. Calcular Matricula\n");
		printf("3. Generar Comprobante\n");
		printf("4. Exportar Comprobante a archivo\n");
		// La opci�n "5. Ordenar Vehiculos (por placa)" ha sido eliminada
		printf("5. Guardar y Salir\n"); // Se cambi� de 6 a 5
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		limpiarPantalla(); // Limpiar pantalla al inicio de cada iteraci�n, antes del switch
		
		switch (opcion) {
		case 1: gestionarVehiculos(); limpiarPantalla(); break;
		case 2: calcularValorMatricula(); break;
		case 3: generarComprobante(); break;
		case 4: exportarComprobante(); break;
		case 5: guardarDatos(); printf("Datos guardados. Saliendo...\n"); break; // Se cambi� de 6 a 5
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			// limpiarPantalla() ya se hace al inicio del bucle, no es necesario aqu�.
			break;
		}
		
	} while (opcion != 5); // Se cambi� de 6 a 5
	
	return 0;
}

//Implementaci�n Nueva funci�n
void gestionarVehiculos() {
	int subOpcion;
	do {
		printf("--- Submenu de Gestion de Vehiculos ---\n");
		printf("1. Registrar Vehiculo\n");
		printf("2. Editar Vehiculo\n");
		printf("3. Eliminar Vehiculo\n");
		printf("4. Buscar Vehiculo\n");
		printf("5. Listar Vehiculos\n");
		printf("6. Registrar Revision Tecnica\n");
		printf("7. Volver al Menu Principal\n"); //Opci�n para salir del submenu
		printf("Seleccione una opcion: ");
		scanf("%d", &subOpcion);
		limpiarBuffer();
		limpiarPantalla(); // Limpiar pantalla al inicio de cada iteraci�n del submenu
		
		switch (subOpcion) {
		case 1: registrarVehiculo(); break;
		case 2: editarVehiculo(); break;
		case 3: eliminarVehiculo(); break;
		case 4: buscarVehiculo(); break;
		case 5: listarVehiculos(); break;
		case 6: registrarRevision(); break;
		case 7: printf("Volviendo al menu principal...\n"); break;
		default:
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			// limpiarPantalla() ya se hace al inicio del bucle, no es necesario aqu�.
			break;
		}
	} while (subOpcion != 7);
}

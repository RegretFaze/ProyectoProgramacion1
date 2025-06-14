#include "vehiculo.h"
#include <stdio.h>

// Prototipo de la nueva funci�n para el submen� de gesti�n de veh�culos
void gestionarVehiculos(); 

int main() {
	int opcion;
	do {
		printf("--- Sistema Integral de Matriculacion Vehicular ---\n");
		printf("1. Gestionar Vehiculos\n"); // Nueva opci�n para el submen�
		printf("2. Calcular Matricula\n");
		printf("3. Generar Comprobante\n");
		printf("4. Exportar Comprobante a archivo\n");
		printf("5. Ordenar Vehiculos (por placa)\n"); // Renumerada de 6 a 5
		printf("6. Guardar y Salir\n"); // Renumerada de 7 a 6
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		limpiarPantalla();
		if (opcion != 6) { 
		}
		
		switch (opcion) {
		case 1: gestionarVehiculos(); limpiarPantalla(); break; // Llama al nuevo submen�, luego limpia al volver.
		case 2: calcularValorMatricula(); break;
		case 3: generarComprobante(); break;
		case 4: exportarComprobante(); break;
		case 5: ordenarVehiculos(); break; 
		case 6: guardarDatos(); printf("Datos guardados. Saliendo...\n"); break; 
		default: 
			limpiarPantalla(); // Limpiar si la opci�n es inv�lida
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			limpiarPantalla(); // Limpiar despu�s de que el usuario lea el error
			break;
		}
		
	} while (opcion != 6); // El bucle principal termina cuando se selecciona la nueva opci�n de salir (6)
	
	return 0;
}

// Implementaci�n de la nueva funci�n para el submen� de gesti�n de veh�culos
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
		printf("7. Volver al Menu Principal\n"); // Opci�n para salir del submen�
		printf("Seleccione una opcion: ");
		scanf("%d", &subOpcion);
		limpiarBuffer();
		
		if (subOpcion != 7) { 
			// No limpiar pantalla inmediatamente si la opci�n es 7, o si es inv�lida
		}
		
		switch (subOpcion) {
		case 1: registrarVehiculo(); limpiarPantalla(); break;
		case 2: editarVehiculo(); limpiarPantalla(); break;
		case 3: eliminarVehiculo(); limpiarPantalla(); break;
		case 4: buscarVehiculo(); limpiarPantalla(); break;
		case 5: listarVehiculos(); limpiarPantalla(); break;
		case 6: registrarRevision(); limpiarPantalla(); break;
		case 7: printf("Volviendo al menu principal...\n"); break;
		default: 
			limpiarPantalla(); // Limpiar si la opci�n es inv�lida
			printf("Opcion invalida. Intente de nuevo.\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			limpiarPantalla(); // Limpiar despu�s de que el usuario lea el error
			break;
		}
	} while (subOpcion != 7);
}

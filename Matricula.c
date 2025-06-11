#include "vehiculo.h"
#include <stdio.h>

int main() {
	int opcion;
	cargarDatos(); // Carga datos (Si hay)
	limpiarPantalla();
	
	do {
		printf("\n--- Sistema Integral de Matriculacion Vehicular ---\n");
		printf("1. Registrar Vehiculo\n");
		printf("2. Editar Vehiculo\n");
		printf("3. Eliminar Vehiculo\n");
		printf("4. Buscar Vehiculo\n");
		printf("5. Listar Vehiculos\n");
		printf("6. Registrar Revision Tecnica\n");
		printf("7. Calcular Matricula\n");
		printf("8. Generar Comprobante\n");
		printf("9. Exportar Comprobante a archivo\n");
		printf("10. Ver Estadisticas\n");
		printf("11. Ordenar Vehiculos (por placa)\n");
		printf("12. Backup de Datos\n");
		printf("13. Guardar y Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		
	
		// Limpiar excepto "Salir"
		if (opcion != 13) {
			limpiarPantalla();
		}
		
		switch (opcion) {
		case 1: registrarVehiculo(); break;
		case 2: editarVehiculo(); break;
		case 3: eliminarVehiculo(); break;
		case 4: buscarVehiculo(); break;
		case 5: listarVehiculos(); break;
		case 6: registrarRevision(); break;
		case 7: calcularValorMatricula(); break;
		case 8: generarComprobante(); break;
		case 9: exportarComprobante(); break;
		case 10: estadisticasVehiculares(); break;
		case 11: ordenarVehiculos(); break;
		case 12: backupDatos(); break;
		case 13: guardarDatos(); printf("Datos guardados. Saliendo...\n"); break;
		default: printf("Opcion invalida. Intente de nuevo.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		break;
		}
		
	} while (opcion != 13);
	
	return 0;
}

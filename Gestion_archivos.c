#include "Gestion_archivos.h"
#include <stdio.h> // Para FILE, fopen, fclose, fscanf, fprintf

// Las variables globales `vehiculos` y `cantidadVehiculos` son definidas en Funciones_principales.c
// y declaradas como `extern` en Funciones_principales.h.
// Para acceder a ellas desde aqu�, necesitamos incluir el archivo donde est�n externadas.
// Es una dependencia cruzada, pero com�n para variables globales en C.
#include "Funciones_principales.h" // Incluye esto para acceder a vehiculos[] y cantidadVehiculos

// Funci�n para cargar los datos de los veh�culos desde un archivo
void cargarDatos() {
	FILE *archivo = fopen(ARCHIVO_DATOS, "r");
	if (archivo == NULL) {
		cantidadVehiculos = 0; // Si el archivo no existe, no hay veh�culos cargados
		return;
	}
	
	cantidadVehiculos = 0; // Reiniciar antes de cargar
	while (fscanf(archivo, "%s %s %d %s %f %d %d %d",
				  vehiculos[cantidadVehiculos].placa,
				  vehiculos[cantidadVehiculos].cedula,
				  &vehiculos[cantidadVehiculos].anio,
				  vehiculos[cantidadVehiculos].tipo,
				  &vehiculos[cantidadVehiculos].avaluo,
				  &vehiculos[cantidadVehiculos].revisiones[0],
				  &vehiculos[cantidadVehiculos].revisiones[1],
				  &vehiculos[cantidadVehiculos].revisiones[2]) == 8 && cantidadVehiculos < MAX_VEHICULOS) {
		cantidadVehiculos++;
	}
	
	fclose(archivo);
}

// Funci�n para guardar los datos de los veh�culos en un archivo
void guardarDatos() {
	FILE *archivo = fopen(ARCHIVO_DATOS, "w");
	if (archivo == NULL) {
		printf("Error al guardar los datos.\n");
		// No limpiar el buffer aqu�, se hace en main si hay un mensaje al usuario
		return;
	}
	
	for (int i = 0; i < cantidadVehiculos; i++) {
		fprintf(archivo, "%s %s %d %s %.2f %d %d %d\n",
				vehiculos[i].placa,
				vehiculos[i].cedula,
				vehiculos[i].anio,
				vehiculos[i].tipo,
				vehiculos[i].avaluo,
				vehiculos[i].revisiones[0],
				vehiculos[i].revisiones[1],
				vehiculos[i].revisiones[2]);
	}
	
	fclose(archivo);
	printf("Datos guardados exitosamente.\n");
	// No limpiar el buffer aqu�, se hace en main si hay un mensaje al usuario
}

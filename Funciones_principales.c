#include "Funciones_principales.h"
#include "Validaciones_funciones_comunes.h" // Para funciones de utilidad y validación, y la estructura Vehiculo
#include <string.h> // Para strcmp, strcpy, strlen, strcspn
#include <stdio.h>  // Para printf, sscanf
#include <ctype.h>  // Para toupper

// Definición de las variables globales para vehículos
Vehiculo vehiculos[MAX_VEHICULOS];
int cantidadVehiculos = 0;

// Las funciones cargarDatos() y guardarDatos() han sido movidas a Gestion_archivos.c

// Función para registrar un nuevo vehículo
void registrarVehiculo() {
	if (cantidadVehiculos >= MAX_VEHICULOS) {
		limpiarPantalla();
		printf("No se pueden registrar mas vehiculos.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	Vehiculo nuevo;
	char inputBuffer[50];
	int tipoNumInput;
	
	// Validación de Placa
	do {
		limpiarPantalla();
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese la placa (Ej: PDP7714): ");
		scanf("%s", nuevo.placa);
		limpiarBuffer();
		for (int i = 0; nuevo.placa[i]; i++) {
			nuevo.placa[i] = toupper(nuevo.placa[i]);
		}
		if (!validarPlaca(nuevo.placa)) {
			printf("Error: Formato de placa invalido. Debe ser 3 letras y 4 digitos (Ej: ABC1234).\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
			continue;
		} else {
			bool placaExistente = false;
			for (int i = 0; i < cantidadVehiculos; i++) {
				if (strcmp(vehiculos[i].placa, nuevo.placa) == 0) {
					printf("Error: Ya existe un vehiculo con esa placa.\n");
					printf("Presione Enter para reintentar...");
					limpiarBuffer();
					placaExistente = true;
					break;
				}
			}
			if (placaExistente) {
				continue;
			}
		}
		break;
	} while (true);
	
	// Validación de Cedula
	do {
		limpiarPantalla();
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese la cedula del propietario (10 digitos): ");
		scanf("%s", nuevo.cedula);
		limpiarBuffer();
		if (!validarCedula(nuevo.cedula)) {
			printf("Error: Formato de cedula invalido. Debe contener solo digitos y ser 10 en total.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break;
		}
	} while (true);
	
	// Validación de Año
	do {
		limpiarPantalla();
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese el anio del vehiculo (ej. 2020): ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%d", &nuevo.anio) != 1 || !validarAnio(nuevo.anio)) {
			printf("Error: Anio invalido. Por favor ingrese un numero valido (1900-2026).\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break;
		}
	} while (true);
	
	// Validación de Tipo (ahora con opciones numéricas)
	do {
		limpiarPantalla();
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese el tipo de vehiculo:\n");
		printf("  1. Carro\n");
		printf("  2. Camion\n");
		printf("  3. Camioneta\n");
		printf("Seleccione una opcion (1-3): ");
		
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%d", &tipoNumInput) != 1 || !validarTipo(tipoNumInput)) {
			printf("Error: Opcion de tipo de vehiculo invalida. Por favor, seleccione 1, 2 o 3.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			switch (tipoNumInput) {
			case 1: strcpy(nuevo.tipo, "carro"); break;
			case 2: strcpy(nuevo.tipo, "camion"); break;
			case 3: strcpy(nuevo.tipo, "camioneta"); break;
			}
			break;
		}
	} while (true);
	
	// Validación de Avalúo
	do {
		limpiarPantalla();
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese el avaluo del vehiculo (valor positivo, max $120,000): ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%f", &nuevo.avaluo) != 1 || !validarAvaluo(nuevo.avaluo)) {
			printf("Error: Avaluo invalido. Por favor ingrese un valor numerico positivo y no mayor a $120,000.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break;
		}
	} while (true);
	
	// Inicializar revisiones
	for (int i = 0; i < 3; i++) {
		nuevo.revisiones[i] = 0;
	}
	
	vehiculos[cantidadVehiculos++] = nuevo;
	limpiarPantalla();
	printf("Vehiculo registrado exitosamente.\n");
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para registrar una revisión técnica
void registrarRevision() {
	limpiarPantalla();
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para registrar revision: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	for (int i = 0; placaBuscar[i]; i++) {
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			encontrado = true;
			
			int revisionesCompletasAntesDeRegistrar = 0;
			for (int j = 0; j < 3; j++) {
				if (vehiculos[i].revisiones[j] == 1) {
					revisionesCompletasAntesDeRegistrar++;
				}
			}
			
			if (revisionesCompletasAntesDeRegistrar == 3) {
				limpiarPantalla();
				printf("El vehiculo con placa %s ya tiene las 3 revisiones tecnicas completas.\n", vehiculos[i].placa);
				printf("¿Desea generar el comprobante de matricula? (s/n): ");
				char opcionGenerarComprobante;
				scanf(" %c", &opcionGenerarComprobante);
				limpiarBuffer();
				if (opcionGenerarComprobante == 's' || opcionGenerarComprobante == 'S') {
					generarComprobante(vehiculos[i].placa);
				}
				printf("Presione Enter para continuar...");
				limpiarBuffer();
				return;
			}
			
			int numRevision;
			char inputBuffer[10];
			
			do {
				limpiarPantalla();
				printf("--- Registrar Revision Tecnica ---\n");
				printf("Placa: %s\n", vehiculos[i].placa);
				printf("Estado actual de Revisiones: [1] %s | [2] %s | [3] %s\n",
					   vehiculos[i].revisiones[0] ? "Aprobada" : "Pendiente",
					   vehiculos[i].revisiones[1] ? "Aprobada" : "Pendiente",
					   vehiculos[i].revisiones[2] ? "Aprobada" : "Pendiente");
				printf("----------------------------------\n");
				
				printf("Ingrese el numero de revision (1-3): ");
				fgets(inputBuffer, sizeof(inputBuffer), stdin);
				inputBuffer[strcspn(inputBuffer, "\n")] = 0;
				
				if (sscanf(inputBuffer, "%d", &numRevision) != 1 || numRevision < 1 || numRevision > 3) {
					printf("Error: Numero de revision invalido. Debe ser 1, 2 o 3. Reintente.\n");
					printf("Presione Enter para reintentar...");
					limpiarBuffer();
				} else {
					if (vehiculos[i].revisiones[numRevision - 1] == 1) {
						printf("Error: La revision %d ya ha sido registrada anteriormente para este vehiculo.\n", numRevision);
						printf("Presione Enter para reintentar con otro numero de revision...");
						limpiarBuffer();
					} else {
						vehiculos[i].revisiones[numRevision - 1] = 1;
						printf("Revision %d registrada correctamente como aprobada.\n", numRevision);
						
						int revisionesCompletasActual = 0;
						for (int j = 0; j < 3; j++) {
							if (vehiculos[i].revisiones[j] == 1) {
								revisionesCompletasActual++;
							}
						}
						
						if (revisionesCompletasActual == 3) {
							limpiarPantalla();
							printf("El vehiculo con placa %s ha completado ahora sus 3 revisiones tecnicas.\n", vehiculos[i].placa);
							printf("¿Desea generar el comprobante de matricula? (s/n): ");
							char opcionGenerarComprobante;
							scanf(" %c", &opcionGenerarComprobante);
							limpiarBuffer();
							if (opcionGenerarComprobante == 's' || opcionGenerarComprobante == 'S') {
								generarComprobante(vehiculos[i].placa);
							}
						}
						
						break;
					}
				}
			} while (true);
			
			if (encontrado) break;
		}
	}
	
	if (!encontrado) {
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para generar un comprobante de matrícula (ahora recibe la placa)
void generarComprobante(const char *placaBuscar) {
	limpiarPantalla();
	
	bool encontrado = false;
	int i_encontrado = -1;
	
	// Buscar el vehículo por la placa proporcionada
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			encontrado = true;
			i_encontrado = i;
			break;
		}
	}
	
	if (!encontrado) {
		printf("Error: Vehiculo con placa %s no encontrado para generar comprobante.\n", placaBuscar);
		return;
	}
	
	bool todasRevisionesCompletas = true;
	for (int j = 0; j < 3; j++) {
		if (vehiculos[i_encontrado].revisiones[j] == 0) {
			todasRevisionesCompletas = false;
			break;
		}
	}
	
	if (!todasRevisionesCompletas) {
		printf("\nAdvertencia: El vehiculo no cuenta con las 3 revisiones tecnicas necesarias, por ende, no se puede generar el comprobante del mismo.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	float valorMatricula = vehiculos[i_encontrado].avaluo * 0.015f;
	
	limpiarPantalla();
	printf("\n========================================\n");
	printf("        COMPROBANTE DE MATRICULA        \n");
	printf("========================================\n");
	printf("Placa       : %s\n", vehiculos[i_encontrado].placa);
	printf("Cedula      : %s\n", vehiculos[i_encontrado].cedula);
	printf("Anio        : %d\n", vehiculos[i_encontrado].anio);
	printf("Tipo        : %s\n", vehiculos[i_encontrado].tipo);
	printf("Avaluo      : $%.2f\n", vehiculos[i_encontrado].avaluo);
	
	printf("\nEstado de Revisiones:\n");
	for (int j = 0; j < 3; j++) {
		printf("Revision %d: %s\n", j + 1,
			   vehiculos[i_encontrado].revisiones[j] ? "Aprobada" : "Pendiente");
	}
	
	printf("\nValor Total de Matricula: $%.2f\n", valorMatricula);
	printf("========================================\n\n");
	
	char opcionExportar;
	printf("¿Desea exportar este comprobante a un archivo? (s/n): ");
	scanf(" %c", &opcionExportar);
	limpiarBuffer();
	
	if (opcionExportar == 's' || opcionExportar == 'S') {
		char nombreArchivo[30];
		sprintf(nombreArchivo, "comprobante_%s.txt", vehiculos[i_encontrado].placa);
		
		FILE *archivo = fopen(nombreArchivo, "w");
		if (archivo == NULL) {
			printf("Error al crear el archivo de comprobante.\n");
			return;
		}
		
		fprintf(archivo, "========================================\n");
		fprintf(archivo, "        COMPROBANTE DE MATRICULA        \n");
		fprintf(archivo, "========================================\n");
		fprintf(archivo, "Placa       : %s\n", vehiculos[i_encontrado].placa);
		fprintf(archivo, "Cedula      : %s\n", vehiculos[i_encontrado].cedula);
		fprintf(archivo, "Anio        : %d\n", vehiculos[i_encontrado].anio);
		fprintf(archivo, "Tipo        : %s\n", vehiculos[i_encontrado].tipo);
		fprintf(archivo, "Avaluo      : $%.2f\n", vehiculos[i_encontrado].avaluo);
		fprintf(archivo, "\nEstado de Revisiones:\n");
		for (int j = 0; j < 3; j++) {
			fprintf(archivo, "Revision %d: %s\n", j + 1,
					vehiculos[i_encontrado].revisiones[j] ? "Aprobada" : "Pendiente");
		}
		fprintf(archivo, "\nValor Total de Matricula: $%.2f\n", valorMatricula);
		fprintf(archivo, "========================================\n");
		
		fclose(archivo);
		
		printf("Comprobante exportado exitosamente a '%s'.\n", nombreArchivo);
	} else {
		printf("El comprobante no fue exportado.\n");
	}
}

// Función para buscar un vehículo
void buscarVehiculo() {
	limpiarPantalla();
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo a buscar: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	for (int i = 0; placaBuscar[i]; i++) {
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			limpiarPantalla();
			printf("\n--- Datos del Vehiculo ---\n");
			printf("Placa       : %s\n", vehiculos[i].placa);
			printf("Cedula      : %s\n", vehiculos[i].cedula);
			printf("Anio        : %d\n", vehiculos[i].anio);
			printf("Tipo        : %s\n", vehiculos[i].tipo);
			printf("Avaluo      : $%.2f\n", vehiculos[i].avaluo);
			
			printf("Revisiones  : [1] %s | [2] %s | [3] %s\n",
				   vehiculos[i].revisiones[0] ? "Aprobada" : "Pendiente",
				   vehiculos[i].revisiones[1] ? "Aprobada" : "Pendiente",
				   vehiculos[i].revisiones[2] ? "Aprobada" : "Pendiente");
			printf("---------------------------\n");
			encontrado = true;
			break;
		}
	}
	
	if (!encontrado) {
		limpiarPantalla();
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para listar todos los vehículos registrados
void listarVehiculos() {
	limpiarPantalla();
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	printf("\n--- Listado de Vehiculos ---\n");
	for (int i = 0; i < cantidadVehiculos; i++) {
		printf("Placa: %-10s Cedula: %-15s Anio: %-5d Tipo: %-10s Avaluo: $%.2f\n",
			   vehiculos[i].placa, vehiculos[i].cedula, vehiculos[i].anio, vehiculos[i].tipo, vehiculos[i].avaluo);
	}
	printf("-----------------------------\n");
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para eliminar un vehículo
void eliminarVehiculo() {
	limpiarPantalla();
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados para eliminar.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	printf("\n--- Lista de Vehiculos Registrados ---\n");
	for (int i = 0; i < cantidadVehiculos; i++) {
		printf("%d. Placa: %-10s Tipo: %-10s Anio: %-4d Avaluo: $%.2f\n",
			   i + 1,
			   vehiculos[i].placa,
			   vehiculos[i].tipo,
			   vehiculos[i].anio,
			   vehiculos[i].avaluo);
	}
	
	int indice;
	char inputBuffer[10];
	
	do {
		printf("\nIngrese el numero del vehiculo que desea eliminar: ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%d", &indice) != 1 || indice < 1 || indice > cantidadVehiculos) {
			limpiarPantalla();
			printf("Error: Indice invalido. Por favor, ingrese un numero de vehiculo valido.\n");
			printf("\n--- Lista de Vehiculos Registrados ---\n");
			for (int i = 0; i < cantidadVehiculos; i++) {
				printf("%d. Placa: %-10s Tipo: %-10s Anio: %-4d Avaluo: $%.2f\n",
					   i + 1,
					   vehiculos[i].placa,
					   vehiculos[i].tipo,
					   vehiculos[i].anio,
					   vehiculos[i].avaluo);
			}
		} else {
			break;
		}
	} while (true);
	
	indice--;
	
	limpiarPantalla();
	printf("Esta seguro que desea eliminar el vehiculo con placa %s? (s/n): ", vehiculos[indice].placa);
	char confirmacion;
	scanf(" %c", &confirmacion);
	limpiarBuffer();
	
	limpiarPantalla();
	if (confirmacion == 's' || confirmacion == 'S') {
		for (int i = indice; i < cantidadVehiculos - 1; i++) {
			vehiculos[i] = vehiculos[i + 1];
		}
		cantidadVehiculos--;
		printf("Vehiculo eliminado correctamente.\n");
	} else {
		printf("Eliminacion cancelada.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

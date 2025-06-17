#include "vehiculo.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Vehiculo vehiculos[MAX_VEHICULOS];
int cantidadVehiculos = 0;

// Función limpiar pantalla
void limpiarPantalla() {
#ifdef _WIN32
	system("cls"); // Para Windows
#else
	system("clear");
#endif
}

// Placa
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

// Cédula
static bool validarCedula(const char *cedula) {
	int len = strlen(cedula);
	if (len < 10) return false;
	
	for (int i = 0; i < len; i++) {
		if (!isdigit(cedula[i])) return false;
	}
	return true;
}

// Año (Limites)
static bool validarAnio(int anio) {
	// Limites del año
	return anio >= 1900 && anio <= 2050;
}

// Vehiculo
static bool validarTipo(const char *tipo) {
	if (strlen(tipo) == 0) return false;
	for (int i = 0; tipo[i] != '\0'; i++) {
		if (!isalpha(tipo[i]) && !isspace(tipo[i])) {
			return false;
		}
	}
	return true;
}

// Avalúo
static bool validarAvaluo(float avaluo) {
	return avaluo > 0;
}

// Funciones Principales

void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void guardarDatos() {
	FILE *archivo = fopen(ARCHIVO_DATOS, "w");
	if (archivo == NULL) {
		printf("Error al guardar los datos.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
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
}

void registrarVehiculo() {
	if (cantidadVehiculos >= MAX_VEHICULOS) {
		limpiarPantalla(); // Si no se puede registrar más
		printf("No se pueden registrar mas vehiculos.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	Vehiculo nuevo;
	char inputBuffer[50];
	
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
			continue; // Pedir la placa de nuevo 
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
				continue; // Pedir la placa de nuevo
			}
		}
		break; // Salir del bucle sino es válido 
	} while (true);
	
	// Validación de Cédula
	do {
		limpiarPantalla(); // Limpiar pantalla por intento
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese la cedula del propietario (min. 10 digitos): ");
		scanf("%s", nuevo.cedula);
		limpiarBuffer();
		if (!validarCedula(nuevo.cedula)) {
			printf("Error: Formato de cedula invalido. Debe contener solo digitos y al menos 10.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break; // Si la cédula es válida, salir del bucle
		}
	} while (true);
	
	// Validación de Año
	do {
		limpiarPantalla(); // Limpiar pantalla para cada intento
		printf("--- Registrar Vehiculo ---\n"); // Título para contexto
		// Eliminado: printf("Placa: %s, Cedula: %s\n", nuevo.placa, nuevo.cedula); // Ya no se muestran datos previos
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
	
	// Validación de Tipo
	do {
		limpiarPantalla(); // Limpiar pantalla para cada intento
		printf("--- Registrar Vehiculo ---\n"); // Título para contexto
		// Eliminado: printf("Placa: %s, Cedula: %s, Anio: %d\n", nuevo.placa, nuevo.cedula, nuevo.anio); // Ya no se muestran datos previos
		printf("Ingrese el tipo de vehiculo (ej. Sedan, SUV): ");
		fgets(nuevo.tipo, sizeof(nuevo.tipo), stdin);
		nuevo.tipo[strcspn(nuevo.tipo, "\n")] = 0;
		
		if (!validarTipo(nuevo.tipo)) {
			printf("Error: Tipo de vehiculo invalido. Solo letras y espacios permitidos y no puede estar vacio.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break;
		}
	} while (true);
	
	// Validación de Avalúo
	do {
		limpiarPantalla(); // Limpiar pantalla para cada intento
		printf("--- Registrar Vehiculo ---\n"); // Título para contexto
		// Eliminado: printf("Placa: %s, Cedula: %s, Anio: %d, Tipo: %s\n", nuevo.placa, nuevo.cedula, nuevo.anio, nuevo.tipo); // Ya no se muestran datos previos
		printf("Ingrese el avaluo del vehiculo (valor positivo): ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%f", &nuevo.avaluo) != 1 || !validarAvaluo(nuevo.avaluo)) {
			printf("Error: Avaluo invalido. Por favor ingrese un valor numerico positivo.\n");
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
	limpiarPantalla(); // Limpiar pantalla final antes del mensaje de éxito
	printf("Vehiculo registrado exitosamente.\n");
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void calcularValorMatricula() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para calcular matricula: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			float valorMatricula = vehiculos[i].avaluo * 0.015f;
			printf("Valor de matricula para %s: $%.2f\n", vehiculos[i].placa, valorMatricula);
			encontrado = true;
			break;
		}
	}
	
	if (!encontrado) {
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void ordenarVehiculos() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos <= 1) {
		printf("No hay suficientes vehiculos para ordenar.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	for (int i = 0; i < cantidadVehiculos - 1; i++) {
		for (int j = 0; j < cantidadVehiculos - i - 1; j++) {
			if (strcmp(vehiculos[j].placa, vehiculos[j + 1].placa) > 0) {
				Vehiculo temp = vehiculos[j];
				vehiculos[j] = vehiculos[j + 1];
				vehiculos[j + 1] = temp;
			}
		}
	}
	
	printf("Vehiculos ordenados por placa exitosamente.\n");
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void registrarRevision() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	// Buscar placa
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para registrar revision: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			int numRevision;
			char inputBuffer[10];
			
			do {
				limpiarPantalla(); // Limpiar pantalla para cada intento de revisión
				printf("--- Registrar Revision Tecnica ---\n"); // Título para contexto
				printf("Placa: %s\n", vehiculos[i].placa); // Mostrar placa del vehículo
				printf("Ingrese el numero de revision (1-3): ");
				fgets(inputBuffer, sizeof(inputBuffer), stdin);
				inputBuffer[strcspn(inputBuffer, "\n")] = 0;
				
				if (sscanf(inputBuffer, "%d", &numRevision) != 1 || numRevision < 1 || numRevision > 3) {
					printf("Error: Numero de revision invalido. Debe ser 1, 2 o 3. Reintente.\n");
					printf("Presione Enter para reintentar...");
					limpiarBuffer();
				} else {
					vehiculos[i].revisiones[numRevision - 1] = 1;
					printf("Revision %d registrada correctamente como aprobada.\n", numRevision);
					encontrado = true;
					break;
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

// Comprobante

void generarComprobante() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para generar el comprobante: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			float valorMatricula = vehiculos[i].avaluo * 0.015f;
			
			limpiarPantalla(); // Limpiar antes de mostrar el comprobante
			printf("\n========================================\n");
			printf("        COMPROBANTE DE MATRICULA        \n");
			printf("========================================\n");
			printf("Placa       : %s\n", vehiculos[i].placa);
			printf("Cedula      : %s\n", vehiculos[i].cedula);
			printf("Anio        : %d\n", vehiculos[i].anio);
			printf("Tipo        : %s\n", vehiculos[i].tipo);
			printf("Avaluo      : $%.2f\n", vehiculos[i].avaluo);
			
			printf("\nEstado de Revisiones:\n");
			for (int j = 0; j < 3; j++) {
				printf("Revision %d: %s\n", j + 1,
					   vehiculos[i].revisiones[j] ? "Aprobada" : "Pendiente");
			}
			
			printf("\nValor Total de Matricula: $%.2f\n", valorMatricula);
			printf("========================================\n\n");
			encontrado = true;
			break;
		}
	}
	
	if (!encontrado) {
		limpiarPantalla(); // Limpiar si no se encontró antes de mostrar el mensaje
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void exportarComprobante() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para exportar el comprobante: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			char nombreArchivo[30];
			sprintf(nombreArchivo, "comprobante_%s.txt", vehiculos[i].placa);
			
			FILE *archivo = fopen(nombreArchivo, "w");
			if (archivo == NULL) {
				printf("Error al crear el archivo de comprobante.\n");
				printf("Presione Enter para continuar...");
				limpiarBuffer();
				return;
			}
			
			float valorMatricula = vehiculos[i].avaluo * 0.015f;
			
			fprintf(archivo, "========================================\n");
			fprintf(archivo, "        COMPROBANTE DE MATRICULA        \n");
			fprintf(archivo, "========================================\n");
			fprintf(archivo, "Placa       : %s\n", vehiculos[i].placa);
			fprintf(archivo, "Cedula      : %s\n", vehiculos[i].cedula);
			fprintf(archivo, "Anio        : %d\n", vehiculos[i].anio);
			fprintf(archivo, "Tipo        : %s\n", vehiculos[i].tipo);
			fprintf(archivo, "Avaluo      : $%.2f\n", vehiculos[i].avaluo);
			fprintf(archivo, "\nEstado de Revisiones:\n");
			for (int j = 0; j < 3; j++) {
				fprintf(archivo, "Revision %d: %s\n", j + 1,
						vehiculos[i].revisiones[j] ? "Aprobada" : "Pendiente");
			}
			fprintf(archivo, "\nValor Total de Matricula: $%.2f\n", valorMatricula);
			fprintf(archivo, "========================================\n");
			
			fclose(archivo);
			
			printf("Comprobante exportado exitosamente a '%s'.\n", nombreArchivo);
			encontrado = true;
			break;
		}
	}
	
	if (!encontrado) {
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void buscarVehiculo() {
	limpiarPantalla(); // Limpiar al entrar a la función
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
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			limpiarPantalla(); // Limpiar antes de mostrar los datos del vehículo
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
		limpiarPantalla(); // Limpiar si no se encontró antes de mostrar el mensaje
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void listarVehiculos() {
	limpiarPantalla(); // Limpiar al entrar a la función
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

void editarVehiculo() {
	limpiarPantalla(); // Limpiar al entrar a la función
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados para editar.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo a editar: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			encontrado = true;
			printf("\n--- Editando Vehiculo (Placa: %s) ---\n", vehiculos[i].placa); // Mostrar placa para contexto
			printf("Deje en blanco si no desea modificar un campo (presione Enter).\n");
			
			char input[50];
			int anioTemp;
			float avaluoTemp;
			
			//Edicion de Cédula
			do {
				printf("Cedula actual: %s\nNueva cedula (o Enter para mantener): ", vehiculos[i].cedula);
				fgets(input, sizeof(input), stdin);
				input[strcspn(input, "\n")] = 0;
				
				if (strlen(input) > 0) {
					if (!validarCedula(input)) {
						limpiarPantalla(); // Limpiar si hay error
						printf("Error: Formato de cedula invalido. Debe contener solo digitos y al menos 10. Reintente.\n");
						printf("Cedula actual: %s\nNueva cedula (o Enter para mantener): ", vehiculos[i].cedula); // Volver a mostrar prompt
					} else {
						strcpy(vehiculos[i].cedula, input);
						break;
					}
				} else {
					break;
				}
			} while (true);
			
			
			// Edicion año
			do {
				printf("Anio actual: %d\nNuevo anio (o Enter para mantener): ", vehiculos[i].anio);
				fgets(input, sizeof(input), stdin);
				input[strcspn(input, "\n")] = 0;
				
				if (strlen(input) > 0) {
					if (sscanf(input, "%d", &anioTemp) == 1 && validarAnio(anioTemp)) {
						vehiculos[i].anio = anioTemp;
						break;
					} else {
						limpiarPantalla(); // Limpiar si hay error
						printf("Error: Anio invalido. Por favor ingrese un numero valido (1900-2026). Reintente.\n");
						printf("Anio actual: %d\nNuevo anio (o Enter para mantener): ", vehiculos[i].anio); // Volver a mostrar prompt
					}
				} else {
					break;
				}
			} while (true);
			
			// Edicion tipo
			do {
				printf("Tipo actual: %s\nNuevo tipo (o Enter para mantener): ", vehiculos[i].tipo);
				fgets(input, sizeof(input), stdin);
				input[strcspn(input, "\n")] = 0;
				
				if (strlen(input) > 0) {
					if (validarTipo(input)) {
						strcpy(vehiculos[i].tipo, input);
						break;
					} else {
						limpiarPantalla(); // Limpiar si hay error
						printf("Error: Tipo de vehiculo invalido. Solo letras y espacios permitidos y no puede estar vacio. Reintente.\n");
						printf("Tipo actual: %s\nNuevo tipo (o Enter para mantener): ", vehiculos[i].tipo); // Volver a mostrar prompt
					}
				} else {
					break;
				}
			} while (true);
			
			// Edición Avaluo
			do {
				printf("Avaluo actual: %.2f\nNuevo avaluo (o Enter para mantener): ", vehiculos[i].avaluo);
				fgets(input, sizeof(input), stdin);
				input[strcspn(input, "\n")] = 0;
				
				if (strlen(input) > 0) {
					if (sscanf(input, "%f", &avaluoTemp) == 1 && validarAvaluo(avaluoTemp)) {
						vehiculos[i].avaluo = avaluoTemp;
						break;
					} else {
						limpiarPantalla(); // Limpiar si hay error
						printf("Error: Avaluo invalido. Por favor ingrese un valor numerico positivo. Reintente.\n");
						printf("Avaluo actual: %.2f\nNuevo avaluo (o Enter para mantener): ", vehiculos[i].avaluo); // Volver a mostrar prompt
					}
				} else {
					break;
				}
			} while (true);
			
			limpiarPantalla(); // Limpiar antes del mensaje de éxito
			printf("Datos actualizados correctamente.\n");
			break; // Salir del bucle for principal de búsqueda
		}
	}
	
	if (!encontrado) {
		limpiarPantalla(); // Limpiar si no se encontró
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

void eliminarVehiculo() {
	limpiarPantalla(); // Limpiar al entrar a la función
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
	
	do { // Validar el índice
		printf("\nIngrese el numero del vehiculo que desea eliminar: ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%d", &indice) != 1 || indice < 1 || indice > cantidadVehiculos) {
			limpiarPantalla(); // Limpiar si hay error
			printf("Error: Indice invalido. Por favor, ingrese un numero de vehiculo valido.\n");
			// Vuelve a mostrar la lista para que el usuario pueda ver los números de nuevo
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
	
	// Antes de confirmar, limpiar para tener un entorno limpio para la pregunta de confirmación
	limpiarPantalla(); 
	printf("Esta seguro que desea eliminar el vehiculo con placa %s? (s/n): ", vehiculos[indice].placa);
	char confirmacion;
	scanf(" %c", &confirmacion);
	limpiarBuffer();
	
	limpiarPantalla(); // Limpiar antes de mostrar el resultado de la eliminación
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

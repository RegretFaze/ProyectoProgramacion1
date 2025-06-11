#include "vehiculo.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Vehiculo vehiculos[MAX_VEHICULOS];
int cantidadVehiculos = 0;

// --- Nueva función para limpiar la pantalla ---
void limpiarPantalla() {
#ifdef _WIN32
	system("cls"); // Para Windows
#else
	system("clear"); // Para sistemas Unix/Linux/macOS
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
	// Ajustado el límite superior al año actual + 1 para ser más realista y dinámico.
	// Considerando la fecha actual (Junio 2025), un límite de 2026 sería razonable.
	return anio >= 1900 && anio <= 2026;
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

void backupDatos() {
	FILE *archivoOriginal = fopen(ARCHIVO_DATOS, "r");
	if (archivoOriginal == NULL) {
		printf("No se encontro el archivo original para hacer backup.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	FILE *archivoBackup = fopen("backup_vehiculos.txt", "w");
	if (archivoBackup == NULL) {
		printf("Error al crear el archivo de backup.\n");
		fclose(archivoOriginal);
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char linea[256];
	while (fgets(linea, sizeof(linea), archivoOriginal)) {
		fputs(linea, archivoBackup);
	}
	
	fclose(archivoOriginal);
	fclose(archivoBackup);
	
	printf("Backup creado exitosamente en 'backup_vehiculos.txt'.\n");
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void cargarDatos() {
	FILE *archivo = fopen(ARCHIVO_DATOS, "r");
	if (archivo == NULL) {
		printf("No hay datos previos.\n");
		return; // No se pide Enter aquí porque main.c llama limpiarPantalla() inmediatamente.
	}
	
	cantidadVehiculos = 0;
	while (fscanf(archivo, "%s %s %d %s %f %d %d %d",
				  vehiculos[cantidadVehiculos].placa,
				  vehiculos[cantidadVehiculos].cedula,
				  &vehiculos[cantidadVehiculos].anio,
				  vehiculos[cantidadVehiculos].tipo,
				  &vehiculos[cantidadVehiculos].avaluo,
				  &vehiculos[cantidadVehiculos].revisiones[0],
				  &vehiculos[cantidadVehiculos].revisiones[1],
				  &vehiculos[cantidadVehiculos].revisiones[2]) == 8) {
		cantidadVehiculos++;
		if (cantidadVehiculos >= MAX_VEHICULOS) {
			printf("Advertencia: Se alcanzo el limite de vehiculos al cargar datos.\n");
			break;
		}
	}
	
	fclose(archivo);
	printf("Datos cargados correctamente.\n");
	// No se pide Enter aquí porque main.c llama limpiarPantalla() inmediatamente después de cargar.
}

void guardarDatos() {
	FILE *archivo = fopen(ARCHIVO_DATOS, "w");
	if (archivo == NULL) {
		printf("Error al guardar los datos.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
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
	// No se pide Enter aquí porque main.c ya lo maneja antes de salir.
}

void registrarVehiculo() {
	if (cantidadVehiculos >= MAX_VEHICULOS) {
		printf("No se pueden registrar mas vehiculos.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	Vehiculo nuevo;
	char inputBuffer[50]; // Buffer temporal
	
	// Validación de Placa
	do {
		printf("Ingrese la placa (Ej: ABC1234): ");
		scanf("%s", nuevo.placa);
		limpiarBuffer();
		// Mayusculas o minusculas
		for (int i = 0; nuevo.placa[i]; i++) {
			nuevo.placa[i] = toupper(nuevo.placa[i]);
		}
		if (!validarPlaca(nuevo.placa)) {
			printf("Error: Formato de placa invalido. Debe ser 3 letras y 4 digitos (Ej: ABC1234).\n");
		} else {
			// Verificacion de existencia
			bool placaExistente = false;
			for (int i = 0; i < cantidadVehiculos; i++) {
				if (strcmp(vehiculos[i].placa, nuevo.placa) == 0) {
					printf("Error: Ya existe un vehiculo con esa placa.\n");
					placaExistente = true;
					break;
				}
			}
			if (placaExistente) {
				continue;
			}
		}
	} while (!validarPlaca(nuevo.placa));
	
	// Validación de Cédula
	do {
		printf("Ingrese la cedula del propietario (min. 10 digitos): ");
		scanf("%s", nuevo.cedula);
		limpiarBuffer();
		if (!validarCedula(nuevo.cedula)) {
			printf("Error: Formato de cedula invalido. Debe contener solo digitos y al menos 10.\n");
		}
	} while (!validarCedula(nuevo.cedula));
	
	// Validación de Año
	do {
		printf("Ingrese el anio del vehiculo (ej. 2020): ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin); //fgets para leer
		inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Eliminar el salto de línea
		
		if (sscanf(inputBuffer, "%d", &nuevo.anio) != 1 || !validarAnio(nuevo.anio)) {
			printf("Error: Anio invalido. Por favor ingrese un numero valido (1900-2026).\n"); // Corregido el mensaje
		}
	} while (!validarAnio(nuevo.anio));
	
	// Validación de Tipo
	do {
		printf("Ingrese el tipo de vehiculo (ej. Sedan, SUV): ");
		fgets(nuevo.tipo, sizeof(nuevo.tipo), stdin);
		nuevo.tipo[strcspn(nuevo.tipo, "\n")] = 0;
		
		if (!validarTipo(nuevo.tipo)) {
			printf("Error: Tipo de vehiculo invalido. Solo letras y espacios permitidos y no puede estar vacio.\n");
		}
	} while (!validarTipo(nuevo.tipo));
	
	// Validación de Avalúo
	do {
		printf("Ingrese el avaluo del vehiculo (valor positivo): ");
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		inputBuffer[strcspn(inputBuffer, "\n")] = 0;
		
		if (sscanf(inputBuffer, "%f", &nuevo.avaluo) != 1 || !validarAvaluo(nuevo.avaluo)) {
			printf("Error: Avaluo invalido. Por favor ingrese un valor numerico positivo.\n");
		}
	} while (!validarAvaluo(nuevo.avaluo));
	
	// Inicializar revisiones
	for (int i = 0; i < 3; i++) {
		nuevo.revisiones[i] = 0;
	}
	
	vehiculos[cantidadVehiculos++] = nuevo;
	printf("Vehiculo registrado exitosamente.\n");
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void calcularValorMatricula() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para calcular matricula: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
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
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void ordenarVehiculos() {
	if (cantidadVehiculos <= 1) {
		printf("No hay suficientes vehiculos para ordenar.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
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
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void registrarRevision() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	// Buscar placa
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para registrar revision: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			int numRevision;
			char inputBuffer[10]; // Temporal buffer for scanf
			
			do {
				printf("Ingrese el numero de revision (1-3): ");
				fgets(inputBuffer, sizeof(inputBuffer), stdin);
				inputBuffer[strcspn(inputBuffer, "\n")] = 0;
				
				if (sscanf(inputBuffer, "%d", &numRevision) != 1 || numRevision < 1 || numRevision > 3) {
					printf("Error: Numero de revision invalido. Debe ser 1, 2 o 3. Reintente.\n");
				} else {
					vehiculos[i].revisiones[numRevision - 1] = 1;
					printf("Revision %d registrada correctamente como aprobada.\n", numRevision);
					encontrado = true;
					break;
				}
			} while (true); // Loop until valid input
			
			if (encontrado) break; // Exit loop if found and processed
		}
	}
	
	if (!encontrado) {
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

// Comprobante

void generarComprobante() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para generar el comprobante: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			float valorMatricula = vehiculos[i].avaluo * 0.015f;
			
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
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void exportarComprobante() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo para exportar el comprobante: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			char nombreArchivo[30];
			sprintf(nombreArchivo, "comprobante_%s.txt", vehiculos[i].placa);
			
			FILE *archivo = fopen(nombreArchivo, "w");
			if (archivo == NULL) {
				printf("Error al crear el archivo de comprobante.\n");
				printf("Presione Enter para continuar..."); // Añadido
				limpiarBuffer(); // Añadido
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
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void buscarVehiculo() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo a buscar: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
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
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void listarVehiculos() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	printf("\n--- Listado de Vehiculos ---\n");
	for (int i = 0; i < cantidadVehiculos; i++) {
		printf("Placa: %-10s Cedula: %-15s Anio: %-5d Tipo: %-10s Avaluo: $%.2f\n",
			   vehiculos[i].placa, vehiculos[i].cedula, vehiculos[i].anio, vehiculos[i].tipo, vehiculos[i].avaluo);
	}
	printf("-----------------------------\n");
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void estadisticasVehiculares() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	int totalVehiculos = cantidadVehiculos;
	int revisionesAprobadas = 0;
	
	for (int i = 0; i < cantidadVehiculos; i++) {
		for (int j = 0; j < 3; j++) {
			if (vehiculos[i].revisiones[j] == 1) {
				revisionesAprobadas++;
			}
		}
	}
	
	printf("\n--- Estadisticas Vehiculares ---\n");
	printf("Total de vehiculos registrados: %d\n", totalVehiculos);
	printf("Total de revisiones aprobadas: %d\n", revisionesAprobadas);
	printf("---------------------------------\n");
	printf("Presione Enter para continuar..."); // Añadido
	limpiarBuffer(); // Añadido
}

void editarVehiculo() {
	if (cantidadVehiculos == 0) {
		printf("No hay vehiculos registrados para editar.\n");
		printf("Presione Enter para continuar..."); // Añadido
		limpiarBuffer(); // Añadido
		return;
	}
	
	char placaBuscar[10];
	printf("Ingrese la placa del vehiculo a editar: ");
	scanf("%s", placaBuscar);
	limpiarBuffer();
	
	bool encontrado = false; // Añadido para manejar el mensaje de "No encontrado"
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			printf("\n--- Editando Vehiculo ---\n");
			printf("Deje en blanco si no desea modificar un campo (presione Enter).\n");
			
			char input[50];
			int anioTemp;
			float avaluoTemp;
			
			//Edicion de Cédula
			do {
				printf("Cedula actual: %s\nNueva cedula (o Enter para mantener): ", vehiculos[i].cedula);
				fgets(input, sizeof(input), stdin);
				input[strcspn(input, "\n")] = 0;
				
				if (strlen(input) > 0) { // Si el usuario ingresó algo
					if (!validarCedula(input)) {
						printf("Error: Formato de cedula invalido. Debe contener solo digitos y al menos 10. Reintente.\n");
					} else {
						strcpy(vehiculos[i].cedula, input);
						break; // Salir del bucle (válida)
					}
				} else { // Mantener el valor actual
					break;
				}
			} while (true); // Repetir (Igual o blanco)
			
			
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
						printf("Error: Anio invalido. Por favor ingrese un numero valido (1900-2026). Reintente.\n"); // Corregido mensaje
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
						printf("Error: Tipo de vehiculo invalido. Solo letras y espacios permitidos y no puede estar vacio. Reintente.\n");
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
						printf("Error: Avaluo invalido. Por favor ingrese un valor numerico positivo. Reintente.\n");
					}
				} else {
					break;
				}
			} while (true);
			
			printf("Datos actualizados correctamente.\n");
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

void eliminarVehiculo() {
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
			printf("Error: Indice invalido. Por favor, ingrese un numero de vehiculo valido.\n");
		} else {
			break; 
		}
	} while (true);
	
	indice--;
	
	printf("Esta seguro que desea eliminar el vehiculo con placa %s? (s/n): ", vehiculos[indice].placa);
	char confirmacion;
	scanf(" %c", &confirmacion);
	limpiarBuffer();
	
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

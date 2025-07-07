#include "vehiculo.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necesario para toupper y tolower

Vehiculo vehiculos[MAX_VEHICULOS];
int cantidadVehiculos = 0;

Usuario usuarios[MAX_USUARIOS]; // Nuevo: Definición del array de usuarios
int cantidadUsuarios = 0;     // Nuevo: Definición de la cantidad de usuarios

// Funcion para limpiar la pantalla
void limpiarPantalla() {
#ifdef _WIN32
	system("cls"); // Para Windows
#else
	system("clear"); // Para sistemas Unix/Linux
#endif
}

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
static bool validarCedula(const char *cedula) {
	int len = strlen(cedula);
	if (len != 10) return false;
	
	for (int i = 0; i < len; i++) {
		if (!isdigit(cedula[i])) return false;
	}
	return true;
}

// Validación de Año (Límites)
static bool validarAnio(int anio) {
	// Límites del año
	return anio >= 1900 && anio <= 2026;
}

// Validación de Tipo de Vehículo
static bool validarTipo(const char *tipo) {
	char tipo_lower[20];
	strcpy(tipo_lower, tipo);
	for (int i = 0; tipo_lower[i]; i++) {
		tipo_lower[i] = tolower(tipo_lower[i]);
	}
	
	return (strcmp(tipo_lower, "carro") == 0 ||
			strcmp(tipo_lower, "camion") == 0 ||
			strcmp(tipo_lower, "camioneta") == 0);
}

// Validación de Avalúo
static bool validarAvaluo(float avaluo) {
	return avaluo > 0 && avaluo <= 120000.0f;
}

// Funciones Principales

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Función para cargar usuarios desde un archivo
void cargarUsuarios() {
	FILE *archivo = fopen(ARCHIVO_USUARIOS, "r");
	if (archivo == NULL) {
		// Si el archivo no existe, crear un usuario por defecto
		// En un sistema real, aquí se podría pedir al usuario que cree el primer admin
		if (cantidadUsuarios == 0) { // Solo añadir si no hay usuarios ya cargados (evitar duplicados si se llama de nuevo)
			strcpy(usuarios[0].username, "admin");
			strcpy(usuarios[0].password, "1234567890"); // Usar una cédula de 10 dígitos como contraseña
			cantidadUsuarios = 1;
			guardarUsuarios(); // Guardar el usuario por defecto
		}
		return;
	}
	
	cantidadUsuarios = 0;
	while (fscanf(archivo, "%s %s", usuarios[cantidadUsuarios].username, usuarios[cantidadUsuarios].password) == 2 && cantidadUsuarios < MAX_USUARIOS) {
		cantidadUsuarios++;
	}
	fclose(archivo);
}

// Función para guardar usuarios en un archivo
void guardarUsuarios() {
	FILE *archivo = fopen(ARCHIVO_USUARIOS, "w");
	if (archivo == NULL) {
		printf("Error al guardar los datos de usuario.\n");
		return;
	}
	
	for (int i = 0; i < cantidadUsuarios; i++) {
		fprintf(archivo, "%s %s\n", usuarios[i].username, usuarios[i].password);
	}
	fclose(archivo);
}

// Función para registrar un nuevo usuario
void registrarNuevoUsuario() {
	if (cantidadUsuarios >= MAX_USUARIOS) {
		limpiarPantalla();
		printf("No se pueden registrar mas usuarios. Limite alcanzado.\n");
		printf("Presione Enter para continuar...");
		limpiarBuffer();
		return;
	}
	
	Usuario nuevoUsuario;
	bool usernameExistente;
	
	do {
		limpiarPantalla();
		printf("--- Registrar Nuevo Usuario ---\n");
		printf("Ingrese un nombre de usuario: ");
		scanf("%s", nuevoUsuario.username);
		limpiarBuffer();
		
		usernameExistente = false;
		for (int i = 0; i < cantidadUsuarios; i++) {
			if (strcmp(usuarios[i].username, nuevoUsuario.username) == 0) {
				printf("Error: Ese nombre de usuario ya existe. Intente con otro.\n");
				printf("Presione Enter para reintentar...");
				limpiarBuffer();
				usernameExistente = true;
				break;
			}
		}
	} while (usernameExistente);
	
	do {
		printf("Ingrese una contrasena (cedula de 10 digitos): ");
		scanf("%s", nuevoUsuario.password);
		limpiarBuffer();
		if (!validarCedula(nuevoUsuario.password)) {
			printf("Error: La contrasena debe ser una cedula de 10 digitos. Reintente.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break;
		}
	} while (true);
	
	usuarios[cantidadUsuarios++] = nuevoUsuario;
	guardarUsuarios(); // Guardar el nuevo usuario en el archivo
	limpiarPantalla();
	printf("Usuario registrado exitosamente!\n");
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para guardar los datos de los vehículos en un archivo
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

// Función para registrar un nuevo vehículo
void registrarVehiculo() {
	if (cantidadVehiculos >= MAX_VEHICULOS) {
		limpiarPantalla(); // Si no se pueden registrar más vehículos
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
		break; // Salir del bucle si es válido
	} while (true);
	
	// Validación de Cedula
	do {
		limpiarPantalla(); // Limpiar pantalla por intento
		printf("--- Registrar Vehiculo ---\n");
		printf("Ingrese la cedula del propietario (10 digitos): ");
		scanf("%s", nuevo.cedula);
		limpiarBuffer();
		if (!validarCedula(nuevo.cedula)) {
			printf("Error: Formato de cedula invalido. Debe contener solo digitos y ser 10 en total.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			break; // Si la cedula es válida, salir del bucle
		}
	} while (true);
	
	// Validación de Año
	do {
		limpiarPantalla(); // Limpiar pantalla para cada intento
		printf("--- Registrar Vehiculo ---\n"); // Título para contexto
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
		printf("Ingrese el tipo de vehiculo (carro, camion, camioneta): "); // Mensaje con opciones
		fgets(nuevo.tipo, sizeof(nuevo.tipo), stdin);
		nuevo.tipo[strcspn(nuevo.tipo, "\n")] = 0;
		
		if (!validarTipo(nuevo.tipo)) {
			printf("Error: Tipo de vehiculo invalido. Solo se aceptan 'carro', 'camion' o 'camioneta'.\n");
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		} else {
			for (int i = 0; nuevo.tipo[i]; i++) {
				nuevo.tipo[i] = tolower(nuevo.tipo[i]);
			}
			break;
		}
	} while (true);
	
	// Validación de Avalúo
	do {
		limpiarPantalla(); // Limpiar pantalla para cada intento
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

// Función para calcular el valor de la matrícula (no se usa en el menú principal)
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
	for (int i = 0; placaBuscar[i]; i++) {
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			encontrado = true;
			// Verificar las 3 revisiones
			bool todasRevisionesCompletas = true;
			for (int j = 0; j < 3; j++) {
				if (vehiculos[i].revisiones[j] == 0) { // Si alguna revisión está pendiente
					todasRevisionesCompletas = false;
					break;
				}
			}
			
			if (todasRevisionesCompletas) {
				float valorMatricula = vehiculos[i].avaluo * 0.015f;
				printf("Valor de matricula para %s: $%.2f\n", vehiculos[i].placa, valorMatricula);
			} else {
				printf("Advertencia: El vehiculo con placa %s no ha completado las 3 revisiones tecnicas. No se puede calcular la matricula.\n", vehiculos[i].placa);
			}
			break;
		}
	}
	
	if (!encontrado) {
		printf("Vehiculo no encontrado.\n");
	}
	printf("Presione Enter para continuar...");
	limpiarBuffer();
}

// Función para registrar una revisión técnica
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
	for (int i = 0; placaBuscar[i]; i++) { // Convertir a mayúsculas
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			int numRevision;
			char inputBuffer[10];
			
			do {
				limpiarPantalla(); // Limpiar pantalla para cada intento de revisión
				printf("--- Registrar Revision Tecnica ---\n");
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

// Función para generar un comprobante de matrícula
void generarComprobante() {
	limpiarPantalla();
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
	for (int i = 0; placaBuscar[i]; i++) { // Convertir a mayúsculas
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
	bool encontrado = false;
	for (int i = 0; i < cantidadVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
			encontrado = true;
			bool todasRevisionesCompletas = true;
			for (int j = 0; j < 3; j++) {
				if (vehiculos[i].revisiones[j] == 0) { // Si alguna revisión está pendiente
					todasRevisionesCompletas = false;
					break;
				}
			}
			
			// Si no todas las revisiones están completas, mostrar advertencia y salir.
			if (!todasRevisionesCompletas) {
				limpiarPantalla(); // Limpiar antes de mostrar el mensaje de advertencia
				printf("\nAdvertencia: El vehiculo no cuenta con las 3 revisiones tecnicas necesarias, por ende, no se puede generar el comprobante del mismo.\n");
				printf("Presione Enter para continuar...");
				limpiarBuffer();
				return; // Salir de la función generarComprobante
			}
			
			// Si todas las revisiones están completas, proceder a mostrar y exportar el comprobante
			float valorMatricula = vehiculos[i].avaluo * 0.015f; // Calcular valor solo si se va a mostrar
			
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
			
			// Preguntar al usuario si desea exportar el comprobante
			char opcionExportar;
			printf("¿Desea exportar este comprobante a un archivo? (s/n): ");
			scanf(" %c", &opcionExportar);
			limpiarBuffer();
			
			if (opcionExportar == 's' || opcionExportar == 'S') {
				char nombreArchivo[30];
				sprintf(nombreArchivo, "comprobante_%s.txt", vehiculos[i].placa);
				
				FILE *archivo = fopen(nombreArchivo, "w");
				if (archivo == NULL) {
					printf("Error al crear el archivo de comprobante.\n");
					printf("Presione Enter para continuar...");
					limpiarBuffer();
					return;
				}
				
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
			} else {
				printf("El comprobante no fue exportado.\n");
			}
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

// Función para buscar un vehículo
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
	for (int i = 0; placaBuscar[i]; i++) { // Convertir a mayúsculas
		placaBuscar[i] = toupper(placaBuscar[i]);
	}
	
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

// Función para listar todos los vehículos registrados
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

// Función para eliminar un vehículo
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
			// Permitir al usuario ver los números de nuevo
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
	
	indice--; // Ajustar a índice base 0
	
	// Antes de confirmar, pedir confirmación
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

// Función de inicio de sesión
bool login() {
	char username[50];
	char password[15];
	int attempts = 0;
	const int MAX_ATTEMPTS = 3;
	
	while (attempts < MAX_ATTEMPTS) {
		limpiarPantalla();
		printf("--- Iniciar Sesion ---\n");
		printf("Usuario: ");
		scanf("%s", username);
		limpiarBuffer();
		
		printf("Contrasena (cedula de 10 digitos): ");
		scanf("%s", password);
		limpiarBuffer();
		
		bool credencialesCorrectas = false;
		for (int i = 0; i < cantidadUsuarios; i++) {
			if (strcmp(username, usuarios[i].username) == 0 && strcmp(password, usuarios[i].password) == 0) {
				credencialesCorrectas = true;
				break;
			}
		}
		
		if (credencialesCorrectas) {
			printf("Inicio de sesion exitoso!\n");
			printf("Presione Enter para continuar...");
			limpiarBuffer();
			return true;
		} else {
			attempts++;
			printf("Credenciales incorrectas. Intentos restantes: %d\n", MAX_ATTEMPTS - attempts);
			printf("Presione Enter para reintentar...");
			limpiarBuffer();
		}
	}
	
	// Si se agotan los intentos, ofrecer registrarse
	limpiarPantalla();
	printf("Demasiados intentos fallidos.\n");
	printf("¿Desea registrar un nuevo usuario? (s/n): ");
	char opcionRegistro;
	scanf(" %c", &opcionRegistro);
	limpiarBuffer();
	
	if (opcionRegistro == 's' || opcionRegistro == 'S') {
		registrarNuevoUsuario();
		return login(); // Intentar iniciar sesión con el nuevo usuario
	}
	
	printf("Saliendo del programa.\n");
	printf("Presione Enter para salir...");
	limpiarBuffer();
	return false;
}

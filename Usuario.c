#include "Usuario.h"
#include "Validaciones_funciones_comunes.h" // Para funciones de utilidad y validación
#include <string.h> // Para strcmp, strcpy
#include <stdio.h>  // Para FILE, fopen, fclose, fscanf, fprintf, printf

// Definición de las variables globales para usuarios
Usuario usuarios[MAX_USUARIOS];
int cantidadUsuarios = 0;

// Función para cargar usuarios desde un archivo
void cargarUsuarios() {
	FILE *archivo = fopen(ARCHIVO_USUARIOS, "r");
	if (archivo == NULL) {
		// Si el archivo no existe, crear un usuario por defecto
		if (cantidadUsuarios == 0) {
			strcpy(usuarios[0].username, "admin");
			strcpy(usuarios[0].password, "1234567890"); // Contraseña de 10 dígitos (cédula)
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

#ifndef USUARIO_H
#define USUARIO_H
#include "Validaciones_funciones_comunes.h" // Para constantes y bool

// Estructura para el usuario
typedef struct {
	char username[50];
	char password[15];
} Usuario;

// Variables globales para usuarios (definidas en user_manager.c)
extern Usuario usuarios[MAX_USUARIOS];
extern int cantidadUsuarios;

// Funciones de gestión de usuarios
void cargarUsuarios();
void guardarUsuarios();
void registrarNuevoUsuario();
bool login();

#endif

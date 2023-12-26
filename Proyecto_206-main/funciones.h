#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <algorithm>

//Inicio de sesion
bool validarNombreUsuario(std::string& usuario);
bool validarUsuario(std::string& usuario, std::string& contrasena);
bool inicioSesion(std::string& usuario, std::string& contrasena);
bool comprobarUsuario(std:: string& usuario);

//Registro
bool registrarUsuario(std::string& usuario, std::string& contrasena);

//Crear evento
void crearEvento();
void introducirNombre(std::string &nombre);
bool comprobarEvento(std::string& nombre);
void introducirTipoEvento(std::string& tipo);
bool comprobarTipoEvento(std::string& tipo);
bool comprobarFechas (std::string& fechaInicio, std::string& fechaFin);
void introducirFechas(std::string& fechaInicio, std::string& fechaFin);
bool guardarEvento(std::string& nombre, std::string& tipo, std::string& descripcion, int precio, int aforo, std::string& fechaInicio, std::string& fechaFin, int duracion); 

//Inscribirse
void preinscribirEvento(std::string& usuario, std::string& nombreEvento);
bool comprobarInscripcion(std::string& usuario, std::string& nombreEvento);
int obtenerAforo(std::string& nombreEvento);
int contarAforoInscritos (std::string &nombreEvento);
bool inscripcion(std::string& usuario, std::string& nombreEvento, int aforo);

//Eliminar evento
void eliminarEvento(std::string& nombre);

//Modificar evento
bool modificarEvento(std::string& nombre);
bool guardarNuevosDatos(std::vector<std::string> vector, std::string& nombre, std::string& nuevoNombre, std::string& tipo, std::string& descripcion, int precio, int aforo, std::string& fechaInicio, std::string& fechaFin, int duracion);

//Listar evento
void listarEvento();

//Comprobar tipo de usuario
int comprobarCorreo(std::string& correo);

//Menús
void menu();
void inicioAdministrador(); 
void menuAdministrador(); 
void inicioUsuario(); 
void menuUsuario(); 

#endif

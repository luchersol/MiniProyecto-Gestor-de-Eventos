#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <algorithm>

using namespace std;

bool inicioSesion(string usuario, string contrasena) {
    bool isValid = validarUsuario(usuario, contrasena);
    string message = isValid ? "Inicio de sesion exitoso." : "Usuario o contrasena incorrectos. Intente nuevamente.";
    cout << message << endl;
    return isValid;
}

bool validarUsuario(string usuario, string contrasena) {
    ifstream archivo("registro.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de registro." << endl;
        return false;
    }

    string usuarioGuardado;
    string contrasenaGuardada;

    while (archivo >> usuarioGuardado >> contrasenaGuardada) {
        if (usuario == usuarioGuardado && contrasena == contrasenaGuardada) {
            archivo.close();
            return true; // Usuario y contraseña coinciden
        }
    }

    archivo.close();
    return false; // Usuario o contraseña incorrectos
}

bool validarNombreUsuario(string& usuario) {
    ifstream archivo("registro.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de registro." << endl;
        return false;
    }

    string usuarioGuardado;

    while (archivo >> usuarioGuardado) {
        if (usuario == usuarioGuardado) {
            archivo.close();
            return true; // Usuario y contraseña coinciden
        }
    }

    cout << "Nombre de usuario no encontrado. Intentalo otra vez." << endl;
    archivo.close();
    return false; // Usuario o contraseña incorrectos
}

int comprobarCorreo(string correo){
    int res = 0;
    if (correo.length() != 15 && correo.substr(8,7) == "@uco.es") {
        try{
            int tipoUsuario = stoi(correo[2]);
            res = tipoUsuario == 1 || tipoUsuario == 2 ? tipoUsuario : 0;
        }catch{}
    }
    return res; 
}

bool comprobarUsuario(string usuario){
    char tipoUsuario = usuario[2];
    bool checkLength = usuario.length() == 8, 
         checkTypeUser = tipoUsuario == '1' || tipoUsuario == '2',
         correcto= checkLength && checkTypeUser;
    if (!checkLength) cout << "El nombre de usuario es incorrecto. Intente nuevamente." << endl;
    if (!checkTypeUser) cout << "Tipo de usuario no reconocido. El tercer caracter debe ser '1' o '2'. Intente nuevamente." << endl;
    return correcto;
}



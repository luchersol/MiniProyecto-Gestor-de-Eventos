#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>
#include "Eventos.cpp"
#include "Inscripciones.cpp"

class IniciarSesion
{
public:
    enum Authority
    {
        USUARIO,
        ADMINISTRADOR,
        ERROR
    };
    static bool inicioSesion(Registros &registros, std::string usuario, std::string contrasena)
    {
        bool isValid = registros.validarRegistro(usuario, contrasena);
        std::string message = isValid ? "Inicio de sesion exitoso." : "Usuario o contrasena incorrectos. Intente nuevamente.";
        std::cout << message << std::endl;
        return isValid;
    }

    static IniciarSesion::Authority comprobarCorreo(Registros &registros, std::string &correo)
    {
        IniciarSesion::Authority res = IniciarSesion::ERROR;
        std::vector<std::string> trozos = split(correo, '@');
        if (correo.length() == 15 && registros.existeRegistro(trozos[0]) && trozos[1] == "uco.es")
        {
            try
            {
                std::string idTipo = correo.substr(2, 1);
                int tipoUsuario = std::stoi(idTipo);
                res = tipoUsuario == 1 ? IniciarSesion::ADMINISTRADOR : tipoUsuario == 2 ? IniciarSesion::USUARIO
                                                                                         : res;
            }
            catch (std::exception &e)
            {
                std::cerr << "Correo invalido." << std::endl;
            }
        }
        return res;
    }

    static bool comprobarUsuario(std::string usuario)
    {
        char tipoUsuario = usuario[2];
        bool checkLength = usuario.length() == 8,
             checkTypeUser = tipoUsuario == '1' || tipoUsuario == '2',
             correcto = checkLength && checkTypeUser;
        if (!checkLength)
            std::cerr << "El nombre de usuario es incorrecto. Intente nuevamente." << std::endl;
        if (!checkTypeUser)
            std::cerr << "Tipo de usuario no reconocido. El tercer caracter debe ser '1' o '2'. Intente nuevamente." << std::endl;
        return correcto;
    }
};

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Registro.cpp"
#include "Utils.h"
#include "Fichero.cpp"

class Registros
{
private:
    std::vector<Registro> registros;
    static std::string RUTA() {
        return "C:\\Users\\lmher\\Desktop\\Blanca\\Proyecto_206-main\\registros.txt";
    };
public:
    Registros()
    {
        std::vector<std::vector<std::string>> lista = Fichero::accionArchivo(Registros::RUTA());
        for (auto &&elemento : lista)
        {
            Registro registro = Registro::parsear(elemento);
            this->registros.push_back(registro);
        }
    }

    void registrarUsuario()
    {
        std::string nombre, contrasena;
        bool tryAgain = true;
        bool isValid = true;
        do
        {
            std::cout << "Introduce nombre:" << std::endl;
            std::cin >> nombre;
            isValid = !existeRegistro(nombre);
            if (isValid)
                std::cout << "Este usuario ya existe." << std::endl;
            std::cout << "¿Quieres intentar de nuevo? (Introduce 'Y' para confirmar)";
            std::string response;
            std::cin >> response;
            tryAgain = response == "Y";
        } while (!isValid && tryAgain);
        
        if(isValid){
            std::cout << "Introduce contrasena:" << std::endl;
            std::cin >> contrasena;
            Registro registro(nombre, contrasena);
            this->registros.push_back(registro);
        }
    }

    // Comprueba que no existe ningún registro de la misma persona
    bool existeRegistro(std::string usuario)
    {
        bool existe = false;
        for (auto &&registro : this->registros)
        {
            if (registro.getUsuario() == usuario)
            {
                existe = true;
                break;
            }
        }
        return existe;
    }

    bool validarRegistro(std::string usuario, std::string contrasena)
    {
        bool existe = false;
        for (auto &&registro : this->registros)
        {
            if(registro.getUsuario() == usuario && registro.getUsuario() == contrasena){
                existe = true;
                break;
            }
        }
        return existe;
    }
};
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Registro.cpp"

class Registros
{
private:
    std::vector<Registro> registros;

public:
    Registros()
    {
        std::ifstream archivo("C:\\Users\\lmher\\Desktop\\Blanca\\Proyecto_206-main\\registros.txt");

        if (!archivo.is_open())
        {
            std::cerr << "Error al abrir el archivo de registros." << std::endl;
            exit(1);
        }
        std::string linea;
        while (std::getline(archivo, linea))
        {
            int delimiter = linea.find_first_of(" ");
            std::string nombre = linea.substr(0, delimiter),
                        contrasena = linea.substr(delimiter + 1);
            Registro registro(nombre, contrasena);
            this->registros.push_back(registro);
        }
        archivo.close();
    }

    void registrarUsuario()
    {
        std::string nombre, contrasena;
        bool tryAgain = true;
        do
        {
            std::cout << "Introduce nombre:" << std::endl;
            std::cin >> nombre;
            bool isValid = !existeRegistro(nombre);
            if (!isValid)
                std::cout << "Este usuario ya existe." << std::endl;
            std::cout << "¿Quieres intentar de nuevo? (Introduce 'Y' para confirmar)";
            tryAgain = std::cin == "Y";
        } while (!isValid && tryAgain);
        
        if(isValid){
            std::cout << "Introduce contrasena:" << std::endl;
            std::cin >> contrasena;
            Registro registro(usuario, contrasena);
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
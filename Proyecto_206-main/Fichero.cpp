#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <algorithm>
#include "Utils.h"

class Fichero
{
public:
    enum Action {GET, CREATE, EDIT, DELETE};

    static std::vector<std::vector<std::string>> accionArchivo(std::string ruta, Action action = Action::GET, std::string linea = "", int index = 0)
    {
        std::vector<std::vector<std::string>> res;
        switch (action)
        {
        case GET:
            Fichero::lecturaArchivo(ruta, res);
            break;
        case CREATE:
            Fichero::anadirEnArchivo(ruta, linea);
            break;
        case EDIT:
            Fichero::modificarLineaArchivo(ruta, linea, index);
            break;
        case DELETE:
            Fichero::eliminarLineaArchivo(ruta, index);
            break;
        default:
            std::cout << "Acción invalida" << std::endl;
            break;
        }
        return res;
    }

    static void lecturaArchivo(std::string ruta, std::vector<std::vector<std::string>> res)
    {
        std::ifstream archivo(ruta);
        if (archivo.is_open())
        {

            std::string linea;
            std::getline(archivo, linea);
            while (std::getline(archivo, linea))
            {
                char delimiter = ';';
                std::vector<std::string> elemento = split(linea, delimiter);
                res.push_back(elemento);
            }
            archivo.close();
        }
        else
        {
            std::cerr << "Error al abrir el archivo de ruta: " + ruta << std::endl;
        }
    };

    static void anadirEnArchivo(std::string ruta, std::string nuevaLinea)
    {
        std::ofstream archivo(ruta, std::ios::app);

        if (archivo.is_open())
        {
            archivo << nuevaLinea << std::endl;
            archivo.close();
        }
        else
        {
            std::cerr << "Error al abrir el archivo." << std::endl;
        }
    }

    static void modificarLineaArchivo(std::string ruta, std::string nuevaLinea, int index)
    {
        std::fstream archivo(ruta, std::ios::trunc);

        if (archivo.is_open())
        {
            int i = 0;
            std::string linea;
            std::getline(archivo, linea); // Saltamos la primera línea
            while (std::getline(archivo, linea))
            {
                if (index == i)
                    linea = nuevaLinea;
                archivo << linea << std::endl;
                i++;
            }
            archivo.close();
        }
        else
        {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        }
    }

    static void eliminarLineaArchivo(std::string ruta, int index)
    {
        std::fstream archivo(ruta, std::ios::trunc);

        if (archivo.is_open())
        {
            int i = 0;
            std::string linea;
            std::getline(archivo, linea);
            while (std::getline(archivo, linea))
            {
                if (index != i)
                {
                    archivo << linea << std::endl;
                }
                i++;
            }
            archivo.close();
        }
        else
        {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        }
    }
};
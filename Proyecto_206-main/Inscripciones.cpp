#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <algorithm>
#include "Inscripcion.cpp"

class Inscripciones
{
private:
    std::vector<Inscripcion> inscripciones;

public:
    Inscripciones()
    {
        std::ifstream archivo("C:\\Users\\lmher\\Desktop\\Blanca\\Proyecto_206-main\\inscripciones.txt");

        if (!archivo.is_open())
        {
            std::cerr << "Error al abrir el archivo de inscripcion." << std::endl;
            exit(1);
        }

        std::string linea;
        while (std::getline(archivo, linea))
        {
            int delimiter = linea.find_first_of("-->");
            std::string nombre = linea.substr(0, delimiter),
                        contrasena = linea.substr(delimiter + 3, linea.length() - delimiter);
            Inscripcion inscripcion(nombre, contrasena);
            this->inscripciones.push_back(inscripcion);
        }
        archivo.close();
    }

    bool inscribirUsuario(std::string &usuario, int &aforo)
    {
        std::string nombreEvento;
        std::cout << "Introduce nombre del evento: " << std::endl;
        std::cin >> nombreEvento;
        Inscripcion inscripcion(usuario, nombreEvento);
        if (this->existeInscripcion(inscripcion))
        {
            std::cout << "La persona ya esta inscrita" << std::endl;
            return false;
        }
        else{
            std::cout << "No se encuentra el evento." << std::endl;
        }

        int contador = this->contarAforoInscritos(nombreEvento);

        if (contador < aforo)
        {
            this->inscripciones.push_back(inscripcion);
            std::cout << "Inscripcion exitosa." << std::endl;
        }
        else
        {
            std::cout << "El aforo esta completo. " << std::endl;
        }

    }

    int contarAforoInscritos(std::string nombreEvento)
    {
        int aforo = 0;
        for (auto &&inscripcion : this->inscripciones)
        {
            if(inscripcion.getNombreEvento() == nombreEvento){
                aforo++;
            }
        }
        return aforo;
    }

    bool existeInscripcion(Inscripcion inscripcion)
    {
        std::string inscrip = inscripcion.getUsuario() + "-->" + inscripcion.getNombreEvento();

        bool existe = false;
        for (auto &&inscripcion : this->inscripciones)
        {
            if (inscripcion.toString() == inscrip)
            {
                existe = true;
                break;
            }
        }

        return existe;
    }
};
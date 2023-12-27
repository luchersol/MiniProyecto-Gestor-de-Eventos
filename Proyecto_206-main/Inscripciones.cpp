#include "Inscripcion.cpp"
#include "Registros.cpp"
#include "Eventos.cpp"
#include "Fichero.hpp"

class Inscripciones
{
private:
    std::vector<Inscripcion> inscripciones;
    static std::string RUTA() {
        return "C:\\Users\\lmher\\Desktop\\Blanca\\Proyecto_206-main\\inscripciones.txt";
    };
public:
    Inscripciones()
    {
        std::vector<std::vector<std::string>> lista = Fichero::accionArchivo(Inscripciones::RUTA());
        for (auto &&elemento : lista)
        {
            Inscripcion inscripcion = Inscripcion::parsear(elemento);
            this->inscripciones.push_back(inscripcion);
        }
    };

    bool inscribirUsuario(std::string &usuario, Eventos eventos)
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
        int aforo = eventos.obtenerAforo(nombreEvento);
        if (contador < aforo)
        {
            this->inscripciones.push_back(inscripcion);
            std::cout << "Inscripcion exitosa." << std::endl;
        }
        else
        {
            std::cout << "El aforo esta completo. " << std::endl;
        }

    };

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
    };

    bool existeInscripcion(Inscripcion in)
    {
        bool existe = false;
        for (auto &&inscripcion : this->inscripciones)
        {
            if (inscripcion.equals(in))
            {
                existe = true;
                break;
            }
        }

        return existe;
    };
};
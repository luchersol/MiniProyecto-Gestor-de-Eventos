#include "Evento.cpp"
#include "Utils.h"
#include "Fichero.hpp"

// Nombre; Tipo; Descripcion; Fecha Inicio; Fecha Fin; Precio; Aforo;  Duracion
class Eventos
{
private:
    std::vector<Evento> eventos;
    static std::string RUTA() {
        return "C:\\Users\\lmher\\Desktop\\Blanca\\Proyecto_206-main\\eventos.txt";
    };
public:
    Eventos()
    {
        std::vector<std::vector<std::string>> lista = Fichero::accionArchivo(Eventos::RUTA());
        for (auto &&elemento : lista)
        {
            Evento evento = Evento::parsear(elemento);
            this->eventos.push_back(evento);
        }
    }

    Evento crearEvento()
    {
        std::string nombre, descripcion;
        Evento::Tipo tipo;
        std::time_t fechaInicio, fechaFin;
        int precio, aforo, duracion;

        this->introducirNombre(nombre);
        Eventos::introducirTipoEvento(tipo);

        std::cout << "Introduzce una descripcion del evento." << std::endl;
        std::cin >> descripcion;

        std::cout << "Introduzca precio del evento." << std::endl;
        std::cin >> precio;

        std::cout << "Introduzca aforo del evento." << std::endl;
        std::cin >> aforo;

        Eventos::introducirFechas(fechaInicio, fechaFin);

        std::cout << "Introduzca duracion del evento(en minutos)." << std::endl;
        std::cin >> duracion;

        return Evento(nombre, tipo, descripcion, fechaInicio, fechaFin, precio, aforo, duracion);
    }

    void introducirNombre(std::string &nombre)
    {
        while (true)
        {
            std::cout << "Introduzca el nombre del evento (pulsa -enter- en una linea vacia para fianlizar)." << std::endl;
            std::cin >> nombre;

            if (this->existeEvento(nombre))
                std::cout << "El nombre del evento ya existe. Introduce otro." << std::endl;
            else
                break;
        }
    }

    static void introducirTipoEvento(Evento::Tipo &tipo)
    {
        std::string strTipo;
        while (true)
        {
            std::cout << "Introduzca el tipo de evento (congreso, ponencia, taller, seminario)." << std::endl;
            std::cin >> strTipo;
            tipo = Evento::parseTipo(strTipo);

            if (tipo != Evento::ERROR)
                break;
            else
                std::cout << "No es congreso, ni ponencia, ni taller, ni seminario. Intentalo de nuevo." << std::endl;
        }
    }

    static void introducirFechas(std::time_t &fechaInicio, std::time_t &fechaFin)
    {
        std::string strFechaInicio, strFechaFin;
        while (true)
        {
            std::cout << "Introduzca fecha de inicio (AAAA-MM-DD)." << std::endl;
            std::cin >> strFechaInicio;
            fechaInicio = parsearFecha(strFechaInicio);

            std::cout << "Introduzca fecha de fin (AAAA-MM-DD)." << std::endl;
            std::cin >> strFechaFin;
            fechaFin = parsearFecha(strFechaFin);

            if (fechaInicio <= fechaFin)
                break;
            else
                std::cout << "La fecha de fin es anterior a la fecha de inicio. Intentalo otra vez." << std::endl;
        }
    }

    bool existeEvento(std::string &nombre)
    {
        bool existe = false;
        for (auto &&evento : this->eventos)
        {
            if(evento.getNombre() == nombre){
                existe = true;
                break;
            }
        }
        
        return existe;
    }

    static bool comprobarTipoEvento(std::string &tipo)
    {
        for (size_t i = 0; i < tipo.length(); i++)
        {
            tipo[i] = std::tolower(tipo[i]);
        }
        return (tipo == "taller" || tipo == "seminario" || tipo == "congreso" || tipo == "ponencia"); // devolver "true" si está correcto
    }

    Evento obtenerEvento(std::string &nombre){
        Evento res = Evento::empty();
        for (auto &&evento : this->eventos)
        {
            if(evento.getNombre() == nombre){
                res = evento;
                break;
            }
        }
        return res;
    }

    void listarEventos()
    {
        std::cout << "Esta opcion solo muestra los eventos disponibles." << std::endl;
        std::cout << std::endl;
        for (auto &&evento : this->eventos)
        {
            std::cout << evento.toString();
        }
    }

    int obtenerAforo(std::string nombreEvento)
    {
        int aforo = 0;
        for (auto &&evento : this->eventos)
        {
            if (evento.getNombre() == nombreEvento)
                aforo = evento.getAforo();
        }
        return aforo;
    }

    void guardarEvento(Evento evento)
    {
        eventos.push_back(evento);
    }

    void modificarEvento()
    {
        std::cout << "Introduce el nombre del evento a modificar: ";
        std::string nombre;
        std::cin >> nombre;
        bool exist = false;
        std::vector<Evento> res;
        for (auto &&evento : this->eventos)
        {
            if (evento.getNombre() == nombre)
            {
                // TODO: PARTE DE MODIFICACIÓN
                exist = true;
                break;
            }
            else
            {
                res.push_back(evento);
            }
        }
        if(!exist) std::cerr << "Nombre no encontrado. Inténtalo otra vez." << std::endl;
        this->eventos = res;
    }

    void eliminarEvento()
    {
        std::cout << "Introduce el nombre del evento a eliminar: ";
        std::string nombre;
        std::cin >> nombre;
        std::vector<Evento> res;
        bool exist = false;
        for (auto &&evento : this->eventos)
        {
            if (evento.getNombre() != nombre)
                res.push_back(evento);
            else
                exist = true;
        }
        if(!exist) std::cout << "Nombre no encontrado. Inténtalo otra vez." << std::endl;;
        this->eventos = res;
    }
};
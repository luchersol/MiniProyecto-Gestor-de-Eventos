#include <string>
#include <iostream>
#include <iosfwd>
#include <ctime>
#include "Utils.h"

class Evento
{
public:
    enum Tipo
    {
        TALLER,
        CONGRECIO,
        PONENCIA,
        SEMINARIO,
        ERROR
    };

private:
    std::string nombre, descripcion;
    std::time_t fechaInicio, fechaFin;
    int precio, aforo, duracion;
    Tipo tipo;

public:
    Evento(std::string &nombre, Tipo tipo, std::string &descripcion, std::time_t &fechaInicio, std::time_t &fechaFin, int &precio, int &aforo, int &duracion)
    {
        this->nombre = nombre;
        this->tipo = tipo;
        this->descripcion = descripcion;
        this->fechaInicio = fechaInicio;
        this->fechaFin = fechaFin;
        this->precio = precio;
        this->aforo = aforo;
        this->duracion = duracion;
    };

    static Evento empty(){
        std::string strVacio = "";
        int intVacio = 0;
        std::time_t timeVacio = time(0);
        Tipo tipoVacio = Tipo::ERROR;
        return Evento(strVacio, tipoVacio, strVacio, timeVacio, timeVacio, intVacio, intVacio, intVacio);
    }

    std::string getNombre()
    {
        return this->nombre;
    };

    Tipo getTipo()
    {
        return this->tipo;
    };

    std::string getTipoLikeString()
    {
        switch (this->tipo)
        {
        case TALLER:
            return "Taller";
        case CONGRECIO:
            return "Congrecio";
        case PONENCIA:
            return "Ponencia";
        case SEMINARIO:
            return "Seminario";
        default:
            return "Tipo no valido";
        }
    };

    std::string getDescripcion()
    {
        return this->descripcion;
    };

    std::time_t getFechaInicio()
    {
        return this->fechaInicio;
    };

    std::time_t getFechaFin()
    {
        return this->fechaFin;
    };

    int getPrecio()
    {
        return this->precio;
    };

    int getAforo()
    {
        return this->aforo;
    };

    int getDuracion()
    {
        return this->duracion;
    };

    static Tipo parseTipo(std::string str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ') + 1;
        if(first == std::string::npos) first = 0;
        str = str.substr(first, last);
        for (size_t i = 0; i < str.length(); i++)
        {
            str[i] = std::tolower(str[i]);
        }
        
        return str == "taller" ? Evento::TALLER : str == "congrecio" ? Evento::CONGRECIO
                                              : str == "ponencia"    ? Evento::PONENCIA
                                              : str == "seminario"   ? Evento::SEMINARIO
                                                                     : Evento::ERROR;
    };

    static Evento parsear(std::vector<std::string> &trozos){
        std::string nombre = trozos[0], 
                    descripcion = trozos[2];
        Evento::Tipo tipo = Evento::parseTipo(trozos[1]);
        std::time_t fechaInicio = parsearFecha(trozos[3]), 
                    fechaFin = parsearFecha(trozos[4]);
        int precio = std::stoi(trozos[5]), 
            aforo = std::stoi(trozos[6]), 
            duracion = std::stoi(trozos[7]); 
        return Evento(nombre, tipo, descripcion, fechaInicio, fechaFin, precio, aforo, duracion);
    };

    std::string toFile(){
        std::string strPrecio = std::to_string(this->precio),
                    strAforo = std::to_string(this->aforo),
                    strDuracion = std::to_string(this->duracion),
                    strFechaInicio = std::ctime(&this->fechaInicio),
                    strFechaFin = std::ctime(&this->fechaFin),
                    strTipo = this->getTipoLikeString();
        std::vector<std::string> atributos = {nombre, strTipo, descripcion, strFechaInicio, strFechaFin, strPrecio, strAforo, strDuracion};
        std::string res = atributos[0];
        for (size_t i = 1; i < atributos.size(); i++)
        {
            res += ";" + atributos[i];
        }
        return res;
    }

    std::string toString()
    {
        std::string strPrecio = std::to_string(this->precio);
        std::string strAforo = std::to_string(this->aforo);
        std::string strDuracion = std::to_string(this->duracion);
        std::string strFechaInicio = std::ctime(&this->fechaInicio);
        std::string strFechaFin = std::ctime(&this->fechaFin);
        std::string strTipo = this->getTipoLikeString();

        return "Nombre: " + this->nombre + "\n" +
               "Tipo: " + strTipo + "\n" +
               "Descripcion: " + this->descripcion + "\n" +
               "Precio: " + strPrecio + "\n" +
               "Aforo: " + strAforo + "\n" +
               "Fecha inicio: " + strFechaInicio +
               "Fecha fin: " + strFechaFin +
               "Duracion: " + strDuracion + "\n\n";
    };

    bool equals(Evento other)
    {
        return this->nombre == other.nombre &&
               this->tipo == other.tipo &&
               this->descripcion == other.descripcion &&
               this->precio == other.precio &&
               this->aforo == other.aforo &&
               this->fechaInicio == other.fechaInicio &&
               this->fechaFin == other.fechaFin &&
               this->duracion == other.duracion;
    }
};
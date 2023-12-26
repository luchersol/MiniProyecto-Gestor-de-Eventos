#include <string>

class Inscripcion
{
private:
    std::string usuario, nombreEvento;
public:
    Inscripcion(std::string &usuario, std::string &nombreEvento){
        this->usuario = usuario;
        this->nombreEvento = nombreEvento;
    }

    std::string getUsuario(){
        return this->usuario;
    }

    std::string getNombreEvento(){
        return this->nombreEvento;
    }

    std::string toString(){
        return this->usuario + "-->" + this->nombreEvento;
    }
};
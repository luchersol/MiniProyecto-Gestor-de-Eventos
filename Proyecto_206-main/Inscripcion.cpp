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

    static Inscripcion parsear(std::vector<std::string> &trozos){
        std::string usuario = trozos[0], 
                    nombreEvento = trozos[1];
        return Inscripcion(usuario, nombreEvento);
    };

    std::string toFile(){
        std::vector<std::string> atributos = {usuario, nombreEvento};
        std::string res = atributos[0];
        for (size_t i = 1; i < atributos.size(); i++)
        {
            res += ";" + atributos[i];
        }
        return res;
    }

    std::string toString(){
        return this->usuario + "-->" + this->nombreEvento;
    }

    bool equals(Inscripcion other){
        return this->usuario == other.usuario && this->nombreEvento == other.nombreEvento;
    }
};
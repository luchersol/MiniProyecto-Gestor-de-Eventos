#include <string>

class Registro
{
private:
    std::string usuario, contrasena;
public:
    Registro(std::string usuario, std::string contrasena)
    {
        this->usuario = usuario;
        this->contrasena = contrasena;
    }

    std::string getUsuario(){
        return this->usuario;
    }

    std::string getContrasena(){
        return this->contrasena;
    }

    static Registro parsear(std::vector<std::string> &trozos){
        std::string usuario = trozos[0], 
                    contrasena = trozos[1];
        return Registro(usuario, contrasena);
    };

    std::string toFile(){
        std::vector<std::string> atributos = {usuario, contrasena};
        std::string res = atributos[0];
        for (size_t i = 1; i < atributos.size(); i++)
        {
            res += ";" + atributos[i];
        }
        return res;
    }

    std::string toString(){
        return this->usuario + " " + this->contrasena;
    }

    bool equals(Registro other){
        return this->usuario == other.usuario && this->contrasena == other.contrasena;
    }
};
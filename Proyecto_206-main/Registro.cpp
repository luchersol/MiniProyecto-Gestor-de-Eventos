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

    std::string toString(){
        return this->usuario + " " + this->contrasena;
    }
};
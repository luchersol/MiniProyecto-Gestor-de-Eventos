#include "IniciarSesion.cpp"

class Menu
{
public:
    Registros registros;
    Eventos eventos;
    Inscripciones inscripciones;
    std::string usuarioActual;
public:
    Menu()
    {
        this->registros = Registros();
        this->eventos = Eventos();
        this->inscripciones = Inscripciones();
        this->usuarioActual = "";
    };

    void show()
    {
        bool cond = true;
        while (cond)
        {
            int opcion;
            this->opcionesMenuPrincipal(opcion);
            switch (opcion)
            {
            case 1:
                this->eventos.listarEventos();
                break;
            case 2:
                this->menuSesion();
                break;
            case 3:
                this->cerrarSesion(cond);
                break;
            default:
                this->opcionNoValida();
                break;
            }
            // system("cls");
        }
    };

    void menuSesion()
    {
        bool cond = true;
        while (cond)
        {
            int opcion;
            this->opcionesMenuSesion(opcion);
            std::string usuario, contrasena;
            switch (opcion)
            {
            case 1:
                this->iniciarSesion();
                break;
            case 2:
                this->registros.registrarUsuario();
                break;
            case 3:
                this->cerrarSesion(cond);
                break;
            default:
                this->opcionNoValida();
                break;
            }
        }
    };

    void iniciarSesion()
    {
        bool cont = true;

        while (cont)
        {
            std::cout << "----------- INICIO SESION -----------" << std::endl;
            std::cout << "Ingrese correo de la UCO: ";
            std::string correo;
            std::cin >> correo;
            switch (IniciarSesion::comprobarCorreo(registros, correo))
            {
            case IniciarSesion::ADMINISTRADOR:
                this->usuarioActual = correo.substr(0, correo.find('@'));
                menuAdministrador();
                break;
            case IniciarSesion::USUARIO:
                this->usuarioActual = correo.substr(0, correo.find('@'));
                menuUsuario();
                break;
            case IniciarSesion::ERROR:
                std::cerr << "Correo no valido." << std::endl;
                cont = false;
                break;
            };
        }
    };

    void menuUsuario()
    {
        bool cond = true;
        while (cond)
        {
            int opcion;
            this->opcionesMenuUsuario(opcion);
            switch (opcion)
            {
            case 1:
                this->eventos.listarEventos();
                break;
            case 2:
                this->inscripciones.inscribirUsuario(this->usuarioActual, this->eventos);
                break;
            case 3:
                this->cerrarSesion(cond);
                break;
            default:
                this->opcionNoValida();
                break;
            }
        }
    };

    void menuAdministrador()
    {
        bool cond = true;
        while (cond)
        {
            int opcion;
            opcionesMenuAdministrador(opcion);
            switch (opcion)
            {
            case 1:
                this->eventos.listarEventos();
                break;
            case 2:
                this->eventos.crearEvento();
                break;
            case 3:
                this->eventos.eliminarEvento();
                break;
            case 4:
                this->eventos.modificarEvento();
                break;
            case 5:
                this->cerrarSesion(cond);
                break;
            default:
                this->opcionNoValida();
                break;
            }
        }
    };

private:
    void cerrarSesion(bool &cond){
        cond = false;
        this->usuarioActual = "";
    }
    void crearMenuOpciones(std::string &titulo, std::vector<std::string> &opciones, int &option)
    {
        std::cout << "-------------------------------------------" << std::endl;
        std::string space = "        ";
        std::cout << space + titulo + space << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (size_t i = 0; i < opciones.size(); i++)
        {
            std::cout << std::to_string(i + 1) + "- " + opciones[i] << std::endl;
        }
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> option;
    };

    void opcionesMenuPrincipal(int &option)
    {
        std::string titulo = "MENU PRINCIPAL";
        std::vector<std::string> opciones = {"Visitante", "Usuario", "Salir"};
        crearMenuOpciones(titulo, opciones, option);
    };

    void opcionesMenuSesion(int &option)
    {
        std::string titulo = "MENU DE SESION";
        std::vector<std::string> opciones = {"Iniciar sesion", "Registrarse", "Volver atras"};
        crearMenuOpciones(titulo, opciones, option);
    };

    void opcionesMenuAdministrador(int &option)
    {
        std::string titulo = "MENU ADMINISTRADOR";
        std::vector<std::string> opciones = {"Listar eventos", "Crear evento", "Eliminar evento", "Modificar evento", "Cerrar sesion"};
        crearMenuOpciones(titulo, opciones, option);
    };

    void opcionesMenuUsuario(int &option)
    {
        std::string titulo = "MENU DE USUARIO";
        std::vector<std::string> opciones = {"Listar eventos", "Inscribirse a evento", "Cerrar sesion"};
        crearMenuOpciones(titulo, opciones, option);
    };

    void opcionNoValida(){
        std::cerr << "Opcion no valida." << std::endl;
    }
};
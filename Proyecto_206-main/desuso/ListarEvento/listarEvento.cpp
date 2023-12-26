#include "../funciones.h"

//lee el fichero de eventos y los imprime por pantalla
void listarEvento() {
    std::ifstream archivo("eventos.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de registro." << std::endl;
        exit(1);
    }

    std::string linea; 
    while(getline(archivo, linea)) {
        std:: string nombre, tipo, descripcion, precio, aforo, fechaInicio, fechaFin, duracion; 
        std::stringstream stream(linea); //convertir string a stream

        //Extraemos los datos
        getline(stream, nombre);
        getline(stream, tipo);
        getline(stream, descripcion);
        getline(stream, precio);
        getline(stream, aforo);
        getline(stream, fechaInicio);
        getline(stream, fechaFin);
        getline(stream, duracion);
        getline(stream, linea);

        //imprimimos
        std::cout << nombre; 
        std::cout << tipo; 
        std::cout << descripcion; 
        std::cout << precio; 
        std::cout << aforo; 
        std::cout << fechaInicio; 
        std::cout << fechaFin; 
        std::cout << duracion; 
        std::cout << std::endl;

    }

    archivo.close();
}

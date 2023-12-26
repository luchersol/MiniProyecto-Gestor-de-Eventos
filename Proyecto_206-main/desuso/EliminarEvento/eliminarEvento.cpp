#include "../funciones.h"

//buscar evento por el nombre para luego eliminarlo
void eliminarEvento(std::string& nombre) {
    std::ifstream archivo("eventos.txt");
    std::ofstream aux("auxiliar.txt", std::ios::app); //añadir al final del fichero 

    if (!archivo.is_open() || !aux.is_open()) {
        std::cerr << "Error al abrir el archivo auxiliar." << std::endl;
        exit(0);
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Nombre: " + nombre) != std::string::npos) { //busca hasta encontrar el nombre
            // Saltar las líneas del evento que queremos borrar
            for (int i = 0; i < 8; ++i) { 
                getline(archivo, linea);
            }
        }
        else {
            aux << linea << std::endl; //guardar resto de lineas
        }
    }

    std::cout << "El evento ha sido eliminado. " << std::endl; 
    
    archivo.close();
    aux.close();
    std::remove("eventos.txt"); //eliminar antiguo fichero
    std::rename("auxiliar.txt", "eventos.txt"); //renombrar nuevo fichero
}
#include "../funciones.h"

using namespace std;

//dentro de inscribirse a un evento están los eventos que cuestan algo y los que no
void preinscribirEvento(string usuario, string nombreEvento) {
    int aforo = obtenerAforo(nombreEvento);
    inscripcion(usuario, nombreEvento, aforo);
}

//funcion de inscripcion
bool inscripcion(string usuario, string nombreEvento, int aforo) {
    ofstream archivo("inscripciones.txt", ios::app);  

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de inscripciones." << endl;
        return false;
    }

    if(comprobarInscripcion(usuario, nombreEvento)) {
        cout << "La persona ya esta inscrita" << endl; 
        return false; 
    }

    int contador = contarAforoInscritos(nombreEvento); 
    
    if(contador < aforo ) {
        archivo << usuario << "-->" << nombreEvento << endl;
        cout << "Inscripcion exitosa." << endl; 
    }
    else {
        cout << "El aforo esta completo. " << endl; 
    }

    archivo.close();
}

bool comprobarInscripcion(string usuario, string nombreEvento) {
    ifstream archivo("inscripciones.txt");  

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de registro." << endl;
        return false;
    }

    string linea; 
    string inscrip = usuario + "-->" + nombreEvento;

    while (getline(archivo, linea)) {
        if (linea == inscrip) {
            archivo.close();
            return true; // Evento encontrado
        }
    }

    archivo.close();
    return false; 
}


int obtenerAforo(string nombreEvento) {
    ifstream archivo("eventos.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de registro." << endl;
        return -1;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Nombre: " + nombreEvento) != string::npos) {
            while (getline(archivo, linea)) {
                if (linea.find("Aforo: ") != string::npos) { //distinto de invalido o no encontrado
                    stringstream stream(linea);
                    string etiqueta;
                    int aforo;

                    
                    stream >> etiqueta >> aforo;

                    archivo.close();
                    return aforo;
                }
            }
        }
    }
}

int contarAforoInscritos (string nombreEvento) { 
    ifstream archivo("inscripciones.txt");  

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de registro." << endl;
        return -1;
    }

    string linea;
    int aforo=0;

    while (getline(archivo, linea)) {
        if (linea.find("-->" + nombreEvento) != string::npos) 
            aforo++;
    }

    archivo.close();
    return aforo; 
}
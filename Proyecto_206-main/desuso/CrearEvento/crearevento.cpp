#include "../funciones.h"

using namespace std;



//esta funcion nos permite crear un evento
void crearEvento() {
    string nombre, tipo, descripcion, fechaInicio, fechaFin; 
    int precio, aforo, duracion; 

    introducirNombre(nombre); //como eran funciones muy largas se ha creado una función especifica para el nombre
    introducirTipoEvento(tipo); //función que además de dar valor al tipo de evento también comprueba si el tipo es correcto

    cout << "Introduzce una descripcion del evento." << endl; 

    cin.ignore();//limpiar buffer

    while (true) { //la descripcion tiene espacios, asi se leen todos 
    
        string linea;
        getline(cin, linea); 
                
        if (linea.empty()) { //cuando haya un enter en la linea vacia se saldrá 
            break;
        }

        descripcion += linea + " "; 
    }
 
    cout << "Introduzca precio del evento." << endl; 
    cin >> precio;

    cout << "Introduzca aforo del evento." << endl; 
    cin >> aforo;

    introducirFechas(fechaInicio, fechaFin); 

    cout << "Introduzca duracion del evento(en minutos)." <<  endl; 
    cin >> duracion;

    if(guardarEvento(nombre, tipo, descripcion, precio, aforo, fechaInicio, fechaFin, duracion)) 
        cout << "Guardado evento con exito." << endl; 
    
}

//sirve para que el usuario pueda nombrar a la actividad
void introducirNombre(string& nombre) {

    while(true) {
        cout << "Introduzca el nombre del evento (pulsa -enter- en una linea vacia para fianlizar)." << endl; 
        
        cin >> nombre; 

        if(comprobarEvento(nombre)) { //una vez añadido el nombre se comprueba si no existe ya
            cout << "El nombre del evento ya existe. Introduce otro." << endl; 
        }
        else { //si todo está bien se sale
            break;
        }
    }
}

//función que comprueba en el fichero si existe un evento con ese nombre
bool comprobarEvento(string& nombre) {
    ifstream archivo("eventos.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de eventos." << endl;
        return false;
    }

    string linea; 
    string nombreEvento = "Nombre: " + nombre;

    while (getline(archivo, linea)) {
        if (linea == nombreEvento) {
            archivo.close();
            return true; // Evento encontrado
        }
    }
    
    archivo.close();
    return false; //si no se ha encontrado
}

void introducirTipoEvento(string& tipo) {
    while(true) {
        cout << "Introduzca el tipo de evento (congreso, ponencia, taller, seminario)." << endl; 
        cin >> tipo;

        if (comprobarTipoEvento(tipo)) { //si el tipo de evento no es ninguno de los cuatro lo vuelve a pedir
            break; //si el tipo de evento es correcto se sale
        }
        else {
            cout << "No es congreso, ni ponencia, ni taller, ni seminario. Intentalo de nuevo." << endl; //si no es correcto se vuelve a pedir
        }
    }
}


//se comprueba si es taller, seminario, congreso o ponencia
bool comprobarTipoEvento(string& tipo) {
    for (int i=0; i < tipo.length(); i++) {
        tipo[i] = tolower(tipo[i]);
    }

    return (tipo=="taller" || tipo=="seminario" || tipo=="congreso" || tipo=="ponencia"); //devolver "true" si está correcto
}

//asignar los valores a las fechas
void introducirFechas(string& fechaInicio, string& fechaFin) {
    while(true) {
        cout << "Introduzca fecha de inicio (AAAA-MM-DD)." << endl; 
        cin >> fechaInicio;

        cout << "Introduzca fecha de fin (AAAA-MM-DD)." << endl; 
        cin >> fechaFin;

        if (comprobarFechas(fechaInicio, fechaFin)){
            break; 
        }
        else {
            cout << "Intentalo otra vez." << endl; 
        }
    }
}

//comprobar que la fecha de inicio sea antes que la fecha de fin
bool comprobarFechas (string& fechaInicio, string& fechaFin) {
    tm tmInicio = {}; 
    tm tmFin = {}; 

    // Convierte la fecha de inicio de string a tm
    istringstream ssInicio(fechaInicio); //se utiliza istringstream para convertir la cadena de fechaInicio a una estructura tm
    ssInicio >> get_time(&tmInicio, "%Y-%m-%d"); //se usa get_time para interpretar la cadena con el formato que tiene

    // Convierte la fecha de fin de string a tm
    istringstream ssFin(fechaFin); 
    ssFin >> get_time(&tmFin, "%Y-%m-%d");

    if (mktime(&tmFin) >= mktime(&tmInicio)) { //mktime convierte estructura tm a time_t 
        return true; 
    } else {
        cout << "La fecha de fin es anterior a la fecha de inicio." << endl;
        return false;
    }
}

//por ultimo se guarda todo en el fichero
bool guardarEvento(string& nombre, string& tipo, string& descripcion, int precio, int aforo, string& fechaInicio, string& fechaFin, int duracion) {
    ofstream archivo("eventos.txt", ios::app); //añadir al final del fichero 

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de eventos." << endl;
        return false;
    }

    archivo << "Nombre: " << nombre << endl; 
    archivo << "Tipo: " << tipo << endl; 
    archivo << "Descripcion: " << descripcion << endl; 
    archivo << "Precio: " << precio << endl;
    archivo << "Aforo: " << aforo << endl;  
    archivo << "Fecha inicio: " << fechaInicio << endl; 
    archivo << "Fecha fin: " << fechaFin << endl; 
    archivo << "Duracion: " << duracion << endl; 
    archivo << endl; 

    return true; 

    archivo.close();
}
#include "SNData.h"

vector<SocialNetworkData> SNData::sns; // Se inicializa el vector de SocialNetworkData ya que es un miembro estatico

void SNData::newSocialNetwork(string name, double avgR, double avgM){ // Metodo newSocialNetwork para agregar una nueva red social
    SocialNetworkData sN; // Se crea un objeto de tipo SocialNetworkData
    for(int i = 0; i < (int)sns.size(); i++){ // Se recorre el vector de redes sociales
        if(sns[i].name == name){throw invalid_argument(name);}} // Si el nombre de la red social ya existe, se lanza una excepcion
    if(avgR <= 0 || avgR >= 1){throw invalid_argument(to_string(avgR));} // Si el promedio de rating es menor o igual a 0 o mayor o igual a 1, se lanza una excepcion
    if(avgM <= 0 || avgM >= 1){throw invalid_argument(to_string(avgM));}// Si el promedio de monetizacion es menor o igual a 0 o mayor o igual a 1, se lanza una excepcion
    sN.name = name; // Se asigna el nombre de la red social
    sN.averageRating = avgR; // Se asigna el promedio de rating
    sN.averageMonetizing = avgM; // Se asigna el promedio de monetizacion
    sns.push_back(sN); // Se agrega la red social al vector
}

bool SNData::checkSN(string name){ // Metodo checkSN para verificar si existe una red social
    for(int i = 0; i < (int)sns.size(); i++){ // Se recorre el vector de redes sociales
        if(sns[i].name == name){return true;}} // Si el nombre de la red social existe, se devuelve true
    return false; // Si no, se devuelve false
}

double SNData::getAvgRating(string name){ // Metodo getAvgRating para obtener el promedio de rating de una red social
    for(int i = 0; i < (int)sns.size(); i++){ // Se recorre el vector de redes sociales 
        if(sns[i].name == name){return sns[i].averageRating;}} // Si el nombre de la red social existe, se devuelve el promedio de rating
    return 0.0; // Si no, se devuelve 0
}

double SNData::getAvgMonetizing(string name){ // Metodo getAvgMonetizing para obtener el promedio de monetizacion de una red social 
    for(int i = 0; i < (int)sns.size(); i++){ // Se recorre el vector de redes sociales
        if(sns[i].name == name){return sns[i].averageMonetizing;}} // Si el nombre de la red social existe, se devuelve el promedio de monetizacion
    return 0.0; // Si no, se devuelve 0
}

void SNData::readFromCSV(string filename){ // Metodo readFromCSV para leer los datos de las redes sociales de un archivo
    string line; // Se declara un string para guardar la linea del archivo
    int lineNumber = 0; // Se declara una variable de tipo int para guardar el numero de linea

    ifstream file; // Se crea un objeto de tipo ifstream
    file.open(filename); // Se abre el archivo
    if(!file.is_open()){Util::error(ERR_FILE);} // Si no se pudo abrir el archivo, se lanza una excepcion

    while(getline(file, line)){ // Mientras se pueda leer una linea del archivo
        lineNumber++; // Se aumenta el numero de linea
        if(line == ""){continue;} // Si la linea esta vacia, se continua con la siguiente lijea directamente sin realizar las siguientes acciones
        int pos1 = line.find(':'); // Se busca el primer caracter ':'
        int pos2 = line.find(':', pos1 + 1); // Se busca el segundo caracter ':' a partir de la posicion del primer caracter ':'
        if(pos1 == -1 || pos2 == -1){cout << "Error line " << lineNumber << endl; continue;} // Si no se encuentran los dos caracteres ':', se imprime un mensaje de error y se continua con la siguiente linea
        string name = line.substr(0, pos1); // Se obtiene el nombre de la red social
        string avgR = line.substr(pos1 + 1, pos2 - pos1 - 1); // Se obtiene el promedio de rating
        string avgM = line.substr(pos2 + 1); // Se obtiene el promedio de monetizacion
        try{
            newSocialNetwork(name, stod(avgR), stod(avgM)); // Se intenta agregar la red social
        }catch(invalid_argument &e){
            cout << "Error line " << endl; // Si hay un error, se imprime un mensaje de error
        }
    }
    file.close(); // Se cierra el archivo
}

void SNData::writeToCSV(string filename){ // Metodo writeToCSV para escribir los datos de las redes sociales en un archivo 
    ofstream file; // Se crea un objeto de tipo ofstream
    file.open(filename); // Se abre el archivo
    if(!file.is_open()){Util::error(ERR_FILE);} // Si no se pudo abrir el archivo, se lanza una excepcion
    for(int i = 0; i < (int)sns.size(); i++){ // Se recorre el vector de redes sociales
        file << sns[i].name << ":" << sns[i].averageRating << ":" << sns[i].averageMonetizing << endl; // Se escribe el nombre, el promedio de rating y el promedio de monetizacion en el archivo
    }
    file.close(); // Se cierra el archivo
}


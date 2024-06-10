#ifndef _SNDATA_H_
#define _SNDATA_H_
#include <iostream>
#include <vector>
#include <fstream>
#include "Util.h" 

using namespace std;

struct SocialNetworkData{ // La estructura SocialNetworkData de la practica
    string name; 
    double averageRating;
    double averageMonetizing; 
};

class SNData{ // La clase SNData de la practica
    private:
        static vector<SocialNetworkData> sns; // Se declara un vector de SocialNetworkData para guardar los datos de las redes sociales
    public:
        static void newSocialNetwork(string name, double avgR, double avgM); // Se declara el metodo newSocialNetwork para agregar una nueva red social
        static bool checkSN(string name); // Se declara el metodo checkSN para verificar si existe una red social
        static double getAvgRating(string name); // Se declara el metodo getAvgRating para obtener el promedio de rating de una red social
        static double getAvgMonetizing(string name); // Se declara el metodo getAvgMonetizing para obtener el promedio de monetizacion de una red social
        static int getNumSNs(){return sns.size();}; // Se declara el metodo getNumSNs para obtener el numero de redes sociales
        static unsigned int getSocialNetworkNumber() {return sns.size();} // Se declara el metodo getSocialNetworkNumber para obtener el numero de redes sociales
        static void readFromCSV(string filename); // Se declara el metodo readFromCSV para leer los datos de las redes sociales de un archivo
        static void writeToCSV(string filename); // Se declara el metodo writeToCSV para escribir los datos de las redes sociales en un archivo
};

#endif


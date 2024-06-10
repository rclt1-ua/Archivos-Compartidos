#ifndef _AGENCY_H
#define _AGENCY_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Util.h"
#include "Influencer.h"
#include "SNFollowers.h"

using namespace std;

struct BinAgency{ // La estructura BinAgency de la practica
    char name[KMAXNAME];
    double money;
    int numInfluencers;
};

class Agency{
    friend ostream& operator<<(ostream& os, const Agency& agency); // Se declara la sobrecarga del operador << como friend, para poder usar esta clase con un cout
    
    private:
        string name; // Se declara un string para guardar el nombre de la agencia
        double money; // Se declara un double para guardar el dinero de la agencia
        vector<Influencer> influencers; // Se declara un vector de Influencer para guardar los influencers
    
    public:
        Agency(string name, double initialMoney); // Se declara el constructor de la clase Agency
        Agency(string file); // Se declara el constructor de la clase Agency con un parametro de tipo string, se usa en el momento de leer los datos de un archivo
        Influencer *searchInfluencer(string infName); // Se declara el metodo searchInfluencer para buscar un influencer
        void addInfluencer(string infName, double commission); // Se declara el metodo addInfluencer para agregar un influencer
        void addFollowers(string infName, string snName, int nFollowers); // Se declara el metodo addFollowers para agregar seguidores al influencer
        void newEvent(vector<string> infNames, int nsns, string snNames[], double evtRatings[]); // Se declara el metodo newEvent para agregar un evento al influencer
        void deleteInfluencer(string infName); // Se declara el metodo deleteInfluencer para eliminar un influencer
        double collectCommissions(); // Se declara el metodo collectCommissions para recolectar la comision de los influencers
        string getName() const {return name;} // Se declara el metodo getName para obtener el nombre de la agencia
        double getMoney() const {return money;} // Se declara el metodo getMoney para obtener el dinero de la agencia
        unsigned int getNumberInfluencers() const {return influencers.size();} // Se declara el metodo getNumberInfluencers para obtener el numero de influencers
        BinAgency toBinAgency() const; // Se declara el metodo toBinAgency para convertir los datos de la agencia en un BinAgency para guardar en un archivo
        void saveData(string filename) const; // Se declara el metodo saveData para guardar los datos de la agencia en un archivo
};

#endif

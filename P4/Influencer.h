// NOMBRE: ARIEL NUÑEZ
#ifndef _INFLUENCER_H
#define _INFLUENCER_H
#include <iostream>
#include <vector>
#include "SNFollowers.h" // Se debe incluir el archivo SNFollowers.h
#include "Util.h" // Se debe incluir el archivo Util.h

using namespace std;

struct BinInfluencer{ // La estructura BinInfluencer de la practica
    char name[KMAXNAME];
    double commission;
    int numFollowers;
};

class Influencer{
    friend ostream & operator<<(ostream &os, const Influencer &influencer); // Se declara la sobrecarga del operador << como friend, para poder usar esta clase con un cout
    private:
        vector<SNFollowers> followers; // Se declara un vector de SNFollowers para guardar los seguidores
        string name; // Se declara un string para guardar el nombre del influencer
        double commission; // Se declara un double para guardar la comision del influencer
    public:
        Influencer(string name); // Se declara el constructor de la clase Influencer
        Influencer(const BinInfluencer &bI); // Se declara el constructor de la clase Influencer con un parametro de tipo BinInfluencer, se usa en el momento de leer los datos de un archivo
        void setCommission(double commission); // Se declara el metodo setCommission para asignar la comision del influencer
        void addFollowers(string snName, int nFollowers); // Se declara el metodo addFollowers para agregar seguidores al influencer
        void addFollowers(const SNFollowers &follower); // Se declara el metodo addFollowers para agregar seguidores al influencer
        void addEvent(int nsns, string sn[], double rat[]); // Se declara el metodo addEvent para agregar eventos al influencer
        double collectCommission(); // Se declara el metodo collectCommission para recolectar la comision del influencer 
        string getName() const {return name;} // Se declara el metodo getName para obtener el nombre del influencer
        vector<SNFollowers> getFollowers() const {return followers;} // Se declara el metodo getFollowers para obtener los seguidores del influencer
        double getCommission() const {return commission;} // Se declara el metodo getCommission para obtener la comision del influencer
        BinInfluencer toBinInfluencer() const; // Se declara el metodo toBinInfluencer para convertir los datos del influencer en un BinInfluencer para guardar en un archivo
};

#endif


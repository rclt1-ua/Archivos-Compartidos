#ifndef _SNFOLLOWERS_H_ 
#define _SNFOLLOWERS_H_
#include <iostream> 
#include <vector>
#include "Util.h"

using namespace std;

struct BinSNFollowers{ // La estructura BinSNFollowers de la practica
    char name[KMAXNAME];
    int numFollowers;
    double money;
};

class SNFollowers{ // La clase SNFollowers de la practica
    friend ostream& operator<<(ostream& os, const SNFollowers& snf); // Se declara la sobrecarga del operador << como friend, para poder usar esta clase con un cout
    private:
        string name; // Se declara un string para guardar el nombre del influencer
        int numFollowers; // Se declara un int para guardar el numero de seguidores
        double money; // Se declara un double para guardar el dinero del influencer
    public:
        SNFollowers(string name, int initialFollowers); // Se declara el constructor de la clase SNFollowers
        SNFollowers(const BinSNFollowers &bSNF); // Se declara el constructor de la clase SNFollowers con un parametro de tipo BinSNFollowers, se usa en el momento de leer los datos de un archivo
        void addFollowers(int nf); // Se declara el metodo addFollowers para agregar seguidores al influencer
        void addEvent(double rating); // Se declara el metodo addEvent para agregar eventos al influencer
        double collectCommission(double commission); // Se declara el metodo collectCommission para recolectar la comision del influencer
        string getName() const {return name;} // Se declara el metodo getName para obtener el nombre del influencer
        int getNumFollowers() const {return numFollowers;} // Se declara el metodo getNumFollowers para obtener el numero de seguidores del influencer
        double getMoney() const {return money;} // Se declara el metodo getMoney para obtener el dinero del influencer
        BinSNFollowers toBinSNFollowers() const; // Se declara el metodo toBinSNFollowers para convertir los datos del influencer en un BinSNFollowers para guardar en un archivo
};

#endif

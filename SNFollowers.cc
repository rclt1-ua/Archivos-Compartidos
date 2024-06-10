#include "SNFollowers.h"
#include "SNData.h"

SNFollowers::SNFollowers(string name, int initialFollowers){ // Constructor de la clase SNFollowers
    SNData sn; // Se crea un objeto de tipo SNData
    if(!sn.checkSN(name)){throw EXCEPTION_UNKNOWN_SN;} // Si no se encuentra el nombre de la red social, se lanza una excepcion
    if(initialFollowers < 0){throw invalid_argument(to_string(initialFollowers));} // Si el numero de seguidores es menor a 0, se lanza una excepcion
    this->name = name; // Se asigna el nombre del influencer
    numFollowers = initialFollowers; // Se asigna el numero de seguidores
    money = 0.0; // Se asigna el dinero que inicialmente es 0
}   

SNFollowers::SNFollowers(const BinSNFollowers &bSNF){ // Constructor de la clase SNFollowers con un parametro de tipo BinSNFollowers
    this->name = bSNF.name; // Se asigna el nombre del influencer
    this->numFollowers = bSNF.numFollowers; // Se asigna el numero de seguidores
    this->money = bSNF.money; // Se asigna el dinero
}

void SNFollowers::addFollowers(int nf){ // Metodo addFollowers para agregar seguidores al influencer
    numFollowers += nf; // Se suman los seguidores
    if(numFollowers < 0){numFollowers = 0;} // Si el numero de seguidores es menor a 0, se asigna 0
}

void SNFollowers::addEvent(double rating){ // Metodo addEvent para agregar eventos al influencer
    SNData sn; // Se crea un objeto de tipo SNData
    double avgRating = sn.getAvgRating(name), // Se obtiene el promedio de rating
        avgMonetizing = sn.getAvgMonetizing(name), // Se obtiene el promedio de monetizacion
        relation = rating / avgRating; // Se obtiene la relacion entre el rating y el promedio de rating
    int newFollowers = 0, // Se declara una variable de tipo int para guardar los nuevos seguidores
        lostFollowers = 0; // Se declara una variable de tipo int para guardar los seguidores perdidos

    if(rating < 0){throw invalid_argument(to_string(rating));} // Si el rating es menor a 0, se lanza una excepcion

    if(relation > 0.8){ // Si la relacion es mayor a 0.8
        newFollowers = relation * numFollowers; // Se calculan los nuevos seguidores
        numFollowers += newFollowers; // Se suman los nuevos seguidores
        money += newFollowers * avgMonetizing; // Se suma el dinero
    }
    else{ // Si la relacion es menor a 0.8
        lostFollowers = (0.9 - relation) * numFollowers; // Se calculan los seguidores perdidos
        numFollowers -= lostFollowers; // Se restan los seguidores perdidos
        if(numFollowers < 0){numFollowers = 0;} // Si el numero de seguidores es menor a 0, se asigna 0
    }
}

double SNFollowers::collectCommission(double commission){ // Metodo collectCommission para recolectar la comision del influencer
    double comissionMoney = 0; // Se declara una variable de tipo double para guardar la comision
    if(commission <= 0 || commission >= 1){throw invalid_argument(to_string(commission));} // Si la comision es menor o igual a 0 o mayor o igual a 1, se lanza una excepcion
    comissionMoney = money * commission; // Se calcula la comision
    money = 0.0; // Se asigna 0 al dinero por que ya se recolecto la comision
    return comissionMoney; // Se devuelve la comision
}

BinSNFollowers SNFollowers::toBinSNFollowers() const{ // Metodo toBinSNFollowers para convertir los datos del influencer en un BinSNFollowers para guardar en un archivo
    BinSNFollowers bSNF; // Se crea un objeto de tipo BinSNFollowers
    for(int i = 0; i < KMAXNAME; i++){ // Se recorre el nombre del influencer para hacer que quepa en el tamaño de la estructura BinSNFollowers
        if(i < (int)name.size()){ // Si el indice es menor al tamaño del nombre
            bSNF.name[i] = name[i]; // Se asigna el caracter del nombre
        } 
        else{ // Si no
            bSNF.name[i] = '\0'; // Se asigna un caracter nulo, esto se hace para que el nombre tenga el tamaño de KMAXNAME
        }
    }
    bSNF.numFollowers = numFollowers; // Se asigna el numero de seguidores
    bSNF.money = money; // Se asigna el dinero
    return bSNF; // Se devuelve el objeto de tipo BinSNFollowers
}

ostream& operator<<(ostream& os, const SNFollowers& snf){ // Sobrecarga del operador << para poder imprimir un objeto de tipo SNFollowers
    os << "[" << snf.name << "|" << snf.numFollowers << "|" << snf.money << "]"; // Se imprime el nombre, el numero de seguidores y el dinero
    return os; // Se devuelve el objeto de tipo ostream
}
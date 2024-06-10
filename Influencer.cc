#include "Influencer.h" // Incluir el archivo de cabecera de la clase

Influencer::Influencer(string name){ // Constructor de la clase Influencer
    this->name = name; // Se asigna el nombre del influencer
    this->commission = 0.1; // Se asigna la comision del influencer 
}

Influencer::Influencer(const BinInfluencer &bI){ // Constructor de la clase Influencer con un parametro de tipo BinInfluencer
    this->name = bI.name; // Se asigna el nombre del influencer
    this->commission = bI.commission; // Se asigna la comision del influencer
}

void Influencer::setCommission(double commission){ // Metodo setCommission para asignar la comision del influencer
    if(commission > 0 && commission < 0.8){ // Si la comision es mayor a 0 y menor a 0.8
        this->commission = commission; // Se asigna la comision
    } else { // Si la comision no esta en el rango
        throw EXCEPTION_WRONG_COMMISSION; // Se lanza una excepcion
    }
}

void Influencer::addFollowers(string snName, int nFollowers){ // Metodo addFollowers para agregar seguidores al influencer
    for(int i = 0; i < (int)followers.size(); i++){ // Se recorre el vector de seguidores
        if(followers[i].getName() == snName){ // Si el nombre del seguidor es igual al nombre del seguidor que se quiere agregar
            followers[i].addFollowers(nFollowers); // Se agregan los seguidores
            return; // Se sale del metodo
        }
    }
    try{ // Si no se encontro el seguidor, se intenta agregar
        SNFollowers snf(snName, nFollowers); // Se crea un objeto de tipo SNFollowers
        followers.push_back(snf); // Se agrega el seguidor al vector de seguidores
    } catch(Exception &e){ // Si hay un error
        Util::error(ERR_UNKNOWN_SN); // Se imprime un mensaje de error
    }
}

void Influencer::addFollowers(const SNFollowers &follower){ // Metodo addFollowers para agregar seguidores al influencer
    followers.push_back(follower); // Se agrega el seguidor al vector de seguidores
}

void Influencer::addEvent(int nsns, string sn[], double rat[]){ // Metodo addEvent para agregar eventos al influencer
    for(int i = 0; i < nsns; i++){ // Se recorre el vector de eventos
        for(int j = 0; j < (int)followers.size(); j++){ // Se recorre el vector de seguidores
            if(followers[j].getName() == sn[i]){ // Si el nombre del seguidor es igual al nombre del seguidor que se quiere agregar
                followers[j].addEvent(rat[i]); // Se agrega el evento al seguidor
            }
        }
    }
}

double Influencer::collectCommission(){ // Metodo collectCommission para recolectar la comision del influencer
    double comision = 0; // Se declara una variable de tipo double para guardar la comision
    for(int i = 0; i < (int)followers.size(); i++){ // Se recorre el vector de seguidores
        comision += followers[i].collectCommission(commission); // Se recolecta la comision
    }
    return comision; // Se devuelve la comision
}

BinInfluencer Influencer::toBinInfluencer() const{ // Metodo toBinInfluencer para convertir los datos del influencer en un BinInfluencer para guardar en un archivo
    BinInfluencer bI; // Se crea un objeto de tipo BinInfluencer
    for(int i = 0; i < KMAXNAME; i++){ // Se recorre el nombre del influencer para hacer que quepa en el tamaño de la estructura BinInfluencer
        if(i < (int)name.size()){ // Si el indice es menor al tamaño del nombre
            bI.name[i] = name[i]; // Se asigna el caracter al nombre
        } else { // Si el indice es mayor al tamaño del nombre
            bI.name[i] = '\0'; // Se asigna un caracter nulo al nombre para terminar la cadena
        }
    }
    bI.commission = commission; // Se asigna la comision al BinInfluencer
    bI.numFollowers = (int)followers.size(); // Se asigna el tamaño del vector de seguidores al BinInfluencer
    return bI; // Se devuelve el BinInfluencer
}

ostream & operator<<(ostream& os, const Influencer &influencer){ // Sobrecarga del operador << para imprimir los datos del influencer
    os << "Influencer: " << influencer.name << " (" << influencer.commission << ")" << endl; // Se imprime el nombre y la comision del influencer
    for(int i = 0; i < (int)influencer.followers.size(); i++){ // Se recorre el vector de seguidores
        os << influencer.followers[i]; // Se imprime el seguidor
    }
    cout << endl; // Se imprime un salto de linea
    return os; // Se devuelve el flujo de salida
}
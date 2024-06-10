#include "Agency.h"

Agency::Agency(string name, double initialMoney) { // Constructor de la clase Agency
    this->name = name; // Se asigna el nombre de la agencia 
    this->money = initialMoney; // Se asigna el dinero de la agencia 
}

Agency::Agency(string filename) { // Constructor de la clase Agency con un parametro de tipo string, se usa en el momento de leer los datos de un archivo
    ifstream file; // Se crea un objeto de tipo ifstream
    BinAgency bA; // Se crea un objeto de tipo BinAgency
    BinInfluencer bI; // Se crea un objeto de tipo BinInfluencer
    BinSNFollowers bSNF; // Se crea un objeto de tipo BinSNFollowers
    file.open(filename, ios::binary); // Se abre el archivo en modo binario
    if (!file.is_open()) { // Si no se pudo abrir el archivo
        Util::error(ERR_FILE); // Se imprime un mensaje de error
        throw EXCEPTION_FILE; // Se lanza una excepcion
    }
    file.read((char *)&bA, sizeof(BinAgency)); // Se lee la estructura BinAgency
    name = bA.name; // Se asigna el nombre de la agencia
    money = bA.money; // Se asigna el dinero de la agencia
    for (int i = 0; i < bA.numInfluencers; i++) { // Se recorre el numero de influencers
        file.read((char *)&bI, sizeof(BinInfluencer)); // Se lee la estructura BinInfluencer
        Influencer inf(bI); // Se crea un objeto de tipo Influencer
        for (int j = 0; j < bI.numFollowers; j++) { // Se recorre el numero de seguidores
            file.read((char *)&bSNF, sizeof(BinSNFollowers)); // Se lee la estructura BinSNFollowers
            SNFollowers snf(bSNF); // Se crea un objeto de tipo SNFollowers
            inf.addFollowers(snf); // Se agrega el seguidor al influencer
        }
        influencers.push_back(inf); // Se agrega el influencer al vector de influencers
    }
    file.close(); // Se cierra el archivo
}

Influencer* Agency::searchInfluencer(string infName) { // Metodo searchInfluencer para buscar un influencer
    for (int i = 0; i < (int)influencers.size(); i++) { // Se recorre el vector de influencers
        if (influencers[i].getName() == infName) { // Si el nombre del influencer es igual al nombre del influencer que se quiere buscar
            return &influencers[i]; // Se devuelve el influencer
        }
    }
    throw EXCEPTION_INFL_NOT_FOUND; // Si no se encontro el influencer, se lanza una excepcion
}

void Agency::addInfluencer(string infName, double commission) { // Metodo addInfluencer para agregar un influencer
    try { // Se intenta buscar el influencer
        searchInfluencer(infName); // Se busca el influencer
        Util::error(ERR_DUPLICATED); // Si se encontro el influencer, se imprime un mensaje de error
    } catch (Exception &e) { // Si no se encontro el influencer
        try { // Se intenta agregar el influencer
            Influencer inf(infName); // Se crea un objeto de tipo Influencer 
            inf.setCommission(commission); // Se asigna la comision al influencer
            influencers.push_back(inf); // Se agrega el influencer al vector de influencers
        } catch (Exception &e) { // Si hay un error
            Util::error(ERR_WRONG_COMMISSION); // Se imprime un mensaje de error
        }
    }
}

void Agency::addFollowers(string infName, string snName, int nFollowers) { // Metodo addFollowers para agregar seguidores al influencer
    try { // Se intenta buscar el influencer
        Influencer *inf = searchInfluencer(infName); // Se busca el influencer
        inf->addFollowers(snName, nFollowers); // Se agregan los seguidores al influencer
    } catch (Exception &e) { // Si no se encontro el influencer
        Util::error(ERR_NOT_FOUND); // Se imprime un mensaje de error
    }
}

void Agency::newEvent(vector<string> infNames, int nsns, string snNames[], double evRats[]) { // Metodo newEvent para agregar un evento al influencer
    for (int i = 0; i < (int)infNames.size(); i++) { // Se recorre el vector de nombres de influencers
        try { // Se intenta buscar el influencer
            Influencer *inf = searchInfluencer(infNames[i]); // Se busca el influencer
            inf->addEvent(nsns, snNames, evRats); // Se agrega el evento al influencer
        } catch (Exception &e) { // Si no se encontro el influencer
            // Sin hacer nada
        }
    }
}

void Agency::deleteInfluencer(string infName) {
    try {
        Influencer *inf = searchInfluencer(infName); // Se busca el influencer
        money += inf->collectCommission(); // Se recolecta la comision del influencer
        for (int i = 0; i < (int)influencers.size(); i++) { // Se recorre el vector de influencers
            if (influencers[i].getName() == infName) { // Si el nombre del influencer es igual al nombre del influencer que se quiere eliminar
                influencers.erase(influencers.begin() + i); // Se elimina el influencer
                return; // Se sale del metodo
            }
        }
    } catch (Exception &e) { // Si no se encontro el influencer
        Util::error(ERR_NOT_FOUND); // Se imprime un mensaje de error
    }
}

double Agency::collectCommissions() { // Metodo collectCommissions para recolectar la comision de los influencers
    double comision = 0;
    for (int i = 0; i < (int)influencers.size(); i++) { // Se recorre el vector de influencers
        comision += influencers[i].collectCommission(); // Se recolecta la comision del influencer
    }
    money += comision; // Se suma la comision al dinero de la agencia
    return comision; // Se devuelve la comision
}

BinAgency Agency::toBinAgency() const { // Metodo toBinAgency para convertir los datos de la agencia en un BinAgency para guardar en un archivo
    BinAgency bA; // Se crea un objeto de tipo BinAgency
    for (int i = 0; i < KMAXNAME; i++) { // Se recorre el nombre de la agencia para hacer que quepa en el tamaño de la estructura BinAgency
        if (i < (int)name.size()) { // Si el indice es menor al tamaño del nombre
            bA.name[i] = name[i]; // Se asigna el caracter del nombre
        } else { // Si no
            bA.name[i] = '\0'; // Se asigna un caracter nulo, esto se hace para que el nombre tenga el tamaño de KMAXNAME
        }
    }
    bA.money = money; // Se asigna el dinero de la agencia
    bA.numInfluencers = (int)influencers.size(); // Se asigna el numero de influencers
    return bA; // Se devuelve el objeto de tipo BinAgency
}

void Agency::saveData(string filename) const { // Metodo saveData para guardar los datos de la agencia en un archivo
    ofstream file; // Se crea un objeto de tipo ofstream
    BinAgency bA = toBinAgency(); // Se crea un objeto de tipo BinAgency
    file.open(filename, ios::binary); // Se abre el archivo en modo binario
    if (!file.is_open()) { // Si no se pudo abrir el archivo
        Util::error(ERR_FILE); // Se imprime un mensaje de error
        throw EXCEPTION_FILE; // Se lanza una excepcion
    }
    file.write((char *)&bA, sizeof(BinAgency)); // Se escribe la estructura BinAgency
    for(int i = 0; i < (int)influencers.size(); i++) { // Se recorre el vector de influencers
        BinInfluencer bI = influencers[i].toBinInfluencer(); // Se crea un objeto de tipo BinInfluencer
        file.write((char *)&bI, sizeof(BinInfluencer)); // Se escribe la estructura BinInfluencer 
        for(int j = 0; j < (int)influencers[i].getFollowers().size(); j++) { // Se recorre el vector de seguidores
            BinSNFollowers bSNF = influencers[i].getFollowers()[j].toBinSNFollowers(); // Se crea un objeto de tipo BinSNFollowers
            file.write((char *)&bSNF, sizeof(BinSNFollowers)); // Se escribe la estructura BinSNFollowers
        }
    }
    file.close(); // Se cierra el archivo
}

ostream& operator<<(ostream &os, const Agency &agency) { // Sobrecarga del operador << para poder imprimir un objeto de tipo Agency
    os << "Agency: " << agency.name << " [" << agency.money << "]" << endl; // Se imprime el nombre de la agencia y el dinero
    for (int i = 0; i < (int)agency.influencers.size(); i++) { // Se recorre el vector de influencers
        os << agency.influencers[i]; // Se imprime el influencer
    }
    return os; // Se devuelve el objeto de tipo ostream
}


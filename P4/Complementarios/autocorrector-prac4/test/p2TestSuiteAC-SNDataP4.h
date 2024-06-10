#include <cxxtest/TestSuite.h>

#include <iostream>
#include <cstring>
using namespace std;

#include "SNData.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>
#include <vector>


using namespace std;


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

private:
			
   vector<SocialNetworkData> vaux;

   void newSocialNetworkAux(string name, double avgR, double avgM) {
		SocialNetworkData aux;
		aux.name=name;
		aux.averageRating=avgR;
		aux.averageMonetizing=avgM;
		vaux.push_back(aux);
	}

	/*const string DIRESPERADA= "test/salida-esperada";
 	const string DIROBTENIDA= "test/salida-obtenida";*/

 public:

  // Tests for SNData ----------------------------------------------------
  void testSNData() {
  
    // añadimos datos de redes sociales al vector auxiliar de SocialNetworkData
    newSocialNetworkAux("TokTik",0.8,0.1);
    newSocialNetworkAux("Infagram",0.6,0.05);
    newSocialNetworkAux("YZ",0.5,0.2);
    newSocialNetworkAux("JungleBook",0.1,0.1);

	 // METODOS P4 - Se comprueba que existen y se hace una prueba con readFromCSV
	 string finput = DIRINPUT+"/socialNetworks.cvs";
	 string foutput = DIROBTENIDA+"/socialNetworks.cvs";
	 SNData::readFromCSV(finput); 

	 TS_ASSERT_EQUALS(SNData::getSocialNetworkNumber(),vaux.size()); //Ambos vectores deben tener el mismo númeo de elementos
	 
    for (SocialNetworkData data : vaux) {	//Comparamos los elementos entre ambos vectores.
			TS_ASSERT_EQUALS(SNData::checkSN(data.name),true);
			TS_ASSERT_DELTA(SNData::getAvgRating(data.name),data.averageRating,0.01);
			TS_ASSERT_DELTA(SNData::getAvgMonetizing(data.name),data.averageMonetizing,0.01);
	 }
	 SNData::writeToCSV(foutput);  //Guarda las redes sociales pero no se comprueba que lo hace bien.
	 
	 //P3
    // checkSN
    TS_ASSERT_EQUALS(SNData::checkSN("Infagrama"),false);
    TS_ASSERT_EQUALS(SNData::checkSN("yz"),false);
    TS_ASSERT_EQUALS(SNData::checkSN("YZ"),true);
    
    // getAvgRating
    TS_ASSERT_DELTA(SNData::getAvgRating("TikTuk"),0.0, 0.01);
    TS_ASSERT_DELTA(SNData::getAvgRating("TokTik"),0.8, 0.01);

    // getAvgMonetizing
    TS_ASSERT_DELTA(SNData::getAvgMonetizing("XY"),0.0, 0.01);
    TS_ASSERT_DELTA(SNData::getAvgMonetizing("YZ"),0.2, 0.01);

    // están mal los 3 parámetros, pero debe lanzar la excepción porque el nombre se repite
    TS_ASSERT_THROWS_ASSERT(SNData::newSocialNetwork("TokTik",-7,-5), const std::exception &e, TS_ASSERT_EQUALS(strcmp(e.what(), "TokTik"),0));
  }
  
};


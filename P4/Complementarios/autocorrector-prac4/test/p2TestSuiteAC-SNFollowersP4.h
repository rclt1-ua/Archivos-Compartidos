#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "SNData.h"
#include "SNFollowers.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>


using namespace std;


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for SNFollowers ----------------------------------------------------
  void testSNFollowersP4() {

    // añadimos datos de redes sociales 
    
  	SNData::newSocialNetwork("TokTik",0.8,0.1);
  	SNData::newSocialNetwork("Infagram",0.6,0.05);
  	SNData::newSocialNetwork("YZ",0.5,0.2);
   SNData::newSocialNetwork("JungleBook",0.1,0.1);
	
    // constructor
   
    SNFollowers snf("TokTik",900);
	 
    // getters
    TS_ASSERT_EQUALS(snf.getName(),"TokTik");
    TS_ASSERT_EQUALS(snf.getNumFollowers(),900);
    TS_ASSERT_EQUALS(snf.getMoney(),0.0);
    
    snf.addFollowers(100);
    TS_ASSERT_EQUALS(snf.getNumFollowers(),1000);
    snf.addEvent(0.65);
	 
    TS_ASSERT_EQUALS(snf.getNumFollowers(),1812);
    TS_ASSERT_DELTA(snf.getMoney(),81.2,0.01);

    // operator<<
    stringstream ss;
    ss << snf;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("[TokTik|1812|81.2]"));

    
    TS_ASSERT_DELTA(snf.collectCommission(0.2),16.24,0.01);   
    TS_ASSERT_DELTA(snf.getMoney(),0.0,0.01);

    ss << snf;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("[TokTik|1812|0]"));
	 //********************************************************

	 /*METODOS P4: Solo comprueba que los métodos existen y sus signaturas son correctas, 
                  y los nombres de los campos del struct son correctos pero no que funcionen bien.*/
	 const BinSNFollowers bsnf = snf.toBinSNFollowers();
	 TS_ASSERT_EQUALS(strcmp(bsnf.name, "TokTik"),0);
	 int nFollowers = bsnf.numFollowers;
	 double money = bsnf.money; 
	 SNFollowers snfollowers(bsnf);
    
  }
  
  
};


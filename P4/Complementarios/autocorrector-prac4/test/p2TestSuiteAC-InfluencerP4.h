#include <cxxtest/TestSuite.h>

#include <iostream>
#include <vector>
using namespace std;

#include "SNData.h"
#include "Influencer.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>


using namespace std;


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Influencer ----------------------------------------------------------
  void testInfluencer() {

    // añadimos datos de redes sociales 
    SNData::newSocialNetwork("TokTik",0.8,0.1);
    SNData::newSocialNetwork("Infagram",0.6,0.05);
    SNData::newSocialNetwork("YZ",0.5,0.2);
    SNData::newSocialNetwork("JungleBook",0.1,0.1);

    // constructor
    Influencer inf("Brian");
    
    TS_ASSERT_EQUALS(inf.getName(),"Brian");
    
    // commission
    inf.setCommission(0.7);
    TS_ASSERT_DELTA(inf.getCommission(),0.7,0.01);
    inf.setCommission(0.5);
    TS_ASSERT_DELTA(inf.getCommission(),0.5,0.01);

    // add followers    
    inf.addFollowers("YZ",567);
    inf.addFollowers("TokTik",900);
    inf.addFollowers("YZ",765);
    inf.addFollowers("TokTik",100);
    
    vector<SNFollowers> ifo = inf.getFollowers();
    TS_ASSERT_EQUALS(ifo.size(),2);
    TS_ASSERT_EQUALS(ifo[0].getName(),"YZ");
    TS_ASSERT_EQUALS(ifo[0].getNumFollowers(),1332);
    TS_ASSERT_EQUALS(ifo[1].getName(),"TokTik");
    TS_ASSERT_EQUALS(ifo[1].getNumFollowers(),1000);

    // operator<<
    stringstream ss;
    ss << inf;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Influencer:Brian(0.5)[YZ|1332|0][TokTik|1000|0]"));

    // social networks, some not known for SNData, some not known for inf
    string sn[] = {"VistaGram","TokTik","Ultrabook","Dyo","Infagram","JungleBook"};
    double rat[]= {  0.7      , 0.65   ,  0.55     , 0.1 , 0.8      , 0.99 };
    inf.addEvent(6,sn,rat);
    
    ss << inf;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Influencer:Brian(0.5)[YZ|1332|0][TokTik|1812|81.2]"));

    TS_ASSERT_DELTA(inf.collectCommission(),40.6,0.01);
    
    ss << inf;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Influencer:Brian(0.5)[YZ|1332|0][TokTik|1812|0]"));

    //***********************************************************************************
	 /* METODOS P4: Comprueba que los métodos existen y sus signaturas son correctas y el struct tiene 
					   los nombres de los campos correctos, pero NO que todo funcionen bien. */
	 const BinInfluencer binf = inf.toBinInfluencer();
	 TS_ASSERT_EQUALS (strcmp(binf.name, "Brian"),0);
	 double com = binf.commission;
	 int nf = binf.numFollowers;
	 Influencer influencer(binf);
	 const SNFollowers snf("YZ", 3500);
	 influencer.addFollowers(snf);	 
  }
};


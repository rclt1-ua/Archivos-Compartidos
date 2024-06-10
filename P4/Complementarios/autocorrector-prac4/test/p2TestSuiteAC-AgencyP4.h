#include <cxxtest/TestSuite.h>

#include <iostream>
using namespace std;

#include "SNData.h"
#include "Agency.h"
#include "Util.h"

#include "Auxiliar.h"

#include <iostream>


using namespace std;


class TestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  // Tests for Agency -----------------------------------------------------------
  void testAgency() {

    // añadimos datos de redes sociales 
    SNData::newSocialNetwork("TokTik",0.8,0.1);
    SNData::newSocialNetwork("Infagram",0.6,0.05);
    SNData::newSocialNetwork("YZ",0.5,0.2);
    SNData::newSocialNetwork("JungleBook",0.1,0.1);


    // constructor
    Agency agP3("Amasando pasta SL",200);

	 //*********************************
	 /* METODOS P4 -- Se comprueba que los métodos de la P4 están implementados en el código del alumno y el struct tiene los nombres de los
							campos correctos */
	 Agency ag(DIRINPUT+"/AgenciaAmasandoPastaSL.dat");  //Constructor P4
	 BinAgency bA = ag.toBinAgency();

    TS_ASSERT_EQUALS(strcmp(bA.name,"Amasando pasta SL"),0);
	 TS_ASSERT_DELTA(bA.money,200,0.01);
	 TS_ASSERT_EQUALS(bA.numInfluencers,0);
	 TS_ASSERT_EQUALS(ag.getNumberInfluencers(),0);
    //*************************************

    //METODOS DE P3
	 ag.addInfluencer("Curro",0.3);
    
    Influencer *pi;
    // no está lo encuentra, debe lanzar la excepción    
    TS_ASSERT_THROWS_ASSERT(pi=ag.searchInfluencer("Brian"), const Exception &e, TS_ASSERT_EQUALS(e, EXCEPTION_INFL_NOT_FOUND));
    
    // esto no debe lanzar la excepción (si se ha añadido bien)
    pi=ag.searchInfluencer("Curro");
    TS_ASSERT_EQUALS(pi->getName(),"Curro");
    TS_ASSERT_DELTA(pi->getCommission(),0.3,0.01);
    
    ag.addInfluencer("Naranjito",0.4);
    
    //operator<<
    stringstream ss;
    ss << ag;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Agency:AmasandopastaSL[200]Influencer:Curro(0.3)Influencer:Naranjito(0.4)"));

    ag.addFollowers("Curro","TokTik",1000);
    ss << ag;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Agency:AmasandopastaSL[200]Influencer:Curro(0.3)[TokTik|1000|0]Influencer:Naranjito(0.4)"));

    ag.deleteInfluencer("Naranjito");
    ss << ag;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Agency:AmasandopastaSL[200]Influencer:Curro(0.3)[TokTik|1000|0]"));

    // newEvent
    string snNames[] = { "TokTik", "JungleBook", "Infagram", "MSN", "YZ" };
    double evRat[]   = {  0.95,   0.05, 0.7, 0.003, 0.85 };
    vector<string> inm;
    inm.push_back("Naranjito");    // no está, lo hemos borrado
    inm.push_back("Pijus Ticus");  // no está
    inm.push_back("Curro");
    inm.push_back("Pijus Magnificus");  // tampoco está
    
    ag.newEvent(inm,5,snNames,evRat);
    
    ss << ag;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Agency:AmasandopastaSL[200]Influencer:Curro(0.3)[TokTik|2187|118.7]"));

    TS_ASSERT_DELTA(ag.collectCommissions(),35.61,0.01);    
    ss << ag;  
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Agency:AmasandopastaSL[235.61]Influencer:Curro(0.3)[TokTik|2187|0]"));

	 //******************************************************
	 //METODOS P4
	 string fobtenida = DIROBTENIDA+"/Agency.dat";
	 string fesperada = DIRESPERADA+"/Agency.dat";
	 ag.saveData(fobtenida);
	 TS_ASSERT_EQUALS(cmpBinAgency(fobtenida, fesperada),0);

  }
  
  
};


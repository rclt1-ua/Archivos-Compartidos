#ifndef _AUXILIARCHECKFILES_H_
#define _AUXILIARCHECKFILES_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

const string DIRESPERADA= "salida-correcta-esperada";
const string DIROBTENIDA= "salida-obtenida";
const string DIRINPUT= "input-files";
struct BFollowers {
  char name[KMAXNAME];
  int nFollowers;
  double money;
};

struct BInfluencer {
  char name[KMAXNAME];
  double commission;
  int nFollowers;
};

struct BAgency {
  char name[KMAXNAME];
  double money;
  int nInfluencers;
};


int compareFiles(const string &sfo, const string &sfc) {
 int salida=0;

 ifstream fo(sfo.c_str());
 ifstream fc(sfc.c_str());
 if (fo.is_open() && fc.is_open()) {
      string so,sc,tmp;

      fo >> tmp;
      while (!fo.eof() || tmp.length()!=0) {
        so=so+tmp;
        tmp="";
        fo >> tmp;
      }
      fc >> tmp;
      while (!fc.eof() || tmp.length()!=0) {
        sc=sc+tmp;
        tmp="";
        fc >> tmp;
      }

      // ignorar los '-' en las líneas
      string scok, sook;
      for (unsigned int i=0; i<so.length(); i++)
        if (so[i]!='-') sook=sook+so[i];
      for (unsigned int i=0; i<sc.length(); i++)
        if (sc[i]!='-') scok=scok+sc[i];

      if (sook!=scok) {
		  
		  cout<<endl<<sook<<endl;
		  cout<<scok<<endl;
        return(-1);
      }
    }
    else {
      cout << "Fichero " << sfo << " o " << sfc << " no encontrado" << endl;
      return(-1);
    }
   return(0);
  }


bool checkBinInfluencer (const BInfluencer &c, const BInfluencer &cr, unsigned int i) {
         bool error=false;
 			if (strcmp(c.name,cr.name)) {
            cout <<endl<< "Error BinInfluencer{"<<i<<"}.name (" << c.name << ")[" << cr.name << "]" << endl;
            error=true;
          }
          else  if (c.commission != cr.commission) {
            cout <<endl<< "Error BinInfluencer{"<<i<<"}.commission (" << c.commission << ")[" << cr.commission << "]" << endl;
            error=true;
          }
          else if (c.nFollowers != cr.nFollowers) {
            cout <<endl<< "Error BinInfluencer{"<<i<<"}.nFollowers (" << c.nFollowers << ")[" << cr.nFollowers << "]" << endl;
            error=true;
          }
  	return error;
}

bool checkBinSNFollowers (const BFollowers &bp, const BFollowers &bpr, unsigned int i) {
         bool error=false;
	 		if (strcmp(bp.name,bpr.name)) {
            cout <<endl<< "Error BinFollowers{"<<i<<"}.name (" << bp.name << ")[" << bpr.name << "]" << endl;       
	    		error=true;
	 		}
	 		else if (bp.nFollowers!=bpr.nFollowers) {
            cout <<endl<< "Error BinFollowers{"<<i<<"}.nFollowers (" << bp.nFollowers<< ")[" << bpr.nFollowers << "]" << endl;   
  	    		error=true;
	 		}
         else if (bp.money != bpr.money) {
            cout <<endl<< "Error BinFollowers{"<<i<<"}.money (" << bp.money << ")[" << bpr.money << "]" << endl;
            error=true;
          }
          
	return error;
}


int cmpBinAgency(string filename, string fnref) {

  ifstream fb,fbr;

  fb.open(filename.c_str(),ios::in|ios::binary);
  fbr.open(fnref.c_str(),ios::in|ios::binary);
  if (fb.is_open() && fbr.is_open())  {
      BAgency bb,bbr;
      bool error=false;

      fb.read((char *)&bb,sizeof(bb));
      fbr.read((char *)&bbr,sizeof(bbr));

      if (strcmp(bb.name,bbr.name)) {
        cout <<endl<< "Error BinAgency.name, (" << bb.name << ")[" << bbr.name << "]" << endl;
        error=true;
      }
      else if (bb.money != bbr.money) {
        cout <<endl<< "Error BinAgency.money, (" << bb.money << ")[" << bbr.money << "]" << endl;
        error=true;
      }
		 if (!error)
      {
        BInfluencer p, pr;
        fb.read((char *)&p,sizeof(p));
        fbr.read((char *)&pr,sizeof(pr));
        unsigned int i=0;
        while (!fb.eof() && !fbr.eof() && i<bbr.nInfluencers && !error) {
        //for (unsigned i=0;i<bbr.nInfluencers && !error;i++) {
  
          error = checkBinInfluencer(p, pr, i);
          if (!error) {
            BFollowers bl,blr;
				unsigned int j=0;
				fb.read((char *)&bl,sizeof(bl));
            fbr.read((char *)&blr,sizeof(blr));
				while (!fb.eof() && !fbr.eof() && j<pr.nFollowers && !error) {
            //for (unsigned j=0; j<pr.nFollowers && !error; j++) {
              	error = checkBinSNFollowers(bl, blr, j);
					j++;
					fb.read((char *)&bl,sizeof(bl));
               fbr.read((char *)&blr,sizeof(blr));				      		
	    	 	}//del for de Followers
         }//del if del error
         fb.read((char *)&p,sizeof(p));
         fbr.read((char *)&pr,sizeof(pr));
          
        }//del for de Influencers
       }//del if de error 

      if ( (!fb.eof()) || (!fbr.eof()) ){
            	cout << "Error: El fichero "<<filename<<" que genera tu código tiene un número de registros distinto al esperado: "<<fnref<< endl;
             	error=true; 
      }
      fb.close();
      fbr.close();
      if (error) return -1;
      else       return 0;
    } //del if opens
    else
      cout << "Error abriendo ficheros (" << filename << ")[" << fnref << "]" << endl;
    return -1;
 }
#endif

#!/bin/bash

DIRPRAC=.

MAXTIME=10 	   # Tiempo máximo de ejecución (en segundos) de una prueba

SAL=salida-correcta-esperada     # Directorio con los ficheros de salidas correctas
OBT=salida-obtenida       # Directorio con los ficheros obtenidos tras la ejecución de los test unitarios.
mata=./mata
autoco=autocorrector-prac4
meikfail=$autoco/makefile-autocorrector
VAL="valgrind -q"
comparefiles=./compareFiles

# -------------- generar y compilar el fichero auxiliar mata.c -----
function genMata() {

if ! test -x mata ; then  # si ya existe no se genera
echo "#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

const int TAMMAXFICH=300000;
int f;int segundos,st;
int segejec=0;
char *nfsal=NULL;
void SeAcabo(int i){
  fprintf(stderr,\"ERROR, tiempo de ejecución agotado... (%d segundos)\\n\",segundos);
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
void SeAcaboFich(int i){
  fprintf(stderr,\"ERROR, fichero de salida muy grande (cuelgue?)... \\n\");
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
int FicheroGrande() {
  struct stat s;  int ret=0;
  if (nfsal != NULL) {
    stat(nfsal,&s);
    if (s.st_size > TAMMAXFICH) ret = 1;
  }
  return ret;
}
void Control(int i){
  segejec++;
  if (segejec >= segundos) SeAcabo(i);
  else if (FicheroGrande()) SeAcaboFich(i);
  else alarm(1);
}
void Salir(int i){exit(1);}
int main(int argc,char *argv[]){
  if (argc < 4) exit(1);
  segundos = atoi(argv[1]);
  nfsal = argv[2];
  signal(SIGALRM,Control);
  signal(SIGCHLD,Salir);
  alarm(1);
  if ((f = fork()) == 0) execvp(argv[3],&argv[3]);
  else wait(&st);
}
" > mata.c
gcc -o mata mata.c
fi
}

echo "*********************************************************"
echo "Autocorrector P2p4 "


# Comprobar si está valgrind instalado
hayValgrind=$(which valgrind)
if test "$hayValgrind" == "" ; then
  echo "AVISO: El corrector se ejecutará sin valgrind, por lo que es posible que"
  echo "el resultado de la corrección no sea fiable. Para comprobar realmente que la"
  echo "práctica es correcta, debes probar el corrector en un ordenador Linux"
  echo "con valgrind instalado antes de la entrega."
  echo
  read -p "Pulsa [Enter] para continuar"
  VAL=""
fi


echo " Generando ficheros auxiliares... "
genMata
rm -f mata.c

# Compilacion
echo
echo "*********************************************************"
echo " Compilando..."
echo "*********************************************************"
#rm -rf src/*.o
#rm -f $PRINCIPAL


cd ..  # los fuentes están en el directorio superior
make -f $meikfail clean > /dev/null
make -f $meikfail testAC-SNDataP4 2>&1

if [ $? -ne 0 ]; then
  echo "LA PRACTICA NO COMPILA"  # si no compila SNData no va nada
else
  make -f $meikfail testAC-SNFollowersP4 2>&1
  make -f $meikfail testAC-InfluencerP4  2>&1
  make -f $meikfail testAC-AgencyP4  2>&1

  cd -
  echo "*********************************************************"
  echo " Ejecutando las pruebas unitarias del autocorrector..."
  echo "*********************************************************"
  rm -rf test/salida-obtenida/*
  tempfile=`mktemp /tmp/prog2iiXXXXX`
  #tempfile2=`mktemp /tmp/prog2iiXXXXX`
  for i in p2TestRunnerAC-SNDataP4 p2TestRunnerAC-SNFollowersP4 p2TestRunnerAC-InfluencerP4 p2TestRunnerAC-AgencyP4; do
   if test -s ./$i ; then
		#rm -f $OBT/$i.salida-obtenida
       #./mata $MAXTIME $tempfile2 $VAL ./$i > $tempfile2 2> $tempfile
		./mata $MAXTIME $OBT/$i.salida-obtenida $VAL ./$i > $OBT/$i.salida-obtenida 2> $tempfile
       
       sgr=$(grep "\.OK\!$" $tempfile)
       if test "$sgr" != "" ; then
				 $comparefiles $OBT/$i.salida-obtenida $SAL/$i.salida-esperada
				 if [ $? -ne 0 ]; then
					echo "$i    Error: La salida obtenida es distinta a la esperada"
        			diff -EwB $OBT/$i.salida-obtenida $SAL/$i.salida-esperada 2>&1
				 else
             	echo "$i OK"
				 fi
       else
             echo -e "\nFALLA LA PRUEBA UNITARIA $i DEL CORRECTOR:\n"
             cat $tempfile
             echo
       fi
       rm -f $tempfile
       #rm -f $tempfile2
   else
      echo "NO COMPILA LA PRUEBA UNITARIA $i DEL CORRECTOR"
   fi;
  done

  echo -e "\nAVISO: EL AUTOCORRECTOR NO PRUEBA TODOS LOS CASOS POSIBLES\n"
fi


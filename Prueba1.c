//CajeroATM
// LIBRERIAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//DEFINICIONES CONSTANTES
#define NOMBRE 15
#define APELLIDO 15
#define PIN 4
#define IBAN 25



//ESTRUCTURA DE USUARIOS
struct Usuario {
  char nombre[NOMBRE];
  char apellido[APELLIDO];
  char pin[PIN];
  float saldo;
  char iban[IBAN];
} usuario;



//MAIN
int main() {
  struct Usuario usuario;
  
  return 0;
}



//MODULOS
//MODULO QUE PREGUNTA AL USUARIO SI TIENE UNA CUENTA O NO
void usuarioSoN(*ususn){
  int ususn;
  printf("Bienvenido al menu\n");
  printf("1. Tengo una cuenta\n"); 
  printf("2. Crear Usuario\n"); 
  scanf("%d", &usu);
  *ususn = ususn;
}


/////MODULOS DE USUARIO SI
//EN CASO DE QUE TENGA CUENTA, SE LE MUESTRA ESTE MENU AL USUARIO
void ususi(*usu){
  int usu;
  printf("Seleccione su operacion\n");
  printf("1. Ingresas dinero\n"); 
  printf("2. Retirar dinero\n"); 
  printf("3. Estado de cuenta\n"); 
  printf("4. Transferencia dinero\n");
  scanf("%d", &usu);
  *usu = usu;
}



//MODULO PARA INGRESOS DE DINERO
void ingr(){
  int din, conf;
  printf("Introduzca la cantidad de dinero que desea ingresar\n");
  scanf("%d", &din);
    if( din % 10 == 0){
      printf("Confirme su operacion s/n\n");
      scanf("%c", &conf);
        if(conf == 's'){
          printf("Se ha ingresado %d en su cuenta\n", din);
          printf("Gracias por utilizar nuestro servicio\n");       
        }
        else{
          printf("Operacion cancelada\n");
          printf("Gracias por utilizar nuestro servicio\n");       
        }       
    }
    else {
      printf("La cantidad introducida debe ser un multiplo de 10\n");
      printf("Operacion fallida\n");
      printf("Gracias por utilizar nuestro servicio\n");
    }
}



//MODULO PARA RETIRO DE DINERO
void retiro(){
  int dinre, confre;
  printf("Introduzca la cantidad de dinero que desea retirar\n");
  scanf("%d", &dinre);
    if( dinre % 10 == 0){
      printf("Confirme su operacion s/n\n");
      scanf("%c", &confre);
        if(confre == 's'){
          printf("Se ha retirado %d de su cuenta\n", dinre);
          printf("Gracias por utilizar nuestro servicio\n");       
        }
        else{
          printf("Operacion cancelada\n");
          printf("Gracias por utilizar nuestro servicio\n");       
        }
    }
    else {
      printf("La cantidad introducida debe ser un multiplo de 10\n");
      printf("Operacion fallida\n");
      printf("Gracias por utilizar nuestro servicio\n");
    }
}





/////MODULOS USUARIO NO
void crearUsuario(struct Usuario *usuario){
  
}

void pedirNombre(char *nombre){
  printf("Introduzca su nombre");
  scanf("%s", nombre);
}

void pedirNombre(char *apellido){
  printf("Introduzca su apellido");
  scanf("%s", apellido);
}


// MODULO PARA GENERAR EL IBAN
void generarIban(char *iban) {
  int i;
  srand( time ( NULL ) );
  strcpy(iban, "ES00");
    for (i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }  
  iban[24] = '\0';
}



void generarPin(char *pin) {
  int i;
  srand( time( NULL ) );
    for (i = 0; i < 4; i++) {
      pin[i] = '0' + rand() % 10;
    }
      pin[4] = '\0';
}

//CajeroATM
// LIBRERIAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



//ESTRUCTURA DE USUARIOS
struct Usuario {
  char nombre[50];
  char contrasena[20];
  float saldo;
  char iban[30];
};



//MAIN
int main() {
  
  return 0;
}



//MODULOS

//MODULO QUE PREGUNTA AL USUARIO SI TIENE UNA CUENTA O NO
void usuarioSoN(){
  int usu;
  
  printf("Bienvenido al menu\n");
  printf("1. Tengo una cuenta\n"); 
  printf("2. Crear Usuario\n"); 
  scanf("%d", &usu);
  
}



//EN CASO DE QUE TENGA CUENTA, SE LE MUESTRA ESTE MENU AL USUARIO
void ususi(){
  int usu;
  
  printf("Seleccione su operacion\n");
  printf("1. Ingresas dinero\n"); 
  printf("2. Retirar dinero\n"); 
  printf("3. Estado de cuenta\n"); 
  scanf("%d", &usu);
  
}



//MODULO PARA INGRESOS DE DINERO
void ingr(){
  int din, conf;
  
  printf("Introduzca la cantidad de dinero que desea ingresar");
  scanf("%d", &din);

  if( din % 10 == 0){
    printf("Confirme su operacion s/n");
    scanf("%c", &conf);

      if(conf == s){
        printf("Se ha ingresado %d en su cuenta", din);
        printf("Gracias por utilizar nuestro servicio");       
      }
      else{
        printf("Operacion cancelada");
        printf("Gracias por utilizar nuestro servicio");       
      }
          
  }

  else {
    printf("La cantidad introducida debe ser un multiplo de 10");
    printf("Operacion fallida");
    printf("Gracias por utilizar nuestro servicio");
  }
}



//MODULO PARA RETIRO DE DINERO
void retiro(){
  int dinre, confre;
  
  printf("Introduzca la cantidad de dinero que desea retirar");
  scanf("%d", &dinre);

  if( dinre % 10 == 0){
    printf("Confirme su operacion s/n");
    scanf("%c", &confre);

      if(confre == s){
        printf("Se ha retirado %d de su cuenta", dinre);
        printf("Gracias por utilizar nuestro servicio");       
      }
      else{
        printf("Operacion cancelada");
        printf("Gracias por utilizar nuestro servicio");       
      }
          
  }

  else {
    printf("La cantidad introducida debe ser un multiplo de 10");
    printf("Operacion fallida");
    printf("Gracias por utilizar nuestro servicio");
  }
}



// MODULO PARA GENERAR EL IBAN
void generarIban(char *iban) {

    strcpy(iban, "ES");

    for (int i = 2; i < 18; ++i) {
        iban[i] = '0' + rand() % 10;
    }
    
    iban[18] = '\0';
}

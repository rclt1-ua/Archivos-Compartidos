# CajeroATM
#include<stdio.h>



int main() {
  
  return 0;
}



void usuario(){
  int usu;
  
  printf("Bienvenido al menu\n");
  printf("1. Tengo una cuenta\n"); 
  printf("2. Crear Usuario\n"); 
  scanf("%d", &usu);
  
}


void ususi(){
  int usu;
  
  printf("Seleccione su operacion\n");
  printf("1. Ingresas dinero\n"); 
  printf("2. Retirar dinero\n"); 
  printf("3. Estado de cuenta\n"); 
  scanf("%d", &usu);
  
}



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


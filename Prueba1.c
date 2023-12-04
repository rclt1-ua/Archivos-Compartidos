//CajeroATM
// LIBRERIAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//DEFINICIONES CONSTANTES
#define NOMUS 8
#define MAX_NA
#define PIN 4
#define IBAN 25
#define USUARIO 50

//Definimos un tipo de dato cadena de caracteres para el nombre y apellidos
typedef struct TCadenaNA [MAX_NA];
//ESTRUCTURA PARA USUARIOS
typedef struct {
  char nomUs[NOMUS];
  TCadenaNA nombre;
  TCadenaNA apellido;
  char pin[PIN];
  float saldo;
  string iban[IBAN];
} TUsuario;

typedef TUsuario TListaUsuarios [USUARIO];
TListaUsuarios listaU;


//MAIN
int main() {
  TUsuario usuario;
  int a, conUs;
  usuarioSoN(a);

  if(a == 1){





    
  } else if (a == 2){
   usuario = crearUsuario();
    contUs=contUs+1;
  }
  return 0;
}



//MODULOS
//MODULO QUE PREGUNTA AL USUARIO SI TIENE UNA CUENTA O NO
void usuarioSoN(int *ususn){
  int ususna;
  printf("Bienvenido al menu\n");
  printf("1. Tengo una cuenta\n"); 
  printf("2. Crear Usuario\n"); 
  scanf("%d", &ususna);
  *ususn = ususna;
}


/////MODULOS DE USUARIO SI
//EN CASO DE QUE TENGA CUENTA, SE LE MUESTRA ESTE MENU AL USUARIO
void ususi(int *usu){
  int usua;
  printf("Seleccione su operacion\n");
  printf("1. Ingresas dinero\n"); 
  printf("2. Retirar dinero\n"); 
  printf("3. Estado de cuenta\n"); 
  printf("4. Transferencia dinero\n");
  scanf("%d", &usua);
  *usu = usua;
}



//MODULO PARA INGRESOS DE DINERO
void ingr(){
  float din;
  char conf;
  printf("Introduzca la cantidad de dinero que desea ingresar\n");
  scanf("%d", &din);
    if( din % 10 == 0 && din > 0){
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
      printf("La cantidad introducida debe ser un multiplo de 10 y mayor que 0\n");
      printf("Operacion fallida\n");
      printf("Gracias por utilizar nuestro servicio\n");
    }
}



//MODULO PARA RETIRO DE DINERO
void retiro(){
  int dinre; 
  char confre;
  printf("Introduzca la cantidad de dinero que desea retirar\n");
  scanf("%d", &dinre);
    if( dinre % 10 == 0 && dinre > 0){
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
      printf("La cantidad introducida debe ser un multiplo de 10 y mayor que 0\n");
      printf("Operacion fallida\n");
      printf("Gracias por utilizar nuestro servicio\n");
    }
}




/////MODULOS USUARIO NO
int crearUsuario(){
 TUsuario usuario;
  float saldo;
  saldo = 0;
  pedirNombre(usuario.nombre);
  pedirApellido(usuario.apellido);
  //generarNomus();
  generarPin(usuario.pin);  
  generarIban(usuario.iban);
  usuario.saldo = saldo;
  return usuario;
}

void generarNomus(TUsuario *usuario){
  TUsuario.nombre
  TUsuario.apellido
  
  
}

void pedirNombre(char nombre[]){
  printf("Introduzca su nombre");
  scanf("%s", nombre);
}

void pedirApellido(char apellido[]){
  printf("Introduzca su apellido");
  scanf("%s", apellido);
}

void generarPin(char pin[]) {
  int i;
  srand( time( NULL ) );
    for (i = 0; i < 4; i++) {
      pin[i] = '0' + rand() % 10;
    } pin[4] = '\0';
}

void generarIban(string *iban) {
  int i;
  srand( time ( NULL ) );
  strcpy(iban, "ES");
    for (i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }  
  iban[24] = '\0';
}





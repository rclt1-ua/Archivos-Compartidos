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
  char iban[IBAN];
} TUsuario;

typedef TUsuario TListaUsuarios [USUARIO];



//MAIN
int main() {
  TUsuario usuario;
  int a, usua;
  int NUsuarios; //contador de usuarios en memoria
  TListaUsuarios listaU; //array de usuarios en memoria

  listaU=0; //trabajando con o usuarios inicialmente
  usuarioSoN(a); //modulo de menu para saber si es un usuario registrado o no
  

  if(a == 1){
    switch(usua){
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
    }



    
  } else if (a == 2){
      if(NUsuarios < USUARIO){
        
          usuario = crearUsuario();
          usuario[NUsuarios] = usuario;
          NUsuarios++; //incrementamos el contador de usuarios de la lista de usuarios
      }
      else{
        printf("NO HAY MAS ESPECIO EN MEMORIA.\n");
      }
      
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
TUsuario crearUsuario(){
 TUsuario usuario;
  float saldo;
  saldo = 0;
  pedirNombre(usuario.nombre);
  pedirApellido(usuario.apellido);
  //generarNomus();
  generarPin(usuario.pin);  
  generarIban(usuario.iban);
  usuario.saldo = saldo;
  //Usuario.fecha = leerfecha(); en el caso que quisieramos registrar la fecha de dado de alta del usuario (se asignan los campos automaticamente) 
  //inicializamos el array de IBAN a 0
  for(int i=0; i<12; i++){
    usuario.iban[i] = 0;
  }
  return usuario;
}

void generarNomus(TUsuario usuario){
  TUsuario.nombre
  TUsuario.apellido
  
  
}

void pedirNombre(TCadena nombre){
  printf("\t*Introduzca su nombre");
  scanf("%s", nombre); //con array de char no se coloca & (se modifica directamente en memoria)
}

void pedirApellido(TCadena apellido){
  printf("\t*Introduzca su apellido");
  scanf("%s", apellido);
}

void generarPin(char pin[]) {
  int i;
  srand( time( NULL ) );
    for (i = 0; i < 4; i++) {
      pin[i] = '0' + rand() % 10;
    } pin[4] = '\0';
}

void generarIban(char iban[]) {
  int i;
  srand( time ( NULL ) );
  strcpy(iban, "ES");
    for (i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }  
  iban[24] = '\0';
}

//por si necesitamos leer una Tfecha
Tfecha leerFecha(){
  Tfecha fecha;
  char c; //caracter para leer la fecha
  do {
      scanf("%d %d %d",&fecha.dia, &c,&fecha.mes, &c,&fecha.anyo);
  }while(fecha.dia< 1 || fecha.dia > 31 || fecha.mes < 1 || fecha.mes > 12);
  return fecha;
}


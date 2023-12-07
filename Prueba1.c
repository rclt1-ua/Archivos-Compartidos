#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// DEFINICIONES CONSTANTES
#define NOMUS 8
#define MAX_NOM 50
#define PIN_DIGITOS 4
#define IBAN 25
#define USUARIO 50

// Definimos un tipo de dato cadena de caracteres para el nombre y apellidos
typedef char TCadenaNA[MAX_NOM];

typedef struct {
    TCadenaNA nombre;
    TCadenaNA apellido;
} TId;

typedef struct {
    char nomUs[NOMUS];
    int pin;
} TDatos;

// ESTRUCTURA PARA USUARIOS
typedef struct {
    TId nombre;
    TDatos usuario;
    float saldo;
    char iban[IBAN];
} TUsuario;

typedef TUsuario TListaUsuarios[USUARIO];

// PROTOTIPOS DE FUNCIONES
TId pedirID();
int generarNumeroAleatorio();
void usuarioSoN(int *ususn);
void crearUsuario(TListaUsuarios listaU, int *NUsuarios);
void generarPin(int *pin);
void generarIban(char iban[], int NUsuarios);
void imprimirUsuario(TUsuario *usuario);
void generarNomUs(TId nombre, char nomUs[]);


// MAIN
int main() {
    TUsuario usuario;
    int a, usua;
    int NUsuarios = 0; // contador de usuarios en memoria
    TListaUsuarios listaU; // array de usuarios en memoria

    listaU[NUsuarios] = usuario; // trabajando con 1 usuario inicialmente
    usuarioSoN(&a); // modulo de menú para saber si es un usuario registrado o no

    if (a == 1) {
        // Mostrar menú de usuario si ya tiene cuenta
        printf("Seleccione su operación\n");
        printf("1. Ingresar dinero\n");
        printf("2. Retirar dinero\n");
        printf("3. Estado de cuenta\n");
        printf("4. Transferir dinero\n");
        scanf("%d", &usua);
        switch (usua) {
            case 1:
                // Lógica para ingreso de dinero
                break;
            case 2:
                // Lógica para retiro de dinero
                break;
            case 3:
                // Lógica para consultar estado de cuenta
                break;
            case 4:
                // Lógica para transferencia de dinero
                break;
            default:
                printf("Opción no válida\n");
        }
    } else if (a == 2) {
        // Crear nuevo usuario
        if (NUsuarios < USUARIO) {
            crearUsuario(listaU, &NUsuarios);
        } else {
            printf("NO HAY MÁS ESPACIO EN MEMORIA.\n");
        }
    }
    return 0;
}

// MODULOS

// MODULO QUE PREGUNTA AL USUARIO SI TIENE UNA CUENTA O NO
void usuarioSoN(int *ususn) {
    int ususna;
    printf("Bienvenido al menú\n");
    printf("1. Tengo una cuenta\n");
    printf("2. Crear Usuario\n");
    scanf("%d", &ususna);
    *ususn = ususna;
}

void crearUsuario(TListaUsuarios listaU, int *NUsuarios) {
    listaU[*NUsuarios].nombre = pedirID();
    generarNomUs(listaU[*NUsuarios].nombre, listaU[*NUsuarios].usuario.nomUs);
    generarPin(&listaU[*NUsuarios].usuario.pin);
    generarIban(listaU[*NUsuarios].iban, *NUsuarios);
    listaU[*NUsuarios].saldo = 0.0;

    // Añadir dos números aleatorios al nombre de usuario
    int numero1 = generarNumeroAleatorio();
    int numero2 = generarNumeroAleatorio();
    char numerosAleatorios[5];
    sprintf(numerosAleatorios, "%d%d", numero1, numero2);
    strcat(listaU[*NUsuarios].usuario.nomUs, numerosAleatorios);

    printf("Usuario creado exitosamente:\n");
    imprimirUsuario(&listaU[*NUsuarios]);

    (*NUsuarios)++;
}

// FUNCION PARA GENERAR UN NUMERO ALEATORIO DE DOS CIFRAS
int generarNumeroAleatorio() {
    return rand() % 100;
}

// MODULO PARA PEDIR NOMBRE Y APELLIDO
TId pedirID() {
    TId persona;
    printf("\t*Introduzca su nombre: ");
    scanf("%s", persona.nombre);
    printf("\t*Introduzca su apellido: ");
    scanf("%s", persona.apellido);
    return persona;
}

// MODULO PARA IMPRIMIR DATOS DE UN USUARIO
void imprimirUsuario(TUsuario *usuario) {
    printf("Nombre: %s %s\n", usuario->nombre.nombre, usuario->nombre.apellido);
    printf("Nombre de usuario: %s\n", usuario->usuario.nomUs);
    printf("PIN: %04d\n", usuario->usuario.pin);
    printf("Saldo: %.2f\n", usuario->saldo);
    printf("IBAN: %s\n", usuario->iban);
}

// MODULO PARA GENERAR NOMBRE DE USUARIO
void generarNomUs(TId nombre, char nomUs[]) {
    // Tomar las tres primeras letras del nombre
    strncpy(nomUs, nombre.nombre, 3);
    nomUs[3] = '\0'; // Añadir el carácter nulo al final
    // Concatenar las tres primeras letras del apellido al nombre de usuario
    strncat(nomUs, nombre.apellido, 3);
    nomUs[6] = '\0'; // Añadir el carácter nulo al final
}

// FUNCIONES AUXILIARES

void generarPin(int *pin) {
    srand(time(NULL));
    *pin = rand() % 10000;
}

void generarIban(char iban[], int NUsuarios) {
    srand(time(NULL));
    strcpy(iban, "ES");
    char numUsuario[4];  // Suponiendo que el número de usuario es de máximo 3 dígitos
    sprintf(numUsuario, "%03d", NUsuarios);
    strcat(iban, numUsuario);
    for (int i = 5; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }
    iban[24] = '\0';
}


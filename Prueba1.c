#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definiciones constantes
#define NOMUS 8
#define MAX_NOM 50
#define PIN_DIGITOS 4
#define IBAN 26
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

// Estructura para usuarios
typedef struct {
    TId nombre;
    TDatos usuario;
    float saldo;
    char iban[IBAN];
} TUsuario;

typedef TUsuario TListaUsuarios[USUARIO];


// Prototipos de funciones
TId pedirID();
int generarNumeroAleatorio();
void usuarioSoN(int *ususn);
void crearUsuario(TListaUsuarios listaU, int *NUsuarios);
void generarPin(int *pin);
void generarIban(char iban[], int NUsuarios);
void imprimirUsuario(TUsuario *usuario);
void generarNomUs(TId nombre, char nomUs[]);
void Ingreso(TUsuario *usuario);
void consultarUsuario(TListaUsuarios listaU, int NUsuarios);




// Función principal (main)
int main() {
    TUsuario usuario;
    int a, usua;
    int NUsuarios = 0;
    TListaUsuarios listaU;

    listaU[NUsuarios] = usuario;
    usuarioSoN(&a);
    srand(time(NULL));

    while (a != 0) {
        if (a == 1) {
            // Menú de usuario registrado
            printf("Seleccione su operación\n");
            printf("1. Ingresar dinero\n");
            printf("2. Retirar dinero\n");
            printf("3. Consultar usuario\n");
            printf("4. Transferir dinero\n");
            printf("Presione 0 para salir\n");
            scanf("%d", &usua);

            switch (usua) {
                case 1:
                    Ingreso(&listaU[NUsuarios]);
                    break;
                case 2:
                    // Lógica para retiro de dinero
                    break;
                case 3:
                    consultarUsuario(listaU, NUsuarios);
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
        // Agregar una pausa antes de volver a mostrar el menú
        printf("\nPresione Enter para continuar...");
        while (getchar() != '\n'); // Limpiar el buffer de entrada

        // Volver a preguntar si el usuario tiene cuenta
        usuarioSoN(&a);
    }

    printf("Gracias por usar nuestros servicios\n");

    return 0;
}





// MODULOS

// MODULO QUE PREGUNTA AL USUARIO SI TIENE UNA CUENTA O NO
void usuarioSoN(int *ususn) {
    int ususna;
    printf("Bienvenido al menú\n");
    printf("1. Tengo una cuenta\n");
    printf("2. Crear Usuario\n");
    printf("3. Consultar usuario\n");
    printf("0. Salir del programa\n");
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
    printf("PIN: %0d\n", usuario->usuario.pin);
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


// MODULO PARA GENERAR UN PIN ALEATORIO DE 4 DIGITOS
void generarPin(int *pin) {
    // Genera un PIN de forma aleatoria
    int digits[4];
    digits[0] = rand() % 10;
    digits[1] = rand() % 10;
    digits[2] = rand() % 10;
    digits[3] = rand() % 10;

    // Desordena los dígitos
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        // Intercambia digits[i] y digits[j]
        int temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
    }

    // Construye el PIN desordenado
    *pin = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
}

void generarIban(char iban[], int NUsuarios) {
    strcpy(iban, "ES");
    char numUsuario[4];  // Suponiendo que el número de usuario es de máximo 3 dígitos
    sprintf(numUsuario, "%02d", NUsuarios);
    strcat(iban, numUsuario);
    for (int i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }
    iban[24] = '\0';
}



void Ingreso(TUsuario *usuario) {
    int cantidad;
    char confirmacion;

    printf("Introduzca la cantidad de efectivo que desea ingresar\n");
    printf("La cantidad debe ser múltiplo de 5\n");
    scanf("%d", &cantidad);

    if (cantidad % 5 == 0) {
        printf("¿Quiere confirmar su transacción? S/N: ");
        scanf(" %c", &confirmacion);

        if (confirmacion == 'S' || confirmacion == 's') {
            usuario->saldo += cantidad;
            printf("Se han añadido %d euros a su cuenta. Nuevo saldo: %.2f euros\n", cantidad, usuario->saldo);
        } else {
            printf("Transacción cancelada\n");
        }
    } else {
        printf("Transacción cancelada. La cantidad introducida no es múltiplo de 5\n");
    }
}



// Módulo para consultar un usuario
void consultarUsuario(TListaUsuarios listaU, int NUsuarios) {
    char nombre[MAX_NOM];
    char apellido[MAX_NOM];
    int pin;

    // Limpiar el búfer de entrada antes de solicitar la información
    while (getchar() != '\n');

    printf("Introduzca su nombre: ");
    scanf("%49s", nombre);
    printf("Introduzca su apellido: ");
    scanf("%49s", apellido);
    printf("Introduzca su PIN: ");
    scanf("%d", &pin);

    // Buscar el usuario en la lista
    int i;
    for (i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].nombre.nombre, nombre) == 0 &&
            strcmp(listaU[i].nombre.apellido, apellido) == 0 &&
            listaU[i].usuario.pin == pin) {
            // Mostrar la información del usuario
            printf("Información del usuario:\n");
            imprimirUsuario(&listaU[i]);
            return;
        }
    }

    // Si no se encuentra el usuario, mostrar un mensaje
    printf("Usuario no encontrado. Verifique sus datos e intente nuevamente.\n");
}

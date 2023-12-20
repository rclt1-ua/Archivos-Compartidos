// LIBRERÍAS --------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "tigr.h"

// CONSTANTES --------------------------------------------------------------
#define NOMUS_LETRAS 15
#define MAX_NOM 50
#define PIN_DIGITOS 4
#define IBAN 26
#define MAX_TRANSACCIONES 100
#define USUARIO 50

// ESTRUCTURAS Y TIPOS DE DATOS ------------------------------------------------
typedef char TCadenaNA[MAX_NOM];

typedef struct {
    TCadenaNA nombre;
    TCadenaNA apellido;
    char identificacion[MAX_NOM];
} TId;

typedef struct {
    float monto;
    char tipo;
    char fecha[11];
    char hora[9];
    char minuto[3];
} TTransaccion;

typedef struct{
    int a;
    int b;
    int c;
    int d;
    int mes;
    int anyo;
    int cvc;
} TTarjeta;

typedef struct {
    TId nombre;
    float saldo;
    char iban[IBAN];
    char fechaNacimiento[11];
    int pin;
    TTransaccion transacciones[MAX_TRANSACCIONES];
    int numTransacciones;
    TTarjeta tarjeta;
} TUsuario;

typedef TUsuario TListaUsuarios[USUARIO];

// MÓDULOS --------------------------------------------------------------
void UsuarioSoN(int *ususn);
int ConsultarUsuario(TListaUsuarios listaU, int NUsuarios, const char *nombre, const char *apellido, int *saldoActualizado);
void Ingreso(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void Retiro(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void Transferencia(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void MostrarHistorialTransacciones(TUsuario *usuario);
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios);
void CargarUsuariosDesdeArchivo(TListaUsuarios listaU, int *NUsuarios);
void CrearUsuario(TListaUsuarios listaU, int *NUsuarios);
TId PedirID();
int EsMenorDeEdad(const char *fechaNacimiento);
int BuscarUsuarioPorIBAN(TListaUsuarios listaU, int NUsuarios, const char *iban);
void ImprimirUsuario(TUsuario *usuario);
void GenerarPin(TListaUsuarios listaU, int NUsuarios, int *pin);
void GenerarIban(char iban[], int NUsuarios);
void ObtenerFechaHora(TTransaccion *transaccion);
TTarjeta GenerarTarjeta();
void GenerarIban(char iban[], int NUsuarios);
int ExistePinEnLista(TListaUsuarios listaU, int NUsuarios, int pin);
void Grafico(int a, int b, int c, int d, int e, int f, int g, char y[], char z[]);
int BuscarUsuarioPorTarjeta(TListaUsuarios listaU, int NUsuarios, const TTarjeta *tarjeta);

// MAIN --------------------------------------------------------------
int main() {
    TUsuario usuario;
    int a, usua;
    int NUsuarios = 0;
    TListaUsuarios listaU;
    char continuar;

     
     
    for (int i = 0; i < USUARIO; ++i) {
        listaU[i] = usuario;
    }

    CargarUsuariosDesdeArchivo(listaU, &NUsuarios);

    printf("%d", NUsuarios);

    do {
        UsuarioSoN(&a);
        if (a == 1) {
            char nombre[MAX_NOM];
            char apellido[MAX_NOM];
            int usuarioEncontradoIndex;
            int saldoActualizado;

            printf("Introduzca su nombre: ");
            scanf("%49s", nombre);
            printf("Introduzca su apellido: ");
            scanf("%49s", apellido);

            usuarioEncontradoIndex = ConsultarUsuario(listaU, NUsuarios, nombre, apellido, &saldoActualizado);

            // Menú de usuario registrado
            if (usuarioEncontradoIndex != -1) {
                do {
                    printf("\n\t Seleccione su operación\n");
                    printf("\n");
                    printf("\t 1. Ingresar dinero\n");
                    printf("\t 2. Retirar dinero\n");
                    printf("\t 3. Consultar usuario\n");
                    printf("\t 4. Transferir dinero\n");
                    printf("\t 5. Mostrar historial de transacciones\n");
                    printf("\t Presione 0 para salir\n");
                    printf("\n");

                    scanf("%d", &usua);

                    switch (usua) {
                        case 1:
                            Ingreso(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 2:
                            Retiro(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 3:
                            ImprimirUsuario(&listaU[usuarioEncontradoIndex]);
                            break;
                        case 4:
                            Transferencia(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 5:
                            MostrarHistorialTransacciones(&listaU[usuarioEncontradoIndex]);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opción no válida\n");
                    }

                    if(usua > 0 && usua <=5){
                        printf("¿Desea realizar otra operación? (s/n): ");
                        scanf(" %c", &continuar);
                        GuardarUsuarios(listaU, NUsuarios);
                        }
                    else{
                        while (getchar() != '\n');
                    };
                    GuardarUsuarios(listaU, NUsuarios);
                } while (continuar == 's' || continuar == 'S');
            } else {
                printf("Usuario no encontrado o PIN incorrecto, compruebe la información ingresada\n");
            }
        } else if (a == 2) {
            // Crear nuevo usuario
            if (NUsuarios < USUARIO) {
                    CrearUsuario(listaU, &NUsuarios);
                    printf("\n");
                GuardarUsuarios(listaU, NUsuarios);
            } else {
                printf("NO HAY MÁS ESPACIO EN MEMORIA.\n");
            }
        }
    } while (a != 0);

     GuardarUsuarios(listaU, NUsuarios);

    printf("Gracias por usar nuestros servicios\n");

    return 0;
}


// MODULO PARA PEDIR NOMBRE Y APELLIDO
TId PedirID() {
    TId persona;
    printf("\n");
    printf("\t *Introduzca su nombre: ");
    scanf("%s", persona.nombre);
    printf("\t *Introduzca su apellido: ");
    scanf("%s", persona.apellido);
    // Solicitar número de identificación (puede contener letras o números)
    printf("\t *Introduzca su número de identificación: ");
    scanf("%s", persona.identificacion);

    return persona;
}


void UsuarioSoN(int *ususn) {
    int ususna;
    printf("\n\t   Bienvenido al menú\n");
    printf("\n");
    printf("\t 1. Tengo una cuenta\n");
    printf("\t 2. Crear Usuario\n");
    printf("\t 0. Salir del programa\n");
    printf("\n");
    printf("Opcion:  ");
    scanf("%d", &ususna);
    *ususn = ususna;
}

int ConsultarUsuario(TListaUsuarios listaU, int NUsuarios, const char *nombre, const char *apellido, int *saldoActualizado) {
    char pinIngresado[PIN_DIGITOS];
    
    for (int i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].nombre.nombre, nombre) == 0 &&
            strcmp(listaU[i].nombre.apellido, apellido) == 0) {
            
            printf("Introduzca su PIN: ");
            scanf("%s", pinIngresado);

            if (atoi(pinIngresado) == listaU[i].pin) {
                // Almacena el saldo actualizado
                *saldoActualizado = listaU[i].saldo;
                // Devolver el índice del usuario encontrado
                return i;
            } else {
                printf("PIN incorrecto. Intente nuevamente.\n");
                // Devolver -1 para indicar PIN incorrecto
                return -1;
            }
        }
    }
    // Si no se encuentra el usuario, devolver -1
    return -1;
}




// MODULO PARA INGRESO DE DINERO --------------------------------------
void Ingreso(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex) {
    int cantidad;
    char confirmacion;

    if (usuarioEncontradoIndex != -1) {
        printf("Introduzca la cantidad de efectivo que desea ingresar\n");
        printf("La cantidad debe ser múltiplo de 5\n");
        scanf("%d", &cantidad);

        if (cantidad % 5 == 0) {
            printf("¿Quiere confirmar su transacción? S/N: ");
            scanf(" %c", &confirmacion);

            if (confirmacion == 'S' || confirmacion == 's') {
                // Crear una nueva transacción de ingreso
                listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].monto = cantidad;
                listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].tipo = 'I'; // Ingreso
                // Ajustar la fecha y hora según sea necesario
                ObtenerFechaHora(&(listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones]));
                // Incrementar el número de transacciones
                listaU[usuarioEncontradoIndex].numTransacciones++;

                // Actualizar el saldo del usuario
                listaU[usuarioEncontradoIndex].saldo += cantidad;

                printf("Se han añadido %d euros a la cuenta del usuario. \n\t **Nuevo saldo**: %.2f euros\n", cantidad, listaU[usuarioEncontradoIndex].saldo);
            } else {
                printf("Transacción cancelada\n");
            }
        } else {
            printf("Transacción cancelada. La cantidad introducida no es múltiplo de 5\n");
        }
    } else {
        printf("Usuario no encontrado. Verifique los datos del usuario.\n");
    }
}

// MODULO PARA RETIRO DE DINERO ---------------------------------------
void Retiro(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex) {
    int cantidad;
    char confirmacion;

    if (usuarioEncontradoIndex != -1) {
        printf("Introduzca la cantidad de efectivo que desea retirar\n");
        printf("La cantidad debe ser múltiplo de 10\n");
        scanf("%d", &cantidad);

        // Verificar si el saldo es suficiente
        if (cantidad <= listaU[usuarioEncontradoIndex].saldo) {
            if (cantidad % 10 == 0) {
                printf("¿Quiere confirmar su transacción? S/N: ");
                scanf(" %c", &confirmacion);

                if (confirmacion == 'S' || confirmacion == 's') {
                    // Crear una nueva transacción de retiro
                    listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].monto = -cantidad;
                    listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].tipo = 'R'; // Retiro
                    // Ajustar la fecha y hora según sea necesario
                    ObtenerFechaHora(&(listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones]));
                    // Incrementar el número de transacciones
                    listaU[usuarioEncontradoIndex].numTransacciones++;

                    // Actualizar el saldo del usuario
                    listaU[usuarioEncontradoIndex].saldo -= cantidad;

                    printf("Se han retirado %d euros de la cuenta del usuario. Nuevo saldo: %.2f euros\n", cantidad, listaU[usuarioEncontradoIndex].saldo);
                } else {
                    printf("Transacción cancelada\n");
                }
            } else {
                printf("Transacción cancelada. La cantidad introducida no es múltiplo de 10\n");
            }
        } else {
            printf("Transacción cancelada. Saldo insuficiente\n");
        }
    } else {
        printf("Usuario no encontrado. Verifique los datos del usuario.\n");
    }
}

// Función para obtener la fecha, hora y minuto actual
void ObtenerFechaHora(TTransaccion *transaccion) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(transaccion->fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(transaccion->hora, "%02d", tm.tm_hour);
    sprintf(transaccion->minuto, "%02d", tm.tm_min);
}


// MODULO DE TRANSFERENCIA ------------------------------------------
// MODULO DE TRANSFERENCIA ------------------------------------------
void Transferencia(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex) {
    float cantidad;
    char confirmacion;
    char ibanDestino[IBAN];

    // Limpiar el búfer de entrada antes de solicitar la información
    while (getchar() != '\n');

    printf("Introduzca el IBAN al que desea transferir dinero: ");
    scanf("%s", ibanDestino);

    // Buscar el usuario destino en la lista
    int indiceDestino = BuscarUsuarioPorIBAN(listaU, NUsuarios, ibanDestino);

    if (indiceDestino != -1) {
        if (usuarioEncontradoIndex != indiceDestino) {
            printf("Introduzca la cantidad de dinero que desea transferir\n");
            printf("Puede incluir centavos\n");
            scanf("%f", &cantidad);

            // Verificar si el saldo es suficiente
            if (cantidad <= listaU[usuarioEncontradoIndex].saldo) {
                printf("¿Quiere confirmar su transacción? S/N: \n");
                scanf(" %c", &confirmacion);

                if (confirmacion == 'S' || confirmacion == 's') {
                    // Crear una nueva transacción de transferencia (salida)
                    listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].monto = -cantidad;
                    listaU[usuarioEncontradoIndex].transacciones[listaU[usuarioEncontradoIndex].numTransacciones].tipo = 'T'; // Transferencia
                    // Ajustar la fecha y hora según sea necesario
                    // Incrementar el número de transacciones
                    listaU[usuarioEncontradoIndex].numTransacciones++;

                    // Actualizar el saldo del usuario de origen
                    listaU[usuarioEncontradoIndex].saldo -= cantidad;

                    // Crear una nueva transacción de transferencia (entrada)
                    listaU[indiceDestino].transacciones[listaU[indiceDestino].numTransacciones].monto = cantidad;
                    listaU[indiceDestino].transacciones[listaU[indiceDestino].numTransacciones].tipo = 'T'; // Transferencia
                    // Ajustar la fecha y hora según sea necesario
                    // Incrementar el número de transacciones
                    listaU[indiceDestino].numTransacciones++;

                    // Actualizar el saldo del usuario de destino
                    listaU[indiceDestino].saldo += cantidad;

                    printf("Se han transferido %.2f euros de %s a %s.\n", cantidad, listaU[usuarioEncontradoIndex].nombre.nombre, listaU[indiceDestino].nombre.nombre);
                } else {
                    printf("Transacción cancelada, %c\n", confirmacion);
                }
            } else {
                printf("Transacción cancelada. Saldo insuficiente\n");
            }
        } else {
            printf("Transacción cancelada. No puedes transferir dinero a la misma cuenta\n");
        }
    } else {
        printf("Usuario destino con IBAN %s no encontrado. Verifique el IBAN e intente nuevamente.\n", ibanDestino);
    }
}




void MostrarHistorialTransacciones(TUsuario *usuario) {
    printf("Historial de Transacciones:\n");
    for (int i = 0; i < usuario->numTransacciones; ++i) {
        printf("Transacción %d: %.2f euros - Tipo: %c - Fecha: %s - Hora: %s:%s\n",
               i + 1,
               usuario->transacciones[i].monto,
               usuario->transacciones[i].tipo,
               usuario->transacciones[i].fecha,
               usuario->transacciones[i].hora,
               usuario->transacciones[i].minuto);
    }
}




// MODULO PARA GUARDAR USUARIOS EN UN ARCHIVO ---------------------
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios) {
    FILE *archivo;
    archivo = fopen("DATOSCAJERO.txt", "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    // Guardar el número total de usuarios
    fprintf(archivo, "%d\n", NUsuarios);

    for (int i = 0; i < NUsuarios; ++i) {
        fprintf(archivo, "%s %.2f %s %s %d %d %d %d %d %d %d %d \n",
                   listaU[i].iban,
                   listaU[i].saldo,
                   listaU[i].nombre.nombre,
                   listaU[i].nombre.apellido,
                   listaU[i].pin,
                   listaU[i].tarjeta.a,
                   listaU[i].tarjeta.b,
                   listaU[i].tarjeta.c,
                   listaU[i].tarjeta.d,
                   listaU[i].tarjeta.mes,
                   listaU[i].tarjeta.anyo,
                   listaU[i].tarjeta.cvc);

        fprintf(archivo, "%d\n", listaU[i].numTransacciones);

        // Guardar transacciones
        for (int j = 0; j < listaU[i].numTransacciones; ++j) {
            fprintf(archivo, "%.2f %c %s %s %s\n",
                    listaU[i].transacciones[j].monto,
                    listaU[i].transacciones[j].tipo,
                    listaU[i].transacciones[j].fecha,
                    listaU[i].transacciones[j].hora,
                    listaU[i].transacciones[j].minuto);
        }

        fprintf(archivo, "\n");
    }

    fclose(archivo);
}




// MODULO PARA CARGAR USUARIOS DESDE UN ARCHIVO ---------------------
void CargarUsuariosDesdeArchivo(TListaUsuarios listaU, int *NUsuarios) {
    FILE *archivo;
    archivo = fopen("DATOSCAJERO.txt", "r");

    if (archivo == NULL) {
        printf("El archivo DATOSCAJERO.txt no existe. No se cargaron usuarios.\n");
        return;
    }

    // Leer el número total de usuarios
    fscanf(archivo, "%d", NUsuarios);

    for (int i = 0; i < *NUsuarios; ++i) {
        fscanf(archivo, "%s %f %s %s %d %d %d %d %d %d %d %d",
               listaU[i].iban,
               &listaU[i].saldo,
               listaU[i].nombre.nombre,
               listaU[i].nombre.apellido,
               &listaU[i].pin,
               &listaU[i].tarjeta.a,
               &listaU[i].tarjeta.b,
               &listaU[i].tarjeta.c,
               &listaU[i].tarjeta.d,
               &listaU[i].tarjeta.mes,
               &listaU[i].tarjeta.anyo,
               &listaU[i].tarjeta.cvc);

        fscanf(archivo, "%d", &listaU[i].numTransacciones);

        // Leer transacciones
        for (int j = 0; j < listaU[i].numTransacciones; ++j) {
            fscanf(archivo, "%f %c %s %s %s",
                   &listaU[i].transacciones[j].monto,
                   &listaU[i].transacciones[j].tipo,
                   listaU[i].transacciones[j].fecha,
                   listaU[i].transacciones[j].hora,
                   listaU[i].transacciones[j].minuto);
        }
    }

    fclose(archivo);
}





// MODULO DE CREAR USUARIO ----------------------------------------
void CrearUsuario(TListaUsuarios listaU, int *NUsuarios) {
    TId fechaNacimiento;
    int esMenor, i;

    listaU[*NUsuarios].nombre = PedirID();

    // Verificar si la identificación ya existe en la lista
    for (i = 0; i < *NUsuarios; ++i) {
        if (strcmp(listaU[i].nombre.identificacion, listaU[*NUsuarios].nombre.identificacion) == 0) {
            printf("Ya existe un usuario con esta identificación. Intente nuevamente.\n");
            break;
        }
    }

    // Si no se encuentra una identificación duplicada, continuar con la creación del usuario
    if (i == *NUsuarios) {
        // Pedir fecha de nacimiento
        printf("\t *Introduzca su fecha de nacimiento (DD/MM/AAAA): ");
        scanf("%s", listaU[*NUsuarios].fechaNacimiento);
        printf("\n");
        // Verificar si el usuario es menor de edad
        esMenor = EsMenorDeEdad(listaU[*NUsuarios].fechaNacimiento);
        if (esMenor) {
            printf("Lo siento, no puedes crear una cuenta porque eres menor de edad o la fecha no es válida.\n");
            // Puedes agregar aquí cualquier código adicional necesario si el usuario es menor
        } else {
            // Continuar con la creación del usuario
            GenerarPin(listaU, *NUsuarios, &listaU[*NUsuarios].pin);
            GenerarIban(listaU[*NUsuarios].iban, *NUsuarios);
            listaU[*NUsuarios].saldo = 0.0;

            listaU[*NUsuarios].tarjeta = GenerarTarjeta();


            printf("Usuario creado exitosamente:\n");
            ImprimirUsuario(&listaU[*NUsuarios]);
            (*NUsuarios)++;
        }
    }
}



// MODULO PARA VERIFICAR MAYORÍA DE EDAD --------------------------------
int EsMenorDeEdad(const char *fechaNacimiento) {
    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Obtener el día, mes y año actual
    int diaActual = tm.tm_mday;
    int mesActual = tm.tm_mon + 1;  // Sumar 1 porque en struct tm, enero es 0
    int anoActual = tm.tm_year + 1900;  // Sumar 1900 porque struct tm cuenta los años desde 1900
    // Obtener la fecha de nacimiento del usuario
    int diaNacimiento, mesNacimiento, anoNacimiento;
    // Verificar si el usuario proporciona el mes y el año
    if (sscanf(fechaNacimiento, "%d/%d/%d", &diaNacimiento, &mesNacimiento, &anoNacimiento) != 3) {
        printf("Error: La fecha de nacimiento \"%s\" no es válida. Debe tener el formato DD/MM/AAAA.\n", fechaNacimiento);
        return 1;  // Indica que la fecha no es válida
    }
    // Verificar si el mes y el año son 0 o no se proporcionan
    if (diaNacimiento == 0|| diaNacimiento == ' '||mesNacimiento == 0 || mesNacimiento == ' '|| anoNacimiento == 0|| anoNacimiento == ' ') {
        printf("Error: La fecha de nacimiento \"%s\" no es válida. Mes y año deben ser mayores a 0.\n", fechaNacimiento);
        return 1;  // Indica que la fecha no es válida
    }
    // Calcular la diferencia de años
    int edad = anoActual - anoNacimiento;
    // Verificar si ya cumplió años este año
    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--;
    }
    // Verificar si la edad es menor de 18 años
    return edad < 18 ? 1 : 0;
}



int BuscarUsuarioPorIBAN(TListaUsuarios listaU, int NUsuarios, const char *iban) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].iban, iban) == 0) {
            return i; // Usuario encontrado, devuelve el índice
        }
    }
    return -1; // Usuario no encontrado
}



void ImprimirUsuario(TUsuario *usuario) {
    printf("Nombre: %s %s\n", usuario->nombre.nombre, usuario->nombre.apellido);
    printf("Saldo: %.2f\n", usuario->saldo);
    printf("IBAN: %s\n", usuario->iban);
    printf("Pin: %d\n", usuario->pin);    
    
    Grafico(usuario->tarjeta.a, usuario->tarjeta.b, usuario->tarjeta.c, usuario->tarjeta.d, usuario->tarjeta.mes, usuario->tarjeta.anyo, usuario->tarjeta.cvc, usuario->nombre.nombre, usuario->nombre.apellido);
}




// MODULO PARA GENERAR UN PIN ALEATORIO DE 4 DIGITOS ----------------------
void GenerarPin(TListaUsuarios listaU, int NUsuarios, int *pin) {
    do {
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
        // Verifica si el PIN ya existe en la lista de usuarios
    } while (ExistePinEnLista(listaU, NUsuarios, *pin));
}

int ExistePinEnLista(TListaUsuarios listaU, int NUsuarios, int pin) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (listaU[i].pin == pin) {
            return 1; // El PIN ya existe en la lista
        }
    }
    return 0; // El PIN no existe en la lista
}





// GENERAR EL IBAN DE LA CUENTA ------------------------------------------
void GenerarIban(char iban[], int NUsuarios) {
    strcpy(iban, "ES");
    char numUsuario[4];  // Suponiendo que el número de usuario es de máximo 3 dígitos
    sprintf(numUsuario, "%02d", NUsuarios);
    strcat(iban, numUsuario);
    for (int i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }
    iban[24] = '\0';
}


TTarjeta GenerarTarjeta() {
    TTarjeta tarjeta;

    tarjeta.a = (54 * 100) + (rand() % 100);
    tarjeta.b = rand() % 10000;
    tarjeta.c = rand() % 10000;
    tarjeta.d = rand() % 10000;
    tarjeta.mes = rand() % 11 + 1;
    tarjeta.anyo = 24 + (rand() % 5 + 5);
    tarjeta.cvc = rand() % 1000;

    return tarjeta;
}


int BuscarUsuarioPorTarjeta(TListaUsuarios listaU, int NUsuarios, const TTarjeta *tarjeta) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (memcmp(&(listaU[i].tarjeta), tarjeta, sizeof(TTarjeta)) == 0) {
            return i; // Usuario encontrado, devuelve el índice
        }
    }
    return -1; // Usuario no encontrado
}



void Grafico(int a, int b, int c, int d, int e, int f, int g, char y[], char z[]) {

    Tigr* screen = tigrWindow(220, 350, "Menu ATM", 0);

    TPixel c0 = tigrRGB(0, 0, 55);
    TPixel c1 = tigrRGB(255, 255, 255); // BLANCO

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, c0);

        int cx = screen->w / 2; // centro
        int cy = screen->h / 2; // centro

        // Imprimir el círculo amarillo en la esquina superior derecha
        tigrCircle(screen, screen->w - 30, 30, 20, tigrRGB(255, 255, 0));
        tigrCircle(screen, screen->w - 60, 30, 20, tigrRGB(255, 0, 0));

        // Imprimir mensajes pegados con separación
        char messageYZ[20];
        sprintf(messageYZ, "%s %s", y, z);
        int twYZ = tigrTextWidth(tfont, messageYZ);
        int thYZ = tigrTextHeight(tfont, messageYZ);
        tigrPrint(screen, tfont, 10, cy - thYZ / 2 + 70, c1, messageYZ);

        char messageA[10];
        sprintf(messageA, "%04d", a);
        int twA = tigrTextWidth(tfont, messageA);
        int thA = tigrTextHeight(tfont, messageA);
        tigrPrint(screen, tfont, 10, cy - thA / 2 + 100, c1, messageA);

        char messageB[10];
        sprintf(messageB, "%04d", b);
        int twB = tigrTextWidth(tfont, messageB);
        int thB = tigrTextHeight(tfont, messageB);
        tigrPrint(screen, tfont, 10 + twA + 5, cy - thB / 2 + 100, c1, messageB);

        char messageC[10];
        sprintf(messageC, "%04d", c);
        int twC = tigrTextWidth(tfont, messageC);
        int thC = tigrTextHeight(tfont, messageC);
        tigrPrint(screen, tfont, 10 + twA + twB + 10, cy - thC / 2 + 100, c1, messageC);

        char messageD[10];
        sprintf(messageD, "%04d", d);
        int twD = tigrTextWidth(tfont, messageD);
        int thD = tigrTextHeight(tfont, messageD);
        tigrPrint(screen, tfont, 10 + twA + twB + twC + 15, cy - thD / 2 + 100, c1, messageD);

        char messageE[10];
        sprintf(messageE, "%02d", e);
        int twE = tigrTextWidth(tfont, messageE);
        int thE = tigrTextHeight(tfont, messageE);
        tigrPrint(screen, tfont, 10, cy - thE + 130, c1, messageE);

        char x = '/';
        char messageX[2];
        messageX[0] = x;
        messageX[1] = '\0';
        int twX = tigrTextWidth(tfont, messageX);
        int thX = tigrTextHeight(tfont, messageX);
        tigrPrint(screen, tfont, 10 + twE + 5, cy - thX / 2 + 124, c1, messageX);

        char messageF[10];
        sprintf(messageF, "%02d", f);
        int twF = tigrTextWidth(tfont, messageF);
        int thF = tigrTextHeight(tfont, messageF);
        tigrPrint(screen, tfont, 10 + twE + 5 + twX + 5, cy - thF + 130, c1, messageF);

        char messageG[10];
        sprintf(messageG, "%03d", g);
        int twG = tigrTextWidth(tfont, messageG);
        int thG = tigrTextHeight(tfont, messageG);
        tigrPrint(screen, tfont, 10, cy - thG / 2 + 150, c1, messageG);

        tigrUpdate(screen);
    }

}





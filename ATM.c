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
const char *const rojo = "\033[1;31m";
const char *const azul = "\033[1;34m";
const char *const amarillo = "\033[1;33m";
const char *const blanco = "\033[1;37m";
const char *const naranja = "\033[0;33m";
const char *const verde = "\033[0;32m";
const char *const normal = "\033[0m";
const char *const oculto = "\033[8m";


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
// MODULOS USUARIO SI
int ConsultarUsuario(TListaUsuarios listaU, int NUsuarios, const char *nombre, const char *apellido, int *saldoActualizado);
void Ingreso(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void Retiro(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void Transferencia(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex);
void MostrarHistorialTransacciones(TUsuario *usuario);
// MODULOS USUARIO NO
TId PedirID();
void CrearUsuario(TListaUsuarios listaU, int *NUsuarios);
//AUXILIARES
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios);
void CargarUsuariosDesdeArchivo(TListaUsuarios listaU, int *NUsuarios);
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

    printf("\033[2J");
     
     
    for (int i = 0; i < USUARIO; ++i) {
        listaU[i] = usuario;
    }

    CargarUsuariosDesdeArchivo(listaU, &NUsuarios); //Carga los archivos


    do {
        UsuarioSoN(&a); //Muestra el menu principal
        if (a == 1) {
            char nombre[MAX_NOM];
            char apellido[MAX_NOM];
            int usuarioEncontradoIndex;
            int saldoActualizado;

            printf("\n");
            printf("\t\t %sIntroduzca su nombre:%s ",naranja, normal);
            scanf("%49s", nombre);
            printf("\t\t %sIntroduzca su apellido:%s ", naranja, normal);
            scanf("%49s", apellido);

            usuarioEncontradoIndex = ConsultarUsuario(listaU, NUsuarios, nombre, apellido, &saldoActualizado);

            // Menú de usuario registrado
            if (usuarioEncontradoIndex != -1) {
                do {
                    printf("\n\t\t\t %sSeleccione su operación%s\n", azul, normal);
                    printf("\n");
                    printf("\t\t 1. Ingresar dinero\n");
                    printf("\n");
                    printf("\t\t 2. Retirar dinero\n");
                    printf("\n");
                    printf("\t\t 3. Transferir dinero\n");
                    printf("\n");
                    printf("\t\t 4. Consultar usuario\n");
                    printf("\n");
                    printf("\t\t 5. Mostrar historial de transacciones\n");
                    printf("\n");
                    printf("\t\t Presione 0 para salir\n");
                    printf("\n");
                    printf("\t\t%sOpcion:%s ", blanco, normal);
                    scanf("%d", &usua);
                    printf("\n");

                    switch (usua) {
                        case 1:
                            Ingreso(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 2:
                            Retiro(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 3:
                            Transferencia(listaU, NUsuarios, usuarioEncontradoIndex);
                            break;
                        case 4:
                            ImprimirUsuario(&listaU[usuarioEncontradoIndex]);
                            break;
                        case 5:
                            MostrarHistorialTransacciones(&listaU[usuarioEncontradoIndex]);
                            break;
                        case 0:
                            break;
                        default:
                            printf("\t\t%sOpción no válida%s\n", rojo, normal);
                    }

                    if(usua > 0 && usua <=5){
                        printf("\n");
                        printf("\n\t\t%s ¿Desea realizar otra operación? (s/n):%s ", blanco, normal);
                        scanf(" %c", &continuar);
                        GuardarUsuarios(listaU, NUsuarios);
                        }
                    else{
                        while (getchar() != '\n');
                    };
                    GuardarUsuarios(listaU, NUsuarios);
                } while (continuar == 's' || continuar == 'S');
            } else {
                printf("\t\t%sUsuario no encontrado o PIN incorrecto, compruebe la información ingresada%s\n", rojo, normal);
            }
        } else if (a == 2) {
            // Crear nuevo usuario
            if (NUsuarios < USUARIO) {
                    CrearUsuario(listaU, &NUsuarios);
                    printf("\n");
                GuardarUsuarios(listaU, NUsuarios);
            } else {
                printf("\t\t%sNO HAY MÁS ESPACIO EN MEMORIA.%s\n", rojo, normal);
            }
        }
    } while (a != 0);

     GuardarUsuarios(listaU, NUsuarios);
    printf("\n");
    printf("\t\t %sGracias por usar nuestros servicios%s\n", azul, normal);
    printf("\n");

    return 0;
}


// MODULO DEL MENU PRINCIPAL, DIRECCIONA AL USUARIO SEGUN SI ES O NO ES UN USUARIO
void UsuarioSoN(int *ususn) {
    int ususna;
    printf("\n\t\t\t   %sBienvenido al menú%s\n", azul, normal);
    printf("\n");
    printf("\t\t\t 1. Tengo una cuenta\n");
    printf("\n");
    printf("\t\t\t 2. Crear Usuario\n");
    printf("\n");
    printf("\t\t\t 0. Salir del programa\n");
    printf("\n");
    printf("\t\t%sOpcion:%s  ", blanco, normal);
    scanf("%d", &ususna);

    *ususn = ususna;
}


//CONSULTA EL USUARIO EN LA LISTA DE USUARIOS
int ConsultarUsuario(TListaUsuarios listaU, int NUsuarios, const char *nombre, const char *apellido, int *saldoActualizado) {
    char pinIngresado[PIN_DIGITOS];
    
    for (int i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].nombre.nombre, nombre) == 0 &&
            strcmp(listaU[i].nombre.apellido, apellido) == 0) {
            
            printf("\t\t %sIntroduzca su PIN:%s ", naranja, oculto);
            scanf("%s", pinIngresado);
            printf("%s", normal);

            if (atoi(pinIngresado) == listaU[i].pin && pinIngresado != 0) {
                // Almacena el saldo actualizado
                *saldoActualizado = listaU[i].saldo;
                // Devolver el índice del usuario encontrado
                return i;
            } else {
                printf("\t\t %sPIN incorrecto. Intente nuevamente.%s\n", rojo, normal);
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

    if (usuarioEncontradoIndex != -1) { //Pregunta si existe el usuario
        printf("\n\t\t%sIntroduzca la cantidad de efectivo que desea ingresar: ", blanco);
        printf("\t\tLa cantidad debe ser múltiplo de 5:%s ", normal);
        scanf("%d", &cantidad);

        if (cantidad % 5 == 0) { //El numero debe ser multiplo de 5
            printf("\t\t %s¿Quiere confirmar su transacción? S/N:%s ", blanco, normal);
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

                printf("\n\t\t %sSe han añadido %d euros a la cuenta del usuario. **Nuevo saldo**: %.2f euros%s\n", verde, cantidad, listaU[usuarioEncontradoIndex].saldo, normal);
            } else {
                printf("\n\t\t %sTransacción cancelada%s\n", rojo, normal);
            }
        } else {
            printf("\n\t\t %sTransacción cancelada. La cantidad introducida no es múltiplo de 5%s\n", rojo, normal);
        }
    } else {
        printf("\n\t\t %sUsuario no encontrado. Verifique los datos del usuario.%s\n", rojo, normal);
    }
}



// MODULO PARA RETIRO DE DINERO ---------------------------------------
void Retiro(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex) {
    int cantidad;
    char confirmacion;

    if (usuarioEncontradoIndex != -1) { //Busca si existe el usuario
        printf("\n\t\t %sIntroduzca la cantidad de efectivo que desea retirar: ", blanco);
        printf("\t\t La cantidad debe ser múltiplo de 10:%s ", blanco);
        scanf("%d", &cantidad);

        // Verificar si el saldo es suficiente
        if (cantidad <= listaU[usuarioEncontradoIndex].saldo) {
            if (cantidad % 10 == 0) {
                printf("\t\t %s¿Quiere confirmar su transacción? S/N: %s", blanco, normal);
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
                    printf("\n\t\t %sSe han retirado %d euros de la cuenta del usuario. Nuevo saldo: %.2f euros%s\n", verde, cantidad, listaU[usuarioEncontradoIndex].saldo, normal);
                } else {
                    printf("\n\t\t %sTransacción cancelada%s\n", rojo, normal);
                }
            } else {
                printf("\n\t\t %sTransacción cancelada. La cantidad introducida no es múltiplo de 10%s\n", rojo, normal);
            }
        } else {
            printf("\n\t\t %sTransacción cancelada. Saldo insuficiente%s\n", rojo, normal);
        }
    } else {
        printf("\n\t\t %sUsuario no encontrado. Verifique los datos del usuario.%s\n", rojo, normal);
    }
}



// MODULO DE TRANSFERENCIA ------------------------------------------
void Transferencia(TListaUsuarios listaU, int NUsuarios, int usuarioEncontradoIndex) {
    float cantidad;
    char confirmacion;
    char ibanDestino[IBAN];

    // Limpiar el búfer de entrada antes de solicitar la información
    while (getchar() != '\n');

    printf("\n\t\t %sIntroduzca el IBAN al que desea transferir dinero:%s \n", blanco, normal);
    scanf("%s", ibanDestino);

    // Buscar el usuario destino en la lista
    int indiceDestino = BuscarUsuarioPorIBAN(listaU, NUsuarios, ibanDestino);

    if (indiceDestino != -1) { //Revisa si existe el IBAN
        if (usuarioEncontradoIndex != indiceDestino) {
            printf("\t\t %sIntroduzca la cantidad de dinero que desea transferir\n", blanco);
            printf("\t\t Puede incluir centavos%s\n", normal);
            scanf("%f", &cantidad);

            // Verificar si el saldo es suficiente
            if (cantidad <= listaU[usuarioEncontradoIndex].saldo) {
                printf("\t\t %s¿Quiere confirmar su transacción? S/N: %s", blanco, normal);
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

                    printf("\n\t\t %sSe han transferido %.2f euros de %s a %s.%s\n", verde, cantidad, listaU[usuarioEncontradoIndex].nombre.nombre, listaU[indiceDestino].nombre.nombre, normal);
                } else {
                    printf("\n\t\t %sTransacción cancelada%s\n", rojo, normal);
                }
            } else {
                printf("\n\t\t %sTransacción cancelada. Saldo insuficiente%s\n", rojo, normal);
            }
        } else {
            printf("\n\t\t %sTransacción cancelada. No puedes transferir dinero a la misma cuenta%s\n", rojo, normal);
        }
    } else {
        printf("\n\t\t %sUsuario destino con IBAN %s no encontrado. Verifique el IBAN e intente nuevamente.%s\n", rojo, ibanDestino, normal);
    }
}


//MUESTRA EL HISTORIAL DE TRANSACCIONES QUE HA REALIZADO EL USUARIO
void MostrarHistorialTransacciones(TUsuario *usuario) {
    printf("\n\t\t\t %sHistorial de Transacciones:%s\n", azul, normal);
    for (int i = 0; i < usuario->numTransacciones; ++i) { //Verifica para que usuario se pide el historial
        printf("Transacción %d: %.2f euros - Tipo: %c - Fecha: %s - Hora: %s:%s\n",
               i + 1,
               usuario->transacciones[i].monto,
               usuario->transacciones[i].tipo,
               usuario->transacciones[i].fecha,
               usuario->transacciones[i].hora,
               usuario->transacciones[i].minuto);
    }
}


//IMPRIME LOS DATOS DEL USUARIO E IMPRIME LA TARJETA DEL MISMO HECHA CON LA LIBRERIA TIGR
void ImprimirUsuario(TUsuario *usuario) {
    printf("\t\t Nombre: %s %s\n", usuario->nombre.nombre, usuario->nombre.apellido);
    printf("\t\t Saldo: %.2f\n", usuario->saldo);
    printf("\t\t IBAN: %s\n", usuario->iban);
    printf("\t\t Pin: %d\n", usuario->pin);    
    
    Grafico(usuario->tarjeta.a, usuario->tarjeta.b, usuario->tarjeta.c, usuario->tarjeta.d, usuario->tarjeta.mes, usuario->tarjeta.anyo, usuario->tarjeta.cvc, usuario->nombre.nombre, usuario->nombre.apellido);
}





//MODULO PARA PEDIRLE AL USUARIO SUS DATOS
TId PedirID() {
    TId persona;
    printf("\n");
    printf("\t\t %s*Introduzca su nombre (Únicamente el primer nombre):%s ", amarillo, normal);
    scanf("%s", persona.nombre);
    printf("\t\t %s*Introduzca su apellido (Únicamente el primer apellido):%s ", amarillo, normal);
    scanf("%s", persona.apellido);
    // Solicitar número de identificación (puede contener letras o números)
    printf("\t\t %s*Introduzca su número de identificación:%s ", amarillo, normal);
    scanf("%s", persona.identificacion);

    return persona;
}



// MODULO DE CREAR USUARIO ----------------------------------------
void CrearUsuario(TListaUsuarios listaU, int *NUsuarios) { 
    TId fechaNacimiento;
    int esMenor, i;

    listaU[*NUsuarios].nombre = PedirID();

    // Verificar si la identificación ya existe en la lista
    for (i = 0; i < *NUsuarios; ++i) {
        if (strcmp(listaU[i].nombre.identificacion, listaU[*NUsuarios].nombre.identificacion) == 0) {
            printf("\n\t\t %sYa existe un usuario con esta identificación. Intente nuevamente.%s\n", rojo, normal);
            break;
        }
    }

    // Si no se encuentra una identificación duplicada, continuar con la creación del usuario
    if (i == *NUsuarios) {
        // Pedir fecha de nacimiento
        printf("\t\t %sIntroduzca su fecha de nacimiento (DD/MM/AAAA):%s ", amarillo, normal);
        scanf("%s", listaU[*NUsuarios].fechaNacimiento);
        printf("\n");
        // Verificar si el usuario es menor de edad
        esMenor = EsMenorDeEdad(listaU[*NUsuarios].fechaNacimiento);
        if (esMenor) {
            printf("\n\t\t %sLo siento, no puedes crear una cuenta porque eres menor de edad o la fecha no es válida.%s\n", rojo, normal);
            // Puedes agregar aquí cualquier código adicional necesario si el usuario es menor
        } else {
            // Continuar con la creación del usuario
            GenerarPin(listaU, *NUsuarios, &listaU[*NUsuarios].pin);
            GenerarIban(listaU[*NUsuarios].iban, *NUsuarios);
            listaU[*NUsuarios].saldo = 0.0;

            listaU[*NUsuarios].tarjeta = GenerarTarjeta();

            printf("\n\t\t %sUsuario creado exitosamente:%s\n", blanco, normal);
            ImprimirUsuario(&listaU[*NUsuarios]);
            (*NUsuarios)++;
        }
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




// MODULO PARA GUARDAR USUARIOS EN UN ARCHIVO ---------------------
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios) {
    FILE *archivo;
    archivo = fopen("DATOSCAJERO.txt", "w");

    if (archivo == NULL) {
        printf("\n\t\t %sError al abrir el archivo para escritura.%s\n", rojo, normal);
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
        printf("\n\t\t %sEl archivo DATOSCAJERO.txt no existe. No se cargaron usuarios.%s\n", rojo, normal);
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
        printf("\n\t\t %sError: La fecha de nacimiento \"%s\" no es válida. Debe tener el formato DD/MM/AAAA.%s\n", rojo, fechaNacimiento, normal);
        return 1;  // Indica que la fecha no es válida
    }
    // Verificar si el mes y el año son 0 o no se proporcionan
    if (diaNacimiento == 0|| diaNacimiento == ' '||mesNacimiento == 0 || mesNacimiento == ' '|| anoNacimiento == 0|| anoNacimiento == ' ') {
        printf("\n\t\t %sError: La fecha de nacimiento \"%s\" no es válida. Mes y año deben ser mayores a 0.%s\n", rojo, fechaNacimiento, normal);
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


//BUSCA DENTRO DE LA LISTA DE USUARIOS EL IBAN QUE CORRESPONDA
int BuscarUsuarioPorIBAN(TListaUsuarios listaU, int NUsuarios, const char *iban) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].iban, iban) == 0) {
            return i; // Usuario encontrado, devuelve el índice
        }
    }
    return -1; // Usuario no encontrado
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


//VERIFICA QUE OTRO USUARIO NO TENGA EL MISMO PIN
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
    strcpy(iban, "ES"); //Para un IBAN español
    char numUsuario[4];  
    sprintf(numUsuario, "%02d", NUsuarios);
    strcat(iban, numUsuario);
    for (int i = 4; i < 24; ++i) {
        iban[i] = '0' + rand() % 10;
    }
    iban[24] = '\0';
}


//GENERA LA TARJETA DEL USUARIO
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



//BUSCA LA TARJETA ASOCIADA AL USUARIO
int BuscarUsuarioPorTarjeta(TListaUsuarios listaU, int NUsuarios, const TTarjeta *tarjeta) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (memcmp(&(listaU[i].tarjeta), tarjeta, sizeof(TTarjeta)) == 0) {
            return i; // Usuario encontrado, devuelve el índice
        }
    }
    return -1; // Usuario no encontrado
}


//LIBRERIA TIGR, MUESTRA LA TARJETA DE DEBITO DEL USUARIO
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







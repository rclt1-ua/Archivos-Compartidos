//BIBLIOTECAS------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

//CONSTANTES------------------------------------------------------------------------
#define NOMUS_LETRAS 15
#define NOMUS_NUMEROS 3
#define MAX_NOM 50
#define PIN_DIGITOS 4
#define IBAN 26
#define MAX_TRANSACCIONES 100
#define USUARIO 50

//ESTRUCTURAS Y TIPOS DE DATOS------------------------------------------------------------------------
typedef char TCadenaNA[MAX_NOM];

typedef struct {
    TCadenaNA nombre;
    TCadenaNA apellido;
    char identificacion[MAX_NOM];  // Agregado para el número de identificación
} TId;

typedef struct {
    char letras[NOMUS_LETRAS + 1];
    int numeros;
} TNombreUsuario;

typedef struct {
    TNombreUsuario nomUs;
    int pin;
} TDatos;

typedef struct {
    float monto;
    char tipo;
    char fecha[11];
    char hora[9];
    char minuto[3]; // Nuevo campo para los minutos
} TTransaccion;

typedef struct {
    TId nombre;
    TDatos usuario;
    float saldo;
    char iban[IBAN];
    char fechaNacimiento[11];
    TTransaccion transacciones[MAX_TRANSACCIONES];
    int numTransacciones;
} TUsuario;

typedef TUsuario TListaUsuarios[USUARIO];

//DECLARACION DE MODULOS ------------------------------------------------------------------------
TId PedirID();
int GenerarNumeroAleatorio();
int EsMenorDeEdad(const char *fechaNacimiento);
int BuscarUsuarioPorIBAN(TListaUsuarios listaU, int NUsuarios, const char *iban);
void UsuarioSoN(int *ususn);
void ConsultarUsuario(TListaUsuarios listaU, int NUsuarios);
void GenerarNomUs(TId nombre, TNombreUsuario *nomUs, int idUnico);
void CrearUsuario(TListaUsuarios listaU, int *NUsuarios);
void GenerarPin(int *pin);
void GenerarIban(char iban[], int NUsuarios);
void Ingreso(TUsuario *listaU, int NUsuarios);
void Retiro(TUsuario *listaU, int NUsuarios);
void Transferencia(TUsuario *listaU, int NUsuarios);
void ImprimirUsuario(TUsuario *usuario);
void MostrarHistorialTransacciones(TUsuario *usuario);
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios);
void CargarUsuarios(TListaUsuarios listaU, int *NUsuarios);






//MODULOS------------------------------------------------------------------------
//MAIN
int main() {
    TUsuario usuario;
    int a, usua;
    int NUsuarios = 0;
    TListaUsuarios listaU;

    // Inicializar la lista de usuarios
    for (int i = 0; i < USUARIO; ++i) {
        listaU[i] = usuario;
    }


    do {
        UsuarioSoN(&a);
        if (a == 1) {
            // Menú de usuario registrado
            printf("Seleccione su operación\n");
            printf("1. Ingresar dinero\n");
            printf("2. Retirar dinero\n");
            printf("3. Consultar usuario\n");
            printf("4. Transferir dinero\n");
            printf("5. Mostrar historial de transacciones\n");
            printf("Presione 0 para salir\n");
            scanf("%d", &usua);

            switch (usua) {
                case 1:
                    Ingreso(listaU, NUsuarios);
                    break;
                case 2:
                    Retiro(listaU, NUsuarios);
                    break;
                case 3:
                    ConsultarUsuario(listaU, NUsuarios);
                    break;
                case 4:
                    Transferencia(listaU, NUsuarios);
                    break;
                case 5:
                    MostrarHistorialTransacciones(&listaU[0]);
                    break;
                default:
                    printf("Opción no válida\n");
            }
        } else if (a == 2) {
            // Crear nuevo usuario
            if (NUsuarios < USUARIO) {
                do {
                    CrearUsuario(listaU, &NUsuarios);
                    // Agregar una pausa antes de volver a preguntar si el usuario quiere crear otro
                    printf("\nPresione Enter para crear otro usuario o 0 para salir...");
                    while (getchar() != '\n'); // Limpiar el buffer de entrada
                    UsuarioSoN(&a);
                } while (a == 2);
            } else {
                printf("NO HAY MÁS ESPACIO EN MEMORIA.\n");
            }
        }

    } while (a != 0);

    printf("Gracias por usar nuestros servicios\n");

    return 0;
}



// MODULOS------------------------------------------------------------------------
// MODULO DE MENU///////////////////////////////////////
void UsuarioSoN(int *ususn) {
    int ususna;
    printf("Bienvenido al menú\n");
    printf("1. Tengo una cuenta\n");
    printf("2. Crear Usuario\n");
    printf("0. Salir del programa\n");
    scanf("%d", &ususna);
    *ususn = ususna;
}

//MODULOS DE USUARIO NO//////////////////////////////////////////////////
//MODULO DE CREAR USUARIO
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
            printf("\t*Introduzca su fecha de nacimiento (DD/MM/AAAA): ");
            scanf("%s", listaU[*NUsuarios].fechaNacimiento);

            // Verificar si el usuario es menor de edad
            esMenor = EsMenorDeEdad(listaU[*NUsuarios].fechaNacimiento);
            if (esMenor) {
                printf("Lo siento, no puedes crear una cuenta porque eres menor de edad o la fecha no es válida.\n");
                // Puedes agregar aquí cualquier código adicional necesario si el usuario es menor
            } else {
                // Continuar con la creación del usuario
                GenerarPin(&listaU[*NUsuarios].usuario.pin);
                GenerarIban(listaU[*NUsuarios].iban, *NUsuarios);
                listaU[*NUsuarios].saldo = 0.0;

                // Añadir dos números aleatorios al nombre de usuario
                int numero1 = GenerarNumeroAleatorio();
                int numero2 = GenerarNumeroAleatorio();
                char numerosAleatorios[5];
                sprintf(numerosAleatorios, "%d%d", numero1, numero2);

                // Concatenar los números aleatorios directamente al nombre de usuario
                strcat(listaU[*NUsuarios].usuario.nomUs.letras, numerosAleatorios);

                printf("Usuario creado exitosamente:\n");
                ImprimirUsuario(&listaU[*NUsuarios]);

                (*NUsuarios)++;
            }
        }
    ;
}



// MODULO PARA PEDIR NOMBRE Y APELLIDO
TId PedirID() {
    TId persona;
    printf("\t*Introduzca su nombre: ");
    scanf("%s", persona.nombre);
    printf("\t*Introduzca su apellido: ");
    scanf("%s", persona.apellido);

    // Solicitar número de identificación (puede contener letras o números)
    printf("\t*Introduzca su número de identificación: ");
    scanf("%s", persona.identificacion);

    return persona;
}



// MODULO PARA GENERAR NOMBRE DE USUARIO
void GenerarNomUs(TId nombre, TNombreUsuario *nomUs, int idUnico) {
    // Tomar las seis primeras letras del nombre
    strncpy(nomUs->letras, nombre.nombre, NOMUS_LETRAS);
    nomUs->letras[NOMUS_LETRAS] = '\0'; // Añadir el carácter nulo al final
    // Concatenar un número aleatorio y un identificador único
    nomUs->numeros = rand() % 1000 + idUnico;
}



// MODULO PARA GENERAR UN PIN ALEATORIO DE 4 DIGITOS
void GenerarPin(int *pin) {
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



//GENERAR EL IBAN DE LA CUENTA
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



//MODULOS DE USUARIO SI//////////////////////////////////////////////////
// MODULO PARA INGRESO DE DINERO
void Ingreso(TUsuario *listaU, int NUsuarios) {
    int cantidad;
    char confirmacion;
    char ibanDestino[IBAN];

    printf("Introduzca el IBAN al que desea ingresar dinero: ");
    scanf("%s", ibanDestino);

    // Buscar el usuario en la lista
    int i;
    for (i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].iban, ibanDestino) == 0) {
            break;
        }
    }

    if (i < NUsuarios) {
        printf("Introduzca la cantidad de efectivo que desea ingresar\n");
        printf("La cantidad debe ser múltiplo de 5\n");
        scanf("%d", &cantidad);

        if (cantidad % 5 == 0) {
            printf("¿Quiere confirmar su transacción? S/N: ");
            scanf(" %c", &confirmacion);

            if (confirmacion == 'S' || confirmacion == 's') {
                // Crear una nueva transacción de ingreso
                listaU[i].transacciones[listaU[i].numTransacciones].monto = cantidad;
                listaU[i].transacciones[listaU[i].numTransacciones].tipo = 'I'; // Ingreso
                // Ajustar la fecha y hora según sea necesario
                // Incrementar el número de transacciones
                listaU[i].numTransacciones++;

                // Actualizar el saldo del usuario
                listaU[i].saldo += cantidad;

                printf("Se han añadido %d euros al usuario con IBAN %s. \n\t **Nuevo saldo**: %.2f euros\n", cantidad, ibanDestino, listaU[i].saldo);
            } else {
                printf("Transacción cancelada\n");
            }
        } else {
            printf("Transacción cancelada. La cantidad introducida no es múltiplo de 5\n");
        }
    } else {
        printf("Usuario con IBAN %s no encontrado. Verifique el IBAN e intente nuevamente.\n", ibanDestino);
    }
}



// MODULO PARA RETIRO DE DINERO
void Retiro(TUsuario *listaU, int NUsuarios) {
    int cantidad;
    char confirmacion;
    char nomUsuario[NOMUS_LETRAS + 4];  // Se ajusta la longitud para el nombre de usuario

    // Limpiar el búfer de entrada antes de solicitar la información
    while (getchar() != '\n');

    printf("Introduzca su nombre de usuario: ");
    scanf("%s", nomUsuario);

    // Buscar el usuario en la lista
    int i;
    for (i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].usuario.nomUs.letras, nomUsuario) == 0 &&
            listaU[i].usuario.nomUs.numeros == atoi(nomUsuario + NOMUS_LETRAS)) {
            printf("Introduzca la cantidad de efectivo que desea retirar\n");
            printf("La cantidad debe ser múltiplo de 10\n");
            scanf("%d", &cantidad);

            // Verificar si el saldo es suficiente
            if (cantidad <= listaU[i].saldo) {
                if (cantidad % 10 == 0) {
                    printf("¿Quiere confirmar su transacción? S/N: ");
                    scanf(" %c", &confirmacion);

                    if (confirmacion == 'S' || confirmacion == 's') {
                        // Crear una nueva transacción de retiro
                        listaU[i].transacciones[listaU[i].numTransacciones].monto = -cantidad;
                        listaU[i].transacciones[listaU[i].numTransacciones].tipo = 'R'; // Retiro
                        // Ajustar la fecha y hora según sea necesario
                        // Incrementar el número de transacciones
                        listaU[i].numTransacciones++;

                        // Actualizar el saldo del usuario
                        listaU[i].saldo -= cantidad;

                        printf("Se han retirado %d euros al usuario. Nuevo saldo: %.2f euros\n", cantidad, listaU[i].saldo);
                    } else {
                        printf("Transacción cancelada\n");
                    }
                } else {
                    printf("Transacción cancelada. La cantidad introducida no es múltiplo de 10\n");
                }
            } else {
                printf("Transacción cancelada. Saldo insuficiente\n");
            }
            break;  // Romper el bucle después de encontrar al usuario
        }
    }

    if (i == NUsuarios) {
        printf("Usuario no encontrado. Verifique el nombre de usuario e intente nuevamente.\n");
    }
}



//MODULO TRANSFERENCIA
void Transferencia(TUsuario *listaU, int NUsuarios) {
    int cantidad;
    char confirmacion;
    char ibanDestino[IBAN];

    // Limpiar el búfer de entrada antes de solicitar la información
    while (getchar() != '\n');

    printf("Introduzca su IBAN (origen): ");
    scanf("%s", ibanDestino);

    // Buscar el usuario en la lista
    int indiceOrigen = BuscarUsuarioPorIBAN(listaU, NUsuarios, ibanDestino);

    if (indiceOrigen != -1) {
        printf("Introduzca el IBAN al que desea transferir dinero: ");
        scanf("%s", ibanDestino);

        // Buscar el usuario destino en la lista
        int indiceDestino = BuscarUsuarioPorIBAN(listaU, NUsuarios, ibanDestino);

        if (indiceDestino != -1) {
            if (indiceOrigen != indiceDestino) {
                printf("Introduzca la cantidad de dinero que desea transferir\n");
                printf("Puede incluir centavos (por ejemplo, 50.75)\n");
                scanf("%d", &cantidad);

                // Verificar si el saldo es suficiente
                if (cantidad <= listaU[indiceOrigen].saldo) {
                    printf("¿Quiere confirmar su transacción? S/N: ");
                    scanf(" %c", &confirmacion);

                    if (confirmacion == 'S' || confirmacion == 's') {
                        // Crear una nueva transacción de transferencia (salida)
                        listaU[indiceOrigen].transacciones[listaU[indiceOrigen].numTransacciones].monto = -cantidad;
                        listaU[indiceOrigen].transacciones[listaU[indiceOrigen].numTransacciones].tipo = 'T'; // Transferencia
                        // Ajustar la fecha y hora según sea necesario
                        // Incrementar el número de transacciones
                        listaU[indiceOrigen].numTransacciones++;

                        // Actualizar el saldo del usuario de origen
                        listaU[indiceOrigen].saldo -= cantidad;

                        // Crear una nueva transacción de transferencia (entrada)
                        listaU[indiceDestino].transacciones[listaU[indiceDestino].numTransacciones].monto = cantidad;
                        listaU[indiceDestino].transacciones[listaU[indiceDestino].numTransacciones].tipo = 'T'; // Transferencia
                        // Ajustar la fecha y hora según sea necesario
                        // Incrementar el número de transacciones
                        listaU[indiceDestino].numTransacciones++;

                        // Actualizar el saldo del usuario de destino
                        listaU[indiceDestino].saldo += cantidad;

                        printf("Se han transferido %d euros de %s a %s.\n", cantidad, listaU[indiceOrigen].nombre.nombre, listaU[indiceDestino].nombre.nombre);
                    } else {
                        printf("Transacción cancelada\n");
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
    } else {
        printf("Usuario origen con IBAN %s no encontrado. Verifique el IBAN e intente nuevamente.\n", ibanDestino);
    }
}



// MODULO PARA IMPRIMIR DATOS DE UN USUARIO
void ImprimirUsuario(TUsuario *usuario) {
    printf("Nombre: %s %s\n", usuario->nombre.nombre, usuario->nombre.apellido);
    printf("Nombre de usuario: %s\n", usuario->usuario.nomUs.letras);
    printf("PIN: %04d\n", usuario->usuario.pin);  // Usar %04d para imprimir el PIN con ceros a la izquierda
    printf("Saldo: %.2f\n", usuario->saldo);
    printf("IBAN: %s\n", usuario->iban);
}



// MODULO PARA MOSTRAR EL HISTORIAL DE TRANSACCIONES
void MostrarHistorialTransacciones(TUsuario *usuario) {
    printf("Historial de Transacciones:\n");
    for (int i = 0; i < usuario->numTransacciones; ++i) {
        printf("Transacción %d: %.2f euros\n", i + 1, usuario->transacciones[i].monto);
    }
}



//MODULOS DE AUXILIARES/////////////////////////////////////////////////
//MODULO PARA VERIFICAR MAYORIA DE EDAD
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



// FUNCION PARA GENERAR UN NUMERO ALEATORIO DE DOS CIFRAS
int GenerarNumeroAleatorio() {
    return rand() % 100;
}



//BUSCAR USUARIO POR IBAN
int BuscarUsuarioPorIBAN(TListaUsuarios listaU, int NUsuarios, const char *iban) {
    for (int i = 0; i < NUsuarios; ++i) {
        if (strcmp(listaU[i].iban, iban) == 0) {
            return i; // Usuario encontrado, devuelve el índice
        }
    }
    return -1; // Usuario no encontrado
}


//CONSULTAR USUARIO
void ConsultarUsuario(TListaUsuarios listaU, int NUsuarios) {
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
            ImprimirUsuario(&listaU[i]);
            return;
        }
    }

    // Si no se encuentra el usuario, mostrar un mensaje
    printf("Usuario no encontrado. Verifique sus datos e intente nuevamente.\n");
}

// MODULO PARA GUARDAR USUARIOS EN UN ARCHIVO
void GuardarUsuarios(TListaUsuarios listaU, int NUsuarios) {
    FILE *archivo;
    archivo = fopen("DATOSCAJERO.txt", "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    for (int i = 0; i < NUsuarios; ++i) {
        fprintf(archivo, "%s %s %d %.2f %s %s %d\n",
                listaU[i].iban,
                listaU[i].usuario.nomUs.letras,
                listaU[i].usuario.nomUs.numeros,
                listaU[i].saldo,
                listaU[i].nombre.nombre,
                listaU[i].nombre.apellido,
                listaU[i].usuario.pin);
        fprintf(archivo, "\n");
    }

    fclose(archivo);
}

// MODULO PARA CARGAR USUARIOS DESDE UN ARCHIVO
void CargarUsuarios(TListaUsuarios listaU, int *NUsuarios) {
    FILE *archivo;
    archivo = fopen("DATOSCAJERO.txt", "r");

    if (archivo == NULL) {
        printf("El archivo DATOSCAJERO.txt no existe. No se cargaron usuarios.\n");
        return;
    }

    while (fscanf(archivo, "%s %s %d %f %s %s %d",
                   listaU[*NUsuarios].iban,
                   listaU[*NUsuarios].usuario.nomUs.letras,
                   &listaU[*NUsuarios].usuario.nomUs.numeros,
                   &listaU[*NUsuarios].saldo,
                   listaU[*NUsuarios].nombre.nombre,
                   listaU[*NUsuarios].nombre.apellido,
                   &listaU[*NUsuarios].usuario.pin) == 7) {
        // Incrementar el número de transacciones
        int numTransacciones;
        fscanf(archivo, "%d", &numTransacciones);

        // Cargar transacciones
        for (int i = 0; i < numTransacciones; ++i) {
            fscanf(archivo, "%f %c %s %s",
                   &listaU[*NUsuarios].transacciones[i].monto,
                   &listaU[*NUsuarios].transacciones[i].tipo,
                   listaU[*NUsuarios].transacciones[i].fecha,
                   listaU[*NUsuarios].transacciones[i].hora);
        }

        // Asignar el número de transacciones cargadas
        listaU[*NUsuarios].numTransacciones = numTransacciones;

        (*NUsuarios)++;
    }

    fclose(archivo);
}

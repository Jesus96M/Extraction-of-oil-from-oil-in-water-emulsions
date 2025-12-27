#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////
//////// DEFINICIONES PARA GENERACION N ALEATORIO ////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned long long randint;
// typedef double randreal;
#define TWOBRMINUS1   18446744073709551615ULL //2^64 - 1
#define TWOBR         18446744073709551616.   //2^64
#define TWOBRM1       9223372036854775808ULL  //2^63
#define FNORM (5.4210108624275218e-20)// max double such that RAND_MAX*NORMF<1
#define CGRANDOM  ( zseed=zseed*3202034522624059733LLU+1)
#define PRRANDOM  ( (ira[ip++]=ira[ip1++]+ira[ip2++]) ^ira[ip3++] )
// #define MYRANDOM   PRRANDOM                         // P-R generator
#define MYRANDOM   CGRANDOM                       // Congruential generator
#define HIRANDOM  ((randint) (PRRANDOM + CGRANDOM)) //Addition of both
#define FRANDOM (FNORM*MYRANDOM)   //A floating point, 0<=pseudo-random<1
#define CGFRANDOM (FNORM*CGRANDOM)   //A floating point, 0<=pseudo-random<1
#define FHIRANDOM (FNORM*HIRANDOM) //A floating point, 0<=pseudo-random<1
randint zseed;
//////////////////////////////////////////////////////////

#define N Lx*Ly //Numero de celdas total
//#define Nmed (Lx*Ly*10)// Cada cuantos pasos mido.
//#define Npasos (Nmed*(5000UL)) // Numero de pasos que da la cadena SI ES LONG
//#define Npasos (Lx*Ly*25000) // Numero de pasos que da la cadena
#define beta 1.0/T
//#define Np (5*Lx*Ly-2*Ly-2*Lx)//Numero de parejas que se pueden proponer para saltos
#define PI 3.14159265358979323846// PI


// VARIABLES GLOBALES
// VARIABLES QUE SE LEEN DE ARCHIVO DE ENTRADA
int Lx, Ly;// Dimensiones del sistema Crece en la direccion x
int restart;// 0 desde el principio. 1 lee un archivo externo
// 1 es el agua y 2 el aceite
double T, A1, A2;// Temperatura y constantes de Hamaker
double J1, J2, J12;//
//
double J1_diag, J2_diag, J12_diag;
double per;//percent of oil in the mix
double density;//densidad de aceite en el total
double rho_r;
double gravity;
double k1,k2;//Interaccion con fuerza externa
int nDroplets;//num de gotas de aceite incialmente
double alpha;
double lambda;
double por;//porcentaje de valor de U desconectado
long Nmed;// Cada cuanto mido
long Nsteps;// Numero de pasos


int numeroCeldasAgua;
int numeroCeldasAceite;
int numeroCeldasAire;

// PUNTEROS PARA LOS QUE HAY QUE RESERVAR MEMORIA
int* C;// valores de las celdas 1=agua 2=aceite
int* r;//vecino derecho
int* l;//vecino izquierdo
int* u;//vecino arriba
int* d;//vecino abajo
int* conectado;//vector que dice si esta (1) o no (0) conectado a la componente principal

int* vecinosArevisar;//lista de vecinos necesaria revisar
int longitudVecinos;//longitud efectiva de lo de arriba

double* alturaMedia;//altura para la media movil
int* alturas;

int* pos_inicial;// Posicion de las gotas de aceite incialmente


int tamanhoDroplets;// Tamanho de las gotas

int x_inicial;
int y_inicial;

double* distanciaEuclideas;
int* indicesDistancias;

long k;//paso del MC
int porce;//medida hecha
// UTILES VARIOS COMODINES

int i,j,kk; // indices
int ind1,ind2;//indices de la propuesta de cambio
int numeroVecinosIndice1Agua;
int numeroVecinosIndice1Aceite;
int numeroVecinosIndice2Agua;
int numeroVecinosIndice2Aceite;
// Vec extra diagonales
int numeroVecinosDiagIndice1Agua;
int numeroVecinosDiagIndice1Aceite;
int numeroVecinosDiagIndice2Agua;
int numeroVecinosDiagIndice2Aceite;
int x_droplet;//Inciio del droplet (varia)

bool aceite5medidoQ;
bool aceite10medidoQ;
bool aceite15medidoQ;
bool aceite20medidoQ;
bool aceite25medidoQ;
bool aceite30medidoQ;
bool aceite35medidoQ;
bool aceite40medidoQ;
bool aceite45medidoQ;
bool aceite50medidoQ;
bool aceiteExtracionmedidoQ;

double aleatorio;
double probabilidad;
// Archivos de salida del sistema
char nombre[50];
FILE *fp;//archivo para leer condiciones.dat
FILE *fp2;
FILE *fp3;//para escribir distancias
FILE *fp4;
FILE *fp5;
FILE *fp6;
FILE *fp7;
FILE *fp8;
FILE *fp9;
char texto[200];//comodin para leer la primera linea
//FILE *fp1;

randint sem;//Semilla leida

// Declaracion de las funciones
void semilla();
void vecinos();
void condicionesIniciales();
void reservaMemoria();
void descripcion();
void configuracion2(int);
void configuracionConectados2(int );
int eligeVecino(int);
void calculaVecinos(int,int);
//
void calculaVecinosDiag(int,int);

//
int piso(int);
int getZ(int);
int getX(int);
double calculaProbabilidad(int,int);
void cambio(int,int);
bool algunVecinoConectadoQ(int);
bool estaraConectadoQ(int,int);
double distanciaEuclidea(int,int);
void calculaDistancias(int);
void ordenaDistancias();
void midePosicionesDistancias();
void mideBordeGota();
void revisaConectados();
void mideSuperficie();
void abreArchivos();
void cierraArchivos();
void calculaInicioDroplet();
bool conectadoGotaQ(int);
void mideExtraccionAceite();
void mideExtraccionAceite2();
void midePorcentajeAceiteEnGota();

void anadirVecino(int );
void quitarVecino(int );
bool perteneceVecinoQ(int );
void revisaVecinosDeCelda(int );
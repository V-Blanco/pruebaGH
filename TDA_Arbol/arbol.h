#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK     1
#define SIN_MEM     0
#define ARBOL_VACIO 0
#define DUPLICADO   0
#define NO_EXISTE   0
#define ERROR_ARCH  -1

typedef struct sNodo{
    void*dato;
    unsigned tamDato;
    struct sNodo*izq,
                *der;
}tNodo;

typedef tNodo*tArbol;

typedef struct{
    int clave,
        pos;
}tIdxIntPos;

typedef struct{
    int clave;
    char nombre[31];
    int stock;
}tVerdura;

typedef void(*Accion)(void*dato);
typedef void(*AccionConParam)(void*dato,void*param);
typedef int(*Cmp)(const void*e1,const void*e2);

typedef int(*LeerIndice)(FILE*pa,void*indice,int pos);
typedef int(*LeerArch)(FILE*pa,void*reg);
typedef void(*AccionParaGrafico)(void*dato,unsigned n);

void crearArbol(tArbol*p);
int arbolVacio(const tArbol*p);
int insertarEnOrden(tArbol*p,const void*dato,unsigned tamDato,Cmp cmp);
int insertarEnOrden_recursivo(tArbol*pa,const void*dato,unsigned tamDato,Cmp cmp);

void recorrerEnOrden(const tArbol*p,void*param,AccionConParam accion);
void recorrerPreOrden(const tArbol*p,void*param,AccionConParam accion);
void recorrerPostOrden(const tArbol*p,Accion accion);
void recorrerEnOrdenInverso(const tArbol*p,Accion accion);

void recorrerNodosDeNivel(tArbol*p,int nivel,Accion accion);
void recorrerNodosHastaNivel(tArbol*p,int nivel,Accion accion);
void recorrerNodosDesdeNivel(tArbol*p,int nivel,Accion accion);

tArbol* buscarNodoEnArbolOrdenado(tArbol*pa,const void*clave,Cmp cmp);
tArbol* mayorNodoArbol(tArbol*pa);
tArbol* menorNodoArbol(tArbol*pa);
const tArbol* buscarMayorNoClave(const tArbol* p, void* dato, unsigned tamDato, Cmp cmp);

int contarNodos(const tArbol*pa);
int contarHojas(const tArbol*pa);
int contarNoHojas(const tArbol*pa);
int contarNodosConHijosPorIzq(const tArbol*pa);
void mostrarHojas(const tArbol*pa);
void mostrarNoHojas(const tArbol*pa);

void eliminarArbol(tArbol*pa);
int eliminarNodo(tArbol*pa,void*datoAEliminar,unsigned tamDato,Cmp cmp);
int eliminarYContarHoja(tArbol*pa);
int eliminarArbolYcontarnodo(tArbol*pa);
void eliminarHojas(tArbol*pa);
int eliminarMenorHoja(tArbol*pa,void*dato,unsigned tamDato,Cmp cmp);

int leerArbolDeArchivoBin(tArbol*arbol,const char*nomArch,unsigned tamDAto,Cmp cmp);
int leerArbolDeArchivoTxt(tArbol*arbol,const char*nomArch,unsigned tamDAto,LeerArch leer,Cmp cmp);

int leerIndiceDeArchTxt(tArbol*pa,const char*nomArch,unsigned tamDato,LeerIndice leer,Cmp cmp);

void balancearArbol(FILE* archivo,tArbol* arbol,int ini,int fin,unsigned tamDato,LeerArch leer,Cmp cmp);
void balancearArbolDesdeArchivoOrdenado(tArbol* arbol,const char* nomArch,unsigned tamDato,LeerArch leer,Cmp cmp);
///el archivo tiene que estar ordenado y ser Binario

void mostrarArbolComoGrafico_r(tArbol*pa,unsigned n,AccionParaGrafico accion);

int alturaArbol(tArbol*pa);
int arbolCompleto(const tArbol*pa);
//int arbolCompleto2(const tArbol*pa);
int arbolCompletoHastaNivel(const tArbol*pa,int n);
//int arbolBalanceado(const tArbol*pa);
//int arbolBalanceado2(const tArbol*pa);
int arbolAVL(const tArbol*pa);

//NO PRIMITIVAS
void mostrarInt(void*dato);
void mostrarInt2(void*e,void*b);
void mostrarIdxComoGrafico(void*dato,unsigned n);
void multiplicarPorN(void*elem,void*n); //map
void grabarIntEnTxt(void*dato,void*param);
int cmpInt(const void*e1,const void*e2);
int cmpIdx(const void*e1,const void*e2);
void mostratIdx(void*e,void*b);
void grabarIdxEnArchivo(void*a,void*b);
int leerIdxClaPosVerdura(FILE*pa,void*indice,int pos);
int leerIdxIntPosDeArchBin(FILE*pa,void*reg);

//podar arbol_ hasta un nivel
//arbol completo, balanceado(completo hasta el nivel anterior), AVL (alturas de los subarboles difieren hasta 1)

#endif // ARBOL_H_INCLUDED

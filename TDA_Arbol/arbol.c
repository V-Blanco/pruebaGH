#include "arbol.h"

#define MAX(X, Y) ((X) > (Y)? (X) : (Y))
#define MIN(X, Y) ((X) < (Y)? (X) : (Y))

void crearArbol(tArbol*p){
    *p=NULL;
}

int arbolVacio(const tArbol*p){
    return *p==NULL;
}

int insertarEnOrden(tArbol*pa,const void*dato,unsigned tamDato,Cmp cmp){
    int resCmp;
    while(*pa)
    {
        resCmp=cmp(dato,(*pa)->dato);
        if(resCmp==0)
            return DUPLICADO;
        if(resCmp>0)
            pa=&(*pa)->der;
        else
            pa=&(*pa)->izq;
    }
    if( ((*pa)=(tNodo*)malloc(sizeof(tNodo)))==NULL || ((*pa)->dato=malloc(tamDato))==NULL )
    {
        free(*pa);
        return SIN_MEM;
    }
    memcpy((*pa)->dato,dato,tamDato);
    (*pa)->tamDato=tamDato;
    (*pa)->izq=NULL;
    (*pa)->der=NULL;
    return TODO_OK;
}

int insertarEnOrden_recursivo(tArbol*pa,const void*dato,unsigned tamDato,Cmp cmp){
    int resCmp;
    if(!*pa)
    {
        if( !((*pa)=(tNodo*)malloc(sizeof(tNodo))) || !((*pa)->dato=malloc(tamDato)) ){
            free(*pa);
            return SIN_MEM;
        }
        memcpy((*pa)->dato,dato,tamDato);
        (*pa)->tamDato=tamDato;
        (*pa)->der=NULL;
        (*pa)->izq=NULL;
        return TODO_OK;
    }
    resCmp=cmp(dato,(*pa)->dato);
    if(resCmp==0)
        return DUPLICADO;
    if(resCmp>0)
        return insertarEnOrden_recursivo(&(*pa)->der,dato,tamDato,cmp);
    return insertarEnOrden_recursivo(&(*pa)->izq,dato,tamDato,cmp);
}

void recorrerEnOrden(const tArbol*p,void*param,AccionConParam accion){
    if(*p==NULL)
        return;
    recorrerEnOrden(&(*p)->izq,param,accion);
    accion((*p)->dato,param);
    recorrerEnOrden(&(*p)->der,param,accion);
}

void recorrerPreOrden(const tArbol*p,void*param,AccionConParam accion){
    if(*p==NULL)
        return;
    accion((*p)->dato,param);
    recorrerPreOrden(&(*p)->izq,param,accion);
    recorrerPreOrden(&(*p)->der,param,accion);
}

void recorrerPostOrden(const tArbol*p,Accion accion){
    if(*p==NULL)
        return;
    recorrerPostOrden(&(*p)->izq,accion);
    recorrerPostOrden(&(*p)->der,accion);
    accion((*p)->dato);
}

void recorrerEnOrdenInverso(const tArbol*p,Accion accion){
    if(*p==NULL)
        return;
    recorrerEnOrdenInverso(&(*p)->der,accion);
    accion((*p)->dato);
    recorrerEnOrdenInverso(&(*p)->izq,accion);
}

void recorrerNodosDeNivel(tArbol*pa,int nivel,Accion accion){
    if(*pa==NULL)
        return;
    if(nivel>1){
        recorrerNodosDeNivel(&(*pa)->izq,nivel-1,accion);
        recorrerNodosDeNivel(&(*pa)->der,nivel-1,accion);
    }
    if(nivel==1)
        accion((*pa)->dato);
}

void recorrerNodosHastaNivel(tArbol*pa,int nivel,Accion accion){
    if(*pa==NULL)
        return;
    if(nivel>0){
        accion((*pa)->dato);
        recorrerNodosHastaNivel(&(*pa)->izq,nivel-1,accion);
        recorrerNodosHastaNivel(&(*pa)->der,nivel-1,accion);
    }
}

void recorrerNodosDesdeNivel(tArbol*pa,int nivel,Accion accion){
    if(*pa==NULL)
        return;
    recorrerNodosDesdeNivel(&(*pa)->izq,nivel-1,accion);
    recorrerNodosDesdeNivel(&(*pa)->der,nivel-1,accion);
    if(nivel<=1)
        accion((*pa)->dato);
}

tArbol* buscarNodoEnArbolOrdenado(tArbol*pa,const void*clave,Cmp cmp){
    int resCmp;
    if(*pa==NULL)
        return NULL;
    while( (*pa)!=NULL && (resCmp=cmp(clave,(*pa)->dato))!=0)
    {
        if(resCmp<0)
            pa=&(*pa)->izq;
        else
            pa=&(*pa)->der;
    }
    if(resCmp==0)
        return pa;
    return NULL;

}

tArbol* mayorNodoArbol(tArbol*pa){
    if(*pa==NULL)
        return NULL;
    while((*pa)->der!=NULL)
        pa=&(*pa)->der;
    return pa;
}

tArbol* menorNodoArbol(tArbol*pa){
    if(*pa==NULL)
        return NULL;
    while((*pa)->izq!=NULL)
        pa=&(*pa)->izq;
    return pa;
}

const tArbol* buscarMayorNoClave(const tArbol* p, void* dato, unsigned tamDato, Cmp cmp){
    if(*p==NULL)
        return NULL;
    const tArbol*mayor=p;
    const tArbol*mayorIzq=buscarMayorNoClave(&(*p)->izq,dato,tamDato,cmp);
    const tArbol*mayorDer=buscarMayorNoClave(&(*p)->der,dato,tamDato,cmp);
    if(mayorIzq!=NULL && cmp((*mayorIzq)->dato,(*mayor)->dato)>0 )
        mayor=mayorIzq;
    if(mayorDer!=NULL && cmp((*mayorDer)->dato,(*mayor)->dato)>0 )
        mayor=mayorDer;
    memcpy(dato,(*mayor)->dato,MIN(tamDato,(*mayor)->tamDato));
    return mayor;
}

int contarNodos(const tArbol*pa){
    if(*pa==NULL)
        return 0;
    return (contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1);
}

int contarHojas(const tArbol*pa){
    if(*pa==NULL)
        return 0;
    if( (*pa)->der== NULL && (*pa)->izq==NULL )
        return 1;
    return (contarHojas(&(*pa)->izq) +  contarHojas(&(*pa)->der));
}

int contarNoHojas(const tArbol*pa){
    if(*pa==NULL)
        return 0;
    if( (*pa)->der== NULL && (*pa)->izq==NULL )
        return 0;
    return (contarNoHojas(&(*pa)->izq) +  contarNoHojas(&(*pa)->der) +1);
}

int contarNodosConHijosPorIzq(const tArbol*pa){
    if((*pa)==NULL)
        return 0;
    if((*pa)->izq == NULL)
        return 0;
    return (contarNodosConHijosPorIzq(&(*pa)->izq)+ contarNodosConHijosPorIzq(&(*pa)->der)+1);
}

void mostrarHojas(const tArbol*pa){
    if(!*pa)
        return;
    if((*pa)->izq == NULL && (*pa)->der == NULL)
        mostrarInt((*pa)->dato);
    mostrarHojas(&(*pa)->izq);
    mostrarHojas(&(*pa)->der);
}

void mostrarNoHojas(const tArbol*pa){
    if(!*pa)
        return;
    if((*pa)->izq != NULL || (*pa)->der != NULL)
        mostrarInt((*pa)->dato);
    mostrarNoHojas(&(*pa)->izq);
    mostrarNoHojas(&(*pa)->der);
}

void eliminarArbol(tArbol*pa){
    if(*pa==NULL)
        return;
    eliminarArbol(&(*pa)->izq);
    eliminarArbol(&(*pa)->der);
    free((*pa)->dato);
    free(*pa);
    *pa=NULL;
}

int eliminarNodo(tArbol*pa,void*datoAEliminar,unsigned tamDato,Cmp cmp){
    if(*pa==NULL)
        return ARBOL_VACIO;
    tArbol*nodoAEliminar=buscarNodoEnArbolOrdenado(pa,datoAEliminar,cmp);
    if(nodoAEliminar==NULL)
        return NO_EXISTE;
    memcpy(datoAEliminar,(*nodoAEliminar)->dato,MIN(tamDato,(*nodoAEliminar)->tamDato));
    free((*nodoAEliminar)->dato);
    if((*nodoAEliminar)->der==NULL && (*nodoAEliminar)->izq==NULL)
    {
        free(*nodoAEliminar);
        *nodoAEliminar=NULL;
        return TODO_OK;
    }
    tArbol*remplazo;
    if( alturaArbol(&(*nodoAEliminar)->izq) > alturaArbol(&(*nodoAEliminar)->der))
        remplazo=mayorNodoArbol(&(*nodoAEliminar)->izq);
    else
        remplazo=menorNodoArbol(&(*nodoAEliminar)->der);
    tNodo*elim=*remplazo;
    (*nodoAEliminar)->dato=elim->dato;
    (*nodoAEliminar)->tamDato=elim->tamDato;
    if(elim->izq!=NULL)
        *remplazo=elim->izq;
    else
        *remplazo=elim->der;
    free(elim);
    return TODO_OK;
}

int eliminarYContarHoja(tArbol*pa){
    if(*pa==NULL)
        return 0;
    if((*pa)->der==NULL && (*pa)->izq==NULL)
    {
        free((*pa)->dato);
        free(*pa);
        *pa=NULL;
        return 1;
    }
    return ( eliminarYContarHoja(&(*pa)->izq)+ eliminarYContarHoja(&(*pa)->der));
}

int eliminarArbolYcontarnodo(tArbol*pa){
    int cant;
    if(*pa==NULL)
        return 0;
    cant=(eliminarArbolYcontarnodo(&(*pa)->izq)+eliminarArbolYcontarnodo(&(*pa)->der));
    free((*pa)->dato);
    free(*pa);
    *pa=NULL;
    return cant+1;
}

void eliminarHojas(tArbol*pa){
    if(*pa==NULL)
        return;
    if((*pa)->izq == NULL && (*pa)->der == NULL)
    {
        free((*pa)->dato);
        free(*pa);
        *pa = NULL;
        return;
    }
    eliminarHojas(&(*pa)->izq);
    eliminarHojas(&(*pa)->der);
}

int eliminarMenorHoja(tArbol*pa,void*dato,unsigned tamDato,Cmp cmp){
    if((*pa)==NULL)
        return 0;
    tArbol*elim=menorNodoArbol(pa);
    while(cmp((*pa)->izq->dato,(*elim)->dato)!=0)
        pa=&(*pa)->izq;
    memcpy(dato,(*elim)->dato,tamDato);
    free((*elim)->dato);
    free(*elim);
    (*pa)->izq=NULL;
    return 1;
}

int leerArbolDeArchivoBin(tArbol*arbol,const char*nomArch,unsigned tamDAto,Cmp cmp){
    void*reg=malloc(tamDAto);
    FILE*pa=fopen(nomArch,"rb");
    if(!pa)
        return ERROR_ARCH;
    fread(reg,tamDAto,1,pa);
    while(!feof(pa)){
        insertarEnOrden(arbol,reg,tamDAto,cmp);
        fread(reg,tamDAto,1,pa);
    }
    fclose(pa);
    free(reg);
    return TODO_OK;
}

int leerArbolDeArchivoTxt(tArbol*arbol,const char*nomArch,unsigned tamDAto,LeerArch leer,Cmp cmp){
    void*reg=malloc(tamDAto);
    FILE*pa=fopen(nomArch,"rt");
    if(!pa)
        return ERROR_ARCH;
    while(leer(pa,reg)==1)
    {
        insertarEnOrden(arbol,reg,tamDAto,cmp);

    }
    free(reg);
    fclose(pa);
    return TODO_OK;
}

int leerIndiceDeArchTxt(tArbol*arbol,const char*nomArch,unsigned tamDato,LeerIndice leer,Cmp cmp){
    void*indice=malloc(tamDato);
    int pos=1;
    FILE*pa=fopen(nomArch,"rt");
    if(pa==NULL)
        return ERROR_ARCH;
    while(leer(pa,indice,pos)==1)
    {
        insertarEnOrden(arbol,indice,tamDato,cmp);
        pos++;
    }
    fclose(pa);
    free(indice);
    return TODO_OK;
}

int leerIdxClaPosVerdura(FILE*pa,void*indice,int pos){
    tIdxIntPos*idx=(tIdxIntPos*)indice;
    tVerdura reg;
    int cmp=fscanf(pa,"%d|%30[^|]|%d\n",&reg.clave,reg.nombre,&reg.stock);
    idx->clave=reg.clave;
    idx->pos=pos;
    return cmp==3;
}

void balancearArbolDesdeArchivoOrdenado(tArbol* arbol,const char* nomArch,unsigned tamDato,LeerArch leer,Cmp cmp){
    int tamArch,cantElem;
    FILE*pa=fopen(nomArch,"rb");
    if(!pa)
        return;
    fseek(pa,0L,SEEK_END);
    tamArch=ftell(pa);
    cantElem=tamArch/tamDato;
    fseek(pa,0L,SEEK_SET);
    balancearArbol(pa,arbol,0,cantElem-1,tamDato,leer,cmp);
    fclose(pa);
}

void balancearArbol(FILE* archivo,tArbol* arbol,int ini,int fin,unsigned tamDato,LeerArch leer,Cmp cmp){
    if(ini>fin)
        return;
    int medio=(ini+fin)/2;
    fseek(archivo,medio*tamDato,SEEK_SET);
    void*dato=malloc(tamDato);
    if(leer(archivo,dato))
        insertarEnOrden(arbol,dato,tamDato,cmp);
    free(dato);
    balancearArbol(archivo,arbol,ini,medio-1,tamDato,leer,cmp);
    balancearArbol(archivo,arbol,medio+1,fin,tamDato,leer,cmp);
}

int leerIdxIntPosDeArchBin(FILE*pa,void*reg){
    tIdxIntPos*dato=(tIdxIntPos*)reg;
    return fread(dato, sizeof(tIdxIntPos),1,pa)==1;
}

void mostrarArbolComoGrafico_r(tArbol*pa,unsigned n,AccionParaGrafico accion){
    if(!*pa)
        return;
    mostrarArbolComoGrafico_r(&(*pa)->der,n+1,accion);
    accion((*pa)->dato,n);
    mostrarArbolComoGrafico_r(&(*pa)->izq,n+1,accion);
}

void mostrarIdxComoGrafico(void*dato,unsigned n){ //n=nivel
    tIdxIntPos*i=(tIdxIntPos*)dato;
    printf("%*s-%3d-\n",n*9," ",i->clave);//%*s : (*=n*6) (s=" ") == es la cantidad de espaios en blanco
}

int alturaArbol(tArbol*pa){
    int hd,hi;
    if(*pa==NULL)
        return 0;
    hi=alturaArbol(&(*pa)->izq);
    hd=alturaArbol(&(*pa)->der);
    return 1+ MAX(hd,hi);
}

int arbolCompleto(const tArbol*pa){
    if((*pa)==NULL)
        return 0;
    if( arbolCompleto(&(*pa)->izq)==alturaArbol(&(*pa)->der))
        return 1;
    return 0;
}

//int arbolCompleto2(const tArbol*pa){
//    int h=alturaArbol(pa);
//    return contarNodos(pa) == pow(2,h)-1;
//}
//
//int arbolBalanceado(const tArbol*pa){
//    return arbolCompletoHastaNivel(pa,alturaArbol(pa)-2);
//}
//
//int arbolBalanceado2(const tArbol*pa){
//    int h=alturaArbol(pa);
//    return contarNodos(pa) == pow(2,h-1)-1;
//}

int arbolCompletoHastaNivel(const tArbol*pa,int n){
    if((*pa)==NULL)
        return n<0;
    if(n==0)
        return 1;
    return arbolCompletoHastaNivel(&(*pa)->izq,n-1) && arbolCompletoHastaNivel(&(*pa)->der,n-1);
}

int arbolAVL(const tArbol*pa){
    int hi,hd;
    if((*pa)==NULL)
        return 1;
    hi=alturaArbol(&(*pa)->izq);
    hd=alturaArbol(&(*pa)->der);
    if(abs(hi-hd)>1)
        return 1;
    return arbolAVL(&(*pa)->izq) && arbolAVL(&(*pa)->der);
}

void mostrarInt(void*dato){
    printf("%d\n",*(int*)dato);
}

void mostrarInt2(void*e,void*b){
    printf("%d\n",*(int*)e);
}

void multiplicarPorN(void*elem,void*n){
    *(int*)elem*=(*(int*)n);
}

int cmpInt(const void*e1,const void*e2){
    return *(int*)e1 - *(int*)e2;
}

void grabarIntEnTxt(void*dato,void*param){
    FILE*pa=(FILE*)param;
    fprintf(pa,"%d\n",*(int*)dato);
}

void grabarIdxEnArchivo(void*dato,void*param){
    FILE*pa=(FILE*)param;
    tIdxIntPos*idx=(tIdxIntPos*)dato;
    fwrite(idx,sizeof(tIdxIntPos),1,pa);
}

int cmpIdx(const void*e1,const void*e2){
    tIdxIntPos*r1=(tIdxIntPos*)e1;
    tIdxIntPos*r2=(tIdxIntPos*)e2;
    return r1->clave - r2->clave;
}

void mostratIdx(void*e,void*b){
    tIdxIntPos*r1=(tIdxIntPos*)e;
    printf("%d | %d\n",r1->clave,r1->pos);
}

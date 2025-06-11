#include "arbol.h"

int main()
{
    tArbol arbol;
//    int i, vec[] = {100,50,75,100,5,105,200,5},insert,elem=100;
    crearArbol(&arbol);

//    for(i=0;i<(sizeof(vec)/sizeof(vec[0]));i++)
//    {
//        insert=insertarEnOrden(&arbol,vec+i,sizeof(vec[0]),cmpInt);
//        if(insert==DUPLICADO)
//            printf("Nodo duplicado:  %d\n",vec[i]);
//        else if(insert==TODO_OK)
//            printf("Nodo insertado correctamente: %d\n",vec[i]);
//        else
//            printf("Nodo no insertado, problema de memoria : %d\n",vec[i]);
//    }
//    puts("\nArbol Ordenado");
//    recorrerEnOrden(&arbol,NULL,mostrarInt);
//    puts("\nArbol en Pre Orden");
//    recorrerPreOrden(&arbol,NULL,mostrarInt2);
//    puts("\nArbol en Post Orden");
//    recorrerPostOrden(&arbol,mostrarInt);
//    puts("\nArbol En Orden Inverso");
//    recorrerEnOrdenInverso(&arbol,mostrarInt);

//    int n=2;
//    recorrerPreOrden(&arbol,&n,multiplicarPorN);
//    printf("\n\n");
//    recorrerPreOrden(&arbol,NULL,mostrarInt2);

//    tArbol*encontrado;
//    encontrado=mayorNodoArbol(&arbol);
//    puts("\nMayor: ");
//    mostrarInt((*encontrado)->dato);
//    encontrado=menorNodoArbol(&arbol);
//    puts("\nMenor: ");
//    mostrarInt((*encontrado)->dato);
//
//    int clave=50;
//    if((encontrado= buscarNodoEnArbolOrdenado(&arbol, &clave, cmpInt))){
//        printf("\nSe encontro el numero: ");
//        mostrarInt((*encontrado)->dato);
//        puts("");
//    }
//
//    printf("\nCantidad de Nodos: %d",contarNodos(&arbol));
//    printf("\nCantidad de nodos No Hojas: %d",contarNoHojas(&arbol));
//    printf("\nCantidad de Hojas: %d\n",contarHojas(&arbol));
//    printf("\nCantidad de nodos con HijosIzq: %d",contarNodosConHijosPorIzq(&arbol));

//    printf("\nAltura: %d",alturaArbol(&arbol));

//    mostrarHojas(&arbol);
//    mostrarNoHojas(&arbol);

//    int elim;
//    eliminarMenorHoja(&arbol,&elim,sizeof(int),cmpInt);
//    printf("\n");
//    eliminarHojas(&arbol);
//    recorrerEnOrden(&arbol,NULL,mostratInt);
//    printf("\nCant Hojas: %d\n",eliminarYContarHoja(&arbol));
//    recorrerEnOrden(&arbol,NULL,mostratInt);

//    if(arbolCompleto(&arbol4))
//        puts("Arbol completo");
//    else
//        puts("Arbol no completo");

//    FILE*pa=fopen("Arbol.txt","wt");
//    if(!pa)
//        return -1;
//    recorrerPreOrden(&arbol,(void*)pa,grabarIntEnTxt);

//    char nomArch[]="verduras.txt";
//    leerIndiceDeArchTxt(&arbol,nomArch,sizeof(tIdxIntPos),leerIdxClaPosVerdura,cmpIdx);
//    //recorrerPostOrden(&arbol,mostratIdx);
//    char nomArch2[]="idxVerdura.data";
//    FILE*pa=fopen(nomArch2,"wb");
//    if(pa==NULL)
//        return ERROR_ARCH;
//    recorrerEnOrden(&arbol,(void*)pa,grabarIdxEnArchivo);
//    fclose(pa);
//
//    balancearArbolDesdeArchivoOrdenado(&arbol,nomArch2,sizeof(tIdxIntPos),leerIdxIntPosDeArchBin,cmpIdx);
//    mostrarArbolComoGrafico_r(&arbol,0,mostrarIdxComoGrafico);

    eliminarArbol(&arbol);
//    printf("%d\n",eliminarArbolYContarNodos(&arbol));
 //   eliminarArbol(encontrado);

    return 0;
}

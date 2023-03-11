#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define p printf
#define s scanf

typedef struct NODO{
    char dato;
    struct NODO *ptrSig;
}tipoNodo;

typedef tipoNodo *nodoCola;

void encolar(nodoCola *, nodoCola *, char);
void desencolar(nodoCola *, nodoCola *);
void recorrer(nodoCola *, int);

int main(){
    nodoCola cabeza=NULL, cola=NULL;
    char texto[50];
    int i, tam;

    p("\n\tPROGRAMA UNO");
    p("\n\nIngresa tu texto luminoso: ");
    gets(texto);
    tam=strlen(texto);
    for(i=0; i<tam; i++)
        encolar(&cabeza, &cola, texto[i]);
    recorrer(&cabeza, tam);
    for(i=0; i<tam; i++)
        desencolar(&cabeza, &cola);

    getchar();
    return 1;
}

void encolar(nodoCola *cabeza, nodoCola *cola, char d){
    nodoCola nuevo;
    nuevo=(nodoCola)malloc(sizeof(tipoNodo));
    if(nuevo!=NULL){
        nuevo->dato=d;
        if(*cabeza==NULL) *cabeza=nuevo;
        else (*cola)->ptrSig=nuevo;
        *cola=nuevo;
        nuevo->ptrSig=*cabeza;
    }else
        p("\nNo hubo suficiente espacio en la memoria");
}

void desencolar(nodoCola *cabeza, nodoCola *cola){
    nodoCola nodo;
    nodo=*cabeza;
    if(nodo!=NULL){
        *cabeza=(*cabeza)->ptrSig;
        (*cola)->ptrSig=*cabeza;
        if(nodo==*cola)
            *cabeza=*cola=NULL;
        free(nodo);
    }else
        p("\nLa cola esta vacia");
}

void recorrer(nodoCola *cabeza, int tam){
    int i, j;
    nodoCola aux;
    aux=*cabeza;
    for(j=0; j<3*tam+1; j++){
        system("cls");
        p("\n\n\t");
        for(i=0; i<tam; i++){
            p("%c ", aux->dato);
            aux=aux->ptrSig;
            if(aux==*cabeza) p("      ");
        }
        aux=aux->ptrSig;
        Sleep(500);
    }
}


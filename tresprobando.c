#include <stdio.h>
#include <stdlib.h>
#define p printf
#define s scanf

typedef struct noodo{
    int NumClien;
    int prio;
    struct noodo *IzqSig;
    struct noodo *DerSig;
}elNodo;

typedef elNodo *nodCola;

void encolarCola(nodCola *, nodCola *, int, int);
void encolarCabeza(nodCola *, nodCola *, int, int);
void desencolarCola(nodCola *, nodCola *);
void recorrer(nodCola *);

int main(){
    nodCola cabeza=NULL, cola=NULL;
    int op, priorida, num=0;

    do{
        p("\n\tPROGRAMA TRES");
        p("\n\nOpciones:");
        p("\n\n1.Ingresar vehiculo\n2.Transportar proximo vehiculo\n3.Mostrar Cola\t");
        p("\n4.Salir");
        s("%i", &op);
        switch(op){
        case 1:
            num++;
            p("\nVehiculo No:\t\t\t[%i]", num);
            p("\nQue tipo de vehiculo es?\tAmbulancia--1\tPatrulla--2\tNormal--3\n\t");
            s("%i", &priorida);
            if(priorida==1 || priorida==2)
                encolarCabeza(&cabeza, &cola, priorida, num);
            else
                encolarCola(&cabeza, &cola, priorida, num);
            p("\n(PRESIONE ENTER)");
            break;
        case 2:
            desencolarCola(&cabeza, &cola);
            break;
        case 3:
            recorrer(&cabeza);
            break;
        case 4:
            return 4;
            break;
        default:
            p("\n\n\t***OPCION NO VALIDA***");
            break;
        }
        fflush(stdin);
        getchar();
        system("cls");
    }while(op!=4);

    getchar();
    return 2;
}

void encolarCola(nodCola *cabeza, nodCola *cola, int pri, int n){
    nodCola nuevo;
    nuevo=(nodCola)malloc(sizeof(elNodo));
    if(nuevo!=NULL){
        nuevo->NumClien=n;
        nuevo->prio=pri;
        nuevo->DerSig=*cola;
        if(*cabeza==NULL)
            *cabeza=nuevo;
        else
            (*cola)->IzqSig=nuevo;
        nuevo->IzqSig=NULL;
        *cola=nuevo;
    }else p("\n\nNo hubo suficiente espacio en memoria");
}

void encolarCabeza(nodCola *cabeza, nodCola *cola, int pri, int n){
    nodCola nuevo, aux;
    nuevo=(nodCola)malloc(sizeof(elNodo));
    if(nuevo!=NULL){
        nuevo->NumClien=n;
        nuevo->prio=pri;
        if(*cabeza==NULL){
            *cabeza=*cola=nuevo;
            nuevo->DerSig=nuevo->IzqSig=NULL;
        }else{
            if(nuevo->prio!=(*cabeza)->prio && nuevo->prio!=2){
                (*cabeza)->DerSig=nuevo;
                nuevo->IzqSig=*cabeza;
                *cabeza=nuevo;
                nuevo->DerSig=NULL;
            }else{
                aux=*cabeza;
                while(nuevo->prio>=aux->prio && aux!=*cola){
                    aux=aux->IzqSig;
                }
                if(aux==*cola && nuevo->prio>=aux->prio){
                    nuevo->IzqSig=NULL;
                    (*cola)->IzqSig=nuevo;
                    nuevo->DerSig=aux;
                    *cola=nuevo;
                }else{
                    if(nuevo->prio==2 && (*cabeza)->prio>2){
                        (*cabeza)->DerSig=nuevo;
                        nuevo->IzqSig=*cabeza;
                        *cabeza=nuevo;
                        nuevo->DerSig=NULL;
                    }else{
                    nuevo->DerSig=aux->DerSig;
                    (aux->DerSig)->IzqSig=nuevo;
                    aux->DerSig=nuevo;
                    nuevo->IzqSig=aux;
                    }
                }
            }
        }

    }else p("\n\nNo hubo suficiente espacio en memoria");
}

void recorrer(nodCola *cabeza){
    nodCola aux;
    aux=*cabeza;
    p("\nCOLA:\t\tFormato de la cola: [No.de vehiculo](Tipo de carro)-->\n\ncabeza");
    while(aux!=NULL){
        p("-->[%i](%i)", aux->NumClien, aux->prio);
        aux=aux->IzqSig;
    }
    p("-->NULL");
}

void desencolarCola(nodCola *cabeza, nodCola *cola){
    int nu;
    nodCola nodo;
    nodo=*cabeza;
    if(nodo!=NULL){
        nu=nodo->NumClien;
        if(*cola==*cabeza){
            *cola=*cabeza=NULL;
        }else{
            (nodo->IzqSig)->DerSig=NULL;
            *cabeza=(*cabeza)->IzqSig;
        }
        if(nodo->prio==1){
            p("\nVehiculo transportado: Ambulancia--[%i]", nu);
        }else if(nodo->prio==2){
            p("\nVehiculo transportado: Patrulla--[%i]", nu);
            }else{
                p("\nVehiculo transportado: Carro Normal--[%i]", nu);
            }
        free(nodo);
    }else
        p("\n\t***La cola esta vacia***");
}



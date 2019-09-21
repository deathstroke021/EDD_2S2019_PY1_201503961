#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include <cstring>
using namespace std;

struct Nodo{
  string dato; // dato entero
  Nodo *der;
  Nodo *izq;
};

Nodo *crearNodo(string);
void insertarNodo(Nodo *&, string);
void mostrarArbol(Nodo *, int);
void preOrden(Nodo *arbol);
void inOrden(Nodo *arbol);
void postOrden(Nodo *arbol);

Nodo *arbol = NULL;

int main(){
  int contador = 0;
  insertarNodo(arbol,"batman");
  insertarNodo(arbol,"Mushroom");
  insertarNodo(arbol,"Pikachu");
  insertarNodo(arbol,"arbol");
  mostrarArbol(arbol,contador);
  preOrden(arbol);
  cout<<"\n";
  inOrden(arbol);
  cout<<"\n";
  postOrden(arbol);


  return 0;
}

Nodo *crearNodo(string n){
  Nodo *nuevo_nodo = new Nodo();

  nuevo_nodo->dato = n;
  nuevo_nodo->der = NULL;
  nuevo_nodo->izq = NULL;

  return nuevo_nodo;
}

void insertarNodo(Nodo *&arbol, string n){
  if(arbol == NULL){
    Nodo *nuevo_nodo = crearNodo(n);
    arbol = nuevo_nodo;
  }
  else{
    string valorRaiz = arbol->dato; // obtener valor valorRaiz
    cout<<valorRaiz<<"\n";
    //cout<<n<<"\n";

    char pal1[30];
    char pal2[30];

    int i;
    for (i = 0; i < sizeof(pal1); i++) {
        pal1[i] = tolower(valorRaiz[i]);
        //cout << pal1[i];
    }

    cout<<"\n";

    for (i = 0; i < sizeof(pal2); i++) {
        pal2[i] = tolower(n[i]);
        //cout << pal2[i];
    }

    //cout<<"\n";

    cout<<strcmp(pal1, pal2)<<"\n";

    if(strcmp(pal1, pal2) == 1 ){ //Si el elemnto es menor a la raiz
      insertarNodo(arbol->izq,n);
    }
    else if(strcmp(pal1, pal2) == -1 ){ //Si el elemento es mayor
      insertarNodo(arbol->der,n);
    }
  }
}

void mostrarArbol(Nodo *arbol, int cont){
  if (arbol == NULL){
    return;
  }
  else{
    mostrarArbol(arbol->der,cont+1);
    for(int i =0; i<cont; i++){
      cout<<"            ";
    }
    cout<<arbol->dato<<endl;
    mostrarArbol(arbol->izq,cont+1);
  }
}

void preOrden(Nodo *arbol){
  if(arbol == NULL){
    return;
  }
  else{
    cout<<arbol->dato<<" - ";
    preOrden(arbol->izq);
    preOrden(arbol->der);

  }
}

void inOrden(Nodo *arbol){
  if(arbol==NULL){
    return;
  }
  else{
    inOrden(arbol->izq);
    cout <<arbol->dato<<" - ";
    inOrden(arbol->der);
  }
}

void postOrden(Nodo *arbol){
  if(arbol == NULL){
    return;
  }
  else{
    postOrden(arbol->izq);
    postOrden(arbol->der);
    cout<<arbol->dato<<" - ";
  }
}

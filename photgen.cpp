

#include <iostream>
using namespace std;


void menu1()
{
    cout<<"\n\t\tPHOTGEN++\n\n";
    cout<<" 1. INSERT IMAGE               "<<endl;
    cout<<" 2. SELECT IMAGE               "<<endl;
    cout<<" 3. APPLY FILTERS              "<<endl;
    cout<<" 4. MANUAL EDITING             "<<endl;
    cout<<" 5. EXPORT IMAGE               "<<endl;
    cout<<" 6. REPORTS                    "<<endl;
    cout<<" 7. SALIR                      "<<endl;


    cout<<"\n INGRESE OPCION: ";
}


/*                        Funcion Principal
---------------------------------------------------------------------*/

int main()
{

  int op;     // opcion del menu


    do
    {
        menu1();  cin>> op;

        switch(op)
        {
            case 1:
            cout<< "\n iNSERTAR IMAGEN: ";

                 /*cout<< "\n NUMERO A INSERTAR: "; cin>> _dato;
                 insertarInicio(lista, _dato);*/
            break;


            case 2:
            cout<< "\n SELECCIONAR IMAGEN: ";

                 /*cout<< "\n NUMERO A INSERTAR: "; cin>> _dato;
                 insertarFinal(lista, _dato );*/
            break;


            case 3:
            cout<< "\n APLICAR FILTRO: ";

                 /*cout<< "\n NUMERO A INSERTAR: ";cin>> _dato;
                 cout<< " Posicion : ";       cin>> pos;
                 insertarElemento(lista, _dato, pos);*/
            break;


            case 4:
            cout<< "\n EDITAR MANUALMENTE: ";

                 /*cout << "\n\n MOSTRANDO LISTA\n\n";
                 reportarLista(lista);*/
            break;


            case 5:
            cout<< "\n EXPORTAR IMAGEN: ";

                 /*cout<<"\n Valor a buscar: "; cin>> _dato;
                 buscarElemento(lista, _dato);*/
            break;

            case 6:
            cout<< "\n REPORTES: ";

                /*cout<<"\n Valor a eliminar: "; cin>> _dato;

                eliminarElemento(lista, _dato);*/
            break;

                    }

        cout<<endl<<endl;
        system("pause");  system("cls");

    }while(op!=7);


   system("pause");
   return 0;
}

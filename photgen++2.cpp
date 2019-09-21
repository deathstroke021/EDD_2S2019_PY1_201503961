#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

ofstream file;
ofstream filescss;
ofstream fileslinef;

string data;
string data2;
string data3;

int counterscss = 1;

int countere = 0;

int count4 = 0;

int counterlinf = 1;

int counterlinc = 1;

string color;

class RGB
{
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;

	RGB(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}

	bool Equals(RGB rgb)
	{
		return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
	}
};

static string DecimalToHexadecimal(int dec) {
	if (dec < 1) return "00";

	int hex = dec;
	string hexStr = "";

	while (dec > 0)
	{
		hex = dec % 16;

		if (hex < 10)
			hexStr = hexStr.insert(0, string(1, (hex + 48)));
		else
			hexStr = hexStr.insert(0, string(1, (hex + 55)));

		dec /= 16;
	}

	return hexStr;
}

static string RGBToHexadecimal(RGB rgb) {
	string rs = DecimalToHexadecimal(rgb.R);
	string gs = DecimalToHexadecimal(rgb.G);
	string bs = DecimalToHexadecimal(rgb.B);

	return '#' + rs + gs + bs;
}

//int counter3= 0;
struct Nodo{
  string dato;
  Nodo *siguiente;
};

void insertarLista(Nodo *&, string);
void mostrarLista(Nodo *);
bool buscarLista(Nodo *, string);
void eliminarLista(Nodo *&lista, string &n);

Nodo *lista = NULL;

Nodo *lista2 = NULL;

Nodo *lista3 = NULL;


void insertarLista(Nodo *&lista, string n){
  Nodo *nuevo_nodo = new Nodo();
  nuevo_nodo->dato = n;

  Nodo *aux1 = lista;
  Nodo *aux2;

  while((aux1 !=NULL) && (aux1->dato < n)){
    aux2 = aux1;
    aux1 = aux1->siguiente;
  }
  if(lista == aux1){
    lista = nuevo_nodo;
  }
  else{
    aux2 ->siguiente = nuevo_nodo;
  }
  nuevo_nodo->siguiente = aux1;
}

void mostrarLista(Nodo *lista){
  Nodo *actual = new Nodo();
  actual = lista;
  cout<<"Reporte lista:"<<"\n";

  while(actual != NULL){
    cout<<actual->dato<<" -> ";
    actual = actual->siguiente;
  }
  cout<<"\n";
}

bool buscarLista(Nodo *lista, string n){
  bool band = false;

  Nodo *actual = new Nodo();
  actual = lista;

  while((actual != NULL) && (actual->dato <= n)){
    if(actual->dato == n){
      band = true;
    }
    actual = actual->siguiente;
  }
  if(band == true){
    return true;
  }
  else{
    return false;

  }
}

void eliminarLista(Nodo *&lista, string &n){
  Nodo *aux = lista;
  n = aux->dato;
  lista = aux->siguiente;
  delete aux;
}

class ColumnNode{ //Clase nodo columna
	friend class RowNode;
	friend class SM;
private:
	ColumnNode *nextCol; // pointer to next column
	int colNo; // column number and value
	string value;
	ColumnNode(int colNo, string val); // constructor to set value and column number
};
ColumnNode::ColumnNode(int colNo, string val){ //Valor nodo en la columna
	value = val;
	this->colNo = colNo;
	nextCol = NULL;
}
class RowNode{ //Clase nodo fila
	friend class SM;
private:
	int rowNo, colSize; // row number & actual number of column nodes inside this row node
	ColumnNode *colHead, *colTail; // pointer to the first and last column inside this row node
	RowNode *nextRow; // pointer to next row node
	RowNode(){}
	RowNode(int rowNo);
	~RowNode();
	void deleteFirstCol(); //deletes the first column node and assigns the next to head
	void overwriteColumn(ColumnNode *curr, string val); // if a column node exists prompts to overwrite the value
	void insertColumn(int colIndex, string val); //inserting column inside a row node
	void printCol(int mSize); // printing column nodes inside a row node
	void graphvizCol(int mSize, int n, int nSize);
	void graphvizCol2(int mSize, int n);
  void scssCol(int mSize, int n, int nSize);
	void linfCol(int mSize, int n, int nSize);
	void lincCol(int mSize,  int nSize);

};
RowNode::RowNode(int rowNo){ //Valor fila
	this->rowNo = rowNo;
	nextRow = NULL;
	colHead = NULL;
	colTail = NULL;
}
RowNode::~RowNode(){ //Destructor
	while (colHead != NULL){ //while loop to delete the first column until there is no column node left
		deleteFirstCol();
	}
}
void RowNode::deleteFirstCol(){ //Eliminar primera columna
	ColumnNode *toBeDeleted = colHead;
	colHead = colHead->nextCol;
	delete toBeDeleted;
	if (colHead == NULL){
		colTail = NULL;
	}
}
void RowNode::overwriteColumn(ColumnNode *curr, string val){ //Sobreescribir columna
	cout << "A value already exists in row no. " << rowNo << " and col no. " << curr->colNo << endl << "Would you like to overwrite? (Y/N) ";
	char oW;
	cin >> oW;
	if (oW == 'Y'){
		curr->value = val;
		cout << "Value has been overwritten." << endl;
	}
	else{
		cout << "Value has not been overwritten." << endl;
	}
}
void RowNode::insertColumn(int colIndex, string val){ //Insertar columna
	if (colHead == NULL || (colTail != NULL && colIndex > colTail->colNo)){ //if the list is empty or column number is greater than the last column number in the current list
		ColumnNode *newNode = new ColumnNode(colIndex, val);
		if (colHead == NULL){ //if the list is empty
			colHead = colTail = newNode;
		}
		else{
			colTail->nextCol = newNode;
			colTail = newNode;
		}
		colSize++;
		return;
	}
	if (colTail->colNo == colIndex){ //if the column number is the same as last column number, prompts to overwrite
		overwriteColumn(colTail, val);
		return;
	}
	if (colIndex < colHead->colNo){//insert at beginning
		ColumnNode *newCol = new ColumnNode(colIndex, val);
		newCol->nextCol = colHead;
		colHead = newCol;
		colSize++;
		return;
	}
	ColumnNode *curr = colHead;
	for (int i = 0; i < colSize; i++){
		if (curr->colNo == colIndex){ //if column node is found, then prompt overwrite
			overwriteColumn(curr, val);
			break;
		}
		else if (curr->nextCol != NULL){
			if (curr->colNo < colIndex && curr->nextCol->colNo > colIndex){//row node can fit between two other nodes (for ex. 4 can fit between 3 5)
				ColumnNode *newCol = new ColumnNode(colIndex, val);
				newCol->nextCol = curr->nextCol;
				curr->nextCol = newCol;
				colSize++;
				break;
			}
			else{
				curr = curr->nextCol;
			}
		}
	}
}
void RowNode::printCol(int mSize){ //Imprimir columna
	int counter = 0;
	ColumnNode *curr = colHead;
	while (counter < mSize){
		/*
		iterates using a counter which will indicate the column size
		if the counter matches the column number then it prints the value and points to the next column
		otherwise it does not exist, so it prints a zero
		if the current column is null and the counter is still less than column size
		then it will have to print zero's for the rest of the iterations
		*/
		if (curr != NULL){
			if (counter == curr->colNo){
				cout << right << setw(5) << curr->value;
				curr = curr->nextCol;
			}
			else{
				cout << setw(5) << right << "0";
			}
		}
		else{
			cout << setw(5) << right << "0";
		}
		counter++;
	}
}

void RowNode::graphvizCol(int mSize, int n, int nSize){ //Imprimir columna
	int counter = 0;
	int counter2 = 0;
	ColumnNode *curr = colHead;

	//file.open("archivo.txt");

	while (counter < mSize){
    //cout <<mSize<<"\n";

		/*
		iterates using a counter which will indicate the column size
		if the counter matches the column number then it prints the value and points to the next column
		otherwise it does not exist, so it prints a zero
		if the current column is null and the counter is still less than column size
		then it will have to print zero's for the rest of the iterations
		*/
		if (curr != NULL){
			if (counter == curr->colNo){

				//Nodos



				file << "N"<< counter <<"_L"<< n << " [label = \""<< curr->value <<"\" width = 1.5, group ="<< counter + 2 <<"];"<<"\n";

        color = curr->value;

				if(counter2 == 0){
          file<<"U"<<n<<" -> N"<< counter <<"_L"<< n << ";"<<"\n";
        }

        if(counter2 != 0){

        int r = counter;
        //cout<<r<<"\n";

        while(r > 0){
          int c = r;
          int ro = n + 1;
          string rc;
          rc =to_string(ro) + "," + to_string(c);
          //cout<<rc<<"\n";
          //int _dato  = atoi(rc.c_str());

          if(buscarLista(lista, rc) == true){
            //cout<<"Encontrado"<< "\n";
            //cout<<"Nodo izquierda"<<"\n";
          }

          else if(buscarLista(lista, rc) == false){
            //cout<<"Encontrado"<< "\n";
            file<<"N"<<counter<<"_L"<<n<< " -> N" << r -1 << "_L"<< n << ";"<<"\n";
            file<<"N"<<r - 1<<"_L"<<n<< " -> N" <<counter<< "_L"<< n << ";"<<"\n";
            //cout<<"Link Nodo previo"<<"\n";
            //cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<"\n";
            r = 1;
          }

          r--;
          //cout<<r<<"\n";

        }
      }


				// Horizontal Links
        /*if (counter2 != 0){
				file<<"N"<<counter2 -1 <<"_L"<<n<< " -> N" <<counter2 << "_L"<< n << ";"<<"\n";
			}

			  if (counter2 != 0){

			  file<<"N"<<counter2 <<"_L"<<n<< " -> N" <<counter2 - 1<< "_L"<< n << ";"<<"\n";
			}*/

			//Vertical Links

			 if (n == 0){
				 file<<"A"<<counter << " -> N" << counter <<"_L0"<< ";"<<"\n";
			 }

			 //Prueba Inici

			 else if (n != 0){

				 int c = n;

				 while(c > 0){
					 int r = c;
					 int co= counter +1;
					 string rc;
					 rc =to_string(r) + "," + to_string(co);
					 //cout<<rc<<"\n";
					 //int _dato  = atoi(rc.c_str());

					 if(buscarLista(lista, rc) == true && c == 1){
						 //cout<<"Encontrado"<< "\n";
						 file<<"A"<<counter << " -> N" << counter<<"_L"<<n<< ";"<<"\n";
						 //cout<<"Link con el header"<<"\n";
             //cout<<"++++++++++++++++++++++++++++++"<<"\n";
					 }

					 else if(buscarLista(lista, rc) == true && c != 1){
						 //cout<<"Encontrado"<< "\n";
						 //cout<<"Nodo arriba"<<"\n";
					 }

					 else if(buscarLista(lista, rc) == false){
						 //cout<<"Encontrado"<< "\n";
						 file<<"N"<<counter <<"_L"<<n<< " -> N" << counter << "_L"<< c - 1<< ";"<<"\n";
						 file<<"N"<<counter <<"_L"<<c-1<< " -> N" <<counter<< "_L"<< n << ";"<<"\n";
						 //cout<<"Link Nodo previo"<<"\n";
             //cout<<"-----------------------------------"<<"\n";
						 c = 1;
					 }


					 //cout<<c<<"\n";
					 c--;

				 }


			 }

       if(n == countere + 2){
         file<<"e"<< countere <<"-> N"<<counter<<"_L"<<n<<"[dir = none, color = \"white\"];"<<"\n";
       }

			 //Prueba fin


				curr = curr->nextCol;
				counter2++;
			}
			else{
				int r = n +1;
				int c= counter + 1;
				//std::string cadena = "";
			  //cadena = std::to_string(entero);
				string rc;
				rc =to_string(r) + "," + to_string(c);

        data = rc;

				//data  = atoi(rc.c_str());

		    insertarLista(lista,data);
				//cout<<rc<<"\n";
				//cout<<"Contador"<<counter3<<"\n";
				//a[counter3] = rc;


				//cout << setw(5) << right << "0";
			}


		}
		else{
			int r = n +1;
			int c= counter + 1;
			//std::string cadena = "";
			//cadena = std::to_string(entero);
			string rc;
			rc =to_string(r) + "," + to_string(c);

			//data  = atoi(rc.c_str());
      data = rc;


			insertarLista(lista, data);

		}
		counter++;

	}

	//file<<"U"<<n<<" -> N0" <<"_L"<< n <<"\n";

  //cout<<nSize<<"\n";


	//file.close();

}

void RowNode::graphvizCol2(int mSize, int n){ //Imprimir columna
	int counter = 0;
	int counter2 = 0;
	ColumnNode *curr = colHead;

	//file.open("archivo.txt");
  file<<"{ rank = same; U"<< n <<";";

	while (counter < mSize){

		/*
		iterates using a counter which will indicate the column size
		if the counter matches the column number then it prints the value and points to the next column
		otherwise it does not exist, so it prints a zero
		if the current column is null and the counter is still less than column size
		then it will have to print zero's for the rest of the iterations
		*/
		if (curr != NULL){
			if (counter == curr->colNo){

				//Nodos

				file << "N"<< counter <<"_L"<< n <<";";

				curr = curr->nextCol;
				counter2++;
			}
			else{

			}
		}
		else{


		}
		counter++;

	}

  file<<"}" <<"\n";

}

void RowNode::scssCol(int mSize,int n, int nSize){ //Imprimir columna
	int counter = 0;
  //int counter2 = 0;
	ColumnNode *curr = colHead;

	while (counter < mSize){

		if (curr != NULL){
			if (counter == curr->colNo){

				filescss << ".pixel:nth-child("<<counterscss<<")"<<"\n";

        string rgb = curr->value;
        std::string s = rgb;
        std::string delimiter = "-";

        size_t pos = 0;
        std::string token;
        int count = 0;
        string c1,c2,c3;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            //std::cout << token << std::endl;
            count = count +1;
            if(count == 1){
              c1 = token;
            }
            else if(count == 2){
              c2 = token;
            }
            //std::cout << count << std::endl;
            s.erase(0, pos + delimiter.length());
        }
        c3 = s;

        int r,g,b;

        r  = atoi(c1.c_str());
        g  = atoi(c2.c_str());
        b  = atoi(c3.c_str());

        RGB data = RGB(r, g, b);
        string value = RGBToHexadecimal(data);

          filescss << "{"<<"\n";
          filescss << "background:"<< value <<";"<<"\n";
          filescss << "}"<<"\n";

				curr = curr->nextCol;

			}
			else{

			}

      //counter2++;


		}
		else{


		}
		counter++;
    counterscss++;

	}

}

void RowNode::linfCol(int mSize,int n, int nSize){ //Imprimir columna
	int counter = 0;

  //int counter2 = 0;
	ColumnNode *curr = colHead;

	while (counter < mSize){

		if (curr != NULL){
			if (counter == curr->colNo){

				file << "node"<< counterlinf <<"[label=\"("<<counter<<","<<n<<") "<<curr->value<< "\"];"<<"\n";
				file<<"node"<<counterlinf -1<< "-> node"<<counterlinf<<";"<<"\n";

				counterlinf++;


				curr = curr->nextCol;

			}
			else{

			}

      //counter2++;


		}
		else{


		}
		counter++;

	}

}

void RowNode::lincCol(int mSize, int nSize){ //Imprimir columna




}

class SM{ //Clase Sparse Matrix
private:
	int n, m; // max number of rows and columns
	int rowSize; // actual size of the row list
	RowNode *rowHead; //pointer to the first row in the list
	RowNode *rowTail; //pointer to the last row in the list
	void insertEntry(int rowIndex, int colIndex, string val); // inserting a new element into a row x column
	void deleteFirstRow();  // deletes the first row node in the list and assigns the next to head
	void printColumnHeader();// will print out the column numbers ( ex 1 2 3 4 5 6 7 8 9 10)
	void graphvizColumnHeader();
	void printEmptyRow(int counter); // will print out an empty row for the counter number (ex 5| 0 0 0 0 0 0)
  void graphvizEmptyRow(int counter);
  void scssEmptyRow(int counter);
	void lincCol();

public:
	SM(int rows, int columns);
	~SM();
	void readElements(string capa);
	void printMatrix();
	void graphvizMatrix(string capa);
  void scsscapas(string capa);
	void graphvizMatrix2();
	void linealizacionfcapas(string capa);
	void linealizacionccapas(string capa);
	//SM * addSM(SM &other);
};

void SM::insertEntry(int rowIndex, int colIndex, string val){ //Insertar nodo
	if (rowTail == NULL || rowIndex > rowTail->rowNo){ //insert at end if the list is empty or the row number is greater than the last row number
		RowNode *newNode = new RowNode(rowIndex);
		if (rowHead == NULL){ // if the list is empty
			rowHead = rowTail = newNode;
		}
		else{
			rowTail->nextRow = newNode;
			rowTail = newNode;
		}
		rowSize++;
		newNode->insertColumn(colIndex, val);
		return;
	}
	if (rowTail->rowNo == rowIndex){ //if the row number is equal to the last row's number then insert column at end
		rowTail->insertColumn(colIndex, val);
		return;
	}
	if (rowIndex < rowHead->rowNo){ //insert at beginning
		RowNode *newRow = new RowNode(rowIndex);
		newRow->nextRow = rowHead;
		rowHead = newRow;
		rowSize++;
		newRow->insertColumn(colIndex, val);
		return;
	}
	RowNode *curr = rowHead;
	for (int i = 0; i < rowSize; i++){
		if (curr->rowNo == rowIndex){ //if row node already exists
			curr->insertColumn(colIndex, val);
			break;
		}
		else if (curr->nextRow != NULL){
			if (curr->rowNo < rowIndex && curr->nextRow->rowNo > rowIndex){//row node can fit between two other nodes (for ex. 4 can fit between 3 5)
				RowNode *newRow = new RowNode(rowIndex);
				newRow->nextRow = curr->nextRow;
				curr->nextRow = newRow;
				rowSize++;
				newRow->insertColumn(colIndex, val);
				break;
			}
			else{
				curr = curr->nextRow;
			}
		}
	}
}
void SM::deleteFirstRow(){ //Eliminar primera fila
	RowNode *toBeDeleted = rowHead;
	rowHead = rowHead->nextRow;
	delete toBeDeleted;
	if (rowHead == NULL){
		rowTail = NULL;
	}
}
void SM::printColumnHeader(){ //Imprimir headers
	cout << "-----------------------------------------------------------" << endl;
	cout << "Sparse-matrix Visual Representation: " << endl << endl;
	cout << " R|C";

	for (int i = 0; i < m; i++){
		cout << right << setw(5) << i;
	}
	cout << endl;
	for (int i = 0; i < m * 6; i++){
		cout << right << "-";
	}
	cout << endl;
}

void SM::graphvizColumnHeader(){ //Imprimir headers

    int count = 0;
    int count2 = 0;
    int count3 = 0;


	for (int i = 0; i < m; i++){
		//cout << right << setw(5) << i;

    while (count <= n){

    int r = count+1;
    int co= i+1;
    string rc;

    rc =to_string(r) + "," + to_string(co);
    //cout<<rc<<"\n";
    //int _dato  = atoi(rc.c_str());

    if(buscarLista(lista, rc) == true){
      count2++;

    }
    count++;
  }

    if(count2 < n){

    file <<"A"<<i<< "[label =\"C"<<i<<"\" width = 1.5 style = filled, group ="<<count3 + 2<<"];"<<"\n";
		/*if (i != m-1){
		file<<"A"<< i <<"->" <<"A"<< i + 1 <<";" <<"\n";
	  }
		if (i > 0){
		file<<"A"<< i <<"->" <<"A"<< i - 1 <<";" <<"\n";*/

    if(count3 == 0){

      file <<"Mt->A"<<i<< ";" << "\n";

    }

    else if(count3 != 0){

      int co = i;

      while(co > 0){
        int c = co -1;
        string rc;
        rc = to_string(c);


        if(buscarLista(lista3, rc) == true){
          //cout<<"Encontrado"<< "\n";
          //cout<<"Nodo izquierda"<<"\n";
        }

        else if(buscarLista(lista3, rc) == false){
          //cout<<"Encontrado"<< "\n";
          file<<"A"<< i <<"->" <<"A"<< co - 1 <<";" <<"\n";
          file<<"A"<< co - 1 <<"->" <<"A"<< i <<";" <<"\n";
          //cout<<"Link Nodo previo"<<"\n";
          //cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<"\n";
          co = 1;
        }

        co--;
        //cout<<r<<"\n";

      }



    }

    count3++;
	  }
    else{

      string co;

      co =to_string(i);

      data3 = co;

      insertarLista(lista3,data3);

    }

    count = 0;
    count2 = 0;
  }

		//file << i << "\n";
	//cout << endl;
	file <<"{ rank = same; Mt; ";


	for (int i = 0; i < m; i++){
    int co = i;
      string rc;
      rc = to_string(co);


      if(buscarLista(lista3, rc) == true){
        //cout<<"Encontrado"<< "\n";
        //cout<<"Nodo izquierda"<<"\n";
      }

      else{
        //cout << right << setw(5) << i;
        file <<"A"<<i<<"; ";

        count4 = i;

        //file << i << "\n";

      }


	}
	file <<"}"<<"\n";



}

void SM::lincCol(){

	//cout<<"Busqueda";

	int count = 0;

for (int i = 0; i < m; i++){
	//cout << right << setw(5) << i;

	while (count < n){

	int r = count+1;
	int co= i+1;
	string rc;

	rc =to_string(r) + "," + to_string(co);
	//cout<<rc<<"\n";
	//int _dato  = atoi(rc.c_str());

	if(buscarLista(lista, rc) == true){
		//cout<<"siguiente"<<"\n";


	}

	else if(buscarLista(lista, rc) == false){

		file << "node"<< counterlinc <<"[label=\"("<<co - 1<<","<<r - 1<<") "<<color<< "\"];"<<"\n";
		file<<"node"<<counterlinc -1<< "-> node"<<counterlinc<<";"<<"\n";
		//cout<<co -1 <<" , "<<r - 1<<"\n";

		counterlinc++;

	}

	count++;
}

	count = 0;
	//cout<<"------------------------"<<"\n";
}


}

void SM::printEmptyRow(int counter){ //Imprimir filas vacias
	for (int i = 0; i < m; i++){
		cout << setw(5) << right << "0";
	}
	cout << endl;
}

void SM::graphvizEmptyRow(int counter){ //Imprimir filas vacias

  int r = counter +1;

	for (int i = 0; i < m; i++){
		//cout << setw(5) << right << "0";
    int c= i + 1;
    //std::string cadena = "";
    //cadena = std::to_string(entero);
    string rc;
    rc =to_string(r) + "," + to_string(c);

    //data  = atoi(rc.c_str());

    data = rc;

    //cout<<data<<"\n";

    insertarLista(lista, data);
	}
	//cout << endl;
}

void SM::scssEmptyRow(int counter){ //Imprimir filas vacias

	for (int i = 0; i < m; i++){
    counterscss++;

	}

}

SM::SM(int rows, int columns){ // Creando la matriz
	n = rows;
	m = columns;
	rowHead = NULL;
	rowTail = NULL;
	rowSize = 0;
	cout << "A zero-based Sparse Matrix has been created with the following dimensions, Row(s) " << n << " and Column(s) " << m << endl;
}
SM::~SM(){ // Destruyecdo la matriz
	while (rowHead != NULL){ //while there are still rows left(row head is not null) keep deleting the first row
		deleteFirstRow();
	}

	cout << "Sparse Matrix has been destroyed" << endl;
}
void SM::readElements(string capa){ //Ingresando elementos matriz
		{
			ifstream ip(capa);

		  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

		  string dato;
		  /*string lastname;
		  string age;
		  string weight;
		  string a;*/
		  int count = 0;
		  int count2 = 0;

		  while(ip.good()){

		    getline(ip,dato,'\n');
		    std::string s = dato;
		    //std::cout << "cadena: "<<s<< '\n';
		    std::string delimiter = ";";

		    size_t pos = 0;
		    std::string token;
		    //count2 = 0;
		    while ((pos = s.find(delimiter)) != std::string::npos) {
		        token = s.substr(0, pos);
		        //std::cout << token << std::endl;
		        //std::cout << count2 << std::endl;
		        count2 = count2 +1;
		        s.erase(0, pos + delimiter.length());
		    }
		    count2 = count2 + 1;
		    //std::cout << s << std::endl;

		    count = count + 1;

		  }

		  //std::cout << "Filas: "<<count - 1<< '\n';
		  int count3 = count2/(count - 1);
		  //std::cout << "Columnas: "<<count3<< '\n';

			//SM *s = new SM(count - 1, count3); // Creando sparse matrix 1

		  ip.close();

		  ifstream ip2(capa);

		  if(!ip2.is_open()) std::cout << "ERROR: File Open" << '\n';

		  string dato2;

		  int row = 0;


		  while(ip2.good() && row < count - 1){

		    int column = 0;
		    while(column < count3 - 1){
		      getline(ip2,dato2,';');
					if(dato2 != "x"){
						insertEntry(row, column, dato2);
					}

		      //std::cout << "Dato: "<<dato2<< '\n';
		      //std::cout << "Column: "<<column<< '\n';
		      column = column + 1;

		    }
		    getline(ip2,dato2,'\n');
				if(dato2 != "x"){
				insertEntry(row, column, dato2);
		   	}
		    //std::cout << "Dato: "<<dato2<< '\n';
		    //std::cout << "Column: "<< "4"<< '\n';
		    //std::cout << "Row: "<<row << '\n';
		    //std::cout << "-------------------" << '\n';
		    row = row + 1;

		  }
		  ip2.close();

		}
}

void SM::printMatrix(){ //Imprimir matrix

	printColumnHeader();
	int counter = 0;
	RowNode * curr = rowHead;
	while (counter < n){
		/*
		while loop with a counter to iterate through the maximum number of rows
		if the counter matches the current row number then it prints the columns inside that row and points to next
		otherwise it prints out empty
		if the current row is null and the counter hasn't reached the end
		then it will print zeros for the rest of the iterations
		*/
		cout << setw(3) << counter << "|";
		if (curr != NULL){
			if (counter == curr->rowNo){
				curr->printCol(m);
				curr = curr->nextRow;
				cout << endl;
			}
			else // No sirve de nada
      {
        printEmptyRow(counter);

      }

		}
		else
    {
      printEmptyRow(counter);

    }

		counter++;
	}
	cout << endl << "-----------------------------------------------------------" << endl;
}

void SM::graphvizMatrix(string capa){ //Crear graphviz matrix




	//ofstream file;
	file.open(capa +".dot");
  file << "digraph Sparce_Matrix {\n";
  file << "node [shape=box]\n";
  file << "Mt[ label = \"Matrix\", width = 1.5, style = filled, group = 1 ];\n";

	graphvizMatrix2();

  int i;
  /*for(i=1; i<=n-2; i++){
  file << "e"<<i-1<<"[ shape = point, width = 0 ];\n";


}*/



	//dot Matrix.dot -Tpng -o Matrix.png

	//graphvizColumnHeader(); //Columnheaders de la matrix
	int counter = 0;
  int counter2 =0;
  int counter3 = 0;
	RowNode * curr = rowHead;
	while (counter < n){
		/*
		while loop with a counter to iterate through the maximum number of rows
		if the counter matches the current row number then it prints the columns inside that row and points to next
		otherwise it prints out empty
		if the current row is null and the counter hasn't reached the end
		then it will print zeros for the rest of the iterations
		*/
		//cout << setw(3) << counter << "|"; Rowheaders de la matrix
		//file<<"U"<< counter  <<"[label = \""<<"R"<< counter <<"\"    width = 1.5 style = filled, group = 1 ];"<<"\n";
		//file<<"U"<< counter <<"->" <<"U"<< counter + 1 <<"\n";

		/*if (counter != n-1){
		file<<"U"<< counter <<"->" <<"U"<< counter + 1 <<";" <<"\n";
	  }
		if (counter > 0){
		file<<"U"<< counter <<"->" <<"U"<< counter - 1 <<";" <<"\n";
  }*/


		//file<<"U"<< counter + 1<<"->" <<"U"<< counter;
		//file << counter <<"\n";
		if (curr != NULL){

			if (counter == curr->rowNo){

        //cout<<"Contador filas: "<<counter<<"\n";
        file<<"U"<< counter  <<"[label = \""<<"R"<< counter <<"\"    width = 1.5 style = filled, group = 1 ];"<<"\n";

        if(counter2 == 0){
          file <<"Mt->U"<< counter << ";" << "\n";

        }

        else if (counter2 != 0){

          int c = counter;

 				 while(c > 0){
 					 int r = c-1;
 					 string rc;
 					 rc =to_string(r);
 					 //cout<<rc<<"\n";
 					 //int _dato  = atoi(rc.c_str());

           if(buscarLista(lista2, rc) == true){
 						 //cout<<"Encontrado"<< "\n";
 						 //cout<<"Nodo arriba"<<"\n";
 					 }

 					 else if(buscarLista(lista2, rc) == false){
 						 //cout<<"Encontrado"<< "\n";
 						 file<<"U"<<counter<<" -> U" << c -1 << ";"<<"\n";
 						 file<<"U"<<c - 1<<" -> U" << counter << ";"<<"\n";
 						 //cout<<"Link Nodo previo"<<"\n";
             //cout<<"-----------------------------------"<<"\n";
 						 c = 1;
 					 }


 					 //cout<<c<<"\n";
 					 c--;

 				 }

        }

        if(counter2 > 1){

          //file << "e"<<counter3<<"[ shape = point, width = 0 ];\n";

          file<<"{ rank = same; U"<<counter-1<<"; e"<< counter3<<"}" <<"\n";

          counter3++;

        }

				curr->graphvizCol(m,counter,n);
				curr->graphvizCol2(m,counter);
				curr = curr->nextRow;
				cout << endl;
        counter2++;
			}
			else {// No sirve de nada

        string r;

        r =to_string(counter);

        data2 = r;

		    insertarLista(lista2,data2);

        graphvizEmptyRow(counter);

      }
		}
		else{

      string r;

      r =to_string(counter);

      data2 = r;

      insertarLista(lista2,data2);

      graphvizEmptyRow(counter);

  }

		counter++;
	}

  graphvizColumnHeader();

	if(counter2 -1 > 1)
	{
		file<<"A"<< count4 <<"-> e0[ dir = none, color = \"white\" ];" <<"\n";

	}

	//file <<"Mt->U0" << ";" << "\n";
	//file <<"Mt->A0" << ";" << "\n";



  //int i;
/*  for(i=1; i<=n-2; i++){
  //file << "e"<<i-1<<"[ shape = point, width = 0 ];\n";

  file<<"{ rank = same; U"<<i<<"; e"<< i - 1<<"}" <<"\n";


}*/

  //file<<"A"<< m-1 <<"-> e0[ dir = none, color = \"white\" ];" <<"\n";

  /*for(i=1; i<n-2; i++){

  file<<"e"<< i-1 <<"-> e"<< i<<"[ dir = none, color = \"white\" ];" <<"\n";


}*/
if(counter3 -1 > 0){

for(i=0; i<counter3 - 1; i++){

file<<"e"<< i<<"-> e"<< i + 1 <<"[ dir = none, color = \"white\" ];" <<"\n";


}
}


	file << "}\n";
	file.close();


}

void SM::graphvizMatrix2(){ //Crear graphviz matrix


  int i;

	int counter = 0;
  int counter2 =0;
  int counter3 = 0;
	RowNode * curr = rowHead;
	while (counter < n){

		if (curr != NULL){

			if (counter == curr->rowNo){


        if(counter2 > 1){

          file << "e"<<counter3<<"[ shape = point, width = 0 ];\n";

          //file<<"{ rank = same; U"<<counter-1<<"; e"<< counter3<<"}" <<"\n";

          counter3++;


        }

				curr = curr->nextRow;
				cout << endl;
        counter2++;
			}
			else {// No sirve de nada


      }
		}
		else{


  }

		counter++;
	}

	countere = counter3 -1;

}

void SM::scsscapas(string capa){ //Crear graphviz matrix

  //file << "Colores capa"<<"\n";

	int counter = 0;
	RowNode * curr = rowHead;
	while (counter < n){

		if (curr != NULL){
			if (counter == curr->rowNo){
				curr->scssCol(m, counter, n);
				//curr->graphvizCol2(m);
				curr = curr->nextRow;
				cout << endl;
			}
			else {
        scssEmptyRow(counter);

      }
		}
		else{
      scssEmptyRow(counter);

  }

		counter++;
	}


}

void SM::linealizacionfcapas(string capa){ //Crear graphviz matrix

	file.open(capa +".dot");
	file<<"digraph firsGraph{" <<"\n";
	file<<"node [shape=record];" <<"\n";
	file<<"rankdir=LR;" <<"\n";
	file<<"node0 [label=\" Inicio \"];" <<"\n";


	int counter = 0;
	RowNode * curr = rowHead;
	while (counter < n){

		if (curr != NULL){
			if (counter == curr->rowNo){
				curr->linfCol(m, counter, n);
				curr = curr->nextRow;
				cout << endl;
			}
			else {
        //scssEmptyRow(counter);

      }
		}
		else{
      //scssEmptyRow(counter);

  }

		counter++;
	}
  file<<"}" <<"\n";
	file.close();
	counterlinf = 1;


}

void SM::linealizacionccapas(string capa){ //Crear graphviz matrix

	file.open(capa +".dot");
	file<<"digraph firsGraph{" <<"\n";
	file<<"node [shape=record];" <<"\n";
	file<<"rankdir=LR;" <<"\n";
	file<<"node0 [label=\" Inicio \"];" <<"\n";

	lincCol();


  file<<"}" <<"\n";
	file.close();
	counterlinc = 1;


}


void html(string nombre, int div, string nombre2){ //Crear graphviz matrix

	file.open(nombre +".html");
  file << "<!DOCTYPE html>\n";
  file << "<html>\n";
  file << "<head>\n";
	file << "<!-- Link to our stylesheet Painting our Pixel Art -->\n";
  file << "<link rel=\"stylesheet\" href=\""<< nombre2 <<".scss\">\n";
  file << "</head>\n";
  file << "<body>\n";
	file << "<!-- div container representing the canvas -->\n";
  file << "<div class=\"canvas\">\n";
  file << "<!-- div containers representing each pixel of the drawing (18px x 21px = 378 pixels) -->\n";
  int count = 0;
  while(count < div){
    file<<"<div class=\"pixel\"></div>\n";
    count++;
  }

  file << "</div>\n";
	file << "</body>\n";
  file << "</html>\n";
	file.close();

}

void scss(int wp, int hp, int w, int h){ //Crear graphviz matrix

  int ch = hp * h;
  int cw = wp * w;

	//file.open(nombre +".scss");
  filescss << "body {\n";
  filescss << "background: #C0C0C0;\n";
  filescss << "height: 100vh;\n";
	filescss << "display: flex;\n";
  filescss << "justify-content: center;\n";
  filescss << "align-items: center;\n";
  filescss << "}\n";
	filescss << ".canvas {\n";
  filescss << "width:"<< cw <<"px;\n";
  filescss << "height:"<< ch <<"px;\n";
  filescss << "}\n";
	filescss << ".pixel {\n";
  filescss << "width: "<< wp <<"px;\n";
  filescss << "height: "<< hp << "px;\n";
  filescss << "float: left;\n";
  filescss << "}\n";
	//file.close();

}


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

inicial(string inicial){

  std::string archivo = inicial;
  std::string delimiter = ".csv";

  size_t pos = 0;
  std::string nombre;

  while ((pos = archivo.find(delimiter)) != std::string::npos) {
      nombre = archivo.substr(0, pos);
      //std::cout << token << std::endl;
      //count = count +1;
      //std::cout << count << std::endl;
      archivo.erase(0, pos + delimiter.length());
  }

	string commando = "mkdir Exports\\"+ nombre;

	system(commando.c_str());

	//dot Matrix.dot -Tpng -o Matrix.png

  filescss.open("Exports\\"+ nombre + "\\"+ nombre +".scss");



  int w = 0;
  int h = 0;
  int pw = 0;
  int ph = 0;

  //ifstream ip("C:\\Users\\Fernando Armira\\Downloads\\Git\\EDD_2S2019_PY1_201503961\\Images\\"+nombre+"\\"+inicial);
	ifstream ip("Images\\"+nombre+"\\"+inicial);

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string dato;
  /*string lastname;
  string age;
  string weight;
  string a;*/
  int count = 0;
  int count2 = 0;
  int rw, rh, rpw, rph;

  while(ip.good()){

    getline(ip,dato,'\n');
    std::string s = dato;
    //std::cout << "cadena: "<<s<< '\n';
    std::string delimiter = ";";

    size_t pos = 0;
    std::string token;
    //count2 = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        //std::cout << token << std::endl;
        //std::cout << count2 << std::endl;
        count2 = count2 +1;
        s.erase(0, pos + delimiter.length());
    }
    count2 = count2 + 1;
    //std::cout << s << std::endl;

    count = count + 1;

  }

  int count3 = count2/(count - 1);
  ip.close(); // cerrando aux archivo imagen inicial

  ifstream ip2("Images\\"+nombre+"\\"+inicial);

  if(!ip2.is_open()) std::cout << "ERROR: File Open" << '\n';

  string dato2;

  int row = 0;

  while(ip2.good() && row < count - 1){

    int column = 0;
    while(column < count3 - 1){
      getline(ip2,dato2,';');
      /*if(dato2 != "x"){
        insertEntry(row, column, dato2);
      }*/
      if(row > 0){

        if (dato2 == "0"){
        std::cout << "Archivo de configuracion"<< '\n';
        std::cout << "Layer: "<<dato2<< '\n';
      }
      else{
        std::cout << "Capas imagen"<< '\n';
        std::cout << "Layer: "<<dato2<< '\n';

      }

      }
      //std::cout << "Column: "<<column<< '\n';
      column = column + 1;

    }
    getline(ip2,dato2,'\n');
    /*if(dato2 != "x"){
    insertEntry(row, column, dato2);
  }*/

    if(row > 0){

      if(dato2 == "config.csv"){

        std::cout << "Nombre: "<<dato2<< '\n';
        //std::cout << "Column: "<< column << '\n';
        //std::cout << "Row: "<<row << '\n';

        ifstream ip("Images\\"+nombre+"\\"+dato2);

        if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

        string dato;
        int count = 0;
        int count2 = 0;

        while(ip.good()){

          getline(ip,dato,'\n');
          std::string s = dato;
          std::string delimiter = ";";

          size_t pos = 0;
          std::string token;
          while ((pos = s.find(delimiter)) != std::string::npos) {
              token = s.substr(0, pos);
              count2 = count2 +1;
              s.erase(0, pos + delimiter.length());
          }
          count2 = count2 + 1;
          count = count + 1;

        }

        int count3 = count2/(count - 1);
        ip.close();

        ifstream ip2("Images\\"+nombre+"\\"+dato2);

        if(!ip2.is_open()) std::cout << "ERROR: File Open" << '\n';

        string dato2;

        int row = 0;

        while(ip2.good() && row < count - 1){

          int column = 0;
          while(column < count3 - 1){
            getline(ip2,dato2,';');
            column = column + 1;
            if(row > 0){
              if(dato2 == "image_width"){
                std::cout << "Image width: "<<'\n';
                rw = row;

              }
              else if(dato2 == "image_height"){
                std::cout << "Image heigth: "<<'\n';
                //std::cout <<row<<'\n';
                rh = row;

              }
              else if(dato2 == "pixel_width"){
                std::cout << "Pixel width: "<<'\n';
                rpw = row;
              }
              else if(dato2 == "pixel_height"){
                std::cout << "Pixel heigth: "<<'\n';
                rph = row;
              }
            }

          }
          getline(ip2,dato2,'\n');

              std::cout <<dato2<<'\n';

              if(row == rw){
                w = atoi(dato2.c_str());
              }
              else if(row == rh){
                h = atoi(dato2.c_str());
              }
              else if(row == rpw){
                pw = atoi(dato2.c_str());
              }
              else if(row == rph){
                ph = atoi(dato2.c_str());
              }

          row = row + 1;

        }
        ip2.close();

        scss(pw,ph,w,h);

      }
      else{
        std::cout << "Nombre: "<<dato2<< '\n';

        /*cout<<h<<"\n";
        cout<<w<<"\n";
        cout<<ph<<"\n";
        cout<<pw<<"\n";*/



        std::string capa = dato2;
        std::string delimiter = ".csv";

        size_t pos = 0;
        std::string token;
        int count = 0;
        while ((pos = capa.find(delimiter)) != std::string::npos) {
            token = capa.substr(0, pos);
            //std::cout << token << std::endl;
            //count = count +1;
            //std::cout << count << std::endl;
            capa.erase(0, pos + delimiter.length());
        }

        SM * ms = new SM(h, w); // Creando sparse matrix 1

                    ms ->readElements("Images\\"+nombre+"\\"+dato2);
                		//ms ->printMatrix();
                		ms ->graphvizMatrix("Exports\\"+ nombre + "\\"+ token);
                    ms ->scsscapas(token);
										ms ->linealizacionfcapas("Exports\\"+ nombre + "\\linf"+ token);
										ms ->linealizacionccapas("Exports\\"+ nombre + "\\linc"+ token);

                    counterscss = 1;

										string commando2 = "dot Exports\\"+ nombre + "\\" + token + ".dot -Tpng -o Exports\\"+ nombre + "\\" + token + ".png";

										system(commando2.c_str());

										string commando3 = "dot Exports\\"+ nombre + "\\linf" + token + ".dot -Tpng -o Exports\\"+ nombre + "\\linf" + token + ".png";

										system(commando3.c_str());

										string commando4 = "dot Exports\\"+ nombre + "\\linc" + token + ".dot -Tpng -o Exports\\"+ nombre + "\\linc" + token + ".png";

										system(commando4.c_str());

										//dot Matrix.dot -Tpng -o Matrix.png


                		delete ms;

                    //mostrarLista(lista);

                    //mostrarLista(lista2);

                    //mostrarLista(lista3);

                    while(lista != NULL){
                    eliminarLista(lista,data);
                    }

                    while(lista2 != NULL){
                    eliminarLista(lista2,data2);
                    }

                    while(lista3 != NULL){
                    eliminarLista(lista3,data3);
                    }

										countere = 0;
										count4 = 0;
										color = " ";



                    /*cout<<"Reporte 1"<<"\n";
                    reportarLista(lista);
                    eliminarElemento(lista);
                    cout<<"Reporte 2"<<"\n";
                    reportarLista(lista);*/


      }

    }



    row = row + 1;

  }
  ip2.close(); // cerrando archivo imagen inicial



  int div= h*w;

  html("Exports\\"+ nombre + "\\"+ nombre,div,nombre);

  filescss.close();

}

int main(){ //Main

  int op;     // opcion del menu
  string ainicial;


    do
    {
        menu1();  cin>> op;

        switch(op)
        {
            case 1:
            cout<< "\n Ingrese nombre archivo inicial: ";
            cin>> ainicial;
            inicial(ainicial);


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

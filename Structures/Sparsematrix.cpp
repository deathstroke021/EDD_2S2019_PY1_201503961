#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

ofstream file;

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
	void graphvizCol(int mSize, int n);
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

void RowNode::graphvizCol(int mSize, int n){ //Imprimir columna
	int counter = 0;
	int counter2 = 0;
	ColumnNode *curr = colHead;

	//file.open("archivo.txt");


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
				//cout << right << setw(5) << curr->value;
				//file << "primera línea\n";
				//file << right << setw(5) << curr->value;
				file << "N"<< counter2 <<"_L"<< n << " [label = \""<< curr->value <<"\" width = 1.5, group ="<< counter + 2 <<"];"<<"\n";
				//file << curr->value <<" "<<counter<<"\n";




				curr = curr->nextCol;
				counter2++;
			}
			else{
				//cout << setw(5) << right << "0";
			}
		}
		else{
			//cout << setw(5) << right << "0";
		}
		counter++;

	}
	file<<"U"<<n<<" -> N0" <<"_L"<< n <<"\n";
	//file.close();

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

public:
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void graphvizMatrix();
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


	for (int i = 0; i < m; i++){
		//cout << right << setw(5) << i;
		file <<"A"<<i<< "[label =\"C"<<i<<"\" width = 1.5 style = filled, group ="<<2+i<<"];"<<"\n";
		if (i != m-1){
		file<<"A"<< i <<"->" <<"A"<< i + 1 <<"\n";
	  }
		if (i > 0){
		file<<"A"<< i <<"->" <<"A"<< i - 1 <<"\n";
	  }



		//file << i << "\n";
	}
	//cout << endl;
	file <<"{ rank = same; Mt; ";

	for (int i = 0; i < m; i++){
		//cout << right << setw(5) << i;
		file <<"A"<<i<<"; ";


		//file << i << "\n";
	}
	file <<"}"<<"\n";

}

void SM::printEmptyRow(int counter){ //Imprimir filas vacias
	for (int i = 0; i < m; i++){
		cout << setw(5) << right << "0";
	}
	cout << endl;
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
void SM::readElements(){ //Ingresando elementos matriz
		{
			ifstream ip("f.csv");

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

		  ifstream ip2("f.csv");

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
				printEmptyRow(counter);
		}
		else
			printEmptyRow(counter);
		counter++;
	}
	cout << endl << "-----------------------------------------------------------" << endl;
}

void SM::graphvizMatrix(){ //Crear graphviz matrix

	//ofstream file;
	file.open("Matrix.dot");
  file << "digraph Sparce_Matrix {\n";
  file << "node [shape=box]\n";
  file << "Mt[ label = \"Matrix\", width = 1.5, style = filled, group = 1 ];\n";
	file << "e0[ shape = point, width = 0 ];\n";
	file << "e1[ shape = point, width = 0 ];\n";

	//dot Matrix.dot -Tpng -o Matrix.png

	graphvizColumnHeader(); //Columnheaders de la matrix
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
		//cout << setw(3) << counter << "|"; Rowheaders de la matrix
		file<<"U"<< counter  <<"[label = \""<<"R"<< counter <<"\"    width = 1.5 style = filled, group = 1 ];"<<"\n";
		//file<<"U"<< counter <<"->" <<"U"<< counter + 1 <<"\n";

		if (counter != n-1){
		file<<"U"<< counter <<"->" <<"U"<< counter + 1 <<"\n";
	  }
		if (counter > 0){
		file<<"U"<< counter <<"->" <<"U"<< counter - 1 <<"\n";
	  }

		//file<<"U"<< counter + 1<<"->" <<"U"<< counter;
		//file << counter <<"\n";
		if (curr != NULL){
			if (counter == curr->rowNo){
				curr->graphvizCol(m,counter);
				curr = curr->nextRow;
				cout << endl;
			}
			else // No sirve de nada
				printEmptyRow(counter);
		}
		else
			printEmptyRow(counter);
		counter++;
	}
	file <<"Mt->U0" <<"\n";
	file <<"Mt->A0" <<"\n";


	file << "}\n";
	file.close();
}

int main(){ //Main

	ifstream ip("f.csv");

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

	SM *s = new SM(count - 1, count3); // Creando sparse matrix 1

	ip.close();


		s->readElements();
		s->printMatrix();
		s->graphvizMatrix();

		delete s;

	system("pause");
	return 0;
}

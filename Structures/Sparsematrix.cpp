#include <iostream>
using namespace std;

class node{ //clase nodo
public:
  int data;
  node* right;
  node* left;
  node* down;
  node* up;

  node(int data){
    this->data = data;
    right = NULL;
    left = NULL;
    down = NULL;
    up = NULL;
  }
};

class matrix{
  public:
    node *head;
    matrix(){
      node *temp = new node(0);
      head = temp;
    }
    void add(int value, int x, int y){
      add_x_header(x); // Cabecera en x
      add_y_header(y); // Cabecera en y
      node *new_node = new node(value);
      add_x(new_node, x);
      add_y(new_node, y);

    }

    void add_x(node *new_node, int x){
      node *temp = head;
      while(temp->data != x){
        temp = temp->right;

      }
      if(temp->down == NULL){
        temp->down = new_node;
        new_node->up = temp;
      }

    }
    void add_y(node *new_node, int y){
      node *temp = head;
      while(temp->data != y){
        temp = temp->down;

      }
      if(temp->right == NULL){
        temp->right = new_node;
        new_node->left = temp;


      }

    }

    void add_x_header(int x){
      if(head->right == NULL){
        node *temp = new node(x);
        head->right = temp;
        temp->left = head;
      }else{
        node *temp = head;
        while(temp->right !=NULL && temp->right->data<x){
          temp = temp->right;
        }
        if (temp->right==NULL){
          node *new_temp = new node(x);
          temp->right = new_temp;
          new_temp->left = temp;
        }else if (temp->right!=NULL && temp->right->data != x){
          node *new_temp = new node(x);
          node *der = temp->right;
          temp->right = new_temp;
          new_temp->left = temp;
          new_temp->right = der;
          der->left = new_temp;

        }

        }
      }

    void add_y_header(int y){
      if (head->down==NULL){
        node *temp = new node(y);
        head->down = temp;
        temp->up = head;
      }else{
        node *temp = head;
        while(temp->down!=NULL && temp->down->data<y){
          temp = temp->down;
        }
        if(temp->down==NULL){
          node *new_temp = new node(y);
          temp->down = new_temp;
          new_temp->up = temp;
        } else if (temp->down!=NULL && temp->down->data != y){
          node *new_temp = new node(y);
          node *der = temp->down;
          temp->down = new_temp;
          new_temp->up = temp;
          new_temp->down = der;
          der->up = new_temp;
        }
      }
    }

    void print_headers(){
      print_x_header();
      cout<<"!\n";
      print_y_header();
    }

    void print_x_header(){
      node *temp = head;
      while(temp->right != NULL){
        cout<<temp->data;
        cout<<"->";
        temp = temp->right;
      }
      cout<<temp->data;
      cout<<"\n";

      }

      void print_y_header(){
        node *temp = head->down;
        while(temp->down != NULL){
          cout<<temp->data;
          cout<<"\n";
          cout<<"!\n";
          temp = temp->down;
        }
        cout<<temp->data;
        cout<<"\n";
        }

        void print_nodes_x(){
          node *temp = head->right;
          while(temp->right != NULL){
            cout<<temp->data;
            cout<<"->";
            if(temp->down !=NULL){
              cout<<temp->down->data;
            }
            cout<<"\n";
            temp = temp->right;
          }
          cout<<temp->data;
          cout<<"->";
          if(temp->down !=NULL){
            cout<<temp->down->data;
          }
          cout<<"\n";
        }

        void print_nodes_y(){
          node *temp = head->down;
          while(temp->down != NULL){
            cout<<temp->data;
            cout<<"->";
            if(temp->right !=NULL){
              cout<<temp->right->data;
            }
            cout<<"\n";
            temp = temp->down;
          }
          cout<<temp->data;
          cout<<"->";
          if(temp->right !=NULL){
            cout<<temp->right->data;
          }
          cout<<"\n";
        }


};


int main(){

  matrix *sm = new matrix;
  sm->add(10,2,1);
  sm->add(12,5,2);
  sm->add(25,3,4);
  sm->add(15,3,6);
  sm->add(35,5,3);
  sm->add(20,7,4);
  sm->print_headers();
  sm->print_nodes_x();
  cout<<"\n";
  sm->print_nodes_y();

  //node *temp = new node(1);
  //cout<<temp->data;
  //cout<<"\n";
  return 0;

}

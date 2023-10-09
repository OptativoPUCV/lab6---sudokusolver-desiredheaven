#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    
      for (int i = 0; i<9; i++)
        {
          int cont[10] = {0};
          
          for (int j =0; j<9; j++)
            {
              int val = n->sudo[i][j];
              if (val != 0)
              {
               if (cont[val] == 0) 
               {
                cont[val] = 1;
               }
                else 
               {
                 return 0;
               }
            }
        }
}
    for (int i = 0; i < 9; i++) {
    int cont[10] = {0};

    for (int j = 0; j < 9; j++) {
      int val = n->sudo[j][i];

      if (val != 0) {
        if (cont[val] == 0) {
          cont[val] = 1;
        } else {
          return 0;  
        }
      }
    }
  }
   for (int k = 0; k < 9; k++) {
    int cont[10] = {0};

    for (int p = 0; p < 9; p++) {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      
      
      
int val = n->sudo[i][j];
      if (val != 0) {
        if (cont[val] == 0) {
          cont[val] = 1;
        } else {
          return 0;
        }
      }
    }
  }

  return 1;  
}

List* get_adj_nodes(Node* n){
    List* list = createList();
    int i, j;
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    n->sudo[i][j] = k;

                    if (is_valid(n)){
                    Node* aux = copy(n);
                    pushBack(list, aux);
                    }
                    n->sudo[i][j] = 0;
                }
                return list;
            }
        }
    }
    return list;
}



int is_final(Node* n){
    for (int i= 0; i < 9 ; i ++)
      {
        for (int j = 0; j < 9; j++)
          {
            if (n->sudo[i][j]==0){

              return 0;
            }
          }
      }
  return 1;
}

Node* DFS(Node* inicial, int* cont) {
  Stack* pila = createStack();
  if (pila == NULL) {
    return NULL;
  }
  *cont = 1;
  push(pila, inicial);

  while (get_size(pila) != 0) {
    Node* nodo = top(pila);
    pop(pila);

    (*cont)--;

    if (is_final(nodo) == 1) {
      return nodo;
    }

    List* adyacentes = get_adj_nodes(nodo);
    Node* aux = getFirst(adyacentes);

    while (aux != NULL) {
      push(pila, aux);
      aux = getNext(adyacentes);

      (*cont)++;
    }

    free(nodo);
  }

  if (*cont == 0) {
    return NULL;
  }

  free(inicial);
  return NULL;
}





/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
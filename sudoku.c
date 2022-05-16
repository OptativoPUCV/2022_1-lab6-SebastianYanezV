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

int is_valid(Node* n)
{
  int *arreglo;
  int i, j, k, p, numero;

  for (i = 0 ; i < 9 ; i++)
  {
    arreglo = (int*) calloc(10, sizeof(int));

    for (j = 0 ; j < 9 ; j++)
    {
      if (n->sudo[i][j] == 0) continue;

      numero = n->sudo[i][j];
      
      if (arreglo[numero] == 0) arreglo[numero] = 1;
      else
      {
        if (arreglo[numero] == 1) return 0;
      }
    }
  }

  for (i = 0 ; i < 9 ; i++)
  {
    arreglo = (int*) calloc(10, sizeof(int));

    for (j = 0 ; j < 9 ; j++)
    {
      if (n->sudo[j][i] == 0) continue;

      numero = n->sudo[j][i];
      
      if (arreglo[numero] == 0) arreglo[numero] = 1;
      else
      {
        if (arreglo[numero] == 1) return 0;
      }
    }
  }

  for (k = 0 ; k < 9 ; k++)
  {
    arreglo = (int*) calloc(10, sizeof(int));

    for (p = 0 ; p < 9 ; p++)
    {   
      int a = 3 * (k/3) + (p/3);
      int b = 3 * (k%3) + (p%3);

      if (n->sudo[a][b] == 0) continue;

      numero = n->sudo[a][b];

      if (arreglo[numero] == 0) arreglo[numero] = 1;
      else
      {
        if (arreglo[numero] == 1) return 0;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list = createList();

  int i, j;
  int cont;

  for (i = 0 ; i < 9 ; i++)
  {
    for (j = 0 ; j < 9 ; j++)
    {
      cont = 1;

      if (n->sudo[i][j] == 0)
      {
        Node *nodo = createNode();

        while (cont <= 9)
        {
          nodo = copy(n);
          nodo->sudo[i][j] = cont;
          if (is_valid(nodo) == 1) pushBack(list, nodo);
          cont++;
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n)
{
  int i, j;
  int final = 1;

  for (i = 0 ; i < 9 ; i++)
  {
    for (j = 0 ; j < 9 ; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        final = 0;
        return final;
      }
    }
  }
  return final;
}

Node* DFS(Node* initial, int* cont)
{
  Stack *S = createStack();
  push(S, initial);

  int largoS = get_size(S);

  while (largoS != 0)
  {
    Node *nodo = top(S);
    pop(S);

    if (is_final(nodo) == 1) return nodo;

    List *nodosAdj = get_adj_nodes(nodo);
    Node *aux = first(nodosAdj);

    while (aux != NULL)
    {
      push(S, aux);
      aux = next(nodosAdj);
    }

    largoS = get_size(S);
    free(nodo);
    (*cont)++;
  }
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
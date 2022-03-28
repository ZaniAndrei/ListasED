#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//---------------------------------------
typedef struct NoLista* PtrNoLista;

typedef struct NoLista{
  int elemento;//int
  PtrNoLista proximo;  //proximo(PtrNoLista)
}NoLista;


typedef struct{
  PtrNoLista inicio;//inicio/primeiro(PtrNoLista)
  int qtde;//qtde elementos
}ListaOrdenada;
//NoLista
//---------------------------------------
//---------------------------------------
//imprimir lista

//opcionais(tarefa):
//maximo(ultimo)
//minimo(primeiro)
//proximo(proximo dele, se existir)
//anterior(anterior dele, se existir)

//iniciar lista
void iniciaListaOrdenada(ListaOrdenada *l) {
  l->inicio = NULL;
  l->qtde = 0;
}

//esta vazia
bool estaVaziaListaOrdenada(ListaOrdenada *l){
  return(l->qtde == 0); //ou inicio == NULL
}

//tamanho
int tamanhoListaOrdenada(ListaOrdenada *l){
  return(l->qtde);
}

void inserirListaOrdenada(ListaOrdenada *l, int x){
  PtrNoLista novo; //criar ponteiro para um novo no(novo)
  novo = malloc(sizeof(NoLista)); //alocar memoria do novo nó(novo)
  novo->elemento = x; //copiar o valor(x) para o novo nó(novo->x)

  //situação A:1a inserção
  //situação B:elemento < primeiro elemento da lista
  //situação C:elemento no meio ou fim da lista

  //se for A ou B:
  if (estaVaziaListaOrdenada(l) || novo->elemento < l->inicio->elemento) {
    novo->proximo = l->inicio; //proximo do novo nó aponta para o inicio da lista
    l->inicio = novo; //inicio aponta para o novo nó
  //senao: (c)
  }else{
    PtrNoLista aux = l->inicio;
    //parar qnd:
    //proximo do aux = NULL
    //proximo do aux(valor>elemento)
    //percorrer a lista e encontrar posicao de inserçao(aux)
    //(proximo do aux tiver um valor>elemento)
    while (aux->proximo != NULL && aux->proximo->elemento <= x) {
      aux = aux->proximo;
    }
    //AUX: uma posição antes do novo elemento
    novo->proximo = aux->proximo; //1. proximo do novo nó aponta para o proximo do aux
    aux->proximo = novo; //2.proximo do aux aponta para o novo nó
  }
      //proximo de aux é o novo elemento
  l->qtde++; //qtde++
}


void imprimirListaOrdenada(ListaOrdenada *l){
  printf("Lista = [");
  PtrNoLista temp;
  for (temp = l->inicio; temp != NULL; temp = temp->proximo) {
    printf("%d ", temp->elemento);
  }
  printf("]\n");
}

//destruir lista
//inserir elemento
//remover elemento
//pesquisar um elemento
//



int main(int argc, char const *argv[]) {
  ListaOrdenada lista;
  iniciaListaOrdenada(&lista);
  if (estaVaziaListaOrdenada(&lista)) {
    printf("ESTA VAZIA AHAAHAHAHHAHAHHA\n");
  }
  printf("Tamanho = %d\n",tamanhoListaOrdenada(&lista));

  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista, 10);//situação A
  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista, 5);//situação B
  imprimirListaOrdenada(&lista);// 5 10
  inserirListaOrdenada(&lista, 8);//situação C
  imprimirListaOrdenada(&lista);// 5 8 10
  inserirListaOrdenada(&lista, 99);//situação C
  imprimirListaOrdenada(&lista);// 5 8 10 99

  return 0;
}

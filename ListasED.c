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

//inserir elemento
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

//pesquisar um elemento
bool pesquisaListaOrdenada(ListaOrdenada *lista, int valor){
  //percorrer a lista e encontrar ou não o elemento
  PtrNoLista aux;
  for (aux = lista->inicio; aux != NULL; aux = aux->proximo) {
    if (aux->elemento == valor) {
      return true;
    }
    if (aux->elemento > valor) {
      return false;
    }
  }
  return false;
}
//remover elemento
bool removerListaOrdenada(ListaOrdenada *lista, int valor){
  PtrNoLista aux;
  //situação 1: LISTA vazia
  //Situação 2: valor < primeiro elemento da LISTA
    if (estaVaziaListaOrdenada(lista) || valor < lista->inicio->elemento) {
      return false;
    }
  //situação 3: valor == primeiro elemento da LISTA
  if (valor == lista->inicio->elemento) {
    //criar um auxiliar
    PtrNoLista aux;
    //aux recebe inicio
    aux = lista->inicio;
    //inicio recebe o prox do inicio
    lista->inicio = lista->inicio->proximo;
    //libera memoria de aux
    free(aux);
    //qtde é decrementada
    lista->qtde--;
    //return vdd
    return(true);
  }
  //situação 4: percorrer a LISTA
  aux = lista->inicio;
  while (aux->proximo != NULL && aux->proximo->elemento < valor) {
    aux = aux->proximo;
    //aux->proximo->elemento == valor (achei)
    //aux->proximo->elemento != valor (nao achei)
  }
  //aux->proximo = NULL == (falso)
  //aux->proximo->elemento != valor (falso)
  if (aux->proximo == NULL || aux->proximo->elemento != valor) {
    return false;
  }
  //aux->proximo->elemento == valor //logica
  //4A:nao achei depois de percorrer
  //4B:achei depois de percorrer
  PtrNoLista remove;
  remove = aux->proximo;

  aux->proximo = aux->proximo->proximo;
  free(remove);
  lista->qtde--;
  return (true);
}

//destruir lista
void destruirListaOrdenada(ListaOrdenada *lista){
  PtrNoLista aux;
  while (tamanhoListaOrdenada(lista) != 0) {
    printf("Lista vazia\n");
    printf("Removendo %d\n", aux->elemento );
    aux = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    free(aux);
    lista->qtde--;
  }
}
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
  inserirListaOrdenada(&lista, 8);//situação B
  imprimirListaOrdenada(&lista);// 5 10
  inserirListaOrdenada(&lista, 8);//situação C
  imprimirListaOrdenada(&lista);// 5 8 10
  inserirListaOrdenada(&lista, 99);//situação C
  imprimirListaOrdenada(&lista);// 5 8 10 99


  int cont1 = 0;
  if (pesquisaListaOrdenada(&lista, 99)) {
    printf("VaLOR ENCONTRADO\n");
  }else{
    printf("NAO ENCONTROU VALOR\n");
  }

  removerListaOrdenada(&lista, 8);
  imprimirListaOrdenada(&lista);
  removerListaOrdenada(&lista, 8);
  imprimirListaOrdenada(&lista);
  destruirListaOrdenada(&lista);
  return 0;
}

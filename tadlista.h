#include <string.h>
#include <stdlib.h>

typedef void *t_dado;

typedef struct tipo_noh {
  struct tipo_noh *ant;
  struct tipo_noh *prox;
  t_dado dado;
} *tnoh;

typedef struct {
  int tamlista;
  tnoh prim;
  tnoh ult;
} tcabec;

typedef tcabec *Lista;

Lista criaLista(void);
int lenLista(Lista lst);
Lista appendLista(Lista lst,t_dado dado);
Lista insereLista(Lista lst, t_dado dd, int pos);
t_dado dadoLista(Lista lst, int pos);
t_dado removeLista(Lista lst, int pos);
Lista limpaLista(Lista lst);
Lista destroiLista(Lista lst);


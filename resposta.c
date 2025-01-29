#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"  

#define MAX 128

//definir os tipos projeto/membro/relacao
typedef struct {
    char id[MAX];
    char descricao[MAX];
} t_projeto;

typedef struct {
    char id[MAX];
    char nome[MAX];
} t_membro;

typedef struct {
    char id_membro[MAX];
    char id_projeto[MAX];
} t_relacao;


// função que sobe projetos dos arquivos para a lista
Lista load_projetos(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Erro ao carregar arquivo!! %s\n", fileName);
        return NULL;
    }

    Lista lst = criaLista();
    t_projeto *projeto;
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        projeto = (t_projeto *)malloc(sizeof(t_projeto));
        if (sscanf(linha, "%[^,], %[^\n]", projeto->id, projeto->descricao) == 2) {
            lst = appendLista(lst, projeto);
        } else {
            free(projeto);
        }
    }
    fclose(file);
    return lst;
}

// função para subir membros do arquivo para a lista
Lista load_membros(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", fileName);
        return NULL;
    }

    Lista lst = criaLista();
    t_membro *membro;
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        membro = (t_membro *)malloc(sizeof(t_membro));
        if (sscanf(linha, "%[^,], %[^\n]", membro->id, membro->nome) == 2) {
            lst = appendLista(lst, membro);
        } else {
            free(membro);
        }
    }
    fclose(file);
    return lst;
}

// função para subir projetos do arquivo para a lista
Lista load_relacoes(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", fileName);
        return NULL;
    }

    Lista lst = criaLista();
    t_relacao *relacao;
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        relacao = (t_relacao *)malloc(sizeof(t_relacao));
        if (sscanf(linha, "%[^,], %[^\n]", relacao->id_membro, relacao->id_projeto) == 2) {
            lst = appendLista(lst, relacao);
        } else {
            free(relacao);
        }
    }
    fclose(file);
    return lst;
}

// função para puxar os membros de um projeto
Lista membros_projeto(char *id_proj, Lista lst_relacoes, Lista lst_membros) {
    Lista resultado = criaLista();
    for (int i = 0; i < lenLista(lst_relacoes); i++) {
        t_relacao *relacao = (t_relacao *)dadoLista(lst_relacoes, i);
        if (strcmp(relacao->id_projeto, id_proj) == 0) {
            for (int j = 0; j < lenLista(lst_membros); j++) {
                t_membro *membro = (t_membro *)dadoLista(lst_membros, j);
                if (strcmp(membro->id, relacao->id_membro) == 0) {
                    resultado = appendLista(resultado, membro);
                }
            }
        }
    }
    return resultado;
}

// função para puxar os projetos de um membro
Lista projetos_membro(char *id_mem, Lista lst_relacoes, Lista lst_projetos) {
    Lista resultado = criaLista();
    for (int i = 0; i < lenLista(lst_relacoes); i++) {
        t_relacao *relacao = (t_relacao *)dadoLista(lst_relacoes, i);
        if (strcmp(relacao->id_membro, id_mem) == 0) {
            for (int j = 0; j < lenLista(lst_projetos); j++) {
                t_projeto *projeto = (t_projeto *)dadoLista(lst_projetos, j);
                if (strcmp(projeto->id, relacao->id_projeto) == 0) {
                    resultado = appendLista(resultado, projeto);
                }
            }
        }
    }
    return resultado;
}

int main() {
    
    Lista lst_membros = load_membros("bdmembros.txt");
    Lista lst_projetos = load_projetos("bdprojetos.txt");
    Lista lst_relacoes = load_relacoes("bdrelacoes.txt");

    int opcao;
    char id[MAX];
    do {
        // MENU
        printf("\nMENU APP LISTA\n");
        printf("==============================\n");
        printf("1. Projetos de 1 Membro\n");
        printf("2. Membros de 1 Projeto\n");
        printf("3. Sair\n");
        printf("Escolha 1 opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        if (opcao == 1) {
            printf("Informe o ID do membro: ");
            fgets(id, MAX, stdin);
            id[strcspn(id, "\n")] = 0;
            Lista resultado = projetos_membro(id, lst_relacoes, lst_projetos);
            if (lenLista(resultado) == 0) {
                printf("Nenhum projeto encontrado %s.\n", id);
            } else {
                for (int i = 0; i < lenLista(resultado); i++) {
                    t_projeto *projeto = (t_projeto *)dadoLista(resultado, i);
                    printf("%s - %s\n", projeto->id, projeto->descricao);
                }
            }
        } else if (opcao == 2) {
            printf("Informe o ID do projeto: ");
            fgets(id, MAX, stdin);
            id[strcspn(id, "\n")] = 0;
            Lista resultado = membros_projeto(id, lst_relacoes, lst_membros);
            if (lenLista(resultado) == 0) {
                printf("Nenhum membro encontrado %s.\n", id);
            } else {
                for (int i = 0; i < lenLista(resultado); i++) {
                    t_membro *membro = (t_membro *)dadoLista(resultado, i);
                    printf("%s - %s\n", membro->id, membro->nome);
                }
            }
        }
    } while (opcao != 3);

    // FREE
    lst_membros = destroiLista(lst_membros);
    lst_projetos = destroiLista(lst_projetos);
    lst_relacoes = destroiLista(lst_relacoes);

    return 0;
}

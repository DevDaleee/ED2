#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *esq, *dir;
}NoArv;

NoArv* inserir_v1(NoArv *raiz, int num){
    if(raiz == NULL){
        NoArv *new = malloc(sizeof(NoArv));
        new->valor = num;
        new->dir = NULL;
        new->esq = NULL;
        return new;
    }else{
        if(num < raiz->valor){
           raiz->esq = inserir_v1(raiz->esq, num);
        }else{
            raiz->dir = inserir_v1(raiz->dir, num);
        }
        return raiz;
    }
}

void inserir_v2(NoArv **raiz, int num){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(NoArv));
        (*raiz)->valor = num;
        (*raiz)->dir = NULL;
        (*raiz)->esq = NULL;
    }else{
        if ( num < (*raiz)->valor){
            inserir_v2(&((*raiz)->esq), num);
        }else{
            inserir_v2(&((*raiz)->dir),num);
        }

    }
}

NoArv* buscar_v1(NoArv *raiz, int num){
    int *achou = NULL;
    if(raiz){
        if(raiz->valor == num){
            achou  =  raiz;
        }else if(num < raiz->valor){
            achou  = buscar_v1(raiz->esq, num);
            
        }else{
            achou  = buscar_v1(raiz->dir, num);
        }
    }
    return achou;
}


void imprimir_v1(NoArv *raiz){
    if(raiz){
        printf("%d  ", raiz->valor);
        imprimir_v1(raiz->esq);
        imprimir_v1(raiz->dir);
    }
}

void imprimir_v1_ordenada(NoArv *raiz){
    if(raiz){
        imprimir_v1_ordenada(raiz->esq);
        printf("%d  ", raiz->valor);
        imprimir_v1_ordenada(raiz->dir);
    }
}


int main(){

    NoArv *busca, *raiz = NULL;
    int op, valor;

    do{
        printf("\n\t 0 - Sair \n\t 1 - Inserir \n\t 2 - Imprimir\n\t 3 - Buscar \n\t");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\n\tDigite um valor: ");
            scanf("%d", &valor);
            //raiz = inserir_v1(raiz, valor);
            inserir_v2(&raiz, valor);
            break;
            
        case 2:
            printf("\n\tPrimeira versao: \n\t");
            imprimir_v1(raiz);
            printf("\n");
            printf("\n\t Segunda versao \n\t");
            imprimir_v1_ordenada(raiz);
            printf("\n");
            break;
        case 3:
            printf("\n\t Digite o valor a ser procurado: ");
            scanf("%d", &valor);
            busca = buscar_v1(raiz, valor);
            if(busca ){
                printf("Valor encontrado: %d\n", busca->valor);
            }else{
                printf("\n\tValor Nao Encontrado\n");
            }
            break;
        default:
            if(op != 0){
                printf("\n\t Opcao Invalida!\n");
            }
            break;
        }
    }while(op != 0);

    return 0;
}
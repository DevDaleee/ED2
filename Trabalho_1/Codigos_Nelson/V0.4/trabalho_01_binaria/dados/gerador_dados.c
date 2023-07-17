#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#define tam 40000

//void gera_crescente(FILE **arq);
void gera_decrescente(FILE **arq);
/*void gera_aleatorio(FILE **arq);
int num_unico(int numero, int *vet, int gerados);
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);*/


int main(void){
    srand(time(NULL));
    FILE *arq;

    //arq = fopen("DadosCrescente.txt", "w");
    arq = fopen("DadosDecrescente.txt", "w");
    //arq = fopen("DadosAleatorios3.txt", "w");

    if (arq == NULL)
    {
        return 0;
    }

    //gera_crescente(&arq);
    gera_decrescente(&arq);
    //gera_aleatorio(&arq);

    fclose(arq);

    return 0;
}

/*void gera_crescente(FILE **arq) {

    for (int i = 1; i <= tam; i++)
    {
        if (i != tam) {
            fprintf(*arq,"%d,", i); 
        }
        else {
            fprintf(*arq, "%d" , i);
        }                      
    }
}*/

void gera_decrescente(FILE **arq) {

    for (int i = tam; i >= 1; i--)
    {
        if (i != 1) {
            fprintf(*arq,"%d,", i); 
        }
        else {
            fprintf(*arq,"%d", i);
        }                      
    }    
}

/*void gera_aleatorio(FILE **arq) {
    int num;
    for (int i=0; i < tam; i++) {
        num = rand() % tam + 1;
        if (i != tam - 1) {
            fprintf(*arq, "%d,", num);
        }
        else {
            fprintf(*arq, "%d", num);
        }
    }

    while (gerados < tam) {
        num = (rand() % intervalo) + 1;

        if ((num_unico(num, vetord, gerados)) == 1) {
            vetord[gerados] = num;

            if (gerados != tam - 1) {
                fprintf(*arq, "%d,", num);    
            }
            else {
                fprintf(*arq, "%d", num);    
            }
            gerados++;
            quicksort(vetord, 0, gerados - 1); 
        } 
    }
}

int num_unico(int numero, int *vet, int gerados) {
    int esquerda = 0;
    int direita = gerados - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;

        if (vet[meio] == numero) {
            return 0; // Elemento encontrado, retorna o índice
        } else if (vet[meio] < numero) {
            esquerda = meio + 1; // O elemento está à direita do meio
        } else {
            direita = meio - 1; // O elemento está à esquerda do meio
        }
    }

    return 1; // Elemento não encontrado
}

// Função auxiliar para trocar dois elementos do vetor
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para encontrar a posição correta do pivô
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // escolhe o último elemento como pivô
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função principal do Quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // Encontra a posição correta do pivô
        int pi = partition(arr, low, high);

        // Aplica o Quicksort recursivamente nas duas metades do vetor
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}*/
/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    04/07/2021
 *  Descrição:          Faça um programa com N threads que localiza um valor em um vetor de inteiros. O espaço de busca no vetor deve ser distribuído para as N threads.  
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>

int vetor[] = {5,15,16,1,2,9,8,7,3,6, 700};
int V;
int TAM = sizeof(vetor)/sizeof(int);

struct data_vetor{
    int inicio;
    int fim;
};

 /*
 *  Descrição:  
 *              Realiza uma varredura em um determinado range do vetor.
 *  Parâmetros:  
 *              *param: estrutura que contem o valor inicial e fim do vetor.
 */

void *thread_find(void *param) {
    struct data_vetor *dados = param;
    printf("Thread id: %ld, Posicao inicio: %d, Posicao final: %d\n", pthread_self(), dados->inicio, dados->fim);

    if (TAM == dados->fim) dados->fim -= 1;
    for(int i = dados->inicio; i <= dados->fim; i++){
        if(vetor[i] == V){
            printf("Thread id: %ld encontrou o valor!\n", pthread_self());
            return NULL;
        }
    
    }
    return NULL;
}
/*
 *  Descrição:  
 *              Inicia todos os parametros, cria e inicializa as threads
 *  Parâmetros:  
 *              argc : quantidade de pamatros passado para a main pelo terminal;
 *              argv : os respectivos parametros;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */

int main(int argc, char* argv[]){
    int N = (argc < 2) ? 3 : (atoi(argv[1]));
    V = (argc < 3) ? 5 : (atoi(argv[2]));
    printf("\nNumero de Threads: %d\n", N);
    printf("Valor a ser encontrado: %d\n", V);
    printf("\nVetor de Busca: "); 
    for(int i = 0;i<TAM;i++ ) printf("%d ", vetor[i]);
    printf("\nTamanho Vetor de Busca: %d \n\n", TAM);

    struct data_vetor dados[N];

    int tam_parte = TAM/N;
    int ini_parte = 0;
    int fim_parte = tam_parte;

    for (int p=0; p < N; p++) {
        dados[p].inicio = ini_parte;
        dados[p].fim = fim_parte;

        ini_parte = fim_parte + 1;
        fim_parte += tam_parte;
    }
    dados[N-1].fim = TAM;
 
    pthread_t t[N];

    for (int p=0; p < N; p++) 
        pthread_create(&t[p], NULL, thread_find, &dados[p]);

    for (int p=0; p < N; p++) 
        pthread_join(t[p], NULL);

    pthread_exit(NULL);
 }

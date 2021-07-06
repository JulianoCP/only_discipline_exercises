/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    04/07/2021
 *  Descrição:          Implemente um programa multithread com pthreads que calcule: 
 *          a)- A mediana de cada linha de uma matriz MxN e devolva o resultado em um vetor de tamanho M.
 *          b)- A média aritmética de cada coluna de uma matriz MxN e devolva o resultado em um vetor detamanho N.
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include "matriz.h"

int **matrix;
int r = 5, c = 5;
float* medias;
int* mediana;

struct data_vetor{
    int inicio;
    int fim;
};

 /*
 *  Descrição:  
 *             Ordena via selectionSort o Array
 *  Parâmetros:  
 *              arr[]: Array a ser ordenado;
 *              n: Tamanho do array;
 */


void selectionSort(int arr[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx]) min_idx = j;
        // Swap 
        arr[min_idx] = arr[min_idx] + arr[i]-(arr[i]=arr[min_idx]);
    }
}


 /*
 *  Descrição:  
 *             Faz a Media de cada Coluna da Matriz Global.
 *  Parâmetros:  
 *              *param: estrutura que contem o valor inicial e final .
 */
void *thread_mean(void *param) {
    struct data_vetor *dados = param;
    for(int i=dados->inicio; i <= dados->fim;i++){
        for(int j=0; j < r ; j++){
            medias[i] += (float)matrix[j][i]/ (float)r;
        }
    }
}

 /*
 *  Descrição:  
 *             Faz a mediana de cada linha da Matriz Global.
 *  Parâmetros:  
 *              *param: estrutura que contem o valor inicial e final .
 */
void *thread_median(void *param){
    struct data_vetor *dados = param;
    for(int i=dados->inicio; i <= dados->fim;i++){
            mediana[i] = matrix[i][ (int)ceil(c/2) ];
    }

}
/*
 *  Descrição:  
 *              Inicia todos os parametros, cria e inicializa as threads.
 *  Parâmetros:  
 *              argc : quantidade de pamatros passado para a main pelo terminal;
 *              argv : os respectivos parametros;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */

int main(int argc, char* argv[]){
    int N = (argc < 2) ? 3 : (atoi(argv[1]));
    int flag = 1;

    printf("Digite:\n[1]-Gerar Matriz\n[2]-Carregar Matriz\n");
    scanf("%d",&flag);
    if (flag != 2){
        printf("Digite o valor da Linha X Coluna, (exemplo, 9 9): ");
        scanf("%d %d", &r, &c);
        
        matrix = create_matrix(r, c);
        srand(time(NULL));   
        generate_elements(matrix, r, c, 99);
    }else{
        
        printf("Matriz carregada a partir do arquivo matrizNova.in\n");
        matrix = read_matrix_from_file("matrizNova.in", &r, &c);
    }
   
    printf("\nNumero de Threads: %d", N);
    printf("\nMatriz [%d]x[%d] \n\n", r, c);

    float mm[c];

    for(int i =0; i<c; i++) mm[i] = 0;
    
    medias = mm;

    pthread_t t[N];
    struct data_vetor dados[N];

    int tam_parte = c/N;
    int ini_parte = 0;
    int fim_parte = tam_parte;

    for (int p=0; p < N; p++) {
        dados[p].inicio = ini_parte;
        dados[p].fim = fim_parte;

        ini_parte = fim_parte + 1;
        fim_parte += tam_parte;
    }
    dados[N-1].fim = c-1;

    print_matrix(matrix, r, c);
    
    for (int p=0; p < N; p++) 
        pthread_create(&t[p], NULL, thread_mean, &dados[p]);

    for (int p=0; p < N; p++) 
        pthread_join(t[p], NULL);


    tam_parte = r/N;
    ini_parte = 0;
    fim_parte = tam_parte;

    for (int p=0; p < N; p++) {
        dados[p].inicio = ini_parte;
        dados[p].fim = fim_parte;

        ini_parte = fim_parte + 1;
        fim_parte += tam_parte;
    }
    dados[N-1].fim = r-1;

    int m_copy[r][c];
    
    for(int i=0; i < r; i++ ){
        for(int j=0; j< c;j++){
            m_copy[i][j] = matrix[i][j];
        }
    }
    
    for(int i = 0; i < r; i++) selectionSort(matrix[i], c);
    
    int nn[r];

    for(int i =0; i<r; i++) nn[i] = 0;
    
    mediana = nn;

    for (int p=0; p < N; p++) 
        pthread_create(&t[p], NULL, thread_median, &dados[p]);

    for (int p=0; p < N; p++) 
        pthread_join(t[p], NULL);

    printf("\nMediana: ");
    for(int i=0; i<r;i++) printf(" [%d]", nn[i]);
    printf("\n");

    printf("\nMedia: ");
    for(int i=0; i<c;i++) printf(" [%.2f]", mm[i]);
    printf("\n");
    
    flag = 1;
    printf("\nDeseja salvar em arquivo?\n[1]-Sim\n[2]-Não\n");
    scanf("%d",&flag);
    if(flag != 2){
        FILE* arq = fopen("matrizNova.in", "w"); 
        FILE* arq_result = fopen("results.txt", "w"); 

        char buffer_tmp[50];
        sprintf(buffer_tmp, "%dx%d\n", r, c);
        fputs(buffer_tmp, arq);
        for (int i= 0; i < r; i++){
            for(int j= 0; j <c; j++){
                char buffer[2];
                sprintf(buffer, "%d", m_copy[i][j]);
                fputs(buffer, arq);
                fputs(" ", arq);
            }
            fputs("\n", arq);
        }
        
        fclose(arq);

        fputs("Mediana das linhas:\n ", arq_result);
        for(int i=0; i< r;i++){
            char buffer[2];
            sprintf(buffer, "%d", mediana[i]);
            fputs(buffer, arq_result);
            fputs(" ", arq_result);
        }
        
        fputs("\nMedias das Colunas:\n ", arq_result);
        for(int i=0; i< c;i++){
            char buffer[50];
            sprintf(buffer, "%f", medias[i]);
            fputs(buffer, arq_result);
            fputs(" ", arq_result);
        }
        fputs("\n", arq_result);
        fclose(arq_result);

        printf("\nArquivos gravados com sucesso!\nArquivos Gerados: matrizNova.in, results.txt\n ");
    }

    pthread_exit(NULL);
}

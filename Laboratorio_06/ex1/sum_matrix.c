/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    26/07/2021
 *  Descrição:           
 *          Faça um aplicativo com threads que processa uma matriz e realiza a  soma dos elementos. Cada thread
 *          deve realizar a leitura de uma linha por vez e a armazenar a soma em uma variável compartilhada. Por
 *          exemplo, considere 3 threads (t1, t2, t3) e uma matriz de 10 linhas. As threads não sabem qual linha
 *          farão a leitura, até o momento que precisarem de mais dados para processar. Assim, a t1 pode ler linhas
 *          0,2,8,9, a t2 pode ler as linhas 1,6, a thread 3 pode ler as linhas 3,4,5,7.
 */

#include "matriz.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *sum_matriz(void *dt);

struct StructThread {
  int rows;
  int cols;
  int **matrix;
  int *soma;
  pthread_mutex_t *lock;
};

/*
 *  Descrição:  
 *              Cria e inicializa as Threads
 *              Cria a estrutura compartilhada por todas as Threads
 *              Cria o Mutex;
 *              Carrega a matrix.in
 */
int main(int argc, char *argv[]) {
  int num_threads = atoi(argv[1]), shared_var = 0, rows, cols;
  int **matrix = read_matrix_for_file("matrix.in", &rows, &cols);
  struct StructThread dt;

  pthread_mutex_t lock[rows];
  for (int i = 0; i < rows; i++) {
    if (pthread_mutex_init(&lock[i], NULL) != 0) {
      printf("\n Mutex %d init failed\n", i);
      return 0;
    }
  }

  dt.matrix = matrix;
  dt.rows = rows;
  dt.cols = cols;
  dt.soma = &shared_var;
  dt.lock = lock;

  pthread_t threads[num_threads];

  for (int i = 0; i < num_threads; i++) pthread_create(&threads[i], NULL, sum_matriz, &dt);
  for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);

  printf("Resultado da Soma: %d\n", shared_var);
  return 0;
}

/*
 *  Descrição:
 *          Verifica se é possivel entrar para fazer a soma da linha
 *          Caso possivel, realiza a soma.
 */
void *sum_matriz(void *dt) {
  struct StructThread *data = dt;
  while (1) {
    int r = 0;
    while (pthread_mutex_trylock(&data->lock[r]) != 0) { 
      r++;
      if (r == data->rows) return NULL; 
    }
  
    int tmp = 0;
    for (int c = 0; c < data->cols; c++) {
      tmp += data->matrix[r][c];
    }
    *data->soma += tmp;
  }
}


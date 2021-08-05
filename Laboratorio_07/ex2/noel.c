/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    05/08/2021
 *  Descrição:           
 *              Problema do papai noel, elfos e renas.
 */

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int count_renas = 0, count_elfos = 0, flag_noel_elfos = 0, flag_noel_renas = 0,
    flag_ocupado_rena = 0, flag_ocupado_elfo = 0;
sem_t mutex_elfos, mutex_renas;

 /*
 *  Descrição:
 *              Controla o fluxo no mutex de elfos. 
 *              Controla o acesso a região critica
 */
void* f_elfos(){
    while(1){
        if(!flag_noel_elfos && !flag_noel_renas && !flag_ocupado_elfo){
          flag_ocupado_elfo = 1;
          sem_wait(&mutex_elfos);
          count_elfos += 1;
          printf("\nElfo[%d] chegou.", count_elfos);
          if (count_elfos == 3) {
            flag_noel_elfos = 1;
            printf("\nElfos acordaram o Papai Noel!!");
            count_elfos = 0;
            }
            sleep(1);
            if(!flag_noel_elfos && !flag_noel_renas) {flag_ocupado_elfo = 0;}
            sem_post(&mutex_elfos);
        } else {
          srand(time(NULL));
          sleep(rand() % 10 + 4);
        }
    }
}

 /*
 *  Descrição:
 *              Controla o fluxo no mutex das renas. 
 *              Controla o acesso a região critica
 */
void* f_renas(){
    srand(time(NULL)); sleep(rand()%10 + 2);
    while(1){
        if(!flag_noel_renas && !flag_ocupado_rena){
            flag_ocupado_rena = 1;
            sem_wait(&mutex_renas);
            count_renas += 1;
            if(count_renas < 9) printf("\nRena[%d] chegou e foi para o estabulo.", count_renas);
            else printf("\nUltima rena chegou e esta no frio esperando o Papai Noel!!");
            if (count_renas == 9) {
              flag_noel_renas = 1;
              printf("\nTodas as renas chegaram para o natal e acordaram o Papai Noel!!");
              count_renas = 0;
              count_elfos = 0;
            }
            sleep(1);
            if (!flag_noel_renas) { flag_ocupado_rena = 0;}
            sem_post(&mutex_renas);
        } else {
          srand(time(NULL));
          sleep(rand() % 10 + 5);
        }
    }
}

 /*
 *  Descrição:  
 *             Gerencia variaveis de controle para as threads de renas e elfos.
 */
void* f_noel(){
    while(1){
        if(flag_noel_renas){
            printf("\n+--------------------------------------------------------------------+");
            printf("\n|    Papai Noel sai com as renans para fazer as entregas do natal    |");
            printf("\n+--------------------------------------------------------------------+");
            printf("\nPapai Noel volta a dormir");
            sleep(1);
            flag_noel_renas = 0;
            flag_ocupado_rena = 0;
            flag_ocupado_elfo = 0;
        }else if(flag_noel_elfos){
            printf("\n+---------------------------------------------------------+");
            printf("\n|    Papai Noel resolvendo as dificuldades dos 3 Elfos    |");
            printf("\n+---------------------------------------------------------+");
            printf("\nPapai Noel volta a dormir");
            sleep(1);
            flag_noel_elfos = 0;
            flag_ocupado_elfo = 0;
        }else{ sleep(1); }
    }
}

 /*
 *  Descrição:  
 *              Cria e inicializa as Threads
 *              inicia o semaforo;
 */
int main(){
    pthread_t elfos, renas, noel;

    sem_init(&mutex_elfos, 0, 1);
    sem_init(&mutex_renas, 0, 1);

    pthread_create(&noel, NULL, f_noel, NULL);
    for(int i = 0 ; i < 9 ; i++){ pthread_create(&elfos, NULL, f_elfos, NULL); }
    for(int i = 0 ; i < 9 ; i++){ pthread_create(&renas, NULL, f_renas, NULL); }
    pthread_join(noel,NULL);
    
    return 0;
}



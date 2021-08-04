/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    04/08/2021
 *  Descrição:           
 *          Considere um arquivo que é acessado para leitura e escrita por diferentes threads 
 *          de forma concorrente.Se o arquivo estiver sendo lido, diferentes threads podem fazer 
 *          o acesso simultaneamente. Se o arquivoestiver sendo escrito, nenhuma outra thread pode 
 *          ler ou escrever no arquivo, isto é, o acesso à escritadeve ser exclusivo. 
 *          Esse padrão de problema é conhecido como o problema dos leitores-escritores.
 *          Implemente uma solução para o problema dos leitores-escritores usando  semáforos. 
 *          Faça uma soluçãoque evite o postergação indefinida das threads escritoras, isto é, 
 *          se chegar uma thread para escrita, elaterá preferência sobre as próximas threads leitoras.
 */

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int count_renas = 0, count_elfos = 0, flag_noel_elfos = 0, flag_noel_renas = 0;
sem_t mutex_elfos, mutex_renas;

 /*
 *  Descrição:  
 *              Controla o fluxo de leitores disponiveis no semaforo;
 *              Controla o uso da região critica
 */
void* f_elfos(){
    srand(time(NULL)); sleep(rand()%5 + 1);
    while(1){
        if(!flag_noel_elfos && !flag_noel_renas){
            sem_wait(&mutex_elfos);
            count_elfos += 1;
            printf("\nElfo[%d] chegou.", count_elfos);
            if(count_elfos == 3) { flag_noel_elfos = 1; printf("\nElfos acordaram o Papai Noel!!"); count_elfos = 0; }
            sleep(1); sem_post(&mutex_elfos);
        }else{ srand(time(NULL)); sleep(rand()%5 + 2); }
    }
}

 /*
 *  Descrição:  
 *              Solicita o acesso a região critica atraves da flag_escritor.
 */
void* f_renas(){
    srand(time(NULL)); sleep(rand()%10 + 2);
    while(1){
        if(!flag_noel_renas){
            sem_wait(&mutex_renas);
            count_renas += 1;
            if(count_renas < 9) printf("\nRena[%d] chegou e foi para o estabulo.", count_renas);
            else printf("\nUltima rena chegou e esta no frio esperando o Papai Noel!!");
            if(count_renas == 9) { flag_noel_renas = 1; printf("\nTodas as renas chegaram para o natal e acordaram o Papai Noel!!"); count_renas = 0; }
            sleep(1); sem_post(&mutex_renas);
        }else{ srand(time(NULL)); sleep(rand()%5 + 2); }
    }
}

 /*
 *  Descrição:  
 *              Solicita o acesso a região critica atraves da flag_escritor.
 */
void* f_noel(){
    while(1){
        if(flag_noel_renas){
            printf("\n+--------------------------------------------------------------------+");
            printf("\n|    Papai Noel sai com as renans para fazer as entregas do natal    |");
            printf("\n+--------------------------------------------------------------------+");
            printf("\nPapai Noel volta a dormir");
            sleep(5);
            flag_noel_renas = 0;
        }else if(flag_noel_elfos){
            printf("\n+---------------------------------------------------------+");
            printf("\n|    Papai Noel resolvendo as dificuldades dos 3 Elfos    |");
            printf("\n+---------------------------------------------------------+");
            printf("\nPapai Noel volta a dormir");
            sleep(2);
            flag_noel_elfos = 0;
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



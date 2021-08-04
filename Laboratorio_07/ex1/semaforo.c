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

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

int count_leitor = 0, flag_escritor = 0; 
sem_t mutex, acesso_documento;

 /*
 *  Descrição:  
 *              Controla o fluxo de leitores disponiveis no semaforo;
 *              Controla o uso da região critica
 */
void* leitor(){
    while(1){
        if(!flag_escritor){
            sem_wait(&mutex);
            count_leitor += 1;
            if(count_leitor == 1) sem_wait(&acesso_documento);
            sem_post(&mutex);
            printf("\nLeitor[%d] fazendo leitura.", count_leitor);
            sleep(1);
            sem_wait(&mutex); 
            printf("\nLeitor[%d] terminou a leitura.", count_leitor);
            count_leitor -= 1;

            if(count_leitor == 0) sem_post(&acesso_documento);
            sem_post(&mutex);

        }else{sleep(1);}
    }
}

 /*
 *  Descrição:  
 *              Solicita o acesso a região critica atraves da flag_escritor.
 */
void* escritor(){
    while(1){
        flag_escritor = 1;
        printf("\n+-------------------------------+");
        printf("\n|    Escritor solicitou acesso. |");
        printf("\n+-------------------------------+");
        sem_wait(&acesso_documento);
        flag_escritor = 0;
        printf("\n+-------------------------------+");
        printf("\n|    Escritor fazendo a escrita.|");
        sem_post(&acesso_documento);
        printf("\n|    Escritor terminou a escrita|");
        printf("\n+-------------------------------+");
        sleep(1);
    }
}

 /*
 *  Descrição:  
 *              Cria e inicializa as Threads
 *              inicia o semaforo;
 */
int main(){
    pthread_t t1,t2,t3,t4;
    
    sem_init(&mutex, 0, 1);
    sem_init(&acesso_documento, 0, 1);
 
    pthread_create(&t1,NULL, leitor,NULL);
    pthread_create(&t2,NULL, leitor,NULL);
    pthread_create(&t3,NULL, leitor,NULL);
    pthread_create(&t4,NULL, escritor,NULL);

    pthread_join(t1,NULL);
    
    return 0;
}
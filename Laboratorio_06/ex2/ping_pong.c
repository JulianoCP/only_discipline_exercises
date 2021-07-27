/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    27/07/2021
 *  Descrição:        
 *                  Faça um aplicativo que execute dois tipos de threads: ping e a pong. 
 *                  As threads ping imprimem na tela a mensagem ping e as threads pong imprimem 
 *                  na tela a mensagem pong. As threads devem cooperar entre si para imprimir sempre 
 *                  alternadas as palavras ping e pong. 
 *                  O programa deve possibilitar informara quantidade de threads a serem executadas de cada tipo.  
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *f_ping(void *st);
void *f_pong(void *st);

struct StructThread{
    int ping_pong;                    
    pthread_mutex_t lock_ping_pong;   
};

 /*
 *  Descrição:  
 *             Cria e Inicializa as threads;
 *             Inicializa a estrutura compartilhada;
 */
int main(int argc, char* argv[]){
    int n_ping = atoi(argv[1]), n_pong = atoi(argv[2]);

    struct StructThread dt;
    if(pthread_mutex_init(&dt.lock_ping_pong, NULL) != 0) printf("\nmutex failed\n");
    dt.ping_pong = 0; 

    pthread_t t_ping[n_ping], t_pong[n_pong];
    for (int i = 0; i < n_ping; i++) pthread_create(&t_ping[i], NULL, f_ping, &dt);
    for (int i = 0; i < n_pong; i++) pthread_create(&t_pong[i], NULL, f_pong, &dt);
    for (int i = 0; i < n_ping; i++) pthread_join(t_ping[i], NULL);
    for (int i = 0; i < n_pong; i++) pthread_join(t_pong[i], NULL);
}

 /*
 *  Descrição:  
 *             Thread Solicita acesso a região critica para imprimir PING 
 *  Parâmetros:  
 *              st: Estrutura de controle.
 */
void *f_ping(void *st) {
    struct StructThread *data = st;
    while(1){                                      
        pthread_mutex_lock(&data->lock_ping_pong);  
        if (data->ping_pong == 0){ printf("ping\n"); data->ping_pong = 1;}
        pthread_mutex_unlock(&data->lock_ping_pong);
    }
}

 /*
 *  Descrição:  
 *             Thread Solicita acesso a região critica para imprimir PONG
 *  Parâmetros:  
 *              st: Estrutura de controle.
 */
void *f_pong(void *st) {
    struct StructThread *data = st;
    while(1){
        pthread_mutex_lock(&data->lock_ping_pong);
        if (data->ping_pong == 1){ printf("pong\n"); data->ping_pong = 0;}
        pthread_mutex_unlock(&data->lock_ping_pong);
    }
}



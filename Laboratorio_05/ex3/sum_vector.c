 /*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    17/07/2021
 *  Descrição:           
 *                  Implemente o exemplo soma de vetores utilizando processos para fazer o cálculo, mas com os vetores
 *                  sendo compartilhados pelos processos. Como os espaços de memória entre os processos são isolados,
 *                  um mecanismo fornecido pelo SO deve ser usado. No caso, use memória compartilhada para que
 *                  todos os filhos operem sobre os dados, e pipes para a realização do despacho de trabalho (intervalo de
 *                  índices no vetor).
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

#define TAM_VET 10
#define MIN_RANGE 0
#define MID_RANGE TAM_VET
#define MAX_RANGE (TAM_VET * 2)
#define INTERVALO (TAM_VET / 2)
#define AMOUNT_CHILD 2
#define SHMSZ (MAX_RANGE + MID_RANGE + AMOUNT_CHILD)

key_t key = 5678;

/*
 *  Descrição:  
 *              Cria dois canais de comunicação Pipe.
 *              Cria dois filhos.
 *              Preenche um vetor com numeros random e divide em dois para os filhos.
 *              Saida: exibe o vetor resultante das somas dos vetores.
 */
int main(){
	//Cria os pipes.
	int pid, pipe_1[2],pipe_2[2], buffer_1[3], buffer_2[3];
	if (pipe(pipe_1) || pipe(pipe_2)){ fprintf(stderr, "Falha ao criar o Pipe\n"); return EXIT_FAILURE; }

    //Cria os filhos e as regiões de memoria compartilhada.
    if ((pid = fork())) { 
        //Pai.
        if ((pid = fork())) {
            int index, memory_id_pai, *memory_pai, *share_pai;

            if ((memory_id_pai = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) { perror("Erro ao tentar criar o segmento de shm."); exit(1); }
            if ((memory_pai = shmat(memory_id_pai, NULL, 0)) == (int*)-1) { perror("Erro ao acoplar o segmento ao espaço de dados do programa."); exit(1); }
            printf("\nRegião de memoria: %d. \n\n", memory_id_pai);

            share_pai = memory_pai;

            for(index = MIN_RANGE; index < MAX_RANGE; index++) share_pai[index] = rand()%10 + 1;

            printf("Primeiro Vetor:");
            for(index = MIN_RANGE; index < MID_RANGE; index++) printf("%d ", share_pai[index]);
            printf("\n");

            printf("Segundo Vetor:");
            for(index = MID_RANGE; index < MAX_RANGE; index++) printf("%d ", share_pai[index]);
            printf("\n\n");

            close(pipe_1[0]);
            buffer_1[1] = MIN_RANGE; buffer_1[1] = MID_RANGE; buffer_1[2] = MAX_RANGE;
            write(pipe_1[1], buffer_1, sizeof(buffer_1));

            close(pipe_2[0]);
            buffer_2[0] = MIN_RANGE + INTERVALO; buffer_2[1] = MID_RANGE + INTERVALO; buffer_2[2] = MAX_RANGE + INTERVALO;
            write(pipe_2[1], buffer_2, sizeof(buffer_2));

            //Esperado os filhos.
            while ((memory_pai[MAX_RANGE + MID_RANGE] != -1) && (memory_pai[MAX_RANGE + MID_RANGE + 1] != -1)){ sleep(1); }
            
            printf("Vetor Resultante:");
            for (int j = MAX_RANGE; j < MAX_RANGE + MID_RANGE; j++) printf("%d ", memory_pai[j]);
            printf("\n\n");

            if (shmdt(memory_pai) == -1){ perror("Erro ao desacoplar da região de memória compartilhada."); exit(1); }
            if (shmctl(memory_id_pai, IPC_RMID, 0) == -1){ perror("Erro ao destruir o segmento compartilhado. (shmctl)."); exit(1); }
            
            wait(NULL);
            return EXIT_SUCCESS;

        } else {
            //FILHO 2.
            close(pipe_2[1]);
            read(pipe_2[0], buffer_2, sizeof(buffer_2));

            int memory_id_filho_2, *memory_filho_2, *share_filho_2;;

            if ((memory_id_filho_2 = shmget(key, SHMSZ, 0666)) < 0){ perror("Erro ao tentar acessar o segmento do Filho 2."); exit(1); }
            if ((memory_filho_2 = shmat(memory_id_filho_2, NULL, 0)) == (int*)-1){ perror("Erro ao acoplar o segmento ao espaço de dados do programa."); exit(1); }

            share_filho_2 = memory_filho_2;
            int index_vetor_1 = buffer_2[0], index_vetor_2 = buffer_2[1], index_vetor_resultado = buffer_2[2];

            //Soma vet_result[n] = vetor_1[n] + vetor_2[n].
            while(index_vetor_1 < buffer_2[0] + INTERVALO) {
                memory_filho_2[index_vetor_resultado] = share_filho_2[index_vetor_1] + share_filho_2[index_vetor_2];
                index_vetor_1++; index_vetor_2++; index_vetor_resultado++;
            }

            //Setando flag, que identifica a finalização do filho 2. 
            memory_filho_2[MAX_RANGE+MID_RANGE+1] = -1;
            if (shmdt(memory_filho_2) == -1){ perror("Erro ao desacoplar da região de memória compartilhada."); exit(1); }
            fflush(stdout);
            return EXIT_SUCCESS;
        }
    } else {
        //FILHO 1.
        close(pipe_1[1]);
        read(pipe_1[0], buffer_1, sizeof(buffer_1));
    
        int memory_id_filho_1, *memory_filho_1, *share_filho_1;;

        if ((memory_id_filho_1 = shmget(key, SHMSZ, 0666)) < 0){ perror("Erro ao tentar acessar o segmento do Filho 1."); exit(1); }
        if ((memory_filho_1 = shmat(memory_id_filho_1, NULL, 0)) == (int*)-1){ perror("Erro ao acoplar o segmento ao espaço de dados do programa."); exit(1); }

        share_filho_1 = memory_filho_1;
        int index_vetor_1 = buffer_1[0], index_vetor_2 = buffer_1[1], index_vetor_resultado = buffer_1[2];

        //Soma vet_result[n] = vetor_1[n] + vetor_2[n].
        while(index_vetor_1 < buffer_1[0] + INTERVALO) {
            memory_filho_1[index_vetor_resultado] = share_filho_1[index_vetor_1] + share_filho_1[index_vetor_2];
            index_vetor_1++; index_vetor_2++; index_vetor_resultado++;
        }

        //Setando flag, que identifica a finalização do filho 1. 
        memory_filho_1[MAX_RANGE+MID_RANGE] = -1;
        if (shmdt(memory_filho_1) == -1){ perror("Erro ao desacoplar da região de memória compartilhada."); exit(1); }
        fflush(stdout);
        return EXIT_SUCCESS;
    }
}
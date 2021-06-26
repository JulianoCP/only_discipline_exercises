/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    25/06/2021
 *  Descrição:          Um programa que receba um vetor e divida para N filhos partes iguais de processamento paralocalizar um item. Exibir o PID dos filhos que encontrarem o valor procurado.
 *
 */

#include <stdio.h>      // getchar();
#include <stdlib.h>     // atoi();
#include <unistd.h>     // fork();
#include <string.h>     // strtok();
#include <sys/types.h>  // pid_t

int TAM_VET = 0;
int  VALOR  = 0;

 /*
 *  Descrição:  
 *              Realiza uma varredura em um subvetor.
 *  Parâmetros:  
 *              VETOR: Vetor completo de busca 
 *              POSI_INICIAL: Posição inicial para iniciar a busca pelo subvetor
 *              POSI_FINAL: Posição final do subvetor  
 */
int buscar(int VETOR[], int POSI_INICIAL, int POSI_FINAL){
    if (POSI_FINAL > TAM_VET){ POSI_FINAL = TAM_VET; }
    for(int i = POSI_INICIAL; i < POSI_FINAL; i++){
        if(VETOR[i] == VALOR){
            printf("\nO Filho com PID: %d encontrou o valor desejado.\n\n" ,getpid());
        }
    }
} 


 /*
 *  Descrição:  
 *              Cria N  processos filhos que chama a função buscar();
 *  Parâmetros:  
 *              VETOR: Vetor completo de busca 
 *              FILHOS: Numero de forks a serem criados
 *              POSI_INICIAL: Posição inicial para iniciar a busca pelo subvetor
 *              POSI_FINAL: Posição final do subvetor  
 */
int criaFork(int VETOR[], int FILHOS, int POSI_INICIAL, int POSI_FINAL){
    if (FILHOS == 0){
        printf("Balanceou as cargas para os filhos.\n");
        return 0;
    }

    pid_t pid = fork();

    if (pid){
        criaFork(VETOR, (FILHOS - 1), POSI_FINAL, POSI_FINAL + (TAM_VET/FILHOS));
    }else{
        buscar(VETOR, POSI_INICIAL, POSI_FINAL);
    }
}

/*
 *  Descrição:  
 *              Converte a string passada por parametro pelo terminal para um vetor de numeros inteiros, e chama o criaFork();
 *  Parâmetros:  
 *              argc : quantidade de pamatros passado para a main pelo terminal;
 *              argv : os respectivos parametros;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */
int main(int argc, char *argv[]){
    
    char *argVet = argv[3];
    char *ch ;
    int VETOR[50];
    int FILHOS = atoi(argv[1]);
    int count = 0;

    ch = strtok(argVet, " ");
    while(ch != NULL){
        VETOR[count] = atoi(ch);
        count++;
        ch = strtok(NULL, " ");
    }

    TAM_VET = count;
    VALOR = atoi(argv[2]);
    criaFork(VETOR, FILHOS, 0, (TAM_VET/FILHOS));
    return 0;
}

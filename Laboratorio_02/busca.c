/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    25/06/2021
 *  Descrição:          Fazer um processo filho executar um comando, o processo pai deve aguardar o término da execução do comando.    
 *
 */

#include <stdio.h>      // getchar();
#include <stdlib.h>     // atoi();
#include <unistd.h>     // fork();
#include <string.h>     // strcat();
#include <sys/types.h>  // pid_t

int TAM_VET = 0;
int  VALOR  = 0;

/*
 *  Descrição:   
 *              Trata o comando recebido para ser executado no execv(); 
 *  Parâmetros:  
 *              comando: lista de parametros
 *              tam: tamanho da lista de parametros
 *
 */
int executa(char* comando[], int tam){

    char folder[1000] = "/bin/";
    strcat(folder, comando[1]);

    if (tam > 2){

        char* parametros[11];
        parametros[0] = comando[1];
        
        int i = 2;
        for(; i < tam; i++ ){
            printf("%s", comando[i]);
            parametros[i-1] = comando[i] ;
        }   
        parametros[i-1] = NULL;
        execv(folder, parametros);

    }else{
    
        char* arr[] = {comando[1], NULL};
        execv(folder, arr);
    }
}

/*
 *  Descrição:  
 *              Cria um processo filho que chama a função executa();
 *  Parâmetros:  
 *              comando: lista de parametros
 *              tam: tamanho da lista de parametros
 */

int buscar(int VETOR[], int POSI_INICIAL, int POSI_FINAL){
    if (POSI_FINAL > TAM_VET){ POSI_FINAL = TAM_VET; }
    for(int i = POSI_INICIAL; i < POSI_FINAL; i++){
        if(VETOR[i] == VALOR){
            printf("\nO Filho com PID: %d encontro o valor desejado.\n\n" ,getpid());
        }
    }
} 

int criaFork(int VETOR[], int FILHOS, int POSI_INICIAL, int POSI_FINAL){
    if (FILHOS == 0){
        printf("Busca finalizada.\n");
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
 *              Chama a função criaFork();
 *              passando a lista de parametros e o tamanho dos argumentos.
 *  Parâmetros:  
 *              argc : quantidade de pamatros passado para a main pelo terminal;
 *              argv : os respectivos parametros;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */
int main(int argc, char *argv[]){
    int FILHOS = atoi(argv[1]);
    int VETOR[] = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10, 11, 12, 13};
    TAM_VET = (int)( sizeof(VETOR) / sizeof(VETOR[0]));
    VALOR = atoi(argv[2]);
    criaFork(VETOR, FILHOS, 0, (TAM_VET/FILHOS));
    return 0;
}

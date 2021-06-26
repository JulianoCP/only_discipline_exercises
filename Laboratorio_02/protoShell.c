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
int criaFork(char* comando[], int tam){
    pid_t pid= fork();

    if (!pid){
        executa(comando,tam);
    }else{
        printf("\n\nComando Finalizado\n\n");
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
   criaFork(argv, argc);
   return 0;
}

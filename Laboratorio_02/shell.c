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
#include <sys/wait.h>   // wait();

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
            //printf("%s", comando[i]);
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
    char ecomer = comando[tam-1][0];
    pid_t pid= fork();
    
    if (!pid){
        if (ecomer == '&'){
            executa(comando,tam-1);
        }else{
            executa(comando,tam);
        }
    }else{
        if(ecomer != '&'){
            wait(NULL);
        }
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
    while(1){ 
        char str1[100];
        char newString[10][10]; 
        int i,j,ctr;
     
        printf("> ");
        fgets(str1, sizeof str1, stdin);    
     

        /*
         * Dar creditos
         */
        j=0; ctr=0;
        for(i=0;i<=(strlen(str1));i++)
        {
            if(str1[i]==' '||str1[i]=='\0')
            {
                newString[ctr][j]='\0';
                ctr++;  //for next word
                j=0;    //for next word, init index to 0
            }
            else
            {
                if (str1[i]=='\n'){
                    continue;
                }else{
                    newString[ctr][j]=str1[i];
                    j++;
                }
            }
        }

        char** cd = malloc(sizeof(char**));
        cd[0] = strdup(newString[0]);
        for(int i =0; i <= ctr; i++){
            cd[i+1] = strdup(newString[i]);
        }
        criaFork(cd, ctr+1);
    }
    return 0;
}

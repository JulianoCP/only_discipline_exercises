 /*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    16/07/2021
 *  Descrição:           
 *                  Faça um programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro programa 
 *                  que realiza o cálculo e devolve a resposta.
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SERVER_FIFO "/tmp/serverfifo"

/*
 *  Descrição:  
 *              Inicia todos os parametros, cria e inicializa o FIFO.
 *              Fica esperando a entrada do writer do FIFO,
 *              Depois pega a string e separa e executa a operação desejada,
 *              retornando o resultado atraves do FIFO
 */


int main(){
    int fd, bytes_read;
    char buf [512];

    // cria um FIFO se inexistente
    if ((mkfifo (SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
        perror ("mkfifo");
        exit (1);
    }

    // abre um FIFO
    if ((fd = open (SERVER_FIFO, O_RDWR)) == -1)
        perror ("open");

     while (1) {
        int numero1 = 0;
        int numero2 = 0;
        char* operacao = " ";

         // lê mensagem do FIFO
         memset (buf, '\0', sizeof (buf));
         if ((bytes_read = read (fd, buf, sizeof (buf))) == -1)
             perror ("read");
         
         if (bytes_read > 0) {
             printf("Processando operação!\n");
            const char s[2] = " ";
            char *token;
            token = strtok(buf, s);
            int count = 0;
                       
            while( token != NULL ) {
                if (count == 0){
                    numero1 =  atoi(token);
                }else if (count == 1){
                    operacao = token; 
                }else if (count == 2){
                    numero2 =  atoi(token);
                }
                count++;
                token = strtok(NULL, s);
           }
            float resultado = 5.0;
            if (strcmp(operacao, "+") == 0){
                resultado = numero1+numero2;

            }else if (strcmp(operacao, "-") == 0){
                resultado = numero1-numero2;

            }else if (strcmp(operacao, "*") == 0){
                resultado = numero1*numero2;
                
            }else if (strcmp(operacao, "/") == 0){
                resultado = (float)numero1/numero2;

            }
            
            memset (buf, '\0', sizeof (buf));
            sprintf (buf, "%f", resultado);
            write (fd, buf, strlen (buf));
            sleep(2);
        }
     }
}

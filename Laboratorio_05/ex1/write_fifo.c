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
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>

#define SERVER_FIFO "/tmp/serverfifo"

char buf [512];

/*
 *  Descrição:  
 *              Inicia todos os parametros, abre o FIFO para enviar e receber informações.
 *              Recebe via argumentos a equação a ser enviada e resolvida pelo read FIFO,
 *              Ao receber o resultado da equação atraves do FIFO é mostrado atraves de um printf na tela.
 */

int main (int argc, char **argv){
    int fd_server;
    int bytes_read;

    if (argc < 2) {
        printf("Expressão Invalida.\n Tente digitar separadamente '1 + 1'\n"); 
        return 0;
    }
    
    char* operacao = argv[1];
    
    if ((fd_server = open (SERVER_FIFO,  O_RDWR)) == -1) {
        perror ("open: server fifo");
        return 1;
    }
        sprintf (buf, "%s", operacao);
        printf("Enviando: %s\n", buf);

        // envia mensagem para o fifo
        write (fd_server, buf, strlen (buf));
    
        sleep(1);
        memset (buf, '\0', sizeof (buf));
         if ((bytes_read = read (fd_server, buf, sizeof (buf))) == -1)
             perror ("read");
         
         if (bytes_read > 0) {
            printf("Resultado: %s\n", buf);
        } 

   if (close (fd_server) == -1) {
       perror ("close");
       return 2;
   }

    return 0;
}

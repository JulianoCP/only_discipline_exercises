 /*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    17/07/2021
 *  Descrição:           
 *                  Faça um programa que manipule arquivos (ler e escrever) e que, ao receber o signal 2 (SIGINT)
 *                  ou signal 15 (SIGTERM), faça uma finalização limpa (graceful stop) – armazenar as informações
 *                  pendentes e fechar o arquivo. 
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char ch = ' ';
int choose = 0;
char buffer[255];

FILE *fp;

//Define uma função tratadora de sinais.
void sig_handler(int signo){
    if (signo == SIGTERM || signo == SIGINT){
        fclose(fp); printf("\nSalvando Arquivo!\n"); printf("Programa finalizado com sucesso\n");
        raise(SIGKILL);
    }
}

//Faz a leitura do arquivo output.txt.
int read_file(){
    fp = fopen("output.txt", "r");
    if (fp == NULL){ perror("Ocorreu um erro ao abrir o arquivo (output.txt)."); return(EXIT_FAILURE);}
    while ((ch = fgetc(fp)) != EOF) printf("%c", ch); 
    return 0;
}

//Faz a escrita no arquivo output.txt.
int write_file(){
    printf("\nDigite 1 Continuar escrevendo no (output.txt)\nDigite 2 Limpar e continuar escrevendo no (output.txt)\nEscolha: "); scanf("%d", &choose);
    if (choose == 1){ read_file(); fp = fopen("output.txt", "a"); }
    else if (choose == 2){ fp = fopen("output.txt", "w"); }

    memset(buffer, '\0', sizeof (buffer));
    printf("\nDigite a palavra quer salvar no arquivo: "); scanf("%s", buffer); fputs(buffer, fp);
    return 0;
}

/*
 *  Descrição:  
 *              Permite o usuário fazer a escolhar entre ler ou escrever em um arquivo.
 *              Associa a função tratadora de sinais e fica esperando a emissão do mesmo.   
 */
int main(){
    //Exibe o PID do processo.
    printf("My PID is %d.\n\n", getpid());

    //Seleciona a ação que vai ser feita com o arquivo.
    printf("Digite 1 Para ler o Arquivo (output.txt)\nDigite 2 Para escrever no arquivo (output.txt)\nEscolha: "); scanf("%d", &choose);
    if (choose == 1) read_file(); else if(choose == 2) write_file(); else return 0;

    //Associa a função tratadora de sinais.
    if (signal(SIGTERM, sig_handler) == SIG_ERR) printf("\ncan't catch SIGTERM\n");
    if (signal(SIGINT, sig_handler) == SIG_ERR) printf("\ncan't catch SIGINT\n");

    //Fica esperando o signal para terminar o processo.
    while (1);

    return 0;
}



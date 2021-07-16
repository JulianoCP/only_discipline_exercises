/*
 *
 *Faça um programa que manipule arquivos (ler e escrever) e que, ao receber o signal 2 (SIGINT)ou signal 15 (SIGTERM), faça uma finalização limpa (graceful stop) –  armazenar as informaçõespendentes e fechar o arquivo.
 *
 *
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

FILE *fp;
/* Define uma função tratadora de sinais. */
void sig_handler(int signo){
    if (signo == SIGTERM || signo == SIGINT){
        printf("Salvando Arquivo! [%d]\n", signo);
        fclose(fp);
        kill(getpid(), SIGKILL);
    }
}


int main(void){

    /* Associa a função tratadora de sinais */
    if (signal(SIGTERM, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGTERM\n");

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");


    /* exibe o PID */
    printf("My PID is %d.\n", getpid());
  
    char str[60];
    fp = fopen("output.txt", "r");
    if(fp=NULL){
        perror("Ocorreu um erro ao abrir o arquivo.");
        return(-1);
    }
    /* Entra em loop para pode dar tempo de receber sinais. */
    fscanf(fp, "%s", str);
    /*while(1)
    if(fgets(str, 60, fp)!=NULL){ 
       puts(str);
    }
    */
    
    fclose(fp);
    return 0;
}



/*
 *  Autor:              Juliano Cesar Petini & Michel Gomes de Souza
 *  Data de criação:    25/06/2021
 *  Descrição:          Simulando uma hierarquia de processos de N niveis.    
 *
 */

#include <stdio.h>      // getchar();
#include <stdlib.h>     // atoi();
#include <unistd.h>     // fork();

/*
 *  Descrição:   
 *              Cria processos em uma hierarquia de N niveis,
 *              chamando recursivamente a função passando num-1.
 *  Parâmetros:  
 *              num : o nivel atual da hierarquia;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */
int criaProcesso(int num){
    if (num == 0){ getchar(); return 0; }
    fork() ? (!fork() ? criaProcesso(num-1) : 0) : criaProcesso(num-1);
    getchar();
}

/*
 *  Descrição:  
 *              Chama pela primeira vez a função criaProcesso(),
 *              passando um numero como parâmetro.
 *  Parâmetros:  
 *              argc : quantidade de pamatros passado para a main pelo terminal;
 *              argv : os respectivos parametros;
 *  Saída:
 *              Retorna 0: Finalizado com sucesso.
 *
 */
int main(int argc, char *argv[]){
    criaProcesso(atoi(argv[1])-1);
    return 0;
}

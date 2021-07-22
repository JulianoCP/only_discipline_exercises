/*------------------------------------------------------------------------
 * Programa:
 *    velha - Implementa o jogo da velha
 *
 * Funcionalidades: 
 *    - inicializa um jogo sem nenhuma marca��o
 *    - desenha a velha
 *    - seta as jogadas
 *    - verifica ganhador ou empate 
 *
 * Sintaxe:  velha 
 *
 * Notas:     
 *    - apesar de possuir um main, suas fun��es podem ser invocadas 
 *------------------------------------------------------------------------
 */

#include <sys/types.h>              /* tipos b�sicos do GNU C */
#include <sys/socket.h>             /* fun��es, tipos e constantes para sockets (UNIX) */
#include <netinet/in.h>             /* fun��es, tipos e constantes para sockets (Internet) */
#include <netdb.h>                  /* dados sobre a rede (ex.: hosts, protocolos, ...) */
#include <unistd.h>                 /* close() */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IP_SERVER     "127.0.0.1"   /* especifica o IP do servidor */
#define PORTA_PADRAO  5000          /* especifica a porta padrao de conexao */
#define MAX_CLIENT    10            /* maximo de conexoes */
#define MAX_BUFFER    100           /* tamanho m�ximo do buffer */

char velha[3][3];
int contador;

void inicio_velha () {
    memset(&velha,' ',sizeof(velha)); 
    contador = 0;
}
    
void desenha_velha () {
    printf ("-------------\n");
    printf ("| %c | %c | %c |\n", velha[0][0], velha[0][1], velha[0][2]);
    printf ("-------------\n");
    printf ("| %c | %c | %c |\n", velha[1][0], velha[1][1], velha[1][2]);
    printf ("-------------\n");
    printf ("| %c | %c | %c |\n", velha[2][0], velha[2][1], velha[2][2]);
    printf ("-------------\n");
}

char verifica_ganhador () {
    /* contabiliza o numero de lances */
    contador++;

    int i;
    for (i=0; i<3; i++) {
        if ((velha[i][0] == velha[i][1]) && (velha[i][1] == velha[i][2])) return velha[i][1];
        if ((velha[0][i] == velha[1][i]) && (velha[1][i] == velha[2][i])) return velha[1][i];
    } //for
    
    /* verifica diagonais */
    if ((velha[0][0] == velha[1][1]) && (velha[1][1] == velha[2][2])) return velha[1][1];
    if ((velha[0][2] == velha[1][1]) && (velha[1][1] == velha[2][0])) return velha[1][1];
    
    /* retorna 0 para empate */
    if (contador == 9) return 0;
    
    /* retorna 32 (espa�o) para jogo indefinido */
    return ' ';
}

int marca_velha (int l, int c, char sinal) {
    if (velha[l][c] != ' ') return -1;
    velha[l][c] = sinal;
    return 1;
}

int main(){
    struct hostent *ptrh; /* ponteiro para a tabela de hosts */
	struct sockaddr_in addr_server, /* estrutura para armazenar o IP e a porta do servidor */
	addr_client; /* estrutura para armazenar o endereco do cliente */
	int serverSocket, /* socket para ouvir conex�es */
	playerSocket; /* socket para comunica��o com o jogador conectado */
	int port; /* porta utilizada na comunica��o */
	char buffer[MAX_BUFFER]; /* armazena os dados recebidos */

    return 0;
}

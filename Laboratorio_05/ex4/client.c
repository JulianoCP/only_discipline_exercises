#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/types.h>             
#include <netdb.h>                  
#include <unistd.h>                 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     

int contador; 
char velha[3][3]; 

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
    int fd, first_conection = 1, line, col;
    char message[100], turn = 'X', check; 

	fd = socket(AF_INET, SOCK_STREAM, 0);
	
    struct sockaddr_in serv; 
	memset(&serv, '\0', sizeof(serv)); 
    memset(message, '\0',sizeof(message));

    serv.sin_family = AF_INET;
	serv.sin_port = htons(8096);

	inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr); 
	connect(fd, (struct sockaddr *)&serv, sizeof(serv));
    printf("Aguardando outro cliente se conectar ao jogo.\n");
	
    inicio_velha();
    desenha_velha();

    while(1) {
        if (first_conection == 1){
            recv(fd, message, 4, 0);
            if ((strcmp(message, "Yes") == 0)){
                recv(fd, message, 4, 0);
                printf("Jogador encontrado, e ele sera o primeiro a jogar, aguarde.\n");
                if ((strcmp(message, "Con") == 0)){
                    first_conection = -1;
                    recv(fd, message, 4, 0);
                    printf("\nPrimeira jogado do oponente: %s \n", message);

                    line = atoi(&message[0]); col = atoi(&message[2]); turn = 'O';
                    if (marca_velha(line, col, turn) != 1){ printf("Jogada do oponente foi um movimento invalido, perdeu a vez."); }
                    else{ printf("\nJogada do oponente feita com sucesso.\n"); desenha_velha(); }

                    memset(message, '\0',sizeof(message));
                    fflush(stdout);  
                }
            }
            else{
                first_conection = -1;
                printf("Já existe um oponente esperando, e você é o primeiro a jogar.\n");
            }
        }
        printf("\nFaça uma jogada: ");
        fgets(message, 100, stdin);
        line = atoi(&message[0]); col = atoi(&message[2]); turn = 'X';
        if (marca_velha(line, col, turn) != 1){ printf("Movimento invalido, perdeu a vez.");}
        else{ printf("\nJogada feita com sucesso.\n"); desenha_velha(); }
        send(fd, message, 4, 0);

        memset(message, '\0',sizeof(message));
        fflush(stdin);

        if ((check = verifica_ganhador()) != ' ') { 
            if ((check = verifica_ganhador()) == 0) printf("\n-> Os Jogadores empataram. <-\n");
            else printf("\n->Ganhador é o %c <-\n", check);
            exit(1);
        }

        recv(fd, message, 4, 0);
        printf("\nJogada do oponente: %s", message);
        line = atoi(&message[0]); col = atoi(&message[2]); turn = 'O';
        if (marca_velha(line, col, turn) != 1){ printf("Jogada do oponente foi um movimento invalido, perdeu a vez."); }
        else{ printf("\nJogada do oponente feita com sucesso.\n"); desenha_velha(); }

        memset(message, '\0',sizeof(message));
        fflush(stdout);        

        if ((check = verifica_ganhador()) != ' ') { 
            if ((check = verifica_ganhador()) == 0) printf("\n-> Os Jogadores empataram. <-\n");
            else printf("\n->Ganhador é o %c <-\n", check);
            exit(1);
        }

	}
    close(fd);
	return 0;
}

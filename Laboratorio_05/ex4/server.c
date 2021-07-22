#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

struct sockaddr_in serv; 
int fd_socket, fd_fifo; 
int conn;
int pipe_1[2];
int pipe_2[2];
char message[100] = ""; 
int flag = 1;

int main(){
    printf("\nServidor Iniciado!\n");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8096); 
	serv.sin_addr.s_addr = INADDR_ANY;
	
	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd_socket, (struct sockaddr *)&serv, sizeof(serv)); 
	listen(fd_socket,2);

    pipe(pipe_1);
    pipe(pipe_2);

	while((conn = accept(fd_socket, (struct sockaddr *)NULL, NULL))) {

        int flag_fork = -1;
        flag_fork = flag;
        if(flag){flag = 0;}

		int pid = fork();
        connect(fd_socket, (struct sockaddr *)&serv, sizeof(serv));
		if(pid == 0){
            if(flag_fork){
            //FILHO 1
                printf("-->Entrou Filho1;\n");
                char cmd[3];
                close(pipe_1[1]);
                while(!read(pipe_1[0],cmd, sizeof(cmd))) break;
                printf("\nFilho 2 Escreveu no Pipe! [%s]\n", cmd);
                send(fd_socket, "OI",2, 0);

			    while (recv(conn, message, 100, 0) > 0) {
                    close(pipe_2[0]);
                    write(pipe_2[1], message, 3);
                    printf("\nEu escrevi para o Filho 2!\n");

                    close(pipe_1[1]);
                    while(!read(pipe_1[0],cmd, sizeof(cmd))) break;
                    printf("\nFilho 1 Escreveu no Pipe! [%s]\n", cmd);
                }
                
            }else{
            //FILHO 2
                char cmd[3];

                printf("-->Entrou Filho2;\n");
			    while (recv(conn, message, 100, 0) > 0) {

                    close(pipe_1[0]);
                    write(pipe_1[1], message, 3);
                    printf("\nEu escrevi para o Filho 1!\n");

                    close(pipe_2[1]);
                    while(!read(pipe_2[0],cmd, sizeof(cmd))) break;
                    printf("\nFilho 1 Escreveu no Pipe! [%s]\n", cmd);
                }
            }  
			
		}
	}
}

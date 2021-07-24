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

int main(){
    int fd, conn, child_pid, pipe_1[2], pipe_2[2], flag = 1;
    char message[100] = " "; 
    
    printf("Servidor Iniciado!\n");
    memset(message, '0',sizeof(message));

	fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv; 
    memset(&serv, '0', sizeof(serv)); 
    
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8096); 
	serv.sin_addr.s_addr = htonl(INADDR_ANY);;
	
	bind(fd, (struct sockaddr *)&serv, sizeof(serv)); 
	listen(fd, 2);

    pipe(pipe_1);
    pipe(pipe_2);

	while((conn = accept(fd, (struct sockaddr *)NULL, NULL))) {
        int flag_fork = flag;
        if(flag == 1){ flag = 0; }

		if ( (child_pid = fork ()) == 0 ){
            if (flag_fork == 1){
                bzero(message, strlen(message));
                while (recv(conn, message, 100, 0) > 0) {
                    printf("Mensagem do filho [1]: %s", message);
                    send(conn, message, strlen(message), 0);
                    bzero(message, strlen(message));
                }
            }
            else {
                bzero(message, strlen(message));
                while (recv(conn, message, 100, 0) > 0) {
                    printf("Mensagem do filho [2]: %s", message);
                    send(conn, message, strlen(message), 0);
                    bzero(message, strlen(message));
                }
            }
        }
	}
    close(conn);
	exit(0);
}

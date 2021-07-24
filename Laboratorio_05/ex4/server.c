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
    int fd, conn, child_pid, pipe_1[2], pipe_2[2], flag = 1, first_msg = 1;
    char message[100] = " ", buffer_1[3], buffer_2[3]; 
    
    printf("Servidor Iniciado!\n");
    memset(message, '\0',sizeof(message));
    memset(buffer_1, '\0',sizeof(buffer_1));
    memset(buffer_2, '\0',sizeof(buffer_2));

	fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv; 
    memset(&serv, '\0', sizeof(serv)); 
    
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
                    close(pipe_1[1]);
                    if (read(pipe_1[0], buffer_1, sizeof(buffer_1)) > 0){
                        send(conn, buffer_1, strlen(buffer_1), 0);
                        memset(buffer_1, '\0',sizeof(buffer_1));
                    }

                    close(pipe_2[0]);
                    write(pipe_2[1], message, (strlen(message) + 1));
                }
            }
            else {
                bzero(message, strlen(message));

                while (recv(conn, message, 100, 0) > 0) {
                    if (first_msg){first_msg = -1; close(pipe_1[0]); write(pipe_1[1], message, (strlen(message) + 1));}

                    close(pipe_2[1]);
                    if (read(pipe_2[0], buffer_2, sizeof(buffer_2)) > 0){
                        send(conn, buffer_2, strlen(buffer_2), 0);
                        memset(buffer_2, '\0',sizeof(buffer_2));
                    }

                    close(pipe_1[0]);
                    write(pipe_1[1], message, (strlen(message) + 1));
                }
            }
        }
	}
    close(conn);
	exit(0);
}

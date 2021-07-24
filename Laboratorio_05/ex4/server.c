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
    int fd, conn, child_pid, pipe_1[2], pipe_2[2], flag = 1, flag_first_msg = 1;
    char message[100] = " ", buffer_1[4], buffer_2[4]; 
    
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
                send(conn, "Yes", 4, 0);
                bzero(message, strlen(message));

                while (!read(pipe_1[0], buffer_1, sizeof(buffer_1))){ }
                send(conn, "Con", 4, 0);

                while (!read(pipe_1[0], buffer_1, sizeof(buffer_1))){ }
                send(conn, buffer_1, sizeof(buffer_1), 1);

                while (recv(conn, message, 100, 0) > 0) {
                    close(pipe_1[1]);
                    read(pipe_1[0], buffer_1, sizeof(buffer_1));
                    send(conn, buffer_1, 4, 0);

                    close(pipe_2[0]);
                    write(pipe_2[1], message, 4);
                }
            }
            else {
                send(conn, "No", 4, 0);
                bzero(message, strlen(message));
                close(pipe_1[0]);
                write(pipe_1[1], "Sta", 4);

                while (recv(conn, message, 100, 0) > 0) {
                    if (flag_first_msg){flag_first_msg = -1;}
                    else{
                        close(pipe_2[1]);
                        read(pipe_2[0], buffer_2, sizeof(buffer_2));
                        send(conn, buffer_2, 4, 0);
                    }
                    close(pipe_1[0]);
                    write(pipe_1[1], message, 4);
                    send(conn, buffer_2, 4, 0);
                }
            }
        }
	}
    close(conn);
	exit(0);
}

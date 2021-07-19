#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
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
int mypipe[2];
char message[100] = ""; 

/* Lê os caracteres do pipe e imprime em stdout. */
void read_from_pipe(int file) {
	FILE *stream;
	int c;
	stream = fdopen(file, "r");
	while ((c = fgetc(stream)) != EOF)
		putchar(c);
	fclose(stream);
}

/* Escreve um texto no pipe. */
void write_to_pipe(int file, char* string) {
	FILE *stream;
	stream = fdopen(file, "w");
	fprintf(stream, "%s",string);
	fclose(stream);
}

int main(){
	FILE *stream;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8096); 
	serv.sin_addr.s_addr = INADDR_ANY;
	
	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd_socket, (struct sockaddr *)&serv, sizeof(serv)); 
	listen(fd_socket,2);

	if (pipe(mypipe)) {
		fprintf(stderr, "Falha ao criar o Pipe.\n");
		return EXIT_FAILURE;
	}

	while((conn = accept(fd_socket, (struct sockaddr *)NULL, NULL))) {
		int pid = fork();
		if(pid == 0) {
			while (recv(conn, message, 100, 0) > 0) {
				if (message[0] == 'q'){
					//close(mypipe[1]);
					int c;
					stream = fdopen(mypipe[0], "r");
					//while ((c = fgetc(stream)) != EOF)
					printf("-->>%d",stream[0]);
					//fclose(stream);
				}
				printf("Message Received: %s\n", message);
				close(mypipe[0]);
				stream = fdopen(mypipe[1], "w");
				fprintf(stream, "%s",message);
				//fclose(stream);
				memset(message, '\0', sizeof (message));
				//write_to_pipe(mypipe[1], message);
			}
			printf("QUe1");
			//exit(0);
		}
	}
	printf("\n\nOLaqwe\n\n");
}
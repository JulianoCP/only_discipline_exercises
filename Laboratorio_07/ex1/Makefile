CC=gcc -Wall

PROGS=semaforo

all: $(PROGS)

clean:
	rm -f $(PROGS)

semaforo: semaforo.c
	$(CC) semaforo.c -o semaforo -lpthread


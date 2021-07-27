CC=gcc -Wall

P1=sum_matrix

PROGS=$(P1)

all: $(PROGS)

$(P1):
	$(CC) $(P1).c -o $(P1) -lpthread
	@echo "Executar: ./sum_matrix <NUMERO_THREADS>"

clean:
	rm $(PROGS)

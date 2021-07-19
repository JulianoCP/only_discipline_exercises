CC=gcc -Wall

PROGS=main

all: $(PROGS)

clean:
	rm -f $(PROGS)

main: main.c
	$(CC) $< -o $@
	@./$@
	


CC=gcc -Wall

PROGS=read_fifo write_fifo

all: $(PROGS)

clean:
	rm -f $(PROGS)

read_fifo: read_fifo.c
	$(CC) $< -o $@

write_fifo: write_fifo.c
	$(CC) $< -o $@

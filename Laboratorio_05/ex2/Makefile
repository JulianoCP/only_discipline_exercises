CC=gcc -Wall

PROGS=read_write_signal

all: $(PROGS)

clean:
	rm -f $(PROGS)

read_write_signal: read_write_signal.c
	$(CC) $< -o $@


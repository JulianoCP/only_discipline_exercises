CC := gcc
FLAGS=-lpthread

thread_find: threadFind.c 
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@ $(FLAGS)
	
	@echo "Executando o arquivo ./$@ 5 15 "
	@./$@ 5 15

repeat: repetido.c 
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@ $(FLAGS)
	
	@echo "Executando o arquivo ./$@"
	@./$@
	
multi: matriz.c multi.c
	@echo "Compilando o arquivo $<"
	@$(CC) -c -o matriz.o matriz.c -I.
	@$(CC) -c -o multi.o multi.c -I. 
	@$(CC) -o multi matriz.o multi.o $(FLAGS)

	@echo "Executando o arquivo ./$@"
	@./$@

clear: 
	@echo "Excluindo binarios"
	@rm thread_find repeat multi matriz.o multi.o



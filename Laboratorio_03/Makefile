CC := gcc
FLAGS=-lpthread

thread_find: threadFind.c 
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@ $(FLAGS)
	
	@echo "Executando o arquivo ./$@ 5 15 "
	@./$@ 5 15


clear: 
	@echo "Excluindo binarios"
	@rm thread_find


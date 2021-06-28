CC := gcc

busca: busca.c 
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@
	
	@echo "Executando o arquivo ./$@ 3 10 '1 2 3 4 5 6 7 8 9 10 11 12 13' "
	@./$@ 3 10 "1 2 3 4 5 6 7 8 9 10 11 12 13"

hierarquia: hierarquia.c
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@
	
	@echo "Executando o arquivo ./$@ 3"
	@./$@ 3

protoshell: protoShell.c
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@

	@echo "Executando o arquivo ./$@ ls -ilha /home/"
	@./$@ ls -ilha /home/

shell: shell.c
	@echo "Compilando o arquivo $<"
	@$(CC) $< -o $@

	@echo "Executando o arquivo ./$@"
	@./$@ 

clear: 
	@echo "Excluindo binarios"
	@rm busca hierarquia protoshell shell


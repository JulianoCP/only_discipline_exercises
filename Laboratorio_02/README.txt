
<>COMO EXECUTAR<>

---------------------------------------------------------------
Programa: hierarquia.c
Compilar: gcc hierarquia.c -o hierarquia
Executar: ./hierarquia <NUMERO>
Exemplo: ./hierarquia 3

MAKE: make hierarquia

---------------------------------------------------------------
Programa: protoShell.c
Compilar: gcc protoShell.c -o protoShell
*Executar: ./protoShell <COMANDO> <PARAMETROS>
Exemplo: 
        ./protoShell ls
        ./protoShell ls -ilha /home/

* Apenas os comandos nativos do Linux são suportados
    Verificar cos comandos com:
            > ls /bin/

MAKE: make protoshell

---------------------------------------------------------------
Programa: busca.c
Compilar: gcc busca.c -o busca
Executar: ./busca <NUM_FILHOS> <VALOR_BUSCA> <STRING_VETOR>
Exemplo:  ./busca 3 10 "1 2 3 4 5 6 7 8 9 10 11 12 13"

MAKE: make busca

---------------------------------------------------------------
Programa: shell.c
Compilar: gcc shell.c -o shell
Executar: ./shell
Exemplo:  ./shell 
        > ls
        > ls /home/
        > ls &
        >
MAKE: make shell
---------------------------------------------------------------




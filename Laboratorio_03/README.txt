
<>COMO EXECUTAR<>

---------------------------------------------------------------
Programa: threadFind.c
Compilar: gcc threadFind.c -o thread_find -lpthread
Executar: ./thread_find <NUMERO_DE_THREADS> <VALOR_PROCURADO>
Exemplo: ./thread_find 3 5

MAKE: make thread_find
---------------------------------------------------------------
Programa: repetido.c
Compilar: gcc repetido.c -o repeat -lpthread
Executar: ./repeat 
Exemplo: ./repeat

MAKE: make repeat
---------------------------------------------------------------
Programa: multi.c
Compilar: 
        gcc -c -o matriz.o matriz.c -I
        gcc -c -o multi.o multi.c -I
        gcc -o multi matriz.o multi.o -lpthread -lm
Executar: ./multi <NUMERO_DE_THREADS>
Exemplo: ./multi 8

MAKE: make multi
---------------------------------------------------------------



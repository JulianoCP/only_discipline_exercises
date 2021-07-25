/*
main (int argc, char *argv[]) {
    int l, c;
    char vez='X';
    
    inicio_velha();
    desenha_velha();
    
    int i=0;
    while (1) {
	
	do {
	   printf ("\nLinha: ");
	   scanf("%i", &l);
	   printf ("Coluna: ");
	   scanf("%i", &c);
	   printf ("\n");
	} while (marca_velha(l,c,vez) != 1);
        
	desenha_velha();
	
	char resp = verifica_ganhador();
	if (resp != ' ') { 
	   if (resp == 0) printf ("\n\nEmpate!!!!!!!\n\n", resp);
	   else printf ("\n\nGanhador é %c\n\n", resp);
	   exit(1);
	} //if
	
	if (i%2 == 0) vez = '0';
	else vez = 'X';
	i++;
    } //while
} //main
*/
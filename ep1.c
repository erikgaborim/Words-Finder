#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "lista.h"
#include "arvore.h"

#define TAMANHO 1000

float Clock(int reset){ //função para medir o tempo
	static clock_t startTime;
	if(reset){
		startTime = clock();
	}
	clock_t endTime = clock();
	return 1000*(((float)(endTime-startTime))/CLOCKS_PER_SEC);
}

//transforma em uma lista de palavras uma unica palavra separada por '-', '/' ou '_'
char** trata_hifen_barra(char* palavra, char sinal, int* contador_palavras_esp){
	char** lista_palavras = (char**) malloc(TAMANHO*sizeof(char*));
	int cont=0;
	char *token;
	while((token = strsep(&palavra, &sinal)) != NULL) {
        lista_palavras[cont] = token;
        cont++; 
    }
   	*contador_palavras_esp = cont;
	return lista_palavras;
}

//remove a pontuacao presente nas palavras (como , e .)
char remove_pontuacao(char* palavra){
	int tamanho_palavra = strlen(palavra);
    for (int i = 0; i < tamanho_palavra; i++) {
    	if(palavra[i] == '-'){
        	return '-';
        }else if(palavra[i] == '/'){
        	return '/';
        }else if(palavra[i] == '_'){
        	return '_';
        }
        if (ispunct(palavra[i])) {
            memmove(&palavra[i], &palavra[i + 1], tamanho_palavra - i);
            tamanho_palavra--;
            i--;
        }
    }
    return 'a';
}

int main(int argc, char ** argv){
	//argc e um inteiro que corresponde a quantidade de argumentos passados pelo terminal na execucao do programa
	//argv e o vetor de strings que guarda os indices passados pelo terminal
	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	int contador_linha;
	Boolean isArvore;

	ListaLigada* lista =  cria_lista();
	Arvore* arvore = cria_arvore();
	Boolean estruturaValida = TRUE;

	if(argc == 3) {
		int contador_palavras=0;
		char** linhas = (char**) malloc(TAMANHO * sizeof(char*));
		if(strcmp ("lista", argv[2]) != 0 && strcmp ("arvore", argv[2]) != 0){
			printf("Tipo de estrutura invalido.");
			estruturaValida = FALSE;
		}else{
			if(strcmp("lista", argv[2]) == 0){ //baseado em lista
				isArvore = FALSE;
			}if(strcmp("arvore", argv[2]) == 0){ //baseado em arvore
				isArvore = TRUE;
			}
			float tempo = Clock(1);
			in = fopen(argv[1], "r"); //in recebe o conteudo do arquivo txt
			if(in == NULL){
				printf("Arquivo nao encontrado!");
				return 0;
			}
			contador_linha = 0;
	 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

			while(in && fgets(linha, TAMANHO, in)){
				
				if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0; //linha para tratar o '\n' para quebra de linha

				copia_ponteiro_linha = linha;
				char* linhaReal = strdup(linha);
				linhas[contador_linha] = linhaReal;

				//insercao das palavras na estrutura escolhida
				if(isArvore){
					while((palavra = strsep(&copia_ponteiro_linha, " "))){
						char* palavraReal = strdup(palavra);
						char sinal = remove_pontuacao(palavraReal);
						if(sinal != 'a'){ //isso significa que a palavra em questao possui '-', '/' ou '_'
							int* contador_palavras_esp = (int*) malloc(sizeof(int));
							char** palavras_especiais = trata_hifen_barra(palavraReal, sinal, contador_palavras_esp);
							for(int i=0; i<*contador_palavras_esp; i++){
								NoArvore* noNovo = (NoArvore*) malloc(sizeof(NoArvore));
								noNovo->valor = palavras_especiais[i];
								noNovo->linha = contador_linha+1;
								noNovo->ocorrencias = 1;
								insereArvore(arvore, noNovo);
								contador_palavras++;
							}
						}else{
							NoArvore* noNovo = (NoArvore*) malloc(sizeof(NoArvore));
							noNovo->valor = palavraReal;
							noNovo->linha = contador_linha+1;
							noNovo->ocorrencias = 1;
							insereArvore(arvore, noNovo);
							contador_palavras++;
						}
					}
				}else{
					while((palavra = strsep(&copia_ponteiro_linha, " "))){
						char* palavraReal = strdup(palavra);
						char sinal = remove_pontuacao(palavraReal);
						if(sinal != 'a'){ //isso significa que a palavra em questao possui '-', '/' ou '_'
							int* contador_palavras_esp = (int*) malloc(sizeof(int));
							char** palavras_especiais = trata_hifen_barra(palavraReal, sinal, contador_palavras_esp);
							for(int i=0; i<*contador_palavras_esp; i++){
								No* noNovo = (No*) malloc(sizeof(No));
								noNovo->valor = palavras_especiais[i];
								noNovo->indice = contador_palavras;
								noNovo->linha = contador_linha+1;
								noNovo->ocorrencias=1;
								noNovo->quantidadeLinhas=1;
								insereLista(lista, noNovo, contador_palavras);
								contador_palavras++;
							}
						}else{
							No* noNovo = (No*) malloc(sizeof(No));
							noNovo->valor = palavraReal;
							noNovo->indice = contador_palavras;
							noNovo->linha = contador_linha+1;
							noNovo->ocorrencias=1;
							noNovo->quantidadeLinhas=1;
							insereLista(lista, noNovo, contador_palavras);
							contador_palavras++;
						}
					}
				}
				contador_linha++;
			}

			tempo = Clock(0);
			printf("Tipo de indice: '%s'", argv[2]);
			printf("\nArquivo de texto: '%s'", argv[1]);
			printf("\nNúmero de linhas no arquivo: %i", contador_linha);
			printf("\nTempo para carregar o arquivo e construir o indice: %f ms", tempo);
		}

		//busca
		while(estruturaValida){
			char entrada[256];
			char palavra1[256];
			char palavraBuscada[256];
			
			printf("\n> ");

			fgets(entrada, sizeof(entrada), stdin);
			entrada[strcspn(entrada, "\n")] = '\0';

			if(strcmp("fim", entrada) == 0) break;

			if (sscanf(entrada, "%s %s", palavra1, palavraBuscada) == 2) {
			    if(strcmp("busca", palavra1) == 0){
			    	float tempoBusca = Clock(1);
			    	if(isArvore){
			    		NoArvore* elementoEncontrado = busca_bin(arvore, palavraBuscada);
			    		if(elementoEncontrado != NULL){
			    			printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):", elementoEncontrado->ocorrencias, palavraBuscada);
			    			int* linhasEncontradas = arranjo_linhas_encontradas(elementoEncontrado);
			    			tempoBusca = Clock(0);
			    			for(int i=0; i<elementoEncontrado->quant_linhas; i++){
				    			printf("\n%04d: %s",linhasEncontradas[i], linhas[linhasEncontradas[i]-1]);
				    		}
			    		}else{
				    		printf("Palavra '%s' nao encontrada.", palavraBuscada);
				    	}
				    	printf("\nTempo de busca: %f ms", tempoBusca);
			    	}else{
				    	No* elementoEncontrado = buscaLista(lista, palavraBuscada, contador_palavras);
				    	int* linhasEncontradas = arranjo_linhas_encontradas_lista(elementoEncontrado);
				    	tempoBusca = Clock(0);

				    	if(elementoEncontrado != NULL){
				    		printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):", elementoEncontrado->ocorrencias, palavraBuscada);
				    		for(int i=0; i<elementoEncontrado->quantidadeLinhas; i++){
				    			printf("\n%04d: %s",linhasEncontradas[i], linhas[linhasEncontradas[i]-1]);
				    		}
				    	}else{
				    		printf("Palavra '%s' nao encontrada.", palavraBuscada);
				    	}
				    	printf("\nTempo de busca: %f ms", tempoBusca);
			    	}
			    }else{
			    	printf("Opcao invalida!");
			    }
			}else{
				printf("Opcao invalida!");
			}
		}
		return 0;
	}
	else{
		printf("Quantidade invalida de argumentos.");
	}

	return 1;
}
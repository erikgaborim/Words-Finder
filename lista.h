#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef char* Palavras;
typedef char** Linhas;

#define TAMANHO 1000

typedef struct _no_ {
	Palavras valor;
	int indice;
	int linha;
	int ocorrencias;
	int quantidadeLinhas;
	struct _no_* palavra_igual;
	struct _no_* proximo;
} No;

typedef struct _listaLigada_ {
	No* primeiro;
	No* ultimo;
} ListaLigada;

void modifica_no(No* noAntigo, No* noNovo){
	noAntigo->palavra_igual = noNovo;
}

ListaLigada* cria_lista(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = NULL;
	
	return lista;
}

void imprime(ListaLigada * lista){

	No* p;

	printf("Lista:");

	for(p = lista->primeiro; p; p = p->proximo){

		printf(" %s", p->valor);
	}

	printf("\n");
}

Boolean insereLista(ListaLigada * lista, No* novo, int indice){

	int i;

	No* p;
	
	if(indice >= 0){

		if(indice == 0){
			lista->primeiro = novo;
		}
		else{

			i = 0;
			p = lista->primeiro;

			while(p){

				if(strcasecmp(novo->valor, p->valor) == 0 && p->palavra_igual == NULL){
					modifica_no(p, novo);
				}

				if(i == indice - 1) break;

				i++;
				p = p->proximo;
			}
		
			novo->proximo = p->proximo;
			p->proximo = novo;
		}

		return TRUE;
	}

	return FALSE;
}

int* arranjo_linhas_encontradas_lista(No* no){
	int* linhas = (int*) malloc(TAMANHO*sizeof(int));
	No* p = (No*) malloc(sizeof(No));
	int cont = 0;

	if(no == NULL){
		return NULL;
	}
	p = no;
	while(p->palavra_igual != NULL){
		no->ocorrencias++;
		if(cont == 0){
			linhas[cont] = p->linha;
			cont++;
		}
		else if(p->linha != linhas[cont-1]){
			linhas[cont] = p->linha;
			cont++;
		}
		p = p->palavra_igual;
	}
	if(cont > 0 && p->linha != linhas[cont-1]){
		linhas[cont] = p->linha;
		cont++;
	}else if(cont == 0){
		linhas[cont] = p->linha;
		cont++;
	}

	no->quantidadeLinhas = cont;
	return linhas;
}


No* buscaLista(ListaLigada* lista, char* palavraBuscada, int qntdPalavras){
	Boolean encontrado;
	No* novo = (No*) malloc(sizeof(No));
	No* p = lista->primeiro;
	novo->valor = palavraBuscada;

	for(int i=0; i<qntdPalavras; i++){
		if(strcasecmp(novo->valor, p->valor) == 0){
			novo = p;
			encontrado = TRUE;
			break;
		}
		if(i == qntdPalavras-1){
			encontrado = FALSE;
			break;
		}
		p = p->proximo;
	}
	if(!encontrado){
		return NULL;
	}
	return novo;
	
}
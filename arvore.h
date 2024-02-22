#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef char* Palavras;
typedef char** Linhas;

#define TAMANHO 1000

typedef struct _no_arvore_ {
	Palavras valor;
	int linha;
	int ocorrencias;
	int quant_linhas;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;
	struct _no_arvore_ * palavra_igual;
} NoArvore;

typedef struct {
	NoArvore* raiz;
} Arvore;

Arvore* cria_arvore(){

	Arvore* arvore = (Arvore*) malloc (sizeof(Arvore));
	arvore->raiz = NULL;	
	return arvore;
}

void imprime_rec(NoArvore* no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec(no->esq);
		printf(" %s", no->valor);
		imprime_rec(no->dir);
	}
}

void imprimeArvore(Arvore * arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}

NoArvore* busca_bin_rec(NoArvore* no, char* palavraBuscada){
	if(no){
		if(strcasecmp(palavraBuscada, no->valor) == 0){
			return no;
		} 
		if(strcasecmp(palavraBuscada, no->valor) < 0) return busca_bin_rec(no->esq, palavraBuscada);
		return busca_bin_rec(no->dir, palavraBuscada);
	}

	return NULL;
}

NoArvore* busca_bin(Arvore* arvore, char* palavraBuscada){
	
	return busca_bin_rec(arvore->raiz, palavraBuscada);	
}

void controla_palavras_iguais(NoArvore* no1, NoArvore* no2){
	NoArvore* p = (NoArvore*) malloc(sizeof(NoArvore));
	p = no1;
	while(p->palavra_igual != NULL){
		p = p->palavra_igual;
	}
	p->palavra_igual = no2;
	no1->ocorrencias++;
	no2->ocorrencias = no1->ocorrencias;
}

int* arranjo_linhas_encontradas(NoArvore* no){
	NoArvore* p = (NoArvore*) malloc(sizeof(NoArvore));
	int* arranjo = (int*) malloc(no->ocorrencias * sizeof(int));
	no->quant_linhas = no->ocorrencias;
	p = no;
	int cont = 0;
	while(p->palavra_igual != NULL){
		if(p->linha != arranjo[cont-1]){
			arranjo[cont] = p->linha;
			cont++;
		}else{
			no->quant_linhas--;
		}
		p = p->palavra_igual;
	}
	if(p->linha != arranjo[cont-1]){
		arranjo[cont] = p->linha;
	}else{
		no->quant_linhas--;
	}
	return arranjo;
}

Boolean insere_ord_rec(NoArvore* raiz, NoArvore* novo){

	if(strcasecmp(novo->valor, raiz->valor) != 0){

		if(strcasecmp(novo->valor, raiz->valor) < 0){

			if(raiz->esq) return insere_ord_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}else{
		controla_palavras_iguais(raiz, novo);
	}

	return FALSE;
}

Boolean insereArvore(Arvore* arvore, NoArvore* novo){
	novo->esq = novo->dir = NULL;

	if(arvore->raiz) return insere_ord_rec(arvore->raiz, novo);
		
	arvore->raiz = novo;
	return TRUE;
}
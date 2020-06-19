//Aluno: João Paulo Vaz Mendes
//Matrícula: 17/0002934
//utilizando o código de Árvore Binária de Busca desenvolvido em aula com o Professor Doutor Vinicius Ruela Pereira Borges
//arquivo de biblioteca .c com funções usadas no arquivo main.c

#include <stdio.h>
#include <stdlib.h>
#include "bib.h"

typedef struct no
{
    Data data;
    int alt;
    struct no *esq;
    struct no *dir;
} no;

int string_comprimento(char str[])
{
	int i = 0;
	while(str[++i]!='\0');
	return i--;
}

void string_clone(char fonte[], char destino[])
{
	int i,fontecomp;
	fontecomp = string_comprimento(fonte);
	for(i = 0;i <= fontecomp;i++)
	{
		destino[i] = fonte[i];
	}
}

int menu()
{
    int op=0, ok =0;


    while(!ok)
    {
        printf("\n\n\n\n\nAmbiente de consultas das avaliações de docentes - Opções\n\n");
        printf("(1) Mostrar informações do nó raiz \n");
        printf("(2) Mostrar a média das chaves das sub-árvores esquerda e direita \n");
        printf("(3) Mostrar todas as avaliações de um docente para as 3 chaves\n");
        printf("(4) Pesquisar o nome dos docentes da árvore esquerda com um das 3 chaves\n");
	printf("(5) Pesquisar o nome dos docentes da árvore direita com um das 3 chaves\n");
	printf("(6) Apresentar a  quantidade de vezes que um docente aparece na árvore direita com uma das 3 chaves \n");
	printf("(7) Apresentar a  quantidade de vezes que um docente aparece na árvore esquerda com uma das 3 chaves \n");
        printf("(0) SAIR\n");
        printf("Digite a sua opcao: ");
        scanf("%d",&op);

        if(op < 0 || op > 7)
        {
            printf("\nERRO: Opção inexistente\n");
            ok = 0;
        }
        else
        {
            ok = 1;
        }
    }
    return op;
}

Tree ** cria_inicializa_Tree()
{
    Tree **novo;
    // Cria um novo endereco para a raiz da arvore
    novo = (Tree **) malloc (sizeof(Tree *));
    // Se alocacao deu certo
    if(novo != NULL)
    {
        // Inicializa a arvore (uma arvore vazia)
        *novo = NULL;
    }
}

int ehVazia_Tree(Tree **root)
{
    if(root != NULL)
    {
        if(*root == NULL)
        {
            return 1; // eh vazia
        }
        else
        {
            return 0; // nao eh vazia
        }
    }
    return -1; // nao existe
}

int alt_NO(Tree* no)
{
	if(no == NULL)
	{
		return -1;
	}
	else
	{
		return no->alt;
	}
}

/*
int alt_ABB(Tree **root)
{
	if(root == NULL)
	{
		return -1;
	}
	else
	{
		if(((*root)->esq == NULL) && ((*root)->dir == NULL))
		{
			return maior(alt_NO((*root)->esq),alt_NO((*root)->dir));
		}
		else
		{
			//alt_ABB();
		}
	}
*/

int fatorBalanceamento_NO(Tree* no)
{
	return labs(alt_NO(no->esq) - alt_NO(no->dir));
}

int maior(int x, int y)
{
	if(x > y)
	{
		return x;
	}
	else
	{
		return y;
	}
}


int insere_Tree(Tree **raiz, Data elem, DadoArvore *info)
{
	int res;

	if(*raiz == NULL)//arvore vazia ou nó folha
	{
		Tree *novo;
		novo = (Tree *) malloc(sizeof(Tree));
	       if(novo == NULL)
	       {
		       return 0;
	       }	       
	       novo->data = elem;
	       novo->alt = 0;
	       novo->esq = NULL;
	       novo->dir = NULL;
	       *raiz = novo;
		info->n_no++;
	       return 1;
	}

	Tree *atual = *raiz;
	if(elem.chave <= atual->data.chave)
	{
		if((res = insere_Tree(&(atual->esq),elem,info)) == 1)
		{
			if(fatorBalanceamento_NO(atual) >= 2)
			{
				if(elem.chave <= (*raiz)->esq->data.chave)
				{
					RotacaoLL(raiz);
				}
				else
				{
					RotacaoLR(raiz);
				}
			}
		}
	}
	else
	{
		if((res=insere_Tree(&(atual->dir),elem,info)) == 1)
		{
			if(fatorBalanceamento_NO(atual) >= 2)
			{
				if((*raiz)->dir->data.chave < elem.chave)
				{
					RotacaoRR(raiz);
				}
				else
				{
					RotacaoRL(raiz);
				}
			}
		}
	}

	atual->alt = maior(alt_NO(atual->esq),alt_NO(atual->dir)) + 1;
	info->n_no++;
	return res;
}

int totalNO_Tree(Tree **raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	if(*raiz == NULL)
	{
		return 0;
	}
	int alt_esq = totalNO_Tree(&((*raiz)->esq));
	int alt_dir = totalNO_Tree(&((*raiz)->dir));
	return(alt_esq + alt_dir +1);
}

int totalNO_esq(Tree **raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	if(*raiz == NULL)
	{
		return 0;
	}
	int alt_esq = totalNO_Tree(&((*raiz)->esq));
	return alt_esq;
}

int totalNO_dir(Tree **raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	if(*raiz == NULL)
	{
		return 0;
	}
	int alt_dir = totalNO_Tree(&((*raiz)->dir));
	return alt_dir;
}

int altura_Tree(Tree **raiz)
{
	if(raiz == NULL)
	{
		return 0;
	}
	if(*raiz == NULL)
	{
		return 0;
	}
	int alt_esq = altura_Tree(&((*raiz)->esq));
	int alt_dir = altura_Tree(&((*raiz)->dir));
	if(alt_esq > alt_dir)
	{
		return (alt_esq +1);
	}
	else
	{
		return (alt_dir + 1);
	}
}


void RotacaoLL(Tree **raiz)
{
	Tree *no;

	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = maior(alt_NO((*raiz)->esq),alt_NO((*raiz)->dir)) + 1;
	no->alt = maior(alt_NO(no->esq),(*raiz)->alt) +1;
	(*raiz) = no;
}

void RotacaoRR(Tree **raiz)
{
	Tree *no;
	
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = (*raiz);
	(*raiz)->alt = maior(alt_NO((*raiz)->esq),alt_NO((*raiz)->dir)) + 1;
	no->alt = maior(alt_NO(no->dir),(*raiz)->alt) + 1;
	(*raiz) = no;
}

void RotacaoLR(Tree **raiz)
{
	RotacaoRR(&(*raiz)->esq);
	RotacaoLL(raiz);
}

void RotacaoRL(Tree **raiz)
{
	RotacaoLL(&(*raiz)->dir);
	RotacaoRR(raiz);
}

void info_raiz(Tree *root)
{
	printf("\nchave: %f\n",root->data.chave);
	printf("código do docente: %d\n",root->data.docente);
	printf("nome do docente: %s\n",root->data.nome);
	printf("turma: %d\n",root->data.turma);
	printf("ano: %d\n",root->data.ano);
	printf("periodo: %d\n",root->data.periodo);
	printf("quantidade de discentes: %d\n",root->data.discente);
	printf("postura profissional média: %f\n",root->data.ppm);
	printf("postura profissional DP: %f\n",root->data.ppd);
	printf("atuação profissional média: %f\n",root->data.apm);
	printf("atuação profissional DP: %f\n",root->data.apd);
	printf("autoavaliação aluno média: %f\n",root->data.aam);
	printf("autoavaliação aluno DP: %f\n",root->data.aad);
}

// Funcao que visita um no
void visit(Tree *no)
{
    printf(" %f ",no->data.chave);
}

void caminha_InOrder_Tree(Tree **root)
{
    if(root != NULL)
    {
        caminha_InOrder_Tree_rec(*root);
    }
    printf("\n");
}

void caminha_InOrder_Tree_rec(Tree *root)
{
    // Criterio de parada da recursao
    if(root == NULL)
    {
        return ;
    }
    caminha_InOrder_Tree_rec(root->esq);
    visit(root);
    caminha_InOrder_Tree_rec(root->dir);
}

float media_chave(Tree **root)
{
	float soma = 0,media;
	int total = 0;
	while(root != NULL)
	{
        	media_chave_rec(*root,&soma,&total);
	}
	media = soma / total;
	return media;
}

void media_chave_rec(Tree *root, float *s,int *t)
{
	if(root == NULL)
	{
		return ;
	}
	media_chave_rec(root->esq,s,t);
	s++;
	t++;
	media_chave_rec(root->dir,s,t);
}

float pega_chave_int(Tree *raiz, int dado)
{
	float chave;
	if(raiz == NULL)
	{
		return -1;
	}
	pega_chave_int(raiz->esq,dado);
	if((chave = volta_chave(raiz,dado)) != 0)
	{
		return chave;
	}
	pega_chave_int(raiz->dir,dado);
}

float volta_chave(Tree *no,int dado)
{
	if(dado == no->data.docente)
	{
		return no->data.chave;
	}
	else
	{
		return 0;
	}
}

int busca_prof(Tree **raiz, int prof)
{
	float chave;
	if(raiz == NULL)
	{
		return 0;
	}
	Tree *atual = *raiz;
	while(atual != NULL)
	{
		chave = pega_chave_int(*raiz,prof);
		if(chave == atual->data.chave)
		{
			printf("postura profissional média: %f\n",atual->data.ppm);
			printf("postura profissional DP: %f\n",atual->data.ppd);
			printf("atuação profissional média: %f\n",atual->data.apm);
			printf("atuação profissional DP: %f\n",atual->data.apd);
			printf("autoavaliação aluno média: %f\n",atual->data.aam);
			printf("autoavaliação aluno DP: %f\n",atual->data.aad);
			return 1;
		}
		if(chave > atual->data.chave)
		{
			atual = atual->dir;
		}
		else
		{
			atual = atual->esq;
		}
	}
	printf("\nCódigo de professor inexistente na árvore\n");
}

int busca_prof_esq(Tree **raiz, int prof)
{
	float chave;
	if(raiz == NULL)
	{
		return 0;
	}
	Tree *atual = (*raiz)->esq;
	while(atual != NULL)
	{
		chave = pega_chave_int(*raiz,prof);
		if(chave == atual->data.chave)
		{
			printf("\nO professor está presente na sub-árvore esquerda\n");
			return 1;
		}
		if(chave > atual->data.chave)
		{
			atual = atual->dir;
		}
		else
		{
			atual = atual->esq;
		}
	}
	printf("\nCódigo de professor inexistente na árvore, ou não sub-árvore esquerda\n");
}

int busca_prof_esq_n(Tree **raiz, int prof)
{
	float chave;
	int n = 0;
	if(raiz == NULL)
	{
		return 0;
	}
	Tree *atual = (*raiz)->esq;
	while(atual != NULL)
	{
		chave = pega_chave_int(*raiz,prof);
		if(chave == atual->data.chave)
		{
			n++;
		}
		if(chave > atual->data.chave)
		{
			atual = atual->dir;
		}
		else
		{
			atual = atual->esq;
		}
	}
	return n;
}

int busca_prof_dir(Tree **raiz, int prof)
{
	float chave;
	if(raiz == NULL)
	{
		return 0;
	}
	Tree *atual = (*raiz)->dir;
	while(atual != NULL)
	{
		chave = pega_chave_int(*raiz,prof);
		if(chave == atual->data.chave)
		{
			printf("\nO professor está presente na sub-árvore direita\n");
			return 1;
		}
		if(chave > atual->data.chave)
		{
			atual = atual->dir;
		}
		else
		{
			atual = atual->esq;
		}
	}
	printf("\nCódigo de professor inexistente na árvore, ou não sub-árvore direita\n");
}

int busca_prof_dir_n(Tree **raiz, int prof)
{
	float chave;
	int n = 0;
	if(raiz == NULL)
	{
		return 0;
	}
	Tree *atual = (*raiz)->dir;
	while(atual != NULL)
	{
		chave = pega_chave_int(*raiz,prof);
		if(chave == atual->data.chave)
		{
			n++;
		}
		if(chave > atual->data.chave)
		{
			atual = atual->dir;
		}
		else
		{
			atual = atual->esq;
		}
	}
	return n;
}

int remove_Arvore(Tree **root, Data elem)
{
    Tree *aux;
    
    // Se arvore existe
    if(root == NULL)
    {
	return -1;
    }
    
    // Se arvore eh vazia
    if(*root == NULL)
    {
	return -1;
    }
    
    // Verifica se o no da raiz eh o no a ser removido
    if((*root)->data.chave == elem.chave)
    {
        // Salva o no raiz
	aux = *root;
        // Encontra um no da ABB para substituir o no raiz e que preserva
        // as propriedades ABB
	*root = substituto_Arvore(*root);
        
        // Ajusta as subarvores esquerda e direita do novo no raiz
	(*root)->esq = aux->esq;
	(*root)->dir = aux->dir;
        
        // Libera o antigo no raiz da memoria
	free(aux);
        
        // Sucesso na remocao
	return 1;
    }
    else
    {
        // Verifica se o no a ser removido estah em alguma subarvore
        // Leva o endereco do no pai (no comeco eh o proprio no raiz)
	if(elem.chave < (*root)->data.chave)
	{
	    return remove_no_Arvore_rec((*root)->esq,*root,elem);
	}
	else
	{
	    return remove_no_Arvore_rec((*root)->dir,*root,elem);
	}
    }   
}

// Funcao que remove um no da arvore que nao esteja na raiz
int remove_no_Arvore_rec(Tree *root, Tree *dad, Data elem)
{

    Tree *substituto;
    Tree *aux_free;
    
    // Se root eh null, chave de busca nao existe na arvore
    if(root == NULL)
    {
        return 0;
    }

    // Se o no atual da arvore eh o no a ser removido
    if(root->data.chave == elem.chave)
    {
        // Procura um no substituto
	substituto = substituto_Arvore(root);

        // Se o substituto existir, isto eh, se o no a ser removido nao eh folha
        if(substituto != NULL)
        {
            // Verifique se o caso 3 eh aplicado, isto eh, se eh o no removido
            // possui subarvores esquerda e direita. Se sim, tais subarvores
            // sao filhas do novo no substituto
            if(root->esq != NULL && root->dir != NULL)
            {
                substituto->dir = root->dir;
                substituto->esq = root->esq;
            }
        }

        // Verifica se o no a ser removido eh o no filho esquerdo ou direito do no pai
	if(dad->dir == root)
	{
            // Se o filho direito do pai serah removido, entao atualiza o novo no filho direito
	    dad->dir = substituto;
	}
	else
	{
            // Se o filho esquerdo do pai serah removido, entao atualiza o novo no filho esquerdo
	    dad->esq = substituto;
	}
	
	// Libera o no root da memoria
	aux_free = root;
	free(aux_free);
        
        // Retorna sucesso
	return 1;
    }
    
    // Continua a caminhar pelos nos mais profundos da arvore
    if(elem.chave > root->data.chave)
    {
	return remove_no_Arvore_rec(root->dir,root,elem);
    }
    else
    {
	return remove_no_Arvore_rec(root->esq,root,elem);
    }
}

// Funcao que obtem um no substituto para um no que serah removido
Tree * substituto_Arvore(Tree *no)
{
    // Endereco do no pai em relacao a um no
    Tree *dad;
    
    // Endereco do novo no a ser posicionado no local onde ocorrera a remocao de algum no
    Tree *novo;

    // CASO 1: O no a ser removido eh folha?
    if(no->esq == NULL && no->dir == NULL)
    {
        // Se sim, basta remover o no, nao havera substituto
	return NULL;
    }
    
    // CASO 2.1: O no a ser removido tem apenas a subarvore direita?
    if(no->esq == NULL)
    {
        // Retorna o endereco da subarvore direita
	return no->dir;
    }
    // CASO 2.2: O no a ser removido tem apenas a subarvore esquerda?
    if(no->dir == NULL)
    {
        // Retorna o endereco da subarvore esquerda
	return no->esq;
    }
    
    /* CASO 3: O no a ser removido possui sub-arvores esquerda e direita
          Deve-se procurar o no substituto, que pode ser:
          1) O no mais profundo a direita da sub-arvore esquerda do no a ser removido
          2) O no mais profundo a esquerda da sub-arvore direita do no a ser removido
          
          A opcao 1 eh implementada aqui!!!
    */
    
    // Procura pelo pai do no mais profundo a direita da sub-arvore esquerda do no a ser removido
    dad = pai_no_mais_direita(no->esq,no);
    //printf("DAD: %d\n",dad->data.chave);
    
    // Precisamos do no pai para ficar mais facil de atualizar a sua nova sub-arvore direita
    novo = dad->dir;
    
    // A sub-arvore direita do no pai eh o no filho esquerdo do no substituto
    dad->dir = novo->esq;
    
    // Retorna o endereco do novo no
    return novo;    
}

// Funcao que retorna o no pai do no mais profundo a direita da subarvore esquerda
Tree * pai_no_mais_direita(Tree *no, Tree *dad)
{  
    // Encontrou o no mais profundo a direita da subarvore esquerda, mas esse no
    // possui um filho esquerdo
    if(no->dir == NULL)
    {
        // Retorna o endereco do pai
	return dad;
    }
   
    // Senao caminha um nivel mais profundo na ABB
    return pai_no_mais_direita(no->dir,no);
}

void  libera_Tree(Tree **root)
{
	if(root != NULL)
	{
		libera_Tree_rec(*root);
	}
}

void libera_Tree_rec(Tree *root)
{
	if(root == NULL)
	{
		return ;
	}
	libera_Tree_rec(root->esq);
	libera_Tree_rec(root->dir);
	free(root);
}

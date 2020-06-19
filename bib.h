//Aluno: João Paulo Vaz Mendes
//Matrícula: 17/0002934
//utilizando o código de Árvore Binária de Busca desenvolvido em aula com o Professor Doutor Vinicius Ruela Pereira Borges
//Arquivo .h de protótipos, definição de tipos dos nós da árvore e estrutura e definição dos dados dentro dos nós. 

struct info
{
	float chave;
	int docente,turma,ano,periodo,discente;
	float ppm,ppd,apm,apd,aam,aad;
	char nome[200];
};

struct infoarvore {
	int n_no,n_no_esq,n_no_dir,altura;
};

typedef struct info Data;

typedef struct no Tree;

typedef struct infoarvore DadoArvore;

// Prototipo das funcoes

int string_comprimento(char str[]);

void string_clone(char fonte[], char destino[]);

int menu();

Tree ** cria_inicializa_Tree();

int ehVazia_Tree(Tree **root);

int alt_NO(Tree* no);

int alt_ABB(Tree **root);

int fatorBalanceamento_NO(Tree* no);

int maior(int x, int y);

int insere_Tree(Tree **raiz, Data elem, DadoArvore *info);

int remove_Arvore(Tree **root, Data elem);

int remove_no_Arvore_rec(Tree *root, Tree *dad, Data elem);

Tree * substituto_Arvore(Tree *no);

Tree * pai_no_mais_direita(Tree *no, Tree *dad);

int totalNO_Tree(Tree **raiz);

int totalNO_esq(Tree **raiz);

int totalNO_dir(Tree **raiz);

int altura_Tree(Tree **raiz);

void RotacaoLL(Tree **raiz);

void RotacaoRR(Tree **raiz);

void RotacaoLR(Tree **raiz);

void RotacaoRL(Tree **raiz);

void info_raiz(Tree *root);

void visit(Tree *no);

void caminha_InOrder_Tree(Tree **root);

void caminha_InOrder_Tree_rec(Tree *root);

float media_chave(Tree **root);

void media_chave_rec(Tree *root, float *s,int *t);

float pega_chave_int(Tree *raiz, int dado);

float volta_chave(Tree *no,int dado);

int busca_prof(Tree **raiz, int prof);

int busca_prof_esq(Tree **raiz, int prof);

int busca_prof_esq_n(Tree **raiz, int prof);

int busca_prof_dir(Tree **raiz, int prof);

int busca_prof_dir_n(Tree **raiz, int prof);

void  libera_Tree(Tree **root);

void libera_Tree_rec(Tree *root);

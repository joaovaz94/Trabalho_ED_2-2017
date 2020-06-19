//aluno: João Paulo Vaz Mendes
//matrícula: 17/0002934
//utilizando o código de Árvore Binária de Busca desenvolvido em aula com o Professor Doutor Vinicius Ruela Pereira Borges
#include <stdio.h>
#include <stdlib.h>
#include "bib.h"

int main()
{
	Tree **root;
	FILE *basedados;
	int i,*le_docente,*le_turma,*le_ano,*le_periodo,*le_discente,nregistros = 0,op=0,cod,codabb;
	float *le_ppm,*le_ppd,*le_apm,*le_apd,*le_aam,*le_aad;
	char c;
static	char linha[200],le_nome[2000][200];
	Data abb1,abb2,abb3;
	Tree **ABB1,**ABB2,**ABB3,*aux;
	DadoArvore dados1,dados2,dados3;

	basedados = fopen("avaliacao_docentes.csv","r+");
	if(basedados == NULL)
	{
		printf("\nERRO! Não foi possível abrir o arquivo de base de dados!");
		return 0;
	}	

	//definição do tamanho do arquivo lido	
	while((c = fgetc(basedados))!=EOF)
	{
		if(c == '\n')
		{
			nregistros++;
		}
	}
	rewind(basedados);

	//leitura da primeira linha que não possui dados
	fscanf(basedados,"%[^\n]\n",linha);

	//printf("\nPrimeira linha: %s\n",linha);

	//alocação dinamica das variáveis de armazenamento do arquivo
	le_docente = (int *) malloc(nregistros*sizeof(int));	
	le_turma = (int *) malloc(nregistros*sizeof(int));
	le_ano = (int *) malloc(nregistros*sizeof(int));
	le_periodo = (int *) malloc(nregistros*sizeof(int));
	le_discente = (int *) malloc(nregistros*sizeof(int));
	le_ppm = (float *) malloc(nregistros*sizeof(float));
	le_ppd = (float *) malloc(nregistros*sizeof(float));
	le_apm = (float *) malloc(nregistros*sizeof(float));
	le_apd = (float *) malloc(nregistros*sizeof(float));
	le_aam = (float *) malloc(nregistros*sizeof(float));
	le_aad = (float *) malloc(nregistros*sizeof(float));
	/*for(i = 0;i < nregistros ;i++)
	{
		le_nome[i] = (char *) malloc(50*sizeof(char));
	}*/

	//leitura a partir da segunda linha que possui dados
	for(i=0; i < (nregistros - 1);i++)
	{
		fscanf(basedados,"%d, %[^,], %d, %d, %d, %d, %f, %f, %f, %f, %f, %f\n",&le_docente[i],le_nome[i],&le_turma[i],&le_ano[i],&le_periodo[i],&le_discente[i],&le_ppm[i],&le_ppd[i],&le_apm[i],&le_apd[i],&le_aam[i],&le_aad[i]);

		//printf("\nLinha %d : %d,%s,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",i,le_docente[i],le_nome[i],le_turma[i],le_ano[i],le_periodo[i],le_discente[i],le_ppm[i],le_ppd[i],le_apm[i],le_apd[i],le_aam[i],le_aad[i]);

	}

//	printf("\nSegunda linha: %d,%s,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",le_docente[0],le_nome[0],le_turma[0],le_ano[0],le_periodo[0],le_discente[0],le_ppm[0],le_ppd[0],le_apm[0],le_apd[0],le_aam[0],le_aad[0]);

//	printf("\nÚltima linha: %d,%s,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",le_docente[i-1],le_nome[i-1],le_turma[i-1],le_ano[i-1],le_periodo[i-1],le_discente[i-1],le_ppm[i-1],le_ppd[i-1],le_apm[i-1],le_apd[i-1],le_aam[i-1],le_aad[i-1]);
	
	//Completando arvore 1 chave: postura profissional media
	ABB1 = cria_inicializa_Tree();	
	//zerando dados de informação da árvore
	dados1.n_no = 0;
	dados1.n_no_esq = 0;
	dados1.n_no_dir = 0;
	dados1.altura = 0;
	for(i = 0; i < (nregistros - 1);i++)
	{
		//inserindo dados na estrutura
		abb1.chave = le_ppm[i]; 
		abb1.docente = le_docente[i];
		string_clone(le_nome[i],abb1.nome);
		abb1.turma = le_turma[i];
		abb1.ano = le_ano[i];
		abb1.periodo = le_periodo[i];
		abb1.discente = le_discente[i];
		abb1.ppm = le_ppm[i];
		abb1.ppd = le_ppd[i];
		abb1.apm = le_apm[i];
		abb1.apd = le_apd[i];
		abb1.aam = le_aam[i];
		abb1.aad = le_aad[i];
		//inserção de elemento na árvore
		//printf("ok %d",i);
		insere_Tree(ABB1,abb1,&dados1);
	}
	printf("\nÁrvore com nota de postura profissional media como chave criada!\n");
	printf("\nnúmero de nós da abb1: %d", /*dados1.n_n*/totalNO_Tree(ABB1));
	printf("\nnúmero de nós esquerdo da abb1: %d",totalNO_esq(ABB1));
	printf("\nnúmero de nós direito da abb1: %d",totalNO_dir(ABB1));
	printf("\naltura da abb1: %d",altura_Tree(ABB1));

	//caminha_InOrder_Tree(ABB1);

	//Completando arvore 2 chave: atuação profissional media
	ABB2 = cria_inicializa_Tree();	
	//zerando dados de informação da árvore
	dados2.n_no = 0;
	dados2.n_no_esq = 0;
	dados2.n_no_dir = 0;
	dados2.altura = 0;
	for(i = 0; i < (nregistros - 1);i++)
	{
		//inserindo dados na estrutura
		abb2.chave = le_apm[i]; 
		abb2.docente = le_docente[i];
		string_clone(le_nome[i],abb2.nome);
		abb2.turma = le_turma[i];
		abb2.ano = le_ano[i];
		abb2.periodo = le_periodo[i];
		abb2.discente = le_discente[i];
		abb2.ppm = le_ppm[i];
		abb2.ppd = le_ppd[i];
		abb2.apm = le_apm[i];
		abb2.apd = le_apd[i];
		abb2.aam = le_aam[i];
		abb2.aad = le_aad[i];
		//inserção de elemento na árvore
		insere_Tree(ABB2,abb2,&dados2);
	}
	printf("\n\n\nÁrvore com nota de atuação profissional media como chave criada!\n");
	printf("\nnúmero de nós da abb2: %d",totalNO_Tree(ABB2));
	printf("\nnúmero de nós esquerdo da abb2: %d",totalNO_esq(ABB2));
	printf("\nnúmero de nós direito da abb2: %d",totalNO_dir(ABB2));
	printf("\naltura da abb2: %d",altura_Tree(ABB2));
	
	//completando arvore 3 chave: autoavaliação aluno media
	ABB3 = cria_inicializa_Tree();	
	//zerando dados de informação da árvore
	dados3.n_no = 0;
	dados3.n_no_esq = 0;
	dados3.n_no_dir = 0;
	dados3.altura = 0;
	for(i = 0; i < (nregistros - 1);i++)
	{
		//inserindo dados na estrutura
		abb3.chave = le_aam[i]; 
		abb3.docente = le_docente[i];
		string_clone(le_nome[i],abb3.nome);
		abb3.turma = le_turma[i];
		abb3.ano = le_ano[i];
		abb3.periodo = le_periodo[i];
		abb3.discente = le_discente[i];
		abb3.ppm = le_ppm[i];
		abb3.ppd = le_ppd[i];
		abb3.apm = le_apm[i];
		abb3.apd = le_apd[i];
		abb3.aam = le_aam[i];
		abb3.aad = le_aad[i];
		//inserção de elemento na árvore
		insere_Tree(ABB3,abb3,&dados3);
	}
	printf("\n\n\nÁrvore com nota de autoavaliação do aluno media como chave criada!\n");
	printf("\nnúmero de nós da abb3: %d",totalNO_Tree(ABB3));
	printf("\nnúmero de nós esquerdo da abb3: %d",totalNO_esq(ABB3));
	printf("\nnúmero de nós direito da abb3: %d",totalNO_dir(ABB3));
	printf("\naltura da abb2: %d",altura_Tree(ABB3));
	
	//caminha_InOrder_Tree(ABB1);

//	printf("\nchave: %d\ndocente: %s\nturma: %d\nano: %d\nperíodo: %d\nnúmero de discentes: %d\nppm: %f\nppd: %f\napm: %f\napd: %f\naam: %f\naad: %f\n",(*ABB1)->data.chave);
	//Menu de acesso das operações
	do
    	{
        	op = menu();
        	if(op == 1)
        	{
			printf("\n\nInformações do nó raiz da árvore 1 - chave: postura profissional media\n\n"); 
			info_raiz(*ABB1);
			printf("\n\nInformações do nó raiz da árvore 2 - chave: atuação profissional media\n\n");
			info_raiz(*ABB2);
			printf("\n\nInformações do nó raiz da árvore 3 - chave: autoavaliação aluno media\n\n");
			info_raiz(*ABB3);
        	}
        	if(op == 2)
        	{
			//printf("ok");
			//printf("\n\nMédia das chaves da sub-árvore esquerda da árvore 1: %f \n\n",media_chave(ABB1));
			//printf("\n\nMédia das chaves da sub-árvore direita de árvore 2: %f \n\n",media_chave(((ABB1)->dir)));
			printf("\n\nOperação vazia\n\n");
        	}
        	if(op == 3)
        	{
			printf("\nDigite o código do professor: ");
			scanf("%d",&cod);
			printf("\n\nÁrvore 1\n\n");
			busca_prof(ABB1,cod);
			printf("\n\nÁrvore 2\n\n");
			busca_prof(ABB2,cod);
			printf("\n\nÁrvore 3\n\n");
			busca_prof(ABB3,cod);
			//printf("\n\nOperação vazia\n\n");
        	}
        	if(op == 4)
        	{
			printf("\nDigite o código do professor: ");
			scanf("%d",&cod);	
			printf("\nEscolha uma árvore para busca (1, 2 ou 3): ");
			scanf("%d",&codabb);
			if(codabb == 1)
			{
				busca_prof_esq(ABB1,cod);
			}
			else
			{
				if(codabb == 2)
				{
					busca_prof_esq(ABB2,cod);
				}
				else
				{
					if(codabb == 3)
					{
						busca_prof_esq(ABB3,cod);
					}
				}
			}
			if(codabb < 0 || codabb > 3)
			{
				printf("\nCódigo para árvore inexistente! repita o procedimento\n");
			}
			//printf("\n\nOperação vazia\n\n");
        	}
		if(op == 5)
        	{
			printf("\nDigite o código do professor: ");
			scanf("%d",&cod);	
			printf("\nEscolha uma árvore para busca (1, 2 ou 3): ");
			scanf("%d",&codabb);
			if(codabb == 1)
			{
				busca_prof_dir(ABB1,cod);
			}
			else
			{
				if(codabb == 2)
				{
					busca_prof_dir(ABB2,cod);
				}
				else
				{
					if(codabb == 3)
					{
						busca_prof_dir(ABB3,cod);
					}
				}
			}
			if(codabb < 0 || codabb > 3)
			{
				printf("\nCódigo para árvore inexistente! repita o procedimento\n");
			}
			//printf("\n\nOperação vazia\n\n");
        	}
		if(op == 6)
        	{
			printf("\nDigite o código do professor: ");
			scanf("%d",&cod);	
			printf("\nEscolha uma árvore para busca (1, 2 ou 3): ");
			scanf("%d",&codabb);
			if(codabb == 1)
			{
				printf("\n\nO docente aparece %d vezes na sub-árvore direita \n\n",busca_prof_dir_n(ABB1,cod));
			}
			else
			{
				if(codabb == 2)
				{
					printf("\n\nO docente aparece %d vezes na sub-árvore direita \n\n",busca_prof_dir_n(ABB2,cod));
				}
				else
				{
					if(codabb == 3)
					{
						printf("\n\nO docente aparece %d vezes na sub-árvore direita \n\n",busca_prof_dir_n(ABB3,cod));
					}
				}
			}
			if(codabb < 0 || codabb > 3)
			{
				printf("\nCódigo para árvore inexistente! repita o procedimento\n");
			}
			//printf("\n\nOperação vazia\n\n");
        	}
		if(op == 7)
        	{
			printf("\nDigite o código do professor: ");
			scanf("%d",&cod);	
			printf("\nEscolha uma árvore para busca (1, 2 ou 3): ");
			scanf("%d",&codabb);
			if(codabb == 1)
			{
				printf("\n\nO docente aparece %d vezes na sub-árvore esquerda \n\n",busca_prof_esq_n(ABB1,cod));
			}
			else
			{
				if(codabb == 2)
				{
					printf("\n\nO docente aparece %d vezes na sub-árvore esquerda \n\n",busca_prof_esq_n(ABB2,cod));
				}
				else
				{
					if(codabb == 3)
					{
						printf("\n\nO docente aparece %d vezes na sub-árvore esquerda \n\n",busca_prof_esq_n(ABB3,cod));
					}
				}
			}
			if(codabb < 0 || codabb > 3)
			{
				printf("\nCódigo para árvore inexistente! repita o procedimento\n");
			}
			//printf("\n\nOperação vazia\n\n");
        	}
    	}while(op);
    
	printf("Execução encerrada\n");
	

	//liberação de memória e fechamento de arquivo
	free(le_docente);
	free(le_turma);
	free(le_ano);
	free(le_periodo);
	free(le_discente);
	free(le_ppm);
	free(le_ppd);
	free(le_apm);
	free(le_apd);
	free(le_aam);
	free(le_aad);
	libera_Tree(ABB1);
	libera_Tree(ABB2);
	libera_Tree(ABB3);
	free(ABB1);
	free(ABB2);
	free(ABB3);
	/*for(i = 0;i < nregistros;i++)
	{
		free(le_nome[i]);
	}*/
	fclose(basedados);
	return 0;
}

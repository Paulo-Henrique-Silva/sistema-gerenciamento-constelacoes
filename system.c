#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/*
    Nº da constelação - int
    Abreviação - char[4]
    Apelido - Char[30]
    Nome em Latim - char[30]
    Quantidade de estrelas - int
    Distancia da terra - float (anos luz)
*/

struct tipo_aluno
{
    int codigo;
    char nome[80];
    float np1, nt1, np2, nt2;
    float media;
};

struct tipo_lista_encadeada
{
    struct tipo_aluno aluno;
    struct tipo_lista_encadeada *prox;
};

typedef struct tipo_lista_encadeada LISTA;
typedef struct tipo_aluno ACADEMICO;

LISTA *primeiro=NULL;
LISTA *ultimo;
int n;

char menu ();
void inicia_lista ();
void cadastra (struct tipo_aluno *lista);
void mostra (struct tipo_aluno *lista);
void salva (struct tipo_aluno *lista);
void carrega (struct tipo_aluno *lista);
void troca(struct tipo_aluno *F1,struct tipo_aluno *F2);
void imprime_lista_ordenada( struct tipo_aluno *lista, int numero);
void imprime_alunos(struct tipo_aluno *lista);
void cria_lista(struct tipo_aluno *i, struct tipo_aluno **inicio, struct tipo_aluno **fim);
void insere(int cod);
void apaga(int cod);
void altera(int cod);
void ordena(); //declaracao da funcao ordena!


int main(void)
{
    char escolha;
    struct tipo_aluno *lista_alunos;
    LISTA *novo;
    int codigo_apaga,codigo_insere,codigo_altera;

    primeiro = NULL;
    ultimo = NULL;
    novo = NULL;

    inicia_lista();
    for ( ;; )
    {
        escolha = menu();

        switch (escolha)
        {
            case 'c':
            case 'C':
            {
                cadastra(lista_alunos);
            }
            break;

            case 's':
            case 'S': { salva(lista_alunos); } break;
            case 'a':
            case 'A': { carrega(lista_alunos); } break;
            case 'l':
            case 'L': { imprime_alunos(lista_alunos); } break;
            case 'x':
            case 'X':
            {
                printf("\nCodigo do aluno que se quer apagar: ");
                scanf("%d",&codigo_apaga);
                apaga(codigo_apaga);
            }
            break;
            case 'i':
            case 'I': {
            printf("\nCodigo do aluno que se quer inserir: ");
            scanf("%d",&codigo_insere);
            insere(codigo_insere);
            } break;
            case 't':
            case 'T':{
            printf("\nCOdigo do aluno cujos dados vao ser alterados: ");
            scanf("%d",&codigo_altera);
            altera(codigo_altera);

            } break;
            case 'e':
            case 'E': { exit (0 ); } break;
            default : { printf ( "Opcao invalida. \n" ); }
            }
        printf ( "\n \n \n" );

    }

    getch();
}

char menu()
{
    char opcao;

    printf ("\n \n \n");
    printf ( " (C)adastrar. \n" );
    printf ( " C(A)arregar. \n" );
    printf ( " (S)alvar. \n" );
    printf ( " (L)istar Alunos Cadastrados. \n" );
    printf ( " E(X)cluir um aluno. \n" );
    printf ( " (I)nserir um aluno. \n" );
    printf ( " Al(T)era os dados de um aluno. \n" );
    printf ( " (E)xit \n" );

    fflush(stdin);
    scanf ( "%c", &opcao );

    return opcao;
}

void inicia_lista()
{
    primeiro = NULL;
    ultimo = NULL;
}

void cadastra (struct tipo_aluno *lista)
{
    int i;
    LISTA *aux;
    LISTA *novo;

    printf ("\n \n \n");
    novo=(LISTA *)malloc(1*sizeof(LISTA));
    novo->prox = NULL;

    printf ( "Nome: \n" );
    fflush (stdin);
    fgets(novo -> aluno.nome, 1024, stdin);

    printf( " Codigo: \n" );
    fflush (stdin);
    scanf("%d",&novo -> aluno.codigo);

    printf ( "Notas: \n" );
    fflush(stdin);

    printf ( "Nota Teorica 1: \n" );
    fflush(stdin);
    scanf("%f",&novo -> aluno.nt1);

    printf ( "Nota Pratica 1: \n" );
    fflush(stdin);
    scanf("%f",&novo -> aluno.np1);

    printf ( "Nota Teorica 2: \n" );
    fflush(stdin);
    scanf("%f", &novo -> aluno.nt2);

    printf ( "Nota Pratica 2: \n" );
    fflush(stdin);
    scanf("%f", &novo -> aluno.np2);

    novo -> aluno.media=((novo -> aluno.nt1*0.7+novo -> aluno.np1*0.3)+(novo -> aluno.nt2*0.7+novo -> aluno.np2*0.3))/2.0;

    if ( NULL == primeiro )
    {
        primeiro = novo;
        ultimo = primeiro;
    }
    else
    {
        ultimo->prox = novo;
        ultimo = novo;
    }

    getchar();
}


void salva (struct tipo_aluno *lista)
{
    FILE *fp;
    LISTA *aux;
    int i, result;

    printf ("\n \n \n");
    fp = fopen("cad_alunos.dat","wb");

    if ( fp == NULL )
    {
        printf ( "O arquivo nao pode ser aberto. \n" );
        return;
    }

    aux = primeiro;

    while(aux!=NULL)
    {
        fwrite(aux,sizeof(ACADEMICO),1,fp);
        aux=aux -> prox;
    }

    fclose (fp);
}

void carrega (struct tipo_aluno *lista)
{
    FILE *fp;
    LISTA *aux,*novo;
    inicia_lista();

    fp = fopen("cad_alunos.dat","rb");

    while(!feof(fp))
    {
        novo = (LISTA *)malloc(1 * sizeof(LISTA));
        fread(&novo -> aluno, sizeof(ACADEMICO), 1, fp);
        novo -> prox = NULL;

        if(primeiro == NULL)
        {
            primeiro = novo;
            ultimo = primeiro;
        }
        else
        {
            ultimo -> prox = novo;
            ultimo = novo;
        }

        novo -> aluno.media=((novo -> aluno.nt1*0.7+novo -> aluno.np1*0.3)+(novo -> aluno.nt2*0.7+novo -> aluno.np2*0.3))/2.0;
    }

    fclose(fp);

    //getch();
}

void imprime_alunos(struct tipo_aluno *lista)
{
    printf("\n\n\n");

    LISTA *aux;
    aux = primeiro;
    n=0;
    while(aux!=NULL)
    {
        n++;
        aux=aux->prox;
    }
    //ordena();

    //essa é a chamada da função ordena

    if(primeiro -> prox == NULL)
    {
    printf("codigo: %d\n" , aux -> aluno.codigo);
    printf("nome: %s \n" , aux -> aluno.nome);
    printf("media: %f\n\n\n" , aux -> aluno.media);
    }

    if(primeiro -> prox != NULL)
    {
        while(aux -> prox !=NULL)
        {
        printf("codigo: %d\n" , aux -> aluno.codigo);
        printf("nome: %s \n" , aux -> aluno.nome);
        printf("media: %f\n\n\n" , aux -> aluno.media);
        aux = aux -> prox;

        }
    }
}

void apaga(int cod)
{
    LISTA *aux=primeiro;
    LISTA *aux2;

    while(aux!= NULL && aux->aluno.codigo != cod )
    {
        aux2=aux;
        aux=aux->prox;
    }
    if(aux != NULL)
    {
        aux2->prox = aux->prox;
        free(aux);
    }

    //getch();
}


void insere(int cod)
{
    LISTA *aux=primeiro;
    LISTA *aux2;
    LISTA *novo;

    novo = (LISTA *)malloc(1*sizeof(LISTA));
    novo->aluno.codigo=cod;

    printf("Digite o nome a ser inserido:");
    fflush(stdin);
    fgets(novo -> aluno.nome, 1024, stdin);
    getchar();

    printf ( "Notas: \n" );fflush(stdin);
    printf ( "Nota Teorica 1: \n" );fflush(stdin);
    scanf("%f",&novo -> aluno.nt1);
    printf ( "Nota Pratica 1: \n" );fflush(stdin);
    scanf("%f",&novo -> aluno.np1);
    printf ( "Nota Teorica 2: \n" );fflush(stdin);
    scanf("%f", &novo -> aluno.nt2);
    printf ( "Nota Pratica 2: \n" );fflush(stdin);
    scanf("%f", &novo -> aluno.np2);
    novo -> aluno.media=((novo -> aluno.nt1*0.7+novo -> aluno.np1*0.3)+(novo -> aluno.nt2*0.7+novo -> aluno.np2*0.3))/2.0;
    getchar();

    if( cod < primeiro->aluno.codigo )
    {
        aux2=primeiro;
        aux=aux->prox;
        aux2->prox=novo;
        aux2->prox->prox = aux;
    }
    else
    {
        while(aux!=NULL && aux->aluno.codigo < cod)
        {

        aux2=aux;
        aux=aux->prox;

        }
        aux2->prox = novo;
        aux2->prox->prox = aux;
    }

    //getch();
}


void altera(int cod)
{
    LISTA *aux;
    LISTA *aux2;
    LISTA *novo;
    char nome_novo[80];
    float n_nt1,n_nt2,n_np1,n_np2;

    aux = primeiro;
    while(aux !=NULL)
    {
        if(aux -> aluno.codigo == cod)
        {
            printf("\nDigite o novo nome: ");
            fflush(stdin);
            fgets(nome_novo, 1024, stdin);
            getchar();
            strcpy(aux->aluno.nome,nome_novo);

            printf("\nDigite a nova Nota Teorica 1: ");fflush(stdin);
            scanf("%f",&n_nt1);
            aux->aluno.nt1=n_nt1;
            printf("\nDigite a nova Nota Pratica 1: ");fflush(stdin);
            scanf("%f",&n_np1);
            aux->aluno.np1=n_np1;
            printf("\nDigite a nova Nota Teorica 2: ");fflush(stdin);
            scanf("%f",&n_nt2);
            aux->aluno.nt2=n_nt2;
            printf("\nDigite a nova Nota Pratica 2: ");fflush(stdin);
            scanf("%f",&n_np2);
            aux->aluno.np2=n_np2;
        }

        aux = aux->prox;
    }

    //getch();
}

void ordena() //essa é a função ordena
{
    LISTA *aux,*aux2;

    aux = primeiro;
    for(aux=primeiro;aux!=NULL;aux=aux->prox)
    {
        aux2=(LISTA *)malloc(1*sizeof(LISTA));

        //if(strcmp(aux->aluno.nome,aux->prox->aluno.nome)>0)

        if(aux -> aluno.codigo > aux -> prox -> aluno.codigo)
        {
        aux2->aluno = aux->aluno;
        aux->aluno = aux->prox->aluno;
        aux->prox->aluno = aux2->aluno;
        }

        free(aux2);
    }

    getch();
}


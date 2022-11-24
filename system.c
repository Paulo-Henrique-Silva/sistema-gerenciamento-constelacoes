#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct constelacao
{
    int codigo;
    char nomeLatim[30];
    char apelido[30];
    char abreviacao[4];
    int qtdEstrelas;
    float distTerra;
};

struct tipo_lista_encadeada
{
    struct constelacao constelacao;
    struct tipo_lista_encadeada *prox;
};

typedef struct tipo_lista_encadeada LISTA;
typedef struct constelacao CONSTELACAO;

LISTA *primeiro;

int menu ();
void inicia_lista();

void imprime(struct tipo_lista_encadeada *lista_constelacoes);
void insere(struct tipo_lista_encadeada *lista_constelacoes);
void apaga(struct tipo_lista_encadeada *lista_constelacoes);
void altera(struct tipo_lista_encadeada *lista_constelacoes);
void ordena(struct tipo_lista_encadeada *lista_constelacoes);
void salva (struct tipo_lista_encadeada *lista_constelacoes);
void carrega(struct tipo_lista_encadeada *lista_constelacoes);

int main(void)
{
    int escolha;
    struct tipo_lista_encadeada *lista_constelacoes = (struct tipo_lista_encadeada*) malloc(sizeof(struct tipo_lista_encadeada*));;

    primeiro = (LISTA *) malloc(sizeof(LISTA));
    primeiro->prox = NULL;
    //indica que a lista está vazia.

    for ( ;; )
    {
        escolha = menu();

        switch (escolha)
        {
            case 1:
                insere(lista_constelacoes);
                break;

            case 2:
                imprime(lista_constelacoes);
                break;

            case 3:
                apaga(lista_constelacoes);
                break;

            case 4:
                altera(lista_constelacoes);
                break;

            case 5:
                ordena(lista_constelacoes);
                break;

            case 6:
                salva(lista_constelacoes);
                break;

            case 7:
                carrega(lista_constelacoes);
                break;

            case 8:
                printf("\n");
                exit(0);
                break;

            default:
                printf( "Opcao invalida. \n" );
                break;
        }
    }

    getch();
}

int menu()
{
    system("cls");

    int opcao;

    printf("\t\t\t\tSISTEMA DE GERENCIAMENTO DE CONSTELACOES\n");
    printf("\t\t\t---------------------------------------------------------\n\n\n");

    printf("[1] - Inserir constelacao\n");
    printf("[2] - Ver constelacoes cadastradas\n");
    printf("[3] - Excluir constelacoes\n");
    printf("[4] - Atualizar constelacoes\n");
    printf("[5] - Ordernar constelacoes\n");
    printf("[6] - Salvar constelacoes\n");
    printf("[7] - Carregar constelacoes por arquivo\n");
    printf("[8] - Sair\n");

    printf("\n\nDigite a operacao: ");
    scanf("%d", &opcao);

    return opcao;
}

void insere(struct tipo_lista_encadeada *lista_constelacoes)
{
    system("cls");
    printf("\t\t\t\t\tINSERIR CONSTELACAO\n");
    printf("\t\t\t----------------------------------------------------\n\n\n");

    LISTA *novo = (LISTA *) malloc(sizeof(LISTA));
    novo->prox = primeiro->prox;

    printf("Digite o codigo de identificacao: ");
    scanf("%d", &novo -> constelacao.codigo);

    do
    {
        printf("Digite o nome em latim: ");
        fflush(stdin);
        scanf("%s", &novo -> constelacao.nomeLatim);
    }
    while(strlen(novo -> constelacao.nomeLatim) > 29);

    do
    {
        printf("Digite o apelido: ");
        fflush(stdin);
        scanf("%s", &novo -> constelacao.apelido);
    }
    while(strlen(novo -> constelacao.apelido) > 29);

    do
    {
        printf("Digite a abreviacao: ");
        fflush(stdin);
        scanf("%s", &novo -> constelacao.abreviacao);
    }
    while(strlen(novo -> constelacao.abreviacao) > 3);

    printf("Digite a quantidade de estrelas: ");
    scanf("%d", &novo -> constelacao.qtdEstrelas);

    printf("Digite a distancia em anos luz: ");
    scanf("%f", &novo -> constelacao.distTerra);

    primeiro->prox = novo;

    printf("\nConstelacao inserida com sucesso!\n");
    getch();
}

void salva(struct tipo_lista_encadeada *lista_constelacoes)
{
    FILE *fp;
    LISTA *atual;

    fp = fopen("constelacoes.txt", "w");

    if (fp == NULL )
    {
        printf("O arquivo nao pode ser aberto.\n");
        return;
    }

    atual = primeiro->prox;

    while(atual != NULL)
    {
        fprintf(fp, "%d %s %s %s %d %.2f\n", atual->constelacao.codigo, atual->constelacao.nomeLatim, atual->constelacao.apelido, atual->constelacao.abreviacao, atual->constelacao.qtdEstrelas, atual->constelacao.distTerra);
        atual = atual -> prox;
    }

    fclose (fp);

    printf("Lista salva!\n");
    getch();
}

void carrega (struct tipo_lista_encadeada *lista_constelacoes)
{
    /*
    FILE *fp;
    LISTA *aux,*novo;
    inicia_lista();

    fp = fopen("cad_alunos.txt","r");

    while(!feof(fp))
    {
        novo = (LISTA *)malloc(1 * sizeof(LISTA));
        fread(&novo -> aluno, sizeof(CONSTELACAO), 1, fp);
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
    */

    getch();
}

void imprime(struct tipo_lista_encadeada *lista_constelacoes)
{
    system("cls");
    printf("\t\t\t\t\t\tCONSTELACOES\n");
    printf("\t\t\t---------------------------------------------------------\n\n\n");

    LISTA *atual = primeiro->prox;

    // Percorre todos os nós da lista, imprimindo o conteúdo de cada um.
    while(atual != NULL)
    {
        printf("%s \n", atual->constelacao.apelido);
        atual = atual->prox;
    }

    getch();
}

void apaga(struct tipo_lista_encadeada *lista_constelacoes)
{
    /*
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

    getch();
    */
}

void altera(struct tipo_lista_encadeada *lista_constelacoes)
{
    /*
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

    getch();
    */
}

void ordena(struct tipo_lista_encadeada *lista_constelacoes)
{
    /*
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
    */
}


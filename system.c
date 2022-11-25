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

LISTA *cabeca; //indica a "cabeça" da lista, ou seja, o nó vazio que aponta para o primeiro elemento.

int menu ();
void inicia_lista();

void imprime();
void insere();
void apaga();
void altera();
void ordena(struct tipo_lista_encadeada *primeiroElem);
void salva ();
void carrega();

int main(void)
{
    int escolha;
    struct tipo_lista_encadeada *lista_constelacoes = (struct tipo_lista_encadeada*) malloc(sizeof(struct tipo_lista_encadeada*));;

    cabeca = (LISTA *) malloc(sizeof(LISTA));
    cabeca->prox = NULL;
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
                ordena(cabeca->prox);
                break;

            case 6:
                salva(lista_constelacoes);
                break;

            case 7:
                carrega(lista_constelacoes);
                break;

            case 8:
                exit(0);
                break;

            default:
                printf("Opcao invalida!");
                getch();
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
    printf("[2] - Ver constelacoes\n");
    printf("[3] - Excluir constelacoes\n");
    printf("[4] - Alterar constelacoes\n");
    printf("[5] - Ordernar constelacoes por codigo\n");
    printf("[6] - Salvar constelacoes em arquivo\n");
    printf("[7] - Carregar constelacoes por arquivo\n");
    printf("[8] - Sair\n");

    printf("\n\nDigite a operacao: ");
    scanf("%d", &opcao);

    return opcao;
}

void insere()
{
    system("cls");
    printf("\t\t\t\t\tINSERIR CONSTELACAO\n");
    printf("\t\t\t----------------------------------------------------\n\n\n");

    LISTA *novo = (LISTA *) malloc(sizeof(LISTA));
    novo->prox = cabeca->prox;

    char buffer[1024];

    int repetiu;

    do
    {
        repetiu = 0;

        printf("Digite o codigo de identificacao: ");
        scanf("%d", &novo -> constelacao.codigo);

        LISTA *atual = cabeca->prox;

        while(atual != NULL) //itera para descobrir se repetiu o codigo
        {
            if (atual->constelacao.codigo == novo->constelacao.codigo)
            {
                repetiu = 1;
                break;
            }

            atual = atual -> prox;
        }
    }
    while (novo -> constelacao.codigo <= 0 || repetiu);

    do
    {
        printf("Digite o nome em latim: ");
        fflush(stdin);
        scanf("%s", &buffer);
    }
    while(strlen(buffer) > 29);

    strcpy(novo -> constelacao.nomeLatim, buffer);

    do
    {
        printf("Digite o apelido: ");
        fflush(stdin);
        scanf("%s", &buffer);
    }
    while(strlen(buffer) > 29);

    strcpy(novo -> constelacao.apelido, buffer);

    do
    {
        printf("Digite a abreviacao: ");
        fflush(stdin);
        scanf("%s", &buffer);
    }
    while(strlen(buffer) > 3);

    strcpy(novo -> constelacao.abreviacao, buffer);

    printf("Digite a quantidade de estrelas: ");
    scanf("%d", &novo -> constelacao.qtdEstrelas);

    printf("Digite a distancia em anos luz: ");
    scanf("%f", &novo -> constelacao.distTerra);

    cabeca->prox = novo;

    printf("\nConstelacao inserida com sucesso!\n");
    getch();
}

void salva()
{
    FILE *fp;
    LISTA *atual;

    fp = fopen("constelacoes.txt", "w");

    if (fp == NULL )
    {
        printf("O arquivo nao pode ser aberto.\n");
        return;
    }

    atual = cabeca->prox;

    while(atual != NULL)
    {
        fprintf(fp, "%d %s %s %s %d %.2f\n", atual->constelacao.codigo, atual->constelacao.nomeLatim, atual->constelacao.apelido, atual->constelacao.abreviacao, atual->constelacao.qtdEstrelas, atual->constelacao.distTerra);
        atual = atual -> prox;
    }

    fclose (fp);

    printf("Lista salva em arquivo!\n");
    getch();
}

void carrega ()
{
    FILE *fp;
    LISTA *aux, *novo;

    fp = fopen("constelacoes.txt", "r");

    if (fp != NULL) //se o arquivo existe
    {
        LISTA *atual = cabeca->prox;

        // Percorre todos os nós da lista, liberando seus conteudos
        while(atual != NULL)
        {
            LISTA *temp = atual;
            free(atual);
            atual = temp->prox;
        }
    }
    else
    {
        printf("Nao foi possivel encontrar o arquivo!\n");
        getch();
        return;
    }

    while(!feof(fp)) //enquanto nao chega ao final do arquivo
    {
        novo = (LISTA *) malloc(sizeof(LISTA));
        novo->prox = cabeca->prox;

        fscanf(fp, "%d %s %s %s %d %f\n", &novo->constelacao.codigo, &novo->constelacao.nomeLatim, &novo->constelacao.apelido, &novo->constelacao.abreviacao, &novo->constelacao.qtdEstrelas, &novo->constelacao.distTerra);

        cabeca->prox = novo;
    }

    fclose(fp);

    printf("Lista carregada!\n");
    getch();
}

void imprime()
{
    system("cls");
    printf("\t\t\t\t\t\tCONSTELACOES\n");
    printf("\t\t\t---------------------------------------------------------\n\n");

    LISTA *atual = cabeca->prox;
    int qtdElementos = 0;

    // Percorre todos os nós da lista, imprimindo o conteúdo de cada um.
    while(atual != NULL)
    {
        printf("\tCODIGO: %d - NOME: %s - APELIDO: %s - ABREVIACAO: %s - QUANTIDADE DE ESTRELAS: %d - DISTANCIA DA TERRA: %.2f\n\n", atual->constelacao.codigo, atual->constelacao.nomeLatim, atual->constelacao.apelido, atual->constelacao.abreviacao, atual->constelacao.qtdEstrelas, atual->constelacao.distTerra);

        atual = atual->prox;
        qtdElementos++;
    }

    if (qtdElementos == 0)
        printf("A lista esta vazia! :/");

    getch();
}

void apaga()
{
    if (cabeca->prox == NULL)
    {
        printf("Lista vazia!");
        getch();
        return;
    }

    system("cls");
    printf("\t\t\t\t\tEXCLUIR CONSTELACAO\n");
    printf("\t\t\t----------------------------------------------------\n\n");

    int cod = 0;

    do
    {
        printf("Digite o codigo de uma constelacao para exclui-la: ");
        scanf("%d", &cod);
    }
    while (cod <= 0);

    LISTA *atual = cabeca->prox, *anterior = cabeca;

    //itera por toda a lista e troca o apontamento do elemento anterior ao que será excluido.
    while(atual != NULL)
    {
        if (atual->constelacao.codigo == cod)
        {
            anterior->prox = atual->prox;
            free(atual);
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf(atual == NULL ? "Constelacao nao encontrada!" : "Constelacao excluida!");
    getch();
}

void altera()
{
    if (cabeca->prox == NULL)
    {
        printf("Lista vazia!");
        getch();
        return;
    }

    system("cls");
    printf("\t\t\t\t\tALTERAR CONSTELACAO\n");
    printf("\t\t\t----------------------------------------------------\n\n");

    int cod = 0;

    do
    {
        printf("Digite o codigo de uma constelacao para altera-la: ");
        scanf("%d", &cod);
    }
    while (cod <= 0);

    LISTA *atual = cabeca->prox, *anterior = cabeca;

    while(atual != NULL)
    {
        if (atual->constelacao.codigo == cod)
        {
            char buffer[1024];

            do
            {
                printf("Digite o novo nome em latim: ");
                fflush(stdin);
                scanf("%s", &buffer);
            }
            while(strlen(buffer) > 29);

            strcpy(atual -> constelacao.nomeLatim, buffer);

            do
            {
                printf("Digite o novo apelido: ");
                fflush(stdin);
                scanf("%s", &buffer);
            }
            while(strlen(buffer) > 29);

            strcpy(atual -> constelacao.apelido, buffer);

            do
            {
                printf("Digite a nova abreviacao: ");
                fflush(stdin);
                scanf("%s", &buffer);
            }
            while(strlen(buffer) > 3);

            strcpy(atual -> constelacao.abreviacao, buffer);

            printf("Digite a nova quantidade de estrelas: ");
            scanf("%d", &atual -> constelacao.qtdEstrelas);

            printf("Digite a nova distancia em anos luz: ");
            scanf("%f", &atual -> constelacao.distTerra);

            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf(atual == NULL ? "Constelacao nao encontrada!" : "Constelacao alterada!");
    getch();
}

//ordena a lista por bubble sort
void ordena(struct tipo_lista_encadeada *primeiroElem)
{
    int foiTrocado;
    LISTA *atual;
    LISTA *anterior = NULL;

    /* se não estiver vazia*/
    if (primeiroElem == NULL)
    {
        printf("Lista vazia!");
        return;
    }

    do
    {
        foiTrocado = 0;
        atual = primeiroElem;

        while (atual->prox != anterior)
        {
            if (atual->constelacao.codigo > atual->prox->constelacao.codigo)
            {
                troca(atual, atual->prox);
                foiTrocado = 1;
            }

            atual = atual->prox;
        }

        anterior = atual;
    }
    while (foiTrocado);

    printf("Lista ordenada!");
    getch();
}

void troca(LISTA *a, LISTA *b)
{
    struct constelacao temp = a->constelacao;
    a->constelacao = b->constelacao;
    b->constelacao = temp;
}

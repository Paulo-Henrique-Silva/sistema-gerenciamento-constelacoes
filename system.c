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
                ordena(cabeca);
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
    printf("[4] - Atualizar constelacoes\n");
    printf("[5] - Ordernar constelacoes por codigo\n");
    printf("[6] - Salvar constelacoes\n");
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

    do
    {
        printf("Digite o codigo de identificacao: ");
        scanf("%d", &novo -> constelacao.codigo);
    }
    while (novo -> constelacao.codigo <= 0);

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
        cabeca = (LISTA *) malloc(sizeof(LISTA));
        cabeca->prox = NULL;
    }
    else
    {
        printf("Nao foi possivel encontrar o arquivo!\n");
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

    printf(atual == NULL ? "Constelacao nao encontrada!" :"Constelacao excluida!");
    getch();
}

void altera()
{
    /*
    LISTA *aux;
    LISTA *aux2;
    LISTA *novo;
    char nome_novo[80];
    float n_nt1,n_nt2,n_np1,n_np2;

    aux = cabeca;
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

void ordena(struct tipo_lista_encadeada *primeiroElem)
{
    if (primeiroElem->prox != NULL && primeiroElem->prox->prox != NULL)
    {
        LISTA *atual, *maior, *anterior;

        atual = primeiroElem->prox;
        maior = primeiroElem->prox;
        anterior = NULL;

        while(atual != NULL)
        {
            if (atual->constelacao.codigo > maior->constelacao.codigo)
            {
                /*Troca o maior valor registrado*/
                maior = atual;
                anterior->prox = atual->prox;

                /*Define o maior como primeiro elemento*/
                maior->prox = primeiroElem->prox;
                primeiroElem->prox = maior;

                //atual = maior;
            }

            anterior = atual;
            atual = atual->prox;
        }

        ordena(maior->prox); //chama a função novamente para ordenar o resto da lista.
    }
    else
    {
        printf("Lista ordenada!");
        getch();
    }
}

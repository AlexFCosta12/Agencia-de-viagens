#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas.h"


ListV cria_lista_viagens()
{
    ListV aux;
    aux = (ListV)malloc(sizeof(voage));
    if (aux!=NULL)
    {
        strcpy(aux->Origem,"");
        strcpy(aux->Destino,"");
        aux->Lugares = 0;
        aux -> ocupados = NULL;
        aux->dataInicio.dia = 0;
        aux->dataInicio.mes = 0;
        aux->dataInicio.ano = 0;
        aux->next = NULL;
    }
    return aux;
}


ListClien cria_lista_clientes()
{
    ListClien aux;
    aux = (ListClien)malloc(sizeof(clien));
    if (aux!=NULL)
    {
        strcpy(aux->nome,"");
        strcpy(aux->BI,"");
        aux->next = NULL;
    }
    return aux;
}

int verifica_codigo(ListV lista_viagens, int codigo)  // 1 se a viagem existir 0 se não
{
    ListV lista = lista_viagens->next;
    while (lista!=NULL)
    {
        if (lista->codigo == codigo)
        {
            return 1;
        }
        lista = lista->next;
    }
    return 0;
}

void Adicionar_inicio(ListV lista_viagens,ListV aux)
{
    aux->next=lista_viagens->next;
    lista_viagens->next = aux;
}
void Adicionar_fim(ListV lista_viagens,ListV aux)
{
    while (lista_viagens->next !=NULL)
    {
        lista_viagens = lista_viagens->next;
    }
    aux->next=lista_viagens->next;
    lista_viagens->next = aux;
}
void Adicionar_Meio (ListV viagens_antes,ListV viagem_depois,ListV aux)
{
    aux->next = viagem_depois;
    viagens_antes->next = aux;
}
int verifica_viagem_existe (ListV lista_viagens,ListV aux) //retorna 1 se a viagem não existe, retorna 0 se existir
{
    ListV listaV = lista_viagens->next;
    while (listaV!= NULL)
    {
        if (strcmp(listaV->Destino,aux->Destino)==0)
        {
            if (verifica_data(listaV,aux)==0)
            {
                return 0;
            }
        }
        if (listaV->next ==  NULL)
        {
            return 1;
        }
        listaV =listaV->next;
    }
    return 1;
}
char* Verifica_BI (char *vetor)
{
    int biteste;
    biteste=atoi(vetor);
    while(strlen(vetor)!=8 || biteste-1==-1 || biteste-1<=9999998)
    {
        printf("insira um numero de bi valido(8 digitos):");
        scanf("%s",vetor);
        biteste=atoi(vetor);
    }
    return vetor;
}

void inserir_clientes (ListClien lista)
{
    char nome[MAX];
    char BI [MAX];
    printf("Inserir Clientes\n");
    ListClien aux;
    aux = (ListClien)malloc(sizeof(clien));
    printf("Nome:");
    scanf("%[^\n]%*c",nome);
    Verifica_Nome (nome);
    strcpy(aux->nome,nome);
    printf("BI (8digitos):");
    scanf("%[^\n]%*c",BI);
    strcpy(aux->BI ,Verifica_BI(BI));
    aux->VAdquirias = cria_lista_viagens();
    aux->VEspera = cria_lista_viagens();
    while (lista->next !=NULL)
    {
      if (strcmp(lista->next->nome,aux->nome)==0){
          printf("Ja existe um cliente com esse nome\n");
        break;
      }else lista = lista->next;
    }
      if (lista->next==NULL){
        aux->next = lista-> next;
        lista-> next = aux;
    }
}

void Verifica_Nome(char *vetor)
{
    int k=0,i;
    int compnome;
    compnome=strlen(vetor);
    while(k<compnome)
    {
        for(i=0; i<compnome-1; i++)
        {
            if( isdigit(vetor[i]) || (vetor[i] >= '!' && vetor[i] <= '/') || (vetor[i] >= ':' && vetor[i] <= '@')
                    || (vetor[i] >= '[' && vetor[i] <= '`') || (vetor[i] >= '{' && vetor[i] <= '~'))
            {
                printf("insina um sem numeros ou simbolos \n");
                k=0;
                fflush(stdin);
                fgets(vetor,100,stdin);
                compnome =strlen(vetor);
                break;
            }
            else
            {
                k=k+1;
            }
        }
    }
    return vetor;
}

void imprime_lista_viagens(ListV lista)
{
    lista = lista->next;
    while (lista!=NULL)
    {
        printf("-------------------\n");
        printf("Codigo da Viagem:%d\n",lista->codigo);
        printf("Origem:%s\nDestino:%s\nLutacao:%d\n",lista->Origem,lista->Destino,lista->Lugares);
        printf("Data Inicio (dd/mm/aa):%d/%d/%d\n",lista->dataInicio.dia,lista->dataInicio.mes,lista->dataInicio.ano);
        printf("-------------------\n");
        lista=lista->next;
    }
}
void imprime_lista_clientes(ListClien lista)
{
    lista = lista->next;
    while (lista!=NULL)
    {
        printf("-------------------\n");
        printf("Nome:%sBI:%s\n",lista->nome,lista->BI);
        printf("-------------------\n");
        lista=lista->next;
    }
}

void Adquirir_viagem (ListClien cliente, ListV lista_viagens,int codigo_viagem)
{
    ListV VAdquirias = cliente -> VAdquirias;
    ListV VEspera = cliente->VEspera;
    ListV listaV = lista_viagens;
    listaV =listaV->next;
    ListV no;
    int i;

    while (listaV!= NULL)
    {
        no = (ListV)malloc(sizeof(voage));
        if (listaV->codigo == codigo_viagem)
        {
            no->codigo = listaV->codigo;
            strcpy(no->Origem,listaV->Origem);
            strcpy(no->Destino,listaV->Destino);
            no->Lugares = listaV->Lugares;
            no->dataInicio = listaV->dataInicio;
            no->ocupados = listaV->ocupados;
            while (VAdquirias->next !=NULL)
            {
                VAdquirias = VAdquirias->next;
            }
            for (i=0; i<no->Lugares; i++)
            {
                if (no->ocupados[i] == NULL)
                {
                    no->ocupados [i] = cliente;
                    no->next = VAdquirias->next;
                    VAdquirias->next= no;
                    break;
                }
                else if (i == (no->Lugares)-1 && no->ocupados[i] !=NULL)
                {
                    printf("Lotacao esgotada, passou para a fila de espera\n");
                    while (VEspera->next!=NULL)
                    {
                        VEspera = VEspera->next;
                    }
                    no->next = VEspera->next;
                    VEspera->next = no;
                }
            }
            break;
        }
        else listaV =listaV->next;
    }
}
void colocar_fila_espera (ListClien cliente, ListV viagem)
{
    ListV Vespera = cliente->VEspera;
    ListV no = (ListV)malloc(sizeof(voage));
    no = viagem;
    while (Vespera->next != NULL)
    {
        Vespera = Vespera->next;
    }
    no->next = Vespera;
    Vespera->next = no;
}

void verifica_listas_esperas(ListClien lista_clientes, ListV lista_viagens)
{
    int i;
    ListClien cliente;
    ListClien ListaClientes = lista_clientes;
    ListaClientes = ListaClientes->next;
    ListV ListaViagens = lista_viagens->next;
    ListV Adquiridas;
    ListV Esperas;
    ListV aux;
    while (ListaClientes!=NULL)
    {
        cliente = ListaClientes;
        Adquiridas = ListaClientes->VAdquirias;
        Esperas = ListaClientes->VEspera;
        while (ListaViagens!=NULL && Esperas->next != NULL)
        {
            if (Esperas->next->codigo == ListaViagens->codigo)
            {
                for (i=0; i<ListaViagens->Lugares; i++)
                {
                    if (ListaViagens->ocupados[i] == NULL)
                    {
                        ListaViagens->ocupados[i] = cliente;
                        aux = (ListV)malloc(sizeof(voage));
                        aux->codigo = ListaViagens->codigo;
                        strcpy(aux->Origem,ListaViagens->Origem);
                        strcpy(aux->Destino,ListaViagens->Destino);
                        aux->Lugares = ListaViagens->Lugares;
                        aux->dataInicio = ListaViagens->dataInicio;
                        aux->ocupados = ListaViagens->ocupados;
                        Esperas->next = Esperas->next->next;
                        ListaViagens = lista_viagens;
                        while (Adquiridas->next!=NULL)
                        {
                            Adquiridas = Adquiridas->next;
                        }
                        aux->next = Adquiridas->next;
                        Adquiridas->next = aux;
                        break;
                    }
                }
            }
            ListaViagens = ListaViagens->next;
        }
        ListaClientes = ListaClientes->next;
    }
}

void imprimi_viagem (ListV lista)
{
    printf("-------------------\n");
    printf("Codifo da Viagem:%d\n",lista->codigo);
    printf("Origem:%s\nDestino:%s\nLutacao:%d\n",lista->Origem,lista->Destino,lista->Lugares);
    printf("Data Inicio (dd/mm/aa):%d/%d/%d\n",lista->dataInicio.dia,lista->dataInicio.mes,lista->dataInicio.ano);
    printf("-------------------\n");
}

void cancelar_reserva (ListClien cliente,int codigoV, ListV lista_viagens)
{
    ListV viagem;
    while (lista_viagens->next != NULL)
    {
        viagem = lista_viagens->next;
        if (viagem->codigo == codigoV)
        {
            Retira_Lugar(viagem,cliente);
            break;
        }
        lista_viagens = lista_viagens->next;
    }
    ListV ViagensAd = cliente->VAdquirias;
    ListV ant = ViagensAd;
    ViagensAd = ViagensAd->next;
    while (ViagensAd!=NULL)
    {
        if (ViagensAd->codigo == codigoV)
        {
            ant ->next = ViagensAd->next;
            break;
        }
        ant = ViagensAd;
        ViagensAd = ViagensAd->next;
    }
}
void Retira_Lugar (ListV Viagem, ListClien cliente)
{
    int tamanho = Viagem->Lugares;
    ListClien *array_lugares = Viagem->ocupados;
    ListClien Viagem_cliente;
    int i;
    for (i=0; i<tamanho; i++)
    {
        Viagem_cliente = array_lugares[i];
        if (strcmp(Viagem_cliente->nome,cliente->nome)==0)
        {
            array_lugares [i] = NULL;
            break;
        }
    }
}

void cancelar_reserva_espera (ListClien cliente,int codigoV)
{
    ListV ViagensAd = cliente->VEspera;
    ListV ant = ViagensAd;
    ViagensAd = ViagensAd->next;
    while (ViagensAd!=NULL)
    {
        if (ViagensAd->codigo == codigoV)
        {
            ant ->next = ViagensAd->next;
            break;
        }
        ant = ViagensAd;
        ViagensAd = ViagensAd->next;
    }
}

void imprimi_clientes_viagem (ListV lista, int codigo)
{
    lista = lista->next;
    int i;
    while (lista!=NULL)
    {
        if (lista->codigo == codigo)
        {
            ListClien *ola = lista->ocupados;
            for (i=0; i<lista->Lugares; i++)
            {
                if (ola[i]!=NULL)
                {
                    printf("%s\n",ola[i]->nome);
                }
            }
            break;
        }
        else lista = lista->next;
    }
}


void Listar_viagem_destino (ListV lista, char *DestinoV)
{
    lista = lista->next;
    while (lista!= NULL)
    {

        if (strcmp(lista->Destino,DestinoV)==0)
        {

            imprimi_viagem(lista);
        }
        lista = lista->next;
    }
}

void listar_clientes_viagens (ListClien lista_clientes)
{
    lista_clientes = lista_clientes->next;
    ListV VAdquiridas;
    ListV VEspera;
    while (lista_clientes!=NULL)
    {
        VAdquiridas = lista_clientes->VAdquirias;
        VEspera = lista_clientes->VEspera;
        if (VAdquiridas->next == NULL && VEspera->next == NULL);
        else
        {
            printf("%s\n",lista_clientes->nome);
        }
        lista_clientes = lista_clientes->next;
    }
}

int verifica_data (ListV viagem1,ListV viagem2)  // se data1>data2 return 1 se data1<data2 return 2 se data1==data2 return 0.
{
    int data1N = viagem1->dataInicio.ano*10000 + viagem1->dataInicio.mes*100 +viagem1->dataInicio.dia;
    int data2N = viagem2->dataInicio.ano*10000 + viagem2->dataInicio.mes*100 +viagem2->dataInicio.dia;
    if (data1N>data2N)
    {
        return 1; // A data 1 é mais recente que a data 2
    }
    else if (data1N<data2N)
    {
        return 2; // A data 2 é mais recente que a data 1
    }
    else return 0;  // São a mesma data.
}

int carrega_lista_viagens(ListV lista_viagens,FILE *ficheiro)
{
    int codigo = 0;
    ListV aux;
    ListV listaV = lista_viagens;
    int i=0;
    char linha[100];
    while(fgets(linha,100,ficheiro))
    {
        aux = (ListV)malloc(sizeof(voage));
        sscanf(linha,"%d %[^.]%*c %[^.]%*c %d %d/%d/%d",&(aux->codigo),aux->Origem,aux->Destino,&(aux->Lugares),&(aux->dataInicio.dia),&(aux->dataInicio.mes),&(aux->dataInicio.ano));
        ListClien *ocupados = (ListClien)malloc(sizeof(clien)*(aux->Lugares));
        for (i=0; i<aux->Lugares; i++)
        {
            ocupados[i] = NULL;
        }
        aux->ocupados = ocupados;
        if (verifica_viagem_existe(listaV,aux)==1)
        {
            aux->next=listaV->next;
            listaV->next = aux;
        }
        codigo++;
    }
    return codigo;
}

void carrega_lista_clientes (ListV lista_viagens,ListClien lista_clientes,FILE *ficheiro) // ultimo parametro se for 0 a viagem esta reservada se for 1 esta em espera.
{
    ListClien aux;
    ListV listaV;
    ListV viagem;
    ListClien listaC = lista_clientes;
    char linha[100];
    int codigo;
    int reserva;//0-viagem adquirida 1-Viagem na lista de espera
    while(fgets(linha,100,ficheiro))
    {
        aux = (ListClien)malloc(sizeof(clien));
        viagem = (ListV)malloc(sizeof(voage));
        listaV = lista_viagens;
        ListClien listaClientes=listaC;
        listaClientes = listaClientes->next;
        sscanf(linha,"%[^.]%*c %s %d %d",aux->nome,aux->BI,&codigo,&reserva);
        while(listaClientes!=NULL)
        {
            if (strcmp(listaClientes->nome,aux->nome)==0)
            {
                if (reserva ==0 || reserva ==1)
                {
                    Adquirir_viagem(listaClientes,listaV,codigo);
                    break;
                }
            }
            else listaClientes = listaClientes->next;
        }
        if (listaClientes == NULL)
        {
            aux->VAdquirias = cria_lista_viagens();
            aux->VEspera = cria_lista_viagens();
            ListV espera = aux->VEspera;

            if (reserva == 0 || reserva == 1)
            {
                Adquirir_viagem(aux,listaV,codigo);
            }
            aux->next=NULL;
            lista_clientes->next = aux;
            lista_clientes = aux;
        }
    }
}


void guarda_lista_clientes (ListClien lista_clientes, FILE *ficheiro)
{
    ListClien listaClientes = lista_clientes->next;
    ListV Adquiridas;
    ListV Espera;
    while (listaClientes!=NULL)
    {
        Adquiridas = listaClientes->VAdquirias;
        Adquiridas = Adquiridas->next;
        Espera = listaClientes->VEspera;
        Espera = Espera->next;
        while(Adquiridas!=NULL)
        {
            fprintf(ficheiro,"%s. %s %d 0\n",listaClientes->nome,listaClientes->BI,Adquiridas->codigo);
            Adquiridas = Adquiridas->next;
        }
        while (Espera !=NULL)
        {
            fprintf(ficheiro,"%s. %s %d 1\n",listaClientes->nome,listaClientes->BI,Espera->codigo);
            Espera = Espera->next;
        }
        listaClientes = listaClientes->next;
    }
}



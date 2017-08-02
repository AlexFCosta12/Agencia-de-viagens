#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas.h"
#include "funcoes.h"
#define MAX 100
void Menu (ListV lista_viagens,ListClien lista_clientes,int codigo)
{
    int i=0;
    int numero;
    char nome[MAX];
    char Destino[MAX];
    int verifica;

    while (i==0)
    {
        verifica_listas_esperas(lista_clientes,lista_viagens);
        FILE *ficheiro_cliente;
        ficheiro_cliente = fopen("clientes.txt", "w");
        guarda_lista_clientes(lista_clientes,ficheiro_cliente);
        fclose(ficheiro_cliente);

        ListClien ClientesLista = lista_clientes;
        i=1;
        printf("-------------------------------------\n");
        printf("-----------Agencia de Viagens--------\n");
        printf("-------------------------------------\n");
        printf("1)Criar Cliente\n2)Listar Viagens\n3)Reservar Viagem\n4)Listar clientes de uma viagem\n5)Listar Viagens de um cliente\n6)Listar clientes\n7)Eliminar cliente de uma viagem\n8)Cancelar reserva da lista de espera\n9)Listar clientes com viagens adquiridas ou em espera\n10)Listar as viagens de um determinado Destino\n11)Sair\n");
        scanf("%d%*c",&numero);
        fflush(stdin);
        int cod;
        system("cls");
        switch (numero)
        {
        case 1:
            inserir_clientes(lista_clientes);
            i=0;
            break;
        case 2:
            imprime_lista_viagens(lista_viagens);
            i=0;
            break;
        case 3:
            printf("Codigo da Viagem:");
            scanf("%d%*c",&cod);
            verifica = verifica_codigo(lista_viagens,cod);
            if (verifica == 1)
            {
                printf("Nome do Cliente:");
                scanf("%[^\n]%*c",nome);
                Verifica_Nome(nome);
                while (ClientesLista->next!=NULL)
                {
                    if (strcmp(nome,ClientesLista->next->nome)==0)
                    {
                        ClientesLista = ClientesLista->next;
                        Adquirir_viagem(ClientesLista,lista_viagens,cod);
                        break;
                    }
                    else
                    {
                        ClientesLista =ClientesLista->next;
                    }
                }
            }
            else
            {
                printf("A viagem com esse codigo não existe\n");
            }
            i=0;
            break;
        case 4:

            printf("Codigo:");
            scanf("%d%*c",&cod);
            verifica = verifica_codigo(lista_viagens,cod);
            if (verifica ==1)
            {
                imprimi_clientes_viagem(lista_viagens,cod);
            }
            else
            {
                printf("A viagem com esse codigo não existe\n");
            }
            i=0;
            break;
        case 5:
            printf("Nome do Cliente:");
            scanf("%[^\n]%*c",nome);
            Verifica_Nome(nome);
            while (ClientesLista->next!=NULL)
            {
                if (strcmp(nome,ClientesLista->next->nome)==0)
                {
                    imprime_lista_viagens(ClientesLista->next->VAdquirias);
                    printf("-----------Viagens em fila de espera------------");
                    imprime_lista_viagens(ClientesLista->next->VEspera);
                    break;
                }
                ClientesLista = ClientesLista->next;
            }
            i=0;
            break;
        case 6:
            imprime_lista_clientes(lista_clientes);
            i=0;
            break;
        case 7:
            printf("Codigo da Viagem:");
            scanf("%d%*c",&cod);
            verifica = verifica_codigo(lista_viagens,cod);
            if (verifica ==1)
            {
                printf("Nome do Cliente:");
                scanf("%[^\n]%*c",nome);
                Verifica_Nome(nome);
                while (ClientesLista->next!=NULL)
                {
                    if (strcmp(nome,ClientesLista->next->nome)==0)
                    {
                        ClientesLista = ClientesLista->next;
                        cancelar_reserva(ClientesLista,cod,lista_viagens);
                        break;
                    }
                    else
                    {
                        ClientesLista =ClientesLista->next;
                    }
                }
            }
            else
            {
                printf("A viagem com esse codigo não existe\n");
            }
            i=0;
            break;
        case 8:
            printf("Codigo da viagem que pertende cancelar o pedido:");
            scanf("%d%*c",&cod);
            verifica = verifica_codigo(lista_viagens,cod);
            if (verifica ==1)
            {
                printf("Nome do Cliente:");
                scanf("%[^\n]%*c",nome);
                Verifica_Nome(nome);
                while ( ClientesLista->next!=NULL)
                {
                    if (strcmp(nome, ClientesLista->next->nome)==0)
                    {
                        ClientesLista=ClientesLista->next;
                        break;
                    }
                    else
                    {
                        ClientesLista = ClientesLista->next;
                    }
                }
                cancelar_reserva_espera( ClientesLista,cod);
            }
            else
            {
                printf("A viagem com esse codigo não existe\n");
            }
            i=0;
            break;
        case 9:
            if (ClientesLista->next == NULL)
            {
                printf("Nao ha clientes com viagens nem adquiridas nem em fila de espera\n");
            }
            else
            {
                listar_clientes_viagens(ClientesLista);
            }
            i=0;
            break;
        case 10:
            printf("Destino:");
            scanf("%[^\n]%*c",Destino);
            Verifica_Nome(Destino);
            Listar_viagem_destino(lista_viagens,Destino);
            i=0;
            break;
        case 11:
            ficheiro_cliente = fopen("clientes.txt", "w");
            guarda_lista_clientes(lista_clientes,ficheiro_cliente);
            fclose(ficheiro_cliente);
            printf("ADEUS!!\n");
            break;
        default:
            printf("Opcao invalida\n");
            i=0;
            break;
        }
    }
}



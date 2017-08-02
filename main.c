#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h"
#include "funcoes.h"
#include "menu.h"


int main()
{
    FILE *ficheiro_viagens;
    ficheiro_viagens = fopen("viagens.txt", "r");
    FILE *ficheiro_clientes;
    ficheiro_clientes = fopen("clientes.txt", "r");
    int codigo =0;
    ListV lista_viagens = cria_lista_viagens();
    codigo = carrega_lista_viagens(lista_viagens,ficheiro_viagens);
    ListClien lista_clientes = cria_lista_clientes();
    carrega_lista_clientes(lista_viagens,lista_clientes,ficheiro_clientes);
    Menu(lista_viagens,lista_clientes,codigo);
    fclose(ficheiro_viagens);
    fclose(ficheiro_clientes);
}

void VerificaListas (ListV lista)
{
    int codigo = 0;
    while (lista->next !=NULL)
    {
        codigo ++;
        lista = lista->next;
    }
}

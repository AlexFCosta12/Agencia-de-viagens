#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
#include <stdio.h>
#include <time.h>
#define MAX 100

typedef struct time
{
    int dia,mes,ano;
}Time;
typedef struct Clientes *ListClien;
typedef struct Viagens *ListV;
typedef struct Viagens
{
    int codigo;
    char Origem [MAX];
    char Destino [MAX];
    int Lugares;
    ListClien *ocupados;
    Time dataInicio;
    ListV next;
} voage;


typedef struct Clientes
{
  char nome[MAX];
  char BI[8];
  ListV VAdquirias;
  ListV VEspera;
  ListClien next;
}clien;
#endif



ListV cria_lista_viagens();
void cria_viagem(ListV,int);
void imprime_lista_viagens(ListV);
void inserir_clientes (ListClien);
int verifica_codigo(ListV, int);
void imprime_lista_clientes(ListClien);
void imprimi_viagem (ListV);
void Adquirir_viagem (ListClien,ListV,int);
void imprimi_clientes_viagem (ListV, int);
void cancelar_viagem (ListV, ListClien, int);
void cancelar_reserva (ListClien,int,ListV);
void Listar_viagem_destino (ListV, char*);
void cancelar_reserva_espera (ListClien,int);
void Retira_Lugar (ListV, ListClien);
void verifica_listas_esperas(ListClien, ListV);
void listar_clientes_viagens (ListClien);
int verifica_data (ListV ,ListV );
int verifica_viagem_existe (ListV,ListV);
void Adicionar_inicio(ListV,ListV);
void Adicionar_fim(ListV,ListV);
int carrega_lista_viagens(ListV ,FILE *);
void carrega_lista_clientes (ListV,ListClien,FILE *);
void guarda_lista_clientes (ListClien, FILE *);
void Verifica_Nome(char*);
char Verifica_BI (char *);

#ifndef funcoes_H // Verifica se um identificador não foi definido caso não será compilado
#define funcoes_H // Define o identificador
#define MAX_CIDADES 200

int calculo(int a);

typedef struct {
    char date[50];
    char domain[50];
    char location[50];
    int value;
    int transaction_count;
} registro;

typedef struct {
    char location[50];
    long long total_value;
    long long total_transactions;
} CidadeInfo;

typedef struct {
    char domain[50];
    int min_value;
    int max_value;
} IndicadorDominio;

void adicionarRegistro();
void verregistro();
void buscaSequencial();
void binouseq();
void buscaBinaria();
int validarData(const char *data);
void filtrarPorDominio();
void freeLocalidades();
int compareStrings();
void listarLocalidadesDistintasOrdenadas();
void calcularMediaPorLocalidade();
int compareCidades();
void gerarRelatorioConsolidado();

#endif// Indica o fim do IFNDEF
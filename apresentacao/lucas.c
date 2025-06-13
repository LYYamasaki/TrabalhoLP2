#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Feitos : M3 , A1, E1, E2

// Escolha entre binario e sequencial

// A1

void binouseq(){
    system("cls");
    int escolha;
    printf("[1] Sequencial\n[2] Binario\n");
    scanf("%d", &escolha);
    if (escolha != 1 && escolha != 2) {
        printf("Escolha invalida\n");
        system("pause");
    }
    if (escolha == 1 ) {
        buscaSequencial();
    }
    if (escolha == 2 ) {
        buscaBinaria();
    }
}


// Busca Sequencial

void buscaSequencial(){
    system("cls");
    int valorbuscado;
    int valorachado = 0;                                                            // Define um int para confirmar se foi localizado
    registro r;
    printf("Valor procurado: ");
    scanf("%d", &valorbuscado);
    printf("============== Resultado da Busca ==============\n");

    FILE *file = fopen("bankdataset.dat", "rb");
    FILE *txt = fopen("busca_valor_sequencial.txt", "w");

    if (file == NULL) {
        printf("Arquivo nao encontrado!");
        return;
    }

    if (file && txt) {                                                                 // Verifica se os arquivos estão disponíveis
        while (fread(&r, sizeof(registro), 1, file) == 1) {                            // o fRead lê 1 linha do registro(variavel anteriormente declarada como R) até que não haja mais
            if (r.value == valorbuscado) {
                printf("\nData: %s\nDominio: %s\nLocalidade: %s\nValor: %d\nTransacoes: %d\n\n",  r.date, r.domain, r.location, r.value, r.transaction_count);
                printf("--------------------------------------------------------\n");
                valorachado = 1;                                                        // Confirma que foi localizado o valor
            }
            fprintf(txt, "%s,%s,%s,%d,%d\n",r.date, r.domain, r.location, r.value, r.transaction_count);
        }
        if (valorachado == 0) {                                                           // Caso não encontre o valor continua 0 e diz que não encontrou
            printf("Valor nao encontrado!\n");
        }
        system("pause");
        fclose(file);
        fclose(txt);
        system("cls");
    } else {
        printf("Arquivo danificado ou corrompido!");
    }
}

// Busca Binaria

int compararvalor(const void *a, const void*b) {                      // Comparador dos Valores
    return ((registro *)a)-> value - ((registro *)b)-> value;           // Retorna o valor da diferença entre A e B
}

void buscaBinaria() {
    system("cls");
    int valorbuscado;
    printf("Valor procurado: ");
    scanf("%d", &valorbuscado);

    FILE *file = fopen("bankdataset.dat", "rb");
    FILE *txt = fopen("busca_valor_binaria.txt", "w");

    if (file == NULL) {
        printf("Arquivo nao encontrado!");
        return;
    }

    fseek(file, 0, SEEK_END);                                           // Move o ponteiro até o final do arquivo
    long tamanho = ftell(file);                                                     // Define o tamanho de bytes do arquivo
    rewind(file);

    int total = tamanho / sizeof(registro);
    registro *vetor = malloc(tamanho);                                              // Define um vetor do tamanho do registro
    fread(vetor, sizeof(registro), total, file);
    fclose(file);

    qsort(vetor, total, sizeof(registro), compararvalor);

    registro chave;
    chave.value = valorbuscado;

    registro *encontrado = bsearch(&chave, vetor, total, sizeof(registro), compararvalor);
    if (encontrado) {
        printf("\nData: %s\nDominio: %s\nLocalidade: %s\nValor: %d\nTransacoes: %d\n\n",encontrado->date, encontrado->domain, encontrado->location, encontrado->value, encontrado->transaction_count);
        fprintf(txt, "%s,%s,%s,%d,%d\n",encontrado->date, encontrado->domain, encontrado->location, encontrado->value, encontrado->transaction_count);
        fclose(txt);
    } else {
        printf("Valor nao encontrado!\n");
    }
    free (vetor);
}

// E1

// Validor de data

int validarData(const char *data) {

    if (data[2] != '/' || data[5] != '/') return 0;

    // Verifica se são numeros

    for (int i = 0 ; i < 10 ; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(data[i])) return 0;
    }

    // Converte os char para inteiro para evitar datas 00/00/0000

    int dia = atoi((char[]){data[0], data[1], '\0'});
    int mes = atoi((char[]){data[3], data[4], '\0'});
    int ano = atoi((char[]){data[6], data[7], data[8], data[9], '\0'});

    if (dia == 0 || mes == 0 || ano == 0) return 0;

    if (mes < 1 || mes > 12) return 0;

    if (dia < 1 || dia > 31) return 0;

    return 1;
}

// Adicionar Registro ao final do arquivo


void adicionarRegistro() {
    system("cls");
    FILE *file = fopen("bankdataset.dat", "ab");
    registro r;

    if (file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    do {
        printf("Digite a data (DD/MM/AAAA): ");
        scanf("%10s",r.date);

        if (!validarData(r.date)) {
            printf("Data invalida! Utilize (DD/MM/AAAA)\n");
            system("pause");
            system("cls");
        }

    } while (!validarData(r.date));

    printf("Digite o dominio: ");
    scanf("%s", r.domain);

    printf("Digite a localidade: ");
    scanf("%s",r.location);

    do {
        printf("Digite o valor (positivo): ");
        scanf("%d", &r.value);
    } while (r.value <= 0);

    do {
        printf("Digite o numero de transacoes (positivo): ");
        scanf("%d", &r.transaction_count);
    } while (r.transaction_count <= 0);

    fwrite(&r, sizeof(r), 1, file);
    fclose(file);
    printf("Registro adicionado com sucesso!\n");
    system("pause");
    system("cls");
}

// M3

// Media Por Localidade

int compareCidades(const void *a, const void *b) {
    return strcmp(((CidadeInfo *)a)-> location, ((CidadeInfo *)b)-> location);
}

void calcularMediaPorLocalidade() {
    system("cls");
    FILE *file = fopen("bankdataset.dat","rb");
    registro r;
    CidadeInfo cidades[MAX_CIDADES];
    int qtd_cidades = 0;

    if (file == NULL) {
        printf("Arquivo nao encontrado!\n");
    }

    if (file) {
        while (fread(&r, sizeof(registro), 1, file) == 1) {
            int encontrada = 0;
            for (int i = 0; i < qtd_cidades; i++) {                            // Verifica se a local está na lista e acumula os valores e transaçaões
                if (strcmp(cidades[i].location, r.location) == 0) {
                    cidades[i].total_value += r.value;
                    cidades[i].total_transactions += r.transaction_count;
                    encontrada = 1;
                    break;
                }
            }                                                                   // Se for um local novo, adiciona o local ao vetor
            if (!encontrada && qtd_cidades <MAX_CIDADES) {
                strcpy(cidades[qtd_cidades].location, r.location);
                cidades[qtd_cidades].total_value = r.value;
                cidades[qtd_cidades].total_transactions = r.transaction_count;
                qtd_cidades++;
            }
        }
        fclose(file);

        qsort(cidades, qtd_cidades, sizeof(CidadeInfo), compareCidades);           // Usa o qsort para ordernar as cidades na ordem alfabetica

        FILE *txt = fopen("media_por_localidade","w");
        printf("+--------------------+------------+\n");
        printf("| Localidade         | Media (R$)|\n");
        printf("+--------------------+------------+\n");
        fprintf(txt,"Localidade,Media\n");

        for (int i = 0; i < qtd_cidades; i++) {                                                    // Calcula a média do valor de transação
            double media = (double)cidades[i].total_value / cidades[i].total_transactions;
            printf("|%-20s| %10.2f |\n", cidades[i].location, media);
            fprintf(txt,"%s,%.2f\n", cidades[i].location, media);
        }

        printf("+--------------------+------------+\n");
        fclose(txt);
        system("pause");
        system("cls");
    } else {
        printf("Arquivo danificado ou corrompido!\n");
    }
}

// E2

void calcularMediaPorLocalidade() {
  system("cls");
  FILE *file = fopen("bankdataset.dat","rb");
  registro r;
  CidadeInfo cidades[MAX_CIDADES];
  int qtd_cidades = 0;

  if (file == NULL) {
    printf("Arquivo nao encontrado!\n");
  }

  if (file) {
    while (fread(&r, sizeof(registro), 1, file) == 1) {
      int encontrada = 0;
      for (int i = 0; i < qtd_cidades; i++) {
        if (strcmp(cidades[i].location, r.location) == 0) {
          cidades[i].total_value += r.value;
          cidades[i].total_transactions += r.transaction_count;
          encontrada = 1;
          break;
        }
      }
      if (!encontrada && qtd_cidades <MAX_CIDADES) {
        strcpy(cidades[qtd_cidades].location, r.location);
        cidades[qtd_cidades].total_value = r.value;
        cidades[qtd_cidades].total_transactions = r.transaction_count;
        qtd_cidades++;
      }
    }
    fclose(file);

    qsort(cidades, qtd_cidades, sizeof(CidadeInfo), compareCidades);

    FILE *txt = fopen("media_por_localidade","w");
    printf("+--------------------+------------+\n");
    printf("| Localidade         | Media (R$)|\n");
    printf("+--------------------+------------+\n");
    fprintf(txt,"Localidade,Media\n");

    for (int i = 0; i < qtd_cidades; i++) {
      double media = (double)cidades[i].total_value / cidades[i].total_transactions;
      printf("|%-20s| %10.2f |\n", cidades[i].location, media);
      fprintf(txt,"%s,%.2f\n", cidades[i].location, media);
    }

    printf("+--------------------+------------+\n");
    fclose(txt);
    system("pause");
    system("cls");
  } else {
    printf("Arquivo danificado ou corrompido!\n");
  }
}

void gerarRelatorioConsolidado() {
  system("cls");
  FILE *file = fopen("bankdataset.dat","rb");
  FILE *txt = fopen("C:\\Testes\\relatorio.txt","w");
  registro r;

  IndicadorDominio dom[100];
  int domCount = 0;
  int total = 0, total_valor = 0, total_trans = 0;

  if (file == NULL || txt == NULL) {
    printf("Arquivo nao encontrado!\n");
  }

  while (fread(&r, sizeof(registro), 1, file) == 1) {
    total++;
    total_valor += r.value;
    total_trans += r.transaction_count;

    int i, achou = 0;
    for (i = 0; i < domCount; i++) {
      if (strcmp(dom[i].domain, r.domain) ==0) {
        if (r.value > dom[i].max_value) dom[i].max_value = r.value;
        if (r.value < dom[i].min_value) dom[i].min_value = r.value;
        achou = 1;
        break;
      }
    }

    if (!achou) {
      strcpy(dom[domCount].domain, r.domain);
      dom[domCount].max_value = dom[domCount].min_value = r.value;
      domCount++;
    }
  }

  fprintf(txt, "========= Relatorio Consolidade =========\n\n");
  fprintf(txt,"Total de registros: %d\n",total);
  fprintf(txt,"Valor total movimentado: R$ %d\n",total_valor);
  fprintf(txt,"Total de transacoes: %d\n", total_trans);
  fprintf(txt,"Valores por dominio: \n\n");

  for (int i = 0; i < domCount; i++) {
    fprintf(txt,"%-10s -> Maior: %d | Menor %d\n", dom[i].domain, dom[i].max_value, dom[i].min_value);
  }

  fclose(file);
  fclose(txt);
  printf("Relatorio gerado com sucesso. \n");
  system("pause");
  system("cls");
}




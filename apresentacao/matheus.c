#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void freeLocalidades(char **localidades, int count) {
  if (localidades == NULL) return;
  for (int i = 0; i < count; i++) {
    if (localidades[i] != NULL) {
      free(localidades[i]);
    }
  }
  free(localidades);
}

int compareStrings(const void *a, const void *b) {
  const char *str_a = *(const char **)a;
  const char *str_b = *(const char **)b;
  return strcmp(str_a, str_b);
}

void listarLocalidadesDistintasOrdenadas() {
  system("cls");
    FILE *fp = NULL;
    FILE *out = NULL;
    registro r;
    char **localidades = NULL;
    int qtd_localidades = 0;
    int capacidade = 10;

    fp = fopen("bankdataset.dat", "rb");
    if (!fp) {
        perror("Erro ao abrir o arquivo binario bankdataset.dat");
        return;
    }

    out = fopen("localidades_ordenadas.txt", "w");
    if (!out) {
        perror("Erro ao criar o arquivo de saida localidades_ordenadas.txt");
        fclose(fp);
        return;
    }

    localidades = (char **)malloc(capacidade * sizeof(char *));
    if (!localidades) {
        fprintf(stderr, "Erro de alocacao de memoria para o vetor de localidades.\n");
        fclose(fp);
        fclose(out);
        return;
    }

    printf("Coletando localidades distintas...\n");
    int registros_lidos_binario = 0;
    while (fread(&r, sizeof(registro), 1, fp) == 1) {
        registros_lidos_binario++;

        char *nova_localidade = (char *)malloc(strlen(r.location) + 1);
        if (!nova_localidade) {
            fprintf(stderr, "Erro de alocacao de memoria para nova localidade.\n");
            freeLocalidades(localidades, qtd_localidades);
            fclose(fp);
            fclose(out);
            return;
        }
        strcpy(nova_localidade, r.location);

        if (qtd_localidades == capacidade) {
            capacidade *= 2;
            char **temp = (char **)realloc(localidades, capacidade * sizeof(char *));
            if (!temp) {
                fprintf(stderr, "Erro de realocacao de memoria para o vetor de localidades.\n");
                free(nova_localidade);
                freeLocalidades(localidades, qtd_localidades);
                fclose(fp);
                fclose(out);
                return;
            }
            localidades = temp;
        }
        localidades[qtd_localidades++] = nova_localidade;
    }
    printf("DEBUG A2: Total de registros lidos do binario: %d\n", registros_lidos_binario);

    fclose(fp);

    qsort(localidades, qtd_localidades, sizeof(char *), compareStrings);

    printf("\nLista de Localidades Distintas (Ordenadas):\n");
    printf("-----------------------------------------\n");

    fprintf(out, "Lista de Localidades Distintas (Ordenadas):\n");
    fprintf(out, "-----------------------------------------\n");

    if (qtd_localidades > 0) {
        printf("%s\n", localidades[0]);
        fprintf(out, "%s\n", localidades[0]);

        for (int i = 1; i < qtd_localidades; i++) {
            if (strcmp(localidades[i], localidades[i-1]) != 0) {
                printf("%s\n", localidades[i]);
                fprintf(out, "%s\n", localidades[i]);
            }
        }
    } else {
        printf("Nenhuma localidade encontrada no arquivo.\n");
        fprintf(out, "Nenhuma localidade encontrada no arquivo.\n");
    }

    printf("-----------------------------------------\n");
    printf("Localidades distintas exportadas para 'localidades_ordenadas.txt'\n");
  system("pause");
    fclose(out);

    freeLocalidades(localidades, qtd_localidades);
  system("cls");
}

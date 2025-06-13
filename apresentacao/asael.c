#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void filtrarPorDominio() {
    system("cls");

    FILE *file = fopen("bankdataset.dat", "rb");
    FILE *txt = fopen("filtro_dominio_NOME.txt","w");
    int count = 0;
    if (file == NULL) {
        printf("Arquivo nao encontrado!\n");
        system("pause");
        system("cls");
        return;
    }

    char dominio[50];
    printf("Digite o dominio (ex: RESTAURANT): ");
    scanf("%s", dominio);

    registro r;
    int encontrados = 0;

    printf("\n+------------+----------------------+--------------------------+--------+------------+\n");
    printf("| Data       | Dominio              | Localidade               | Valor  | Transacoes |\n");
    printf("+------------+----------------------+--------------------------+--------+------------+\n");

    while (fread(&r, sizeof(registro), 1, file) == 1) {
        if (count < 100) {
            if (strcmp(r.domain, dominio) == 0) {
                printf("| %-10s | %-20s | %-24s | %6d | %10d |\n",
                       r.date, r.domain, r.location, r.value, r.transaction_count);
                fprintf(txt,"| %-10s | %-20s | %-24s | %6d | %10d |\n",r.date, r.domain, r.location, r.value, r.transaction_count);
                encontrados++;
                count ++;
            }
        }
    }


    if (encontrados == 0) {
        printf("| registro encontrado com o dominio \"%s\".\n", dominio);
    }

    printf("+------------+----------------------+--------------------------+--------+------------+\n");

    fclose(file);
    system("pause");
    system("cls");
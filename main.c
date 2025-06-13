#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h" // Inclui o diretorio do "funcoes.c" para utilizar dentro desse código

int main() {
    int escolha;
    int escolha1;
    do {
        printf("========== Menu Principal ==========\n");
        printf("[1] Listar todos os regristros\n");
        printf("[2] Filtrar registros por dominio\n");
        printf("[3] Somar total de transacoes por dominio\n");
        printf("[4] Exportar registros por data\n");
        printf("[5] Calcular media por localidade\n");
        printf("[6] Buscar registro por valor (seq/bin)\n");
        printf("[7] Listar localidades distintas ordenadas\n");
        printf("[8] Inserir novo registro no arquivo\n");
        printf("[9] Gerar relatorio consolidado\n");
        printf("[0] Sair do Programa\n");
        printf("==============================\n");
        printf("Digite sua opcao: ");
        escolha1 = scanf("%d", &escolha);

        if (escolha1 != 1) {                                                          // Verifica se a escolha não foi uma letra
            printf("Entrada invalida! Use apenas numeros\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);                              // Tira qualquer caracter invadálidos até o fim da linha
            system("pause");                                                 // Aguarda para poder ver a mensagem de erro
            system("cls");
            continue;
        }
        if (escolha < 0 || escolha > 9) {                                             // Verifica se foi digitado um numero entre 0 e 9
            printf("Opcao invalida! Escolha uma opcao de 0 a 9\n");
            system("pause");                                                 // Aguarda para poder ver a mensagem de erro
            system("cls");
            continue;
        }

        switch (escolha) {
            case(0):  break;
            case(1): verregistro(); break;
            case(2): filtrarPorDominio(); break;
            case(5): calcularMediaPorLocalidade(); break;
            case(6): binouseq(); break;
            case(7): listarLocalidadesDistintasOrdenadas(); break;
            case(8): adicionarRegistro(); break;
            case(9): gerarRelatorioConsolidado(); break;

            }
    } while (escolha != 0);
    return 0;
}
#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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


// Função E.1 - Adicionar Novo Registro ao final do arquivo

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

// Função B.1 | Listar Todos os Registros

void verregistro() {
  system("cls");                                                      // Limpa o terminal para melhor visibilidade
  int count = 0;                                                               // inicia uma variavel int para utilizar em como limite
  FILE *file = fopen("bankdataset.dat", "rb");                   // abre o arquivo dos registros em binario ( rb = read binary )
  FILE *txt = fopen("relatorio_registros.txt", "w");             // abre / cria o relatorio txt ( w = write )
  registro r;                                                                  // Declara uma variavel R do tipo struct citada no #funcoes.c
  if (file == NULL) {
    printf("Arquivo nao encontrado!");                                   // Verifica se o arquivo existe
    return;
  }

  if (file && txt) {                                                           // Verifica se os arquivos estão disponíveis
    fprintf(txt, "+-----------+----------------------+--------------------------------+---------------------+------------+\n");
    fprintf(txt, "|Data       | Dominio              | Localidade                     | Valor               | Transacoes |\n");
    fprintf(txt, "+-----------+----------------------+--------------------------------+---------------------+------------+\n");

    printf("+-----------+----------------------+--------------------------------+---------------------+------------+\n");
    printf("|Data       | Dominio              | Localidade                     | Valor               | Transacoes |\n");
    printf("+-----------+----------------------+--------------------------------+---------------------+------------+\n");

    while (fread(&r, sizeof(registro), 1, file) == 1) {       // o fRead lê 1 linha do registro(variavel anteriormente declarada como R) até que não haja mais

      if (count < 100) {                                                      // Utilização do count para ler somente os primeiros 100 registros
        printf("|%-10s | %-18s   | %-17s              | %7d             | %5d      |\n", r.date, r.domain, r.location, r.value, r.transaction_count);
      }
      fprintf(txt, "|%-10s | %-18s   | %-17s              | %7d             | %5d      |\n", r.date, r.domain, r.location, r.value, r.transaction_count);
      count++;
    }
    printf("+-----------+----------------------+--------------------------------+---------------------+------------+\n");
    system("pause");                             // Pausa para poder ler os dados
    fclose(file);                                         // Fecha o arquivo binario anteriormente aberto
    fclose(txt);                                          // Fecha o arquivo texto aberto / criado para salvar os dados binarios
    system("cls");                               // Limpa o terminal antes de voltar para o menu principal
  } else {
    printf("Arquivo danificado ou corrompido!");    // Caso os arquivos não estejam disponível avisa o erro e retorna
  }
}

  // Função A.1 | Buscar Registro Por Valor de Transação //

  int compararvalor(const void *a, const void*b) {                      // Comparador dos Valores
    return ((registro *)a)-> value - ((registro *)b)-> value;           // Retorna o valor da diferença entre A e B
  }

  // Busca Sequencial ( 1 a 1 )

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

    if (file && txt) {                                                          // Verifica se os arquivos estão disponíveis
      while (fread(&r, sizeof(registro), 1, file) == 1) {       // o fRead lê 1 linha do registro(variavel anteriormente declarada como R) até que não haja mais
        if (r.value == valorbuscado) {
          printf("\nData: %s\nDominio: %s\nLocalidade: %s\nValor: %d\nTransacoes: %d\n\n",  r.date, r.domain, r.location, r.value, r.transaction_count);
          printf("--------------------------------------------------------\n");
          valorachado = 1;                                                      // Confirma que foi localizado o valor
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

// Busca binaria ( carrega em um vetor e ordena pelo qsort e dps a busca binaria com bserch )

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
  system("pause");
  system("cls");
}

// Asael  B.2

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
}

// Matheus A.2

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

// Calcular Media por Cidade M.3

int compareCidades(const void *a, const void *b) {                                // A
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

  void formatarMoeda(long long valor, char *buffer) {
    char temp[50];
    sprintf(temp, "%lld", total_valor);

    int len = strlen(temp);
    int commas = (len - 1) / 3;
    int new_len = len + commas;

    buffer[0] = 'R';
    buffer[1] = '$';
    buffer[2] = ' ';

    int j = new_len + 2;
    buffer[j--] = '\0';

    int count = 0;
    for (int i = len - 1; i >= 0; i--) {
      buffer[j--] = temp[i];
      count++;
      if (count == 3 && i != 0) {
        buffer[j--] = '.';
        count = 0;
      }
    }
  }

  char buffer_total_valor[60];
  char buffer_max_value[60];
  char buffer_min_value[60];
  formatarMoeda(total_valor, buffer_total_valor);

  fprintf(txt, "========= Relatorio Consolidade =========\n\n");
  fprintf(txt,"Total de registros: %d\n",total);
  fprintf(txt,"Valor total movimentado: R$ %d\n", buffer_total_valor);
  fprintf(txt,"Total de transacoes: %d\n", total_trans);
  fprintf(txt,"Valores por dominio: \n\n");

  for (int i = 0; i < domCount; i++) {
    formatarMoeda(dom[i].max_value, buffer_max_value);
    formatarMoeda(dom[i].min_value, buffer_min_value);
    fprintf(txt,"%-10s -> Maior: %d | Menor %d\n", dom[i].domain, buffer_max_value, buffer_min_value);
  }

  fclose(file);
  fclose(txt);
  printf("Relatorio gerado com sucesso. \n");
  system("pause");
  system("cls");
}

void creditos() {
  system("cls");
   const char* ascii_art_pato =
".:+#%#+:......:+=.-+=:.....:=*+=:.....................................-+-.....-+-...........-*#%#=..\n"
".:%##+:......:+=-+=:....:-=-=:........................................-=-....:==:..........-*#%#=..\n"
".:%##+:......:+++=:....:=+=-:..........................................-=-....:+=:.........-*#%#=..\n"
".:%##+:......-**+:...:=++-:.............................................-+-....-+=.........-*###=..\n"
".:*%##+:......=#*-..:-++-:...........................................:::::-=-....=+-........-*###=..\n"
".:*%##+:.....:+*=..:=+=:.............................................::----==-...:++:.......-*###=..\n"
".:*%##+:.....-*+:.-++-..................................................:::-=+-...-+-.......-*###+:. \n"
".:*%##+......=*-:=+=:.    ..............................................    .-+=:.:++:......-*###+:. \n"
".:*%##+.....-**=++=:.      ...........................................        :==-:-*=......:*###+:. \n"
".-*%##=....:+#**+-..       .....................=....................          .-+=-+*-.....:*##%+:. \n"
".-#%##=....-###+:.           ...............:=%+=+@+..............              .-+**#+:....:*##%*:. \n"
".-#%##=...-*##=:.             .............:++**++*#+............                 :=*##+:...:+##%*:. \n"
".-#%##-..:+##+:                  .........+*+=+=+*##%........                      .-*##=:...+###*:. \n"
".-#%#*-.:+##+-:.                  ........****=+@@#*%#-.....                        .:+##=:..=##%*:. \n"
".=#%#*-:=##*=--.                   ....:.+#**%@%*.%*%## ........   ..... .............:+##=:.=##%*-. \n"
".=#%#*-=##*==-:                    %%#::-#%#%@#+=-+*#%#................................:+##=:=##%#-: \n"
".=#%##+*#*=---:.                   %-:-%*#@%%%#**+%**%#-......................::........-*##=+##%#=- \n"
":+#%#####+::---:.                  -  ...+%@@@*#==---@%=......................::.........=*#####%#+= \n"
":*#%####*-:-==-:....................#    +%#-%#*----==*%:.....................::.........:+#####%#*= \n"
":*%%####+---==-:....................+   .:::=%@*-==+#=+#-....................:--:......:::-*####%#*= \n"
"-#%%###*=--===-::...................-#*#*-:#-%%%%#%**++*%....................:--:......:-::+####%#*+ \n"
"=#%%###+--====---:......................#:.=-=@%#*++****%....................:--:.....:-=::-*####%#+ \n"
"+#%###*=---===---:....................-#::::-==*@#####***...................:---:....:-==---+####%#+ \n"
"+#%###*---====-:::..:.................+-::::-=*#@%%%%%### ..................::---:..:-=====-=*###%#* \n"
"*%%###+--=====-:...:-:..............#:::.:--=+%@@@@@%###:....................:----:.:-=======*#####* \n"
"#%###*=-=======-:..:-:............-.-:..:--==%@@@@@@%%#%:...................:-----:::=====+==+###%%# \n"
"#%###*=========--::-=:...........:-==:..=+=-.=@@@@@%%%%+...................:------::-====+++=+*###%# \n"
"%%###+=========-:---=-:..........:-%#==+##:.. @@@@%%###-   ................:---------====+++++*###%# \n"
"%%###+=+=======-::-==--:....:......##........ .@@%%####-    ..............::-------=====++++++*###%% \n"
"%%##*++++======----===--:................. ....#@%#**#%=   ................::-----======+++++++###%% \n"
"%%##*++++=======--====--.......................%%#*+*#*: .  ...............:------======+++++++*##%% \n"
"%%##*+++++=============-.......................@%#+=*%+ .  ...............:------======++++++++*##%% \n"
"%###*++++++============-:......................%%*=+*%#    ..............:------=======++++++++*##%% \n"
"%###*++++++=============-::....................*%*=+*%# .................::-----======++=++++++*###% \n"
"%###*+++++++=============--:...................##+=+#%#  ... ............:::---=======+++++++++*###% \n"
"%###*+++++++===============-:.................=##+=+##.  . ...............::---=======+=+++++++*###% \n"
"%###*++++++++==============--::::::...........%%*++*#*.  . .........:....::---=====++=+==++++++*###% \n"
"####*++++++++===============------:..........:#%*++*%@  ...........:-:.::----=====+++++++++++++*###% \n"
"%###++++++++++===================--..........+%#+++#@-  ..........:---::::--=====+++++==+++++++*###% \n"
"%###++++++++++=-=================--..........-:-+++#@. ...........:----:.:-=====++++++==+++++++*###% \n"
"%###*+++++++++=-+===============---:........-:     .-. .....::.....:---..:-=====+++++++++++++++*###% \n"
"####*++++++++++++===============--::.......:#+=:   .- ......::....:-==-::-=====++++++++++++++++*###% \n"
"%###*+++++++++++++==============--::.......%%%%####*%%......::...:-=====-======++++++++++++++++*#### \n"
"%###*++++++++++++++==============---:.....:*%%####%%% .....::::.:--============++++++++++++++++*###% \n"
"%###*+++++++++++++++=============--::....-#%%#####%%#......:--::::-===========+++++++++++++++++*#### \n"
"%###*+++++++++++++++=============::..... =%%%######%%#....::---::-============+++++++++++++++++*###% \n"
"%###*++++++++++++++++=============-.....:*%%%###*##%%+.::::------===========+++++++++++++++++++*###% \n"
"%###*++++++++++++++++=============-:...-%#####****#%%+.::-------===========++++++++++++++++++++*#### \n"
"%###*++++++++++++++++++=========:==-:..#*%%##*****#%%#+:------============+=+++++++++++++++++++*###% \n"
"%###*+++++++++++++++++++++=========-:.#**%#*+******=%%*+-----=========+=+++:+++++++++++++++++++*###% \n"
"%###*+++++++++++++++++++++==========-:%%%#********#%%%#*=-+*=--========++++-+++++++++++++++++++*###% \n"
"%###*++++++++++++++++++++++=========--#%###********##%%%*+=-...:-:+-===++++++++++*+++-+++++++++*###% \n"
"####*++++++++++++++++++++++=========+*#%###****+****#%%%%#=-:.:-.::.#+++++++++***%*++=++++++++**###% \n"
"%##***++++++++++++++++++++++=========#%%*##**+++****##%##%-::::::.::.+*+++:++%@@#+@+++++++++++**###% \n"
"%###**+++++++++++++++++++++++=======+#%%###**++*****####*:----::::::::.%=+-++++*%*@%++++++++++**###% \n"
"%###**++++++++++++++++++++++++======##%%###*********####=:::--====-----::-+++++%@@@%#=++++++++**###% \n"
"%###**++++++++++++++++++++++++++++==%#%%###**********###=:::::-+**++*=-:::.+%%@@@@@+-:++++++++**###% \n"
"%%##**+++++++++==+++++++++++++++++++*%%%####*******#####=:::::::-++#####=##.-%%@@@@#-@++=+++++*####% \n"
"%####*++++++++++++++++++++++++++++++@%%%#######**#######-::::::::--*#%%#+*+==:.***@@=+ =*++++**####% \n"
"#####**+++++++++++++++++++++++++++++%%%%###############+---::-::---==*=@*##*=+==-:+=. -*-++++**##### \n"
"#####**+++++++++++++++++++++++++++++%#%%###############+::----------=- @@%%###*++==#:-@=#*+++**####* \n"
"######*+++++++++++++++++++++++++++++%*%%%############%#=::*==---:--==.###@%%%%##*+@*+  :+:++**#####* \n"
"######**++++++++++++++++++++++++++++##%%%%%%######%%%%*:::-#+===:==+:=%*###%*%#%%@%: .:+++++**#####* \n"
"##*=###**+++++++++++++++++++++++++++*%#%%%%%%%%%%%%%%%+::::-%+++-==..#*##*%:-#@@@@:::%#++++**####*#* \n"
"#**####***++++++++++++++++++++++++++++#@%%%%%%%%%%%%%#:::::::*#+=+:.@%##*%@.#* +%*@@#++++++**#####*# \n"
"**=#####**++++++++++++++++++++++++++++#%%%%%##%%%%%%#+::::::::=#=+-#%%%%%@-#=. .*@%*++++++**######** \n"
"**#**####**++++++++++++++++++++++++++++%%%%%+#%%%%%%+---:-:::::--+*+*####*=-:   -@*++++++**####**#** \n"
"*=++######**+++++++++++++++++++++++++++@*%@%%%%%%%%*==-------::-::--:---:::-:..:=+++++++**######**** \n"
"+++*#*#####**++++++++-++++++++++++++++++#%=%%%%%%%#+====---=---:::::::::::----=+*+++++**######*#*+++ \n"
"++*#*****####**++++++-++++++++++++++++++*#:%%%%%%#++++======------:--------==++#*++++**###******#*++ \n"
"++*********###**+++++++++++++++++++++++++++*@%%#**++++++===+==============++*+%*++++**###*********++ \n"
"+++++++++++******+++++++++++++++++++++++++++#+******+++++++**===++=+=+++==**+++:++++******+++++++*++ \n"
"=+++++++++++++++++++++++++++++++++=++++=++++++%++********+++++++*===++***++*#+++=++**++++++++++++++= \n"
"=++============--:+##*+===+++++============++++++%+******+****++====+*#**#-+=====+++++++=========+== \n"
"============-::*+--======+=-:-#@%+===============++@*##**#*****++==+***@+=:========================= \n"
"=======--====-::::-----=-+#*******#=--------------=%%@#=*#####@#**+*+#=------=:=========-------=-==- \n"
"============+-::::-----====+++++***@------------===##%+=*###*++*#*##---=-=-==============---======== \n"
"=============:::::-----====+++++***=-----------=***#*#%#%-------+*#+================================ \n"
"=============-:::------====+++++***#===========-.:+++++#@====+##@**@%=============================== \n"
"+++====:=====+:::------====+++++***#===========*=.=++++++===**++++###-=+=====-===================+++ \n"
"++++====++=+=*:-------=====+++++*****++++++++++*=.:=+++==+++=:=::+#++=+++++++++++++++===+=+=====++++ \n"
"++++++++++++++--------====+++++++***%+++++++++++-.:-+++-=++++.:::-++#=+++++******+++++++++++++++++++ \n"
"++++++++++++++-------=====+++++++***-+++++++++++-.::=++#*++++:.::=*+*#*************+++++++++++++++++ \n"
"++++*+++*******-----=====-++++++****#+++++======-.+:-++*+====#.::-##**+++++****************+++++++++ \n"
"++************#----=====+=++++++*****====-------:.:=-++=-----#.::-++=--=======++***********+***+++++ \n"
"+**************-========++++++++*****=------:::==.:+:+=-:::::#..:-++:----------==+***************++* \n"
"+**************========+++++++++****#+::-:::::=:..:-:++-:::::#..:-+++--------===-+****************++ \n"
"+**********++++*======+++++++++******-.::::*=.+...:=*++=:::::=..:-++%--------==-==+++*****=*******++ \n"
"+**+***+++=====+=====+++++++++*******=::::.-:...:::=++++----#...:-=+*---:.-----:-=====+++++***+***++ \n"
"+*+++++============++++++++++********=::.#:...-:::++++**=+=#..::*=++.:-:::---:.----====-==++**+**++= \n"
"+++========-:-==+++++++++++++*********:::*++:---++##%##*=*-...::-**=.-:.-::-::----:--====:===+++*+++ \n"
"++=======:=--=:=##%**##++++++********#-==:#**#%%#*#****+....::-=+**#:--::::-::----.---=======+++*++- \n"
"+========-====-=#%%####%+*#@#+*******+++*+::::::+*+++-*@-..:=++++%##%===:::-:---:-----=-==--:+++*++- \n"
"++++++-=======-=**##%@%%%###%%*#%@%*###=#*--*#@%+:--=++-:--#%%*+@***+::-:::-:--------======++++=++++ \n"
"+++++++++===-=-=++****+**#%%%#%%%%%*#%++##%%###+=:--=--++#*+++**++++=:::::-::-:=----==--=++*---::+++ \n"
"++++*+++++++====+++++++******++####%@@@###*+==--::--=::-----========-:::::--------===++***++---::+++ \n"
"+++++++*+*****++++++++++++++++*++******+++--:.:-+-..:==-:....:--=++=-:::::-----====+*******++:-:++++ \n"
"+++++++++***#*******+++=++++--=+++++++-:::::::::::-====:..:::::-===-::.:::----=++**********+++++++++ \n"
"***++++++*###*************++===++++++=:::::::::::--====----=-:::-==-:::::------==**********++++++++* \n"
"***+**++**###****************++++++++=:::::::::::-===+==::::::::-=+=-::::--------=****#*++*+*++*++**\n";
  printf("%s", ascii_art_pato);
system("pause");
exit(0);
}

void normalizarData(char *dataOriginal, char *dataNormalizada) {
  char temp[50];

  // Copia para um buffer temporário pra usar o strtok -> (função para dividir a string)

  strcpy(temp,dataOriginal);

  // Normaliza as datas de 18/2/2022 -> 18/02/2022 por exemplo

  char *dia_str = strtok(temp,"/");
  char *mes_strstr = strtok(NULL,"/");
  char *ano_str = strtok(NULL,"/");

  int dia = atoi(dia_str);
  int mes = atoi(mes_strstr);
  int ano = atoi(ano_str);

  // Formata a string com os zeros a esquerda para os dias  e mês

  sprintf(dataNormalizada,"%02d/%02d/%04d", dia, mes, ano);
}

void exportarPorData() {
  system("cls");
  char dataBusca[50];
  printf("Digite a data a ser exportada (DD/MM/AAAA): ");
  scanf("%s", dataBusca);

  char dataConvertida[16];
  snprintf(dataConvertida, sizeof(dataConvertida), "export_%.4s%.2s%.2s.csv", dataBusca + 6, dataBusca + 3, dataBusca);

  FILE *file = fopen("bankdataset.dat","rb");
  FILE *csv = fopen(dataConvertida, "w");
  registro r;

  if (file == NULL ) {
    printf("Arquivo nao encontrado!");
    system("pause");
    return;
  }

  if (file && csv) {
    fprintf(csv,"date,domain,locatiom,value,transaction_count\n");

    while (fread(&r, sizeof(r), 1, file) == 1) {
      char dataRegistroNormalizada[50];
      normalizarData(r.date, dataRegistroNormalizada);

      if ((strcmp)(dataRegistroNormalizada, dataBusca) == 0) {
        fprintf(csv,"%s,%s,%s,%d,%d\n",r.date, r.domain, r.location,r.value, r.transaction_count);
      }
    }
    fclose(file);
    fclose(csv);
    printf("Arquivo \"%s\" exportado com sucesso!\n", dataConvertida);
    system("pause");
    system("cls");
  } else {
    printf("Arquivo corrompido ou não encontrado");
    system("pause");
    system("cls");
  }
}

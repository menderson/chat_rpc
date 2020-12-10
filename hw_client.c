#include <rpc/rpc.h>
#include <stdio.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

// variaveis de controle
int id_user;
int ultima_msg_recebida = 1;

int main(int argc, char *argv[]) {
  // Estrutura RPC de comunicação
  CLIENT *cl;

  // Arquivo
  FILE *file;

  // Parâmetros das funções
  // struct param2 par_f2;
  char *par_f1 = (char *)malloc(256 * sizeof(char));
  char *par_f2 = (char *)malloc(1024 * 1024 * sizeof(char));

  // Retorno das funções
  char **ret_f0 = NULL;
  int *ret_f1 = NULL;
  int *ret_f2 = NULL;
  char **ret_f3 = NULL;
  int *ret_f4 = NULL;

  // Verificação dos parâmetros oriundos da console
  if(argc != 3) {
    printf("ERRO: ./client <hostname>\n");
    exit(1);
  }

  // Conexão com servidor RPC
  cl = clnt_create(argv[1], PROG, VERS, "tcp");
  if(cl == NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  // Nome do usuario
  printf("Digite seu nome:\n");
  scanf("%s", par_f1);

  // id usuario
  ret_f4 = func4_1(NULL, cl);
  id_user = *ret_f4;

  // Funções chat
  while(1) {
    int comando;
    printf("\n0-Enviar msg\n1-Receber as msgs\n2-Fechar\n\n");
    scanf("%d", &comando);
    if(comando == 2) break;

    if(comando == 1) {
      // RECEBE A TAG DO ARQUIVO
      ret_f0 = func0_1(NULL, cl);
      if(ret_f0 == NULL) {
        clnt_perror(cl, argv[1]);
        exit(1);
      }

      // RECEBE O ARQUIVO
      ret_f3 = func3_1(NULL, cl);
      if(ret_f3 == NULL) {
        clnt_perror(cl, argv[1]);
        exit(1);
      }

      if(strcmp(*ret_f3, "") == 0) {
        printf("Arquivo vazio\n");
      } else {
        // Salva o arquivo
        FILE *fileREAD;
        char fileName[256];
        sprintf(fileName, "%s-%d.client", par_f1, ultima_msg_recebida);
        fileREAD = fopen(fileName, "w");
        fputs(*ret_f3, fileREAD);
        fclose(fileREAD);
        contador++;
      }
    }

    if(comando == 0) {
      // Envia o nome
      ret_f1 = func1_1(&par_f1, cl);
      if(ret_f1 == NULL) {
        clnt_perror(cl, argv[1]);
        exit(1);
      }

      // Envia msg
      printf("Digite o nome do arquivo para enviar: ");
      char file_name[256];
      scanf("%s", file_name);
      file = fopen(file_name, "r");
      if(file == NULL) {
        printf("Error: Na abertura do arquivo (%s)\n", file_name);
        exit(1);
      }
      char buffer[256];
      while(fgets(buffer, sizeof(buffer), file)) {
        sprintf(par_f2, "%s%s", par_f2, buffer);
      }
      fclose(file);
      ret_f2 = func2_1(&par_f2, cl);
      if(ret_f2 == NULL) {
        clnt_perror(cl, argv[1]);
        exit(1);
      }

      printf("Msg enviada\n");
    }
  }
  fclose(file);
  return 0;
}

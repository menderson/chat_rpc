
#include <rpc/rpc.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int id = 0;
int contador = 1;
char nick[256];
char fileName[256];

//%%%%%%%%%%%%%%% GUARDA NOME USUARIO %%%%%%%%%%%%%%%%%%%%%%%%%%
char **func0_1_svc(void *a, struct svc_req *req) {
  static char msg[256];
  static char *p;

  strcpy(msg, nick);
  p = msg;

  return (&p);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int *func1_1_svc(char **a, struct svc_req *req) {
  static int ret = 0;
  strcpy(nick, *a);
  return (&ret);
}

//%%%%%%%%%%%%%%%%%%%% RECEBE ARQUIVO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int *func2_1_svc(char **a, struct svc_req *req) {
  static int ret = 0;
  static int err = -1;
  FILE *file;
  sprintf(fileName, "%s-%d.serv", nick, contador);
  file = fopen(fileName, "w");

  fputs(*a, file);
  fclose(file);
  contador++;
  printf("Arquivo recebido de <%s>\n", nick);
  return (&ret);
}

//%%%%%%%%%%%%%%%%%%%%% ENVIA ARQUIVO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
char **func3_1_svc(void *a, struct svc_req *req) {
  char msg[1024 * 1025] = "";
  static char *p = "";
  FILE *file;
  file = fopen(fileName, "r");
  if(file == NULL) return (&p);
  char buffer[256];
  while(fgets(buffer, sizeof(buffer), file)) {
    sprintf(msg, "%s%s", msg, buffer);
  }

  p = msg;
  printf("Mendsagem de  <%s> enviada\n", nick);
  return (&p);
}

// retorna um id para o cliente
int *func4_1_svc(void *a, struct svc_req *req) {
  id++;
  return (&id);
}
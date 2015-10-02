/* Inicializa o pacote. Retorna "0" se inicializou corretamente;
   "-1" caso contrário. */
int so_init (void);

/* Cria uma thread cuja rotina de execução é apontada por "proc".
   A função retorna o TID (Thread Identification) da thread criada
   (valor positivo) ou "-1" em caso de erro. */
int so_create (void (*proc)(int), int arg);

/* Espera (fica parada) que a thread identificada pelo "tid" seja
   encerrada (so_exit). O estado de retorno é colocado em "*status".
   A função retorna "0" se bem sucedida e "-1" em caso de erro. */
int so_join (int tid, int *status);

/* Encerra, imediatamente, a thread onde foi chamada, sinalizando
   para um eventual "join" o encerramento da thread. */
void so_exit (int status);

/* A thread de onde foi chamada libera a CPU, ativando o escalonador. */
void so_yield (void);

/* Retorna o TID da thread de onde foi chamada. */
int so_getid (void);


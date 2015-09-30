#include "../include/pidata.h"

/*
void print_element(TCB_t *element);
TCB_t *new_element(TCB_t *element, int new_tid, int new_credCreate);
*/

TCB_t *new_element(TCB_t *element, int new_tid, int new_credCreate);
TCB_t *remove_element(TCB_t *first, TCB_t *deleted);
TCB_t *delete_element(TCB_t *first, TCB_t *deleted);
TCB_t *find_element(TCB_t *first, int credReal);
TCB_t *find_tid(TCB_t *first, int tid);
TCB_t *move_element(TCB_t *first, TCB_t *element, int credReal);
TCB_t *insert_element(TCB_t *first, TCB_t *element);
TCB_t *insert_new(TCB_t *first, int credCreate, int tid);
void print_element(TCB_t *element);
void print_list(TCB_t *first);

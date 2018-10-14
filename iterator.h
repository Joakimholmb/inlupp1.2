#pragma once
#include "common.h"

typedef struct link link_t;
typedef struct iter ioopm_list_iterator_t;
typedef struct list ioopm_list_t;

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);

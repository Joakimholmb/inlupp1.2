#ifndef __INLUPP1_H__
#define __INLUPP1_H__
#pragma once
#include <stdbool.h>

//typedef struct iter ioopm_list_iterator_t; TODO HA I ITERATOR 

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, int element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
int ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);

#endif

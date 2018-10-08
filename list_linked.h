#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "common.h"

typedef struct link link_t;
typedef struct list ioopm_list_t;
typedef struct iter ioopm_list_iterator_t; //TODO: FULT, HA I ITERATOR.H

typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);

// ************** LIST_LINKED FUNC DECLARATIONS ************

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function *compare);
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, size_t index, elem_t value);
elem_t ioopm_linked_list_get(ioopm_list_t *list, size_t index);
void ioopm_linked_list_append(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_clear(ioopm_list_t *list);
elem_t ioopm_linked_list_remove(ioopm_list_t *list, size_t index);

int ioopm_linked_list_size(ioopm_list_t *list);
bool ioopm_linked_list_is_empty(ioopm_list_t *list);
bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element, bool (*compare)(elem_t, elem_t));

bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x);
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x);
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(elem_t *, elem_t *), void *x);


// ************** ITERATOR FUNC DECLARATIONS ************

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);
//static link_t *insert_aux(link_t *link, int elem);


/*
ioopm_list_t *ioopm_linked_list_create();
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value);
int ioopm_linked_list_get(ioopm_list_t *list, int index);
void ioopm_linked_list_append(ioopm_list_t *list, int value);
void ioopm_linked_list_prepend(ioopm_list_t *list, int value);
void ioopm_linked_list_clear(ioopm_list_t *list);
elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index);

int ioopm_linked_list_size(ioopm_list_t *list);
bool ioopm_linked_list_is_empty(ioopm_list_t *list);
bool ioopm_linked_list_contains(ioopm_list_t *list, int element);
bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(int, int), void *x);
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(int, int), void *x);
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(int *, int *), void *x);

// ************** ITERATOR FUNC DECLARATIONS ************ TODO, FLYTTA TILL ITERATOR.H

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, int element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
int ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);
*/
//#endif

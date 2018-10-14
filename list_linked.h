#pragma once
#include "common.h"

typedef struct link link_t;
typedef struct list ioopm_list_t;

// ************** LIST_LINKED FUNC DECLARATIONS ************

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function compare);
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, size_t index, elem_t value);
elem_t ioopm_linked_list_get(ioopm_list_t *list, size_t index);
void ioopm_linked_list_append(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_clear(ioopm_list_t *list);
elem_t ioopm_linked_list_remove(ioopm_list_t *list, size_t index);

int ioopm_linked_list_size(ioopm_list_t *list);
bool ioopm_linked_list_is_empty(ioopm_list_t *list);
bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element);

bool ioopm_linked_list_all(ioopm_list_t *list, void *x);
bool ioopm_linked_list_any(ioopm_list_t *list, void *x);
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(elem_t *, elem_t *), void *x);

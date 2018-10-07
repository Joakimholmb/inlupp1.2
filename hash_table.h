#pragma once

//#ifndef __INLUPP1_H__
//#define __INLUPP1_H__
#include <stdbool.h>
#include "list_linked.h"

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

//extern bool *ioopm_apply_function;
//extern void *ioopm_apply_function2;

typedef bool(*ioopm_apply_function)(int key, char *value, void *extra);
typedef void(*ioopm_apply_function2)(int key, char **value, void *extra);


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);
ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);
//int *ioopm_hash_table_keys(ioopm_hash_table_t *ht);
char **ioopm_hash_table_values(ioopm_hash_table_t *ht);
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key);
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value);
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function2 apply_fun, void *arg);

ioopm_list_t *ioopm_hash_table_keys2(ioopm_hash_table_t *ht);


//#endif

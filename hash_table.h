#pragma once
#include "common.h"
#include "list_linked.h"
#include <stdbool.h>
#include <stdlib.h>


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

ioopm_hash_table_t *ioopm_hash_table_create(hash_func func);
entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key);
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function2 apply_fun, void *arg);

int string_knr_hash(elem_t str);

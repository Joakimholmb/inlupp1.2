/*
TODO:

Fixa apply_to_all så tester funkar.
Fixa ioopm_hash_table_all tester.
Lägg till Typ till ioopm_apply func & ändra i h.- och .c filen där de förekommer.
Hur placera in den i h. filen.

*/


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include "list_linked.h"
#include "hash_table.h"
#define No_Buckets 17

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[17];
  size_t size;
  hash_func *hash_function; 
};

// FUNCTION DECLARATIONS

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);
entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key);
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);
static elem_t destroy_next_entry(entry_t *entry);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
static void clear_bucket(entry_t *entry, ioopm_hash_table_t *ht);
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
static bool key_equiv(elem_t key, elem_t value_ignored, void *x);
static bool value_equiv(elem_t key_ignored, elem_t value, void *x);
elem_t string_knr_hash(elem_t str);

// **************************

//        FUNCTIONS

// **************************

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(0);
  int j = 0;
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *dummy_entry = &ht->buckets[i];
      entry_t *entry = dummy_entry->next;
      while (entry != NULL)
        {
          
          ioopm_linked_list_insert(list, j, entry->key);
            ++j;
            entry = entry->next;
        }
    }
  
  return list;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{ 
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));

  return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{

  //elem_t hash = string_knr_hash(key);
  //int bucket = hash.i % No_Buckets;
  
  int bucket = key.i % No_Buckets;

  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  if (next != NULL && next->key.i == key.i)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->size += 1;
    }
  
}
/*
  static entry_t *find_previous_entry_for_key(entry_t *entry, int key)
{
   entry_t *cursor = entry;
     
   while(cursor->next != NULL && key > cursor->next->key)
    {
      if(key == cursor->next->key)
        {
          return cursor;
        }     
      else
        {
          cursor = cursor->next;
        }
    }
   
  return cursor;
}
*/
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
  
}


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key.i % No_Buckets], key);
  entry_t *next = tmp->next;

  if (next && next->value.i && next->key.i == key.i)
    {
      return (option_t) { .defined = true, .value = next->value };
    }
  else
    {
      return (option_t) { .defined = false };
    }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  entry_t *previous = find_previous_entry_for_key(&ht->buckets[key.i % No_Buckets], key);
  
  if(previous->next != NULL)
    {
      elem_t value = destroy_next_entry(previous);
      ht->size -= 1;
      return value;
    }
  
  return (elem_t)0;
}



static elem_t destroy_next_entry(entry_t *entry)
{
  entry_t *next_entry = entry->next;

  elem_t value = next_entry->value;
  entry->next = next_entry->next;
  free(next_entry);
  return value;

  
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for(int i = 0; i<No_Buckets; ++i)

    {
      entry_t *bucket = &ht->buckets[i];
      entry_t *entry = bucket->next;
      bucket->next = NULL;
      clear_bucket(entry, ht);
    }
  free(ht);
  return;
}

static void clear_bucket(entry_t *entry, ioopm_hash_table_t *ht)
{
  if(entry == NULL)
    {
      return;
    }
  else
    {
      while(entry != NULL)
        {
          entry_t *var = entry->next;
          free(entry);
          entry = var;
          ht->size -= 1;
        }
    }
  return;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  
  return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *bucket = &ht->buckets[i];
      entry_t *entry = bucket->next;
      bucket->next = NULL;
      clear_bucket(entry, ht);
    }
  return;
}
/*
int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *keys = calloc(1, sizeof(ht->size));
  int j = 0;
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *dummy_entry = &ht->buckets[i];
      entry_t *entry = dummy_entry->next;
      while (entry != NULL)
        {
          keys[j] = entry->key;
          ++j;
          entry = entry->next;
        }
    }
  return keys;
}
*/
// OLD VALUE FUNC BEFORE LINKED LIST RETURN HEJ
/*
elem_t **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  elem_t **values = calloc(1, sizeof(ht->size));
  int j = 0;
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *dummy_entry = &ht->buckets[i];
      entry_t *entry = dummy_entry->next;
      while (entry != NULL)
        {
          values[j] = entry->value;
          ++j;
          entry = entry->next;
        }
    }
  return values;
}
*/

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(0);
  int j = 0;
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *dummy_entry = &ht->buckets[i];
      entry_t *entry = dummy_entry->next;
      while (entry != NULL)
        {
          ioopm_linked_list_insert(list, j, entry->value);
          ++j;
          entry = entry->next;
        }
    }
  return list;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  //return ioopm_hash_table_lookup(ht, key).defined;
  return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  return ioopm_hash_table_any(ht, value_equiv, &value);
  /*
  char **values = ioopm_hash_table_values(ht);
  int i = 0;

  for(; i<ht->size; ++i)
    {
      if(value == values[i])
        {
          free(values);
          return true;
        }
    }
  free(values);
  return false;
  */
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg)
{
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *bucket  = &ht->buckets[i];
      entry_t *entry = bucket->next;
      
      while(entry != NULL)
        {
          if(!(pred(entry->key, (entry->value), arg)))
            {
              return false;
            }
          entry = entry->next;
        }     
    }
  return true;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg)
{
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *entry  = &ht->buckets[i];
      entry = entry->next;
      while(entry != NULL)
        {
          if(pred(entry->key, (entry->value), arg) == true)
            {
              return true;
            }
          else
            {
              entry = entry->next;
            }
        }     
    }
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function2 apply_fun, void *arg)
{
  for(int i = 0; i<No_Buckets; ++i)
    {
      entry_t *bucket  = &ht->buckets[i];
      entry_t *entry = bucket->next;
      while(entry != NULL)
        {
          apply_fun(entry->key, &(entry->value), arg);
          entry = entry->next;
        }     
    }
  return;
}

static bool key_equiv(elem_t key, elem_t value_ignored, void *x)
{
  
  elem_t *other_key_ptr = x;
  elem_t other_key = *other_key_ptr;
  if (key.i == other_key.i)
    {
      return (key.i == other_key.i);
    }
  else
    {
      elem_t key_compare1 = string_knr_hash(key);
      elem_t key_compare2 = string_knr_hash(other_key);
      return (key_compare1.i == key_compare2.i);
    }
  return false;
  
  //return (key.i == other_key.i || key.c == other_key.c);
}

static bool value_equiv(elem_t key_ignored, elem_t value, void *x)
{
  elem_t *other_value_ptr = x;
  elem_t *other_value = other_value_ptr;
  return value.c == (*other_value).c;
}

// **************** RECURSIVE find_previous_entry_for_key, NOT ORIGINAL

entry_t *find_previous_entry_for_key(entry_t *entry, elem_t entrykey)
{

  entry_t *cursor = entry;
  entry_t *entry_next = cursor->next;

  if(entry_next == NULL || entry_next->key.i == entrykey.i || entrykey.i < entry_next->key.i)
    {
      return cursor;
    }
  return find_previous_entry_for_key(entry_next, entrykey);
}

// **********************

elem_t string_knr_hash(elem_t str)
{
  /*
  elem_t result = (elem_t)0;
  elem_t ascii = (elem_t)32;
  */
  elem_t result = {.i = 0};
  elem_t ascii = {.i = 32};
  char *s = str.c;
  
  do
    {
      result.i = result.i * ascii.i + *s;
    }
  while (*++s != '\0');
  return result;
}

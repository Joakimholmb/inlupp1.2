#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include "hash_table.h"

#define No_Buckets 17

// FUNCTION DECLARATIONS

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
static entry_t *find_previous_entry_for_key(entry_t *entry, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);
static char *destroy_next_entry(entry_t *entry);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
static void clear_bucket(entry_t *entry);



// **************************

//        FUNCTIONS

// **************************



ioopm_hash_table_t *ioopm_hash_table_create()
{ 
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));

  return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  int bucket = key % No_Buckets;
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }

}

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

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
  
}


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);
  entry_t *next = tmp->next;

  if (next && next->value && next->key == key)
    {
      return (option_t) { .defined = true, .value = next->value };
    }
  else
    {
      return (option_t) { .defined = false };
    }
}

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  entry_t *previous = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);
  
  if(previous->next != NULL)
    {
      char *value = destroy_next_entry(previous);
      return value;
    }

  return NULL;
}

static char *destroy_next_entry(entry_t *entry)
{
  entry_t *next_entry = entry->next;

  char *value = next_entry->value;
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
      clear_bucket(entry);
    }
  free(ht);
  return;
}

static void clear_bucket(entry_t *entry)
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
        }
    }
  return;
}

// **************** REKURSIV find_previous_entry_for_key, EJ ORGINAL
/*
  static entry_t *find_previous_entry_for_key(entry_t *entry, int entrykey)
  {

  entry_t *cursor = entry;

  if(cursor->next == NULL)
  {
  return cursor;
  }
  if(cursor->next->key == entrykey)
  {
  return cursor;
    }
  if(entrykey < cursor->next->key)
    {
      return cursor;
    }
  return find_previous_entry_for_key(cursor->next, entrykey);
}
*/
// **********************

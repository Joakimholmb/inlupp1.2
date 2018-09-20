#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include "inlupp1.h"

// STRUCT DECLARATIONS
/*
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[17];
};

typedef struct option option_t;
struct option
{
  bool defined;
  char *value;
};
*/

// FUNCTION DECLARATIONS

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
static entry_t *find_previous_entry_for_key(entry_t *entry, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);
char *entry_destroy(entry_t *previous);
void print_bucket(int num_buckets, entry_t *entry);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
void clear_bucket(entry_t *entry);

// ********************* TEST CODE

// *********************

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  //if (next != NULL && next->key == key)
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }

}


// ORGINAL, TA BORT KOMMENTAR!!!!


static entry_t *find_previous_entry_for_key(entry_t *entry, int entrykey)
{
   entry_t *cursor = entry;
     
   while(cursor->next != NULL && entrykey > cursor->next->key)
    {
      if(entrykey == cursor->next->key)
        {
          return cursor;
        }     
      else
        {
          cursor = cursor->next;
        }
    }
   //printf("next key: %", cursor->next);
  return cursor;
}

// REKURSIV, EJ ORGINAL
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

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new = calloc(1, sizeof(entry_t));

 //entry_t *new = NULL;

  new->key = key;
  new->value = value;
  new->next = next;

  return new;
  
}


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % 17], key);
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
  entry_t *previous = find_previous_entry_for_key(&ht->buckets[key % 17], key);
  //entry_t *entry = previous->next;
  
  if(previous->next != NULL)
    {
      char *value = entry_destroy(previous);
      return value;
    }

  return NULL;

  
}

char *entry_destroy(entry_t *previous)
{
  entry_t *entry = previous->next;

  char *value = entry->value;
  previous->next = entry->next;
  free(entry);
  return value;

  
}

void print_bucket(int num_buckets, entry_t *entry)
{
  entry_t *adress;
  adress = entry;
  for (int i = 0; i < num_buckets; ++i)
    {
      printf("Key: %d, Value %s\n", adress->key, adress->value);
      adress = adress->next;
    }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for(int i = 0; i<17; ++i)
    {
      entry_t *bucket = &ht->buckets[i];
      entry_t *entry = bucket->next;
      clear_bucket(entry);
    }
  free(ht);
  return;
}

void clear_bucket(entry_t *entry)
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


//int main(int argc, char *argv[])
//{


  //entry_t a = { .key = 1, .value = argv[1] };

  /*
  entry_t b = { .key = 2, .value = argv[2], .next = &a };
  entry_t c = { .key = 3, .value = argv[3], .next = &b };
  entry_t d = { .key = 4, .value = argv[4] };
  entry_t e = { .key = 5, .value = argv[5] };
  entry_t f = { .key = 6, .value = argv[6], .next = &e };
  ioopm_hash_table_t ht = { .buckets = { 0 } };
  ht.buckets[3] = c;
  ht.buckets[8] = d;
  ht.buckets[15] = f;
  */
 

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  //ioopm_hash_table_insert(ht, 1, argv[1]);
  //entry_t new = entry_create(2, argv[1], NULL);
  entry_t a = { .key = 1, .value = argv[1] };
  ht->buckets[0] = a;
  printf("Key: %d\nVal: %s\n", a.key, a.value);
  */
  //entry_t *new = entry_create(2, argv[1], NULL);
 

  //ioopm_hash_table_insert(ht, 4, "2342");

  /*
  printf("Key: %d\n", ht->buckets[5].key);
  printf("Key: %d\n", ht->buckets[5].next->key);
  printf("Key: %d\n", ht->buckets[5].next->next->key);
  printf("Key: %d\n", ht->buckets[5].next->next->next->key);
  
  
  while(ht->buckets[5].next != NULL)
    {
      printf("Key: %d\n", ht->buckets[5].key);
    }
  
  
  
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  nentry_t c = { .key = 8, .value = "42424", .next = NULL };
  entry_t a = { .key = 6, .value = "23", .next = &c };
  entry_t b = { .key = 4, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;
  //entry_t *hitta = find_previous_entry_for_key(&d, 6);
  //printf("Key: %d\n", hitta->key);

  ioopm_hash_table_insert(ht, 6, "123");

  int buck = 5 % 17;

  entry_t *hitta = find_previous_entry_for_key(&ht->buckets[buck], 7);
  printf("Key: %d\n", hitta->key);
  */

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 8, .value = "42424", .next = NULL };
  entry_t a = { .key = 6, .value = "23", .next = &c };
  entry_t b = { .key = 4, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;
  //entry_t *hitta = find_previous_entry_for_key(&d, 5);
  //printf("Key: %d\n", hitta->key);

  ioopm_hash_table_insert(ht, 6, "123");

  //int buck = 5 % 17;

  //entry_t *hitta = find_previous_entry_for_key(&ht->buckets[buck], 7);
  //printf("Key: %d\n", hitta->key);
  */



  // TESTA REKURSIV!!!!

  // CHECKING KEY 40 after INSERT 40

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  ioopm_hash_table_insert(ht, 40, "123");
  printf("Key: %d, Value1: %s\n", d.key, d.value);
  printf("Key: %d, Value2: %s\n", d.next->key, d.next->value);
  printf("Key: %d, Value3: %s\n", d.next->next->key, d.next->next->value);
  printf("Key: %d, Value4: %s\n", d.next->next->next->key, d.next->next->next->value);
  printf("Key: %d, Value5: %s\n", d.next->next->next->next->key, d.next->next->next->next->value);
  */

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  ioopm_hash_table_insert(ht, 23, "123");
  printf("Key: %d, Value1: %s\n", d.key, d.value);
  printf("Key: %d, Value2: %s\n", d.next->key, d.next->value);
  printf("Key: %d, Value3: %s\n", d.next->next->key, d.next->next->value);
  printf("Key: %d, Value4: %s\n", d.next->next->next->key, d.next->next->next->value);
  printf("Key: %d, Value5: %s\n", d.next->next->next->next->key, d.next->next->next->next->value);
  */



  
  // RELEVANT TEST CASE BELOW:

  // CHECKING KEY 40 after INSERT 40

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  ioopm_hash_table_insert(ht, 40, "123");
  option_t varde1 = ioopm_hash_table_lookup(ht, 23); // Kolla innanvärde
  option_t varde2 = ioopm_hash_table_lookup(ht, 40);
  option_t varde3 = ioopm_hash_table_lookup(ht, 57); // kolla eftervärde
  printf("Key1: %d Value1: %s\n", varde1.value);
  printf("Key1: %d Value2: %s\n", varde2.value);
  printf("Key1: %d Value3: %s\n", varde3.value);
  */

  // CHECKING KEY 23 after INSERT 23, ANPASSA EFTER DENNA?

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  option_t varde1 = ioopm_hash_table_lookup(ht, 6); // Kolla innanvärde
  option_t varde2 = ioopm_hash_table_lookup(ht, 23);
  option_t varde3 = ioopm_hash_table_lookup(ht, 57); // Kolla eftervärde

  printf("Before Value1: %s\n", varde1.value);
  printf("Before Value2: %s\n", varde2.value);
  printf("Before Value3: %s\n", varde3.value);

  ioopm_hash_table_insert(ht, 23, "666");
  option_t varde4 = ioopm_hash_table_lookup(ht, 6); // Kolla innanvärde
  option_t varde5 = ioopm_hash_table_lookup(ht, 23);
  option_t varde6 = ioopm_hash_table_lookup(ht, 57); // Kolla eftervärde

  printf("After Value1: %s\n", varde4.value);
  printf("After Value2: %s\n", varde5.value);
  printf("After Value3: %s\n", varde6.value);
  */

  // TEST FOR REMOVE

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;
  print_bucket(4, &ht->buckets[6 % 17]);

  ioopm_hash_table_insert(ht, 40, "123");
  print_bucket(5, &ht->buckets[6 % 17]);
  
  char *remove = ioopm_hash_table_remove(ht, 6);
  printf("Removed value: %s\n", remove);
  print_bucket(4, &ht->buckets[6 % 17]);
  */

  // DETTA ÄR BRA REMOVE TEST
  
  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t *c = entry_create(57, "42424", NULL);
  entry_t *a = entry_create(23, "223", c);
  entry_t *b = entry_create(6, "5555", a);
  entry_t *d = entry_create(0, NULL, b);
  printf("\nCREATE:\n");
  ht->buckets[6] = *d;
  print_bucket(4, &ht->buckets[6 % 17]);

  
  printf("\nINSERT KEY 40, VALUE 123:\n");
  ioopm_hash_table_insert(ht, 40, "123");
  print_bucket(5, &ht->buckets[6 % 17]);
  
  printf("\nREMOVE KEY 6, VALUE 5555:\n");
  char *remove = ioopm_hash_table_remove(ht, 6);
  print_bucket(4, &ht->buckets[6 % 17]);
  
*/
  
  
  //*********************************

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t *c = entry_create(57, "42424", NULL);
  entry_t *a = entry_create(23, "223", c);
  entry_t *b = entry_create(6, "5555", a);
  entry_t *d = entry_create(0, NULL, b);
  printf("\nCREATE:\n");
  ht->buckets[6] = *d;
  print_bucket(4, &ht->buckets[6 % 17]);

  printf("\nDESTROY HASH TABLE:\n");
  ioopm_hash_table_destroy(ht);
  free(ht);

  for(int i=0; i<17; ++i)
    {
      print_bucket(1, &ht->buckets[i % 17]);
    }
  print_bucket(4, &ht->buckets[6 % 17]);
  */

  //**************************** DESTROY HASHTABLE WITH INSERTIONS INSTEAD
  /*
  
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  ioopm_hash_table_insert(ht, 6, "5555");
  ioopm_hash_table_insert(ht, 23, "223");
  ioopm_hash_table_insert(ht, 40, "666");
  ioopm_hash_table_insert(ht, 57, "42424");
  ioopm_hash_table_insert(ht, 40, "123");
 
  printf("\nDESTROY HASH TABLE:\n");
  ioopm_hash_table_destroy(ht);
  */
    
  // return 0;
  
  



  // }






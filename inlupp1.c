#include <stdlib.h>
#include <stdio.h>

// STRUCT DECLARATIONS

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

// FUNCTION DECLARATIONS

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
static entry_t *find_previous_entry_for_key(entry_t *entry, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

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
      puts("Når if-sats");
      next->value = value;
    }
  else
    {
      puts("når else sats");
      entry->next = entry_create(key, value, next);
    }

}

static entry_t *find_previous_entry_for_key(entry_t *entry, int entrykey)
{
  /*
  entry_t *cursor = entry;
  //entry_t *next = cursor->next;
  entry_t *tmp = cursor;
  while(cursor->next != NULL && entrykey <= cursor->next->key)
    {
      if(entrykey == cursor->next->key)
        {
          return cursor;
        }
      else
        {
          tmp = cursor;
          cursor = cursor->next;
        }
    }
  return tmp;
  */
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

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new = calloc(1, sizeof(entry_t));

 //entry_t *new = NULL;

  new->key = key;
  new->value = value;
  new->next = next;

  return new;
  
}

char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(ht->buckets[key % 17], key);
  entry_t *next = tmp->next;

  if (next && next->key == key)
    {
      /// If entry was found, return its value...
      return next->value;
    }
  else
    {
      /// ... else return NULL
      return NULL; /// hmm...
    }
}

int main(int argc, char *argv[])
{
  
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
  entry_t c = { .key = 8, .value = "42424", .next = NULL };
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
  
  


  
  
  return 0;
}

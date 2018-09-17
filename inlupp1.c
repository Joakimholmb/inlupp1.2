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
entry_t *entry_create(int key, char *value, entry_t *next);
entry_t *find_previous_entry_for_key(entry_t *entry, int key);

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
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }

}

entry_t *find_previous_entry_for_key(entry_t *entry, int entrykey)
{
  entry_t *cursor = entry;
  entry_t *next = cursor->next;
  entry_t *tmp = cursor;
  while(next != NULL && entrykey <= next->key)
    {
      if(entrykey == next->key)
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
}

entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new = NULL;

  new->key = key;
  new->value = value;
  new->next = next;

  return new;
  
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

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  //ioopm_hash_table_insert(ht, 1, argv[1]);
  entry_t *new = entry_create(2, argv[1], NULL);
  ht->buckets[0] = *new;
  printf("Key: %d\nVal: %s\n", new->key, new->value);
  
  return 0;
}

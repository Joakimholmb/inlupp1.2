#ifndef __INLUPP1_H__
#define __INLUPP1_H__
#include <stdbool.h>

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

#endif

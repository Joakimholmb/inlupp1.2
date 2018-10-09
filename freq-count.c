#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
//#include "list_linked.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

struct entry
{
  elem_t key;       // holds the key
  elem_t *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[17];
  size_t size;
  hash_func *hash_function; 
};

struct link
{
  elem_t element;
  link_t *next;
};

struct list
{
  link_t *first;
  size_t size;
  link_t *last;
  ioopm_eq_function *func;
};

struct iter 
{
  link_t *prev;
  link_t *current;
  ioopm_list_t *list;
};

//****************************************

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(* (char * const *) p1, * (char * const *) p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  printf("%s\n", word);
  elem_t key = (elem_t*) { .buf = word};
  if(ioopm_hash_table_has_key(ht, key))
    {
      entry_t *previous = find_previous_entry_for_key(&ht->buckets[0], key);
      puts(key.buf);
      previous->next->value += 1;
      return;
    }
  else
    {
      ioopm_hash_table_insert(ht, key, (elem_t*)1);
    }
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true) 
    {
      char *buf = NULL;
      size_t len = 0;
      getline(&buf, &len, f);

      if (feof(f))
        {
          free(buf);
          break;
        }
      
      for (char *word = strtok(buf, Delimiters);
           word && *word;
           word = strtok(NULL, Delimiters)
           )
        {
          process_word(word, ht);
        }

      free(buf);
    }
  
  fclose(f);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(0);
  
  if (argc > 1)
    {
      for (int i = 1; i < argc; ++i)
        {
          process_file(argv[i], ht);
        }

      /// FIXME: obtain an array of keys to sort them
      ioopm_list_t *list = ioopm_hash_table_keys(ht);
      link_t *link = list->first;
      char *buf[555];
      for (int i = 0; i < list->size; ++i)
        {
          buf[i]  = link->element.buf;
          puts(buf[i]);
          link = link->next;
        }
      //char *keys[] = { "Bb", "Dd", "Aa", "Cc", "Hh", "Ff", "Gg" };
      sort_keys(buf, list->size);
      for (int i = 0; i < list->size; ++i) puts(buf[i]);
    }
  else
    {
      puts("Usage: freq-count file1 ... filen");
    }
}

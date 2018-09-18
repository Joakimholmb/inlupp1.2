#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CUnit/CUnit.h>

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

typedef struct option option_t;
struct option
{
  bool defined;
  char *value;
};

// FUNCTION DECLARATIONS

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
static entry_t *find_previous_entry_for_key(entry_t *entry, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

void test_func(void);
void test_lookup1();
// ********************* TEST CODE

void test_func(void)
{
  //TEST ioopm_hash_table_insert()
}

void test_lookup1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  CU_ASSERT(ioopm_hash_table_lookup(ht, 40).value == NULL);
  ioopm_hash_table_insert(ht, 40, "123");
  // ändrat lookup func att returnera option_t
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 23).value, "223");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 40).value, "123");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 57).value, "42424");

}

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
      printf("entry(previous) key: %d, and value: %s\n", entry->key, entry->value);
      entry->next = entry_create(key, value, next);
      printf("EFTER ENTRY CREATE: entry(previous) key: %d, and value: %s\n", entry->key, entry->value);
      printf("EFTER ENTRY CREATE: entry(next) key: %d, and value: %s\n", entry->next->key, entry->next->value);
      printf("EFTER ENTRY CREATE: entry(next->next) key: %d, and value: %s\n", entry->next->next->key, entry->next->next->value);
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
  printf("Key: %d\n", entry->key);

  if(cursor->next == NULL)
    {
      return cursor;
    }
  if(entrykey < cursor->next->key)
    {
      return cursor;
    }
  if(cursor->key == entrykey)
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

  if (next && next->value)
    {
      return (option_t) { .defined = true, .value = next->value };
    }
  else
    {
      return (option_t) { .defined = false };
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
  printf("Value1: %s\n", varde1.value);
  printf("Value2: %s\n", varde2.value);
  printf("Value3: %s\n", varde3.value);
  */

  // CHECKING KEY 23 after INSERT 23, ANPASSA EFTER DENNA?

  /*
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  entry_t c = { .key = 57, .value = "42424", .next = NULL };
  entry_t a = { .key = 23, .value = "223", .next = &c };
  entry_t b = { .key = 6, .value = "5555", .next = &a };
  entry_t d = { .key = 0, .value = NULL, .next = &b };
  ht->buckets[6] = d;

  ioopm_hash_table_insert(ht, 23, "666");
  option_t varde1 = ioopm_hash_table_lookup(ht, 6); // Kolla innanvärde
  option_t varde2 = ioopm_hash_table_lookup(ht, 23);
  option_t varde3 = ioopm_hash_table_lookup(ht, 57); // Kolla eftervärde

  printf("Value1: %s\n", varde1.value);
  printf("Value2: %s\n", varde2.value);
  printf("Value3: %s\n", varde3.value);
  */
  

  //*********************************

    
  return 0;
}

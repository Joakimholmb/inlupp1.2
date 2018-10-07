#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "hash_table.h"
#include "list_linked.h"
#include <errno.h>


// FIXA OPTION_T problem
struct option
{
  bool defined;
  char *value;
};

struct elem
{
  int32_t i;
};


//static FILE* temp_file = NULL;

int init_suite_insert(void)
{
  return 0;
}

int clean_suite_insert(void)
{
  return 0;
}

int init_suite_lookup(void)
{
  return 0;
}

int clean_suite_lookup(void)
{
  return 0;
}

int init_suite_remove(void)
{
  return 0;
}

int clean_suite_remove(void)
{
  return 0;
}

int init_suite_size(void)
{
  return 0;
}

int clean_suite_size(void)
{
  return 0;
}

int init_suite_clear(void)
{
  return 0;
}

int clean_suite_clear(void)
{
  return 0;
}

int init_suite_getkeys(void)
{
  return 0;
}

int clean_suite_getkeys(void)
{
  return 0;
}

int init_suite_getvalues(void)
{
  return 0;
}

int clean_suite_getvalues(void)
{
  return 0;
}

int init_suite_haskey(void)
{
  return 0;
}

int clean_suite_haskey(void)
{
  return 0;
}

int init_suite_hasvalue(void)
{
  return 0;
}

int clean_suite_hasvalue(void)
{
  return 0;
}

int init_suite_ApplyToAll(void)
{
  return 0;
}

int clean_suite_ApplyToAll(void)
{
  return 0;
}

int init_suite_All(void)
{
  return 0;
}

int clean_suite_All(void)
{
  return 0;
}

//************ TODO: EGNA TESTFUNKTIONER


void test_lookup1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i < 17; ++i) /// 18 is a bit magical 
    {
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i).value);
    }
  ioopm_hash_table_destroy(ht);
}



void test_insert1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  ioopm_hash_table_insert(ht, 6, "5555");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 6).value, "5555");
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, 40).defined, false)
  ioopm_hash_table_insert(ht, 40, "666");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 40).value, "666");
  ioopm_hash_table_insert(ht, 40, "123");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 40).value, "123");

  ioopm_hash_table_destroy(ht);
}

void test_remove1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 9, "595");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_remove(ht, 9), "595");
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, 9).defined, false);
  
  ioopm_hash_table_destroy(ht);
}

void test_remove2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, 15).defined, false);
  CU_ASSERT_EQUAL(ioopm_hash_table_remove(ht, 15), NULL);
  
  ioopm_hash_table_destroy(ht);
}

void test_size1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_size2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 14, "123");
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  
  ioopm_hash_table_destroy(ht);
}

void test_size3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 14, "123");
  ioopm_hash_table_remove(ht, 14);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 1, "123");
  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 3, "333");
  ioopm_hash_table_remove(ht, 3);

  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_getkeys1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 3, "333");
  ioopm_hash_table_insert(ht, 12, "421");

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 3);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 1).i, 12);
  
  free(keys);
  ioopm_hash_table_destroy(ht);
}

void test_getkeys2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 0);
  //CU_ASSERT_EQUAL(keys[16], NULL);
  
  free(keys);
  ioopm_hash_table_destroy(ht);
}

void test_getkeys3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  ioopm_hash_table_insert(ht, 5, "59");
  ioopm_hash_table_remove(ht, 5);
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 0);
  
  free(keys);
  ioopm_hash_table_destroy(ht);
}

void test_getvalues1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 3, "333");
  ioopm_hash_table_insert(ht, 12, "421");

  char **values = ioopm_hash_table_values(ht);

  
  CU_ASSERT_EQUAL(values[0], "333");
  CU_ASSERT_EQUAL(values[1], "421");
  
  free(values);
  ioopm_hash_table_destroy(ht);
}

void test_getvalues2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char **values = ioopm_hash_table_values(ht);

  
  CU_ASSERT_EQUAL(values[0], NULL);
  CU_ASSERT_EQUAL(values[16], NULL);
  
  free(values);
  ioopm_hash_table_destroy(ht);
}

void test_getvalues3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char **values = ioopm_hash_table_values(ht);

  ioopm_hash_table_insert(ht, 5, "59");
  ioopm_hash_table_remove(ht, 5);
  
  CU_ASSERT_EQUAL(values[0], NULL);
  
  free(values);
  ioopm_hash_table_destroy(ht);
}

void test_haskey1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 5, "59");
  
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 5));
  
  ioopm_hash_table_destroy(ht);
}

void test_haskey2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 3));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 5, "59");
  
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "59"));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, "4"));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, 5, "59");
  ioopm_hash_table_remove(ht, 5);
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, "59"));
  
  ioopm_hash_table_destroy(ht);
}

void aux_apply_to_all(int key_ignored, char **value, void *x)
{
  (*value)[1] = '\0';

  return;
}


void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char str[] = "50";
  char str2[] = "80";

  ioopm_hash_table_insert(ht, 2, str);
  ioopm_hash_table_insert(ht, 30, str2);

  ioopm_hash_table_apply_to_all(ht, aux_apply_to_all, NULL);
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 2).value, "5");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, 30).value, "8");
  
  ioopm_hash_table_destroy(ht);
}

bool aux_all(int key_ignored, char *value, void *x)
{
  if(value[0] == '5' && value[1] == '2')
    {
      return true;
    }

  return false;
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char str[] = "52";
  char str2[] = "52";
  char str3[] = "52";

  ioopm_hash_table_insert(ht, 4, str);
  ioopm_hash_table_insert(ht, 44, str2);
  ioopm_hash_table_insert(ht, 6, str3);

  
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, aux_all, NULL))
  
  ioopm_hash_table_destroy(ht);
}


//******************

//      MAIN

//******************
int main()
{
  CU_pSuite pSuiteLookup = NULL;
  CU_pSuite pSuiteInsert = NULL;
  CU_pSuite pSuiteRemove = NULL;
  CU_pSuite pSuiteSize = NULL;
  CU_pSuite pSuiteClear = NULL;
  CU_pSuite pSuiteGetKeys = NULL;
  CU_pSuite pSuiteGetValues = NULL;
  CU_pSuite pSuiteHasKey = NULL;
  CU_pSuite pSuiteHasValue = NULL;
  CU_pSuite pSuiteApplyToAll = NULL;
  CU_pSuite pSuiteAll = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // LOOKUP SUITE
  pSuiteLookup = CU_add_suite("lookup Suite", init_suite_lookup, clean_suite_lookup);
  if(NULL == pSuiteLookup)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteLookup, "test of lookup()", test_lookup1))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // INSERT SUITE
  pSuiteInsert = CU_add_suite("Insert Suite", init_suite_insert, clean_suite_insert);
  if(NULL == pSuiteInsert)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteInsert, "test of insert()", test_insert1))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // REMOVE SUITE
  pSuiteRemove = CU_add_suite("Remove Suite", init_suite_remove, clean_suite_remove);
  if(NULL == pSuiteRemove)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteRemove, "test of remove()", test_remove1) || (NULL == CU_add_test(pSuiteRemove, "test of remove()", test_remove2))))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // SIZE SUITE

  pSuiteSize = CU_add_suite("Size Suite", init_suite_size, clean_suite_size);
  if(NULL == pSuiteSize)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteSize, "test of size()", test_size1)) || (NULL == CU_add_test(pSuiteSize, "test of size()", test_size2)) || (NULL == CU_add_test(pSuiteSize, "test of size()", test_size3)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // CLEAR SUITE

  pSuiteClear = CU_add_suite("Clear Suite", init_suite_clear, clean_suite_clear);
  if(NULL == pSuiteClear)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteClear, "test of clear()", test_clear1)) || (NULL == CU_add_test(pSuiteClear, "test of clear()", test_clear2)) || (NULL == CU_add_test(pSuiteClear, "test of clear()", test_clear3)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // GETKEYS SUITE

  pSuiteGetKeys = CU_add_suite("GetKeys Suite", init_suite_getkeys, clean_suite_getkeys);
  if(NULL == pSuiteGetKeys)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteGetKeys, "test of getkeys1()", test_getkeys1)) || (NULL == CU_add_test(pSuiteGetKeys, "test of getkeys2()", test_getkeys2)) || (NULL == CU_add_test(pSuiteGetKeys, "test of getkeys3()", test_getkeys3)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // GETVALUES SUITE

  pSuiteGetValues = CU_add_suite("Getvalues Suite", init_suite_getvalues, clean_suite_getvalues);
  if(NULL == pSuiteGetValues)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteGetValues, "test of getvalues1()", test_getvalues1)) || (NULL == CU_add_test(pSuiteGetValues, "test of getvalues2()", test_getvalues2)) || (NULL == CU_add_test(pSuiteGetValues, "test of getvalues3()", test_getvalues3)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // HASKEY SUITE
  
  pSuiteHasKey = CU_add_suite("HasKey Suite", init_suite_haskey, clean_suite_haskey);
  if(NULL == pSuiteHasKey)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteHasKey, "test of haskey1()", test_haskey1) || (NULL == CU_add_test(pSuiteHasKey, "test of haskey2()", test_haskey2))))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  // HASVALUE SUITE

  pSuiteHasValue = CU_add_suite("Hasvalue Suite", init_suite_hasvalue, clean_suite_hasvalue);
  if(NULL == pSuiteHasValue)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if((NULL == CU_add_test(pSuiteHasValue, "test of hasvalue1()", test_hasvalue1) || (NULL == CU_add_test(pSuiteHasValue, "test of hasvalue2()", test_hasvalue2)) || (NULL == CU_add_test(pSuiteHasValue, "test of hasvalue3()", test_hasvalue3))))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // APPLTOALL SUITE

  pSuiteApplyToAll = CU_add_suite("ApplyToAll Suite", init_suite_ApplyToAll, clean_suite_ApplyToAll);
  if(NULL == pSuiteApplyToAll)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteApplyToAll, "test of ApplyToAll()", test_apply_to_all))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // APPLTOALL SUITE

  pSuiteAll = CU_add_suite("All Suite", init_suite_All, clean_suite_All);
  if(NULL == pSuiteAll)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteAll, "test of All()", test_all))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  // RUN TESTS

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

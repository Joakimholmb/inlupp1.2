#include <string.h>
#include "CUnit/Basic.h"
#include "hash_table.h"

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




//****************** TODO: EGNA KÖRNINGAR
int main()
{
  CU_pSuite pSuiteLookup = NULL;
  CU_pSuite pSuiteInsert = NULL;
  CU_pSuite pSuiteRemove = NULL;
  CU_pSuite pSuiteSize = NULL;
  CU_pSuite pSuiteClear = NULL;

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
  

    // RUN TESTS

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

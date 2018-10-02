#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "list_linked.h"

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}
//************ EGNA TESTFUNKTIONER

void test_get1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 5);
  
  ioopm_linked_list_destroy(list);
}

void test_get2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_append(list, 1000);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 1000);
  
  ioopm_linked_list_destroy(list);
}

void test_get3()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_prepend(list, 2000);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 2000);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 5);
  
  ioopm_linked_list_destroy(list);
}

void test_remove1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_remove(list, 3);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 3), 0);
  
  ioopm_linked_list_destroy(list);
}

void test_remove2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_insert(list, 1, 21);
  ioopm_linked_list_remove(list, 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 21);
  
  ioopm_linked_list_destroy(list);
}

void test_remove3()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_insert(list, 1, 21);
  ioopm_linked_list_insert(list, 2, 40);
  ioopm_linked_list_remove(list, 1);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 40);
  
  ioopm_linked_list_destroy(list);
}

//******************

//      MAIN

//******************
int main()
{
  CU_pSuite pSuiteGet = NULL;
  CU_pSuite pSuiteRemove = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // GET SUITE
  pSuiteGet = CU_add_suite("get Suite", init_suite, clean_suite);
  if(NULL == pSuiteGet)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteGet, "test of get1()", test_get1) || (NULL == CU_add_test(pSuiteGet, "test of get2()", test_get2) || (NULL == CU_add_test(pSuiteGet, "test of get3()", test_get3))))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // REMOVE SUITE

  pSuiteRemove = CU_add_suite("remove Suite", init_suite, clean_suite);
  if(NULL == pSuiteRemove)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteRemove, "test of remove1()", test_remove1) || (NULL == CU_add_test(pSuiteRemove, "test of remove2()", test_remove2) || (NULL == CU_add_test(pSuiteRemove, "test of remove2()", test_remove3))))
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

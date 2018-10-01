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
  //ioopm_linked_list_destroy(list);
}

//******************

//      MAIN

//******************
int main()
{
  CU_pSuite pSuiteGet = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // GET SUITE
  pSuiteGet = CU_add_suite("get Suite", init_suite, clean_suite);
  if(NULL == pSuiteGet)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteGet, "test of get1()", test_get1))
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

#include <string.h>
#include "CUnit/Basic.h"
#include "inlupp1.h"

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


//************ TODO: EGNA TESTFUNKTIONER


void test_lookup()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i < 17; ++i) /// 18 is a bit magical 
    {
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i).value);
    }
  ioopm_hash_table_destroy(ht);
}



void test_insert()
{

}






//****************** TODO: EGNA KÖRNINGAR
int main()
{
  CU_pSuite pSuiteLookup = NULL;
  //CU_pSuite pSuiteInsert = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  
  pSuiteLookup = CU_add_suite("lookup Suite", init_suite_lookup, clean_suite_lookup);
  if(NULL == pSuiteLookup)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteLookup, "test of lookup()", test_lookup))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }


  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

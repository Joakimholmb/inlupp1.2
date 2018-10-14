#include "CUnit/Basic.h"
#include "list_linked.h"
#include "hash_table.h"

struct hash_table
{
  size_t no_buckets;
  entry_t *buckets;  
  size_t size;
  hash_func func; 
};

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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(key_extract_int);
  for (int i = 0; i < 17; ++i) /// 18 is a bit magical 
    {
      elem_t value = (elem_t)i;
      CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, value).value.c, NULL);
    }
  ioopm_hash_table_destroy(ht);
}



void test_insert1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(key_extract_int);
  
  ioopm_hash_table_insert(ht, (elem_t)1, (elem_t)"23");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)1).value.c, "23");
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)18).defined, false)
  ioopm_hash_table_insert(ht, (elem_t)18, (elem_t)"50");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)18).value.c, "50");
  ioopm_hash_table_insert(ht, (elem_t)18, (elem_t)"hej");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)18).value.c, "hej");

  ioopm_hash_table_destroy(ht);
}

void test_remove1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)9, (elem_t)"595");
  
  elem_t str = ioopm_hash_table_remove(ht, (elem_t)9);
  
  CU_ASSERT_EQUAL(str.c, "595");
  
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)9).defined, false);
  
  ioopm_hash_table_destroy(ht);
}

void test_remove2()
{ 
 ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)15).defined, false);

  elem_t str = ioopm_hash_table_remove(ht, (elem_t)15);
  
  CU_ASSERT_EQUAL(str.c, NULL);
  
  ioopm_hash_table_destroy(ht);
}

void test_size1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_size2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)14, (elem_t)"123");
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  
  ioopm_hash_table_destroy(ht);
}

void test_size3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)14, (elem_t)"123");
  ioopm_hash_table_remove(ht, (elem_t)14);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)1, (elem_t)"123");
  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_clear3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)3, (elem_t)"333");
  ioopm_hash_table_remove(ht, (elem_t)3);

  ioopm_hash_table_clear(ht);
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_getkeys1()
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL); 
  
  ioopm_hash_table_insert(ht, (elem_t)3, (elem_t)"333");
  
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 3);
  
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
  
}

void test_getkeys2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

   
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 0);

  
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
}

void test_getkeys3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  elem_t str = (elem_t)"hej";

  ioopm_hash_table_insert(ht, str, (elem_t)"59");
  ioopm_hash_table_remove(ht, str);

  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys, 0).i, 0);
  
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
}

void test_getvalues1()
{
  
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)3, (elem_t)"333");
  ioopm_hash_table_insert(ht, (elem_t)12, (elem_t)"421");

  ioopm_list_t *values = ioopm_hash_table_values(ht);

  CU_ASSERT_EQUAL(ioopm_linked_list_get(values, 0).c, "333");
  CU_ASSERT_EQUAL(ioopm_linked_list_get(values, 1).c, "421");
  
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
  
}

void test_getvalues2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_list_t *values = ioopm_hash_table_values(ht);

  CU_ASSERT_EQUAL(ioopm_linked_list_get(values, 0).c, NULL);
  
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
}

void test_getvalues3()
{
  
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_list_t *values = ioopm_hash_table_values(ht);

  ioopm_hash_table_insert(ht, (elem_t)5, (elem_t)"59");
  ioopm_hash_table_remove(ht, (elem_t)5);
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(values, 0).c, NULL);
  
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
  
}

void test_haskey1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)5, (elem_t)"59");
  
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, (elem_t)5));
  
  ioopm_hash_table_destroy(ht);
}

void test_haskey2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t)3));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  elem_t five = (elem_t)5;
  elem_t str = (elem_t)"59";

  ioopm_hash_table_insert(ht, five, str);
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, str));
  
  //ioopm_hash_table_insert(ht, (elem_t)5, (elem_t)"59");
  
  //CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, (elem_t)"59"));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t)"4"));
  
  ioopm_hash_table_destroy(ht);
}

void test_hasvalue3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  ioopm_hash_table_insert(ht, (elem_t)5, (elem_t)"59");
  ioopm_hash_table_remove(ht, (elem_t)5);
  
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t)"59"));
  
  ioopm_hash_table_destroy(ht);
}

void aux_apply_to_all(elem_t key_ignored, elem_t *value, void *x)
{
  //(*value)[1] = '\0';

  *value = (elem_t)10;

  return;
}


void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);
  
  /*
  ioopm_hash_table_insert(ht, (elem_t)2, (elem_t)str);
  ioopm_hash_table_insert(ht, (elem_t)30, (elem_t)str2);

  ioopm_hash_table_apply_to_all(ht, aux_apply_to_all, NULL);
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)2).value, "5");
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)30).value, "8");
  */
  ioopm_hash_table_insert(ht, (elem_t)2, (elem_t)5);

  ioopm_hash_table_apply_to_all(ht, aux_apply_to_all, NULL);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)2).value.i, 10);
  
  
  ioopm_hash_table_destroy(ht);
}

bool aux_all(elem_t key_ignored, elem_t value, void *x)
{
  elem_t compare = (elem_t)52;
  return (value.i == compare.i);
  
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL);

  elem_t fifty_two = (elem_t)52;
  
  ioopm_hash_table_insert(ht, (elem_t)4, fifty_two);
  ioopm_hash_table_insert(ht, (elem_t)44, fifty_two);
  ioopm_hash_table_insert(ht, (elem_t)6, fifty_two);

  
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, aux_all, NULL));
  
  ioopm_hash_table_destroy(ht);
}

void test_resize()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(key_extract_int);

  for(int i=10; i<60; ++i)
    {
     
      ioopm_hash_table_insert(ht, (elem_t)i, (elem_t)i);
    }

  
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t)50).value.i, 50);
  
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
  CU_pSuite pSuiteResize = NULL;

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

  // RESIZE SUITE

  pSuiteResize = CU_add_suite("test of Resize", init_suite_All, clean_suite_All);
  if(NULL == pSuiteResize)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteResize, "test of resize()", test_resize))
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

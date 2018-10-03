#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "list_linked.h"
//#include "iterator.h" //FIXA SÅ HÄMTA TVÅ MODULER BROR
#include <errno.h>

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

void test_get4()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 0);
  
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

void test_size1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_append(list, 8);
  ioopm_linked_list_prepend(list, 40);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 3);
  ioopm_linked_list_remove(list, 1);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 2);

  ioopm_linked_list_destroy(list);
  
}

bool aux_list_all(int x, int y)
{
  return (x == y);
}

void test_list_all1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_insert(list, 1, 5);
  ioopm_linked_list_insert(list, 2, 5);
  int x = 5;
  int *y = &x;
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, aux_list_all, y));

  ioopm_linked_list_destroy(list);
}

void test_list_all2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  int x = 5;
  int *y = &x;
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, aux_list_all, y));

  ioopm_linked_list_destroy(list);
}

void test_list_any1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_insert(list, 1, 15);
  ioopm_linked_list_insert(list, 2, 25);
  int x = 15;
  int *y = &x;
  CU_ASSERT_TRUE(ioopm_linked_list_any(list, aux_list_all, y));

  ioopm_linked_list_destroy(list);
}

void test_list_any2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  int x = 5;
  int *y = &x;
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, aux_list_all, y));

  ioopm_linked_list_destroy(list);
}

void test_list_any3()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 15);
  int x = 5;
  int *y = &x;
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, aux_list_all, y));

  ioopm_linked_list_destroy(list);
}

void aux_apply_to_all(int *x, int *y)
{
  *x = *y;
  return;
}

void test_apply_to_all1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_insert(list, 1, 15);

  int x = 10;
  int *y = &x;
  ioopm_linked_apply_to_all(list, aux_apply_to_all, y);

  CU_ASSERT_TRUE(ioopm_linked_list_all(list, aux_list_all, y));
  
  ioopm_linked_list_destroy(list);
}

void test_apply_to_all2()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int x = 10;
  int *y = &x;
  ioopm_linked_apply_to_all(list, aux_apply_to_all, y);

  CU_ASSERT_FALSE(ioopm_linked_list_all(list, aux_list_all, y));
  
  ioopm_linked_list_destroy(list);
}

//************ ITER TESTS ************

void test_iter_insert1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_insert(iterator, 5);
  CU_ASSERT_EQUAL(ioopm_iterator_current(iterator), 5);

  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(list);
}

void test_iter_insert2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_insert(iterator, 5);
  CU_ASSERT_EQUAL(ioopm_iterator_current(iterator), 5);
  ioopm_iterator_insert(iterator, 3);
  CU_ASSERT_EQUAL(ioopm_iterator_current(iterator), 3);

  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(list);
}

//************ ITER HAS NEXT TESTS ************

void test_iter_has_next1()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  CU_ASSERT_FALSE(ioopm_iterator_has_next(iterator));

  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(list);
}

void test_iter_has_next2()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_insert(iterator, 5);
  ioopm_iterator_insert(iterator, 3);
  CU_ASSERT_TRUE(ioopm_iterator_has_next(iterator));

  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(list);
}

//******************

//      MAIN

//******************
int main()
{
  CU_pSuite pSuiteGet = NULL;
  CU_pSuite pSuiteRemove = NULL;
  CU_pSuite pSuiteSize = NULL;
  CU_pSuite pSuiteListAll = NULL;
  CU_pSuite pSuiteListAny = NULL;
  CU_pSuite pSuiteApplyAll = NULL;
  CU_pSuite pSuiteIterInsert = NULL;
  CU_pSuite pSuiteIterHasNext = NULL;
  
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // GET SUITE
  pSuiteGet = CU_add_suite("get Suite", init_suite, clean_suite);
  if(NULL == pSuiteGet)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteGet, "test of get1()", test_get1) || (NULL == CU_add_test(pSuiteGet, "test of get2()", test_get2) || (NULL == CU_add_test(pSuiteGet, "test of get3()", test_get3) || (NULL == CU_add_test(pSuiteGet, "test of get4()", test_get4)))))
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

  // SIZE SUITE
  pSuiteSize = CU_add_suite("size Suite", init_suite, clean_suite);
  if(NULL == pSuiteSize)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteSize, "test of size1()", test_size1))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // LIST_ALL SUITE
  pSuiteListAll = CU_add_suite("list_all Suite", init_suite, clean_suite);
  if(NULL == pSuiteListAll)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteListAll, "test of list_all1()", test_list_all1) || (NULL == CU_add_test(pSuiteListAll, "test of list_all2()", test_list_all2)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // LIST_ANY SUITE
  pSuiteListAny = CU_add_suite("list_any Suite", init_suite, clean_suite);
  if(NULL == pSuiteListAny)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteListAny, "test of list_any1()", test_list_any1) || (NULL == CU_add_test(pSuiteListAny, "test of list_any2()", test_list_any2) ||  (NULL == CU_add_test(pSuiteListAny, "test of list_any3()", test_list_any3))))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // APPLY_ALL SUITE
  pSuiteApplyAll = CU_add_suite("apply_all Suite", init_suite, clean_suite);
  if(NULL == pSuiteApplyAll)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteApplyAll, "test of apply_all1()", test_apply_to_all1) || (NULL == CU_add_test(pSuiteApplyAll, "test of apply_all2()", test_apply_to_all2)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  //Iterator_insert suite
  pSuiteIterInsert = CU_add_suite("Iter_Insert Suite", init_suite, clean_suite);
  if(NULL == pSuiteIterInsert)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteIterInsert, "test of iter_insert1()", test_iter_insert1) || (NULL == CU_add_test(pSuiteIterInsert, "test of iter_insert2()", test_iter_insert2)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  //Iterator_has_next SUITE
  pSuiteIterHasNext = CU_add_suite("Iter_has_next Suite", init_suite, clean_suite);
  if(NULL == pSuiteIterHasNext)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuiteIterHasNext, "test of iter_has_next1()", test_iter_has_next1) || (NULL == CU_add_test(pSuiteIterHasNext, "test of iter_has_next2()", test_iter_has_next2)))
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

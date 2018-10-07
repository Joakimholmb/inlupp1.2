//#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_linked.h"
//#include "iterator.h"
#include <errno.h>

extern int errno;


struct elem
{
  int32_t i;
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
};

struct iter 
{
  link_t *prev;
  link_t *current;
  ioopm_list_t *list;
};



// ************** LIST_LINKED FUNC DECLARATIONS ************

static link_t *link_new(link_t *next, elem_t value);
static link_t *find_previous_link(ioopm_list_t *list, size_t index);
ioopm_list_t *ioopm_linked_list_create();
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, size_t index, elem_t value);
elem_t ioopm_linked_list_get(ioopm_list_t *list, size_t index);
void ioopm_linked_list_append(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value);
void ioopm_linked_list_clear(ioopm_list_t *list);
elem_t ioopm_linked_list_remove(ioopm_list_t *list, size_t index);
int ioopm_linked_list_size(ioopm_list_t *list);
bool ioopm_linked_list_is_empty(ioopm_list_t *list);
bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element);
bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x);
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x);
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(elem_t *, elem_t *), void *x);


// ************** ITERATOR FUNC DECLARATIONS ************

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);
static link_t *insert_aux(link_t *link, elem_t elem);
/*

  FUNKTIONER

*/

static link_t *link_new(link_t *next, elem_t value)
{
  link_t *link_new = calloc(1, sizeof(link_t));
  link_new->next = next;
  link_new->element = value;
  
  return link_new;
}

static link_t *find_previous_link(ioopm_list_t *list, size_t index)
{
  link_t *cursor = list->first;
  if (cursor == NULL)
    {
      return NULL;
    }

  else if (index == 0 || index == 1)
    {
      return cursor;
    }
  else
    {
      for(size_t i = 0; i < (index-1); ++i)
        {
          cursor = cursor->next;
        }
    }
  return cursor;
}

ioopm_list_t *ioopm_linked_list_create()
{
  ioopm_list_t *result = calloc(1, sizeof(ioopm_list_t));

  return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  ioopm_linked_list_clear(list);
  free(list);
  return;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
  link_t *link = list->first;

  if(link == NULL)
    {
      return;
    }

  while(link->next != NULL)
    {
      link_t *var = link->next;
      free(link);
      link = var;
      list->size -= 1;
    }
  free(link);
  return;
}

void ioopm_linked_list_insert(ioopm_list_t *list, size_t index, elem_t value)
{
  if (list->first == NULL) // TODO: KAN HA APPEND HÄR, MEN MÅSTE ÄNDRA APPEND
    {
      
      list->first = link_new(NULL, value);
      list->last = list->first;
    }
  else
    {
      if (index == list->size)
        {
          ioopm_linked_list_append(list, value);
          return;
        }
      else
        {
          link_t *prev_link = find_previous_link(list, index);
          link_t *next_link = prev_link->next;
          link_t *new_link = link_new(next_link,value);
          prev_link->next = new_link;
        }
    }
  list->size += 1;
  return;
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, size_t index)
{
  elem_t zero = {0};
  if(list->size < index)
    {
      errno = EINVAL;
      return zero;
    }
  else
    {
      link_t *link = find_previous_link(list, (index+1));
      if(link == NULL)
        {
          errno = EINVAL;
          return zero;
        }
      return link->element;
    }
  
  
  return zero;
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{
  if (list->last == NULL)
    {
      ioopm_linked_list_insert(list, 0, value);
    }
  else
    {
      
      link_t *new_link = link_new(NULL, value);
      list->last->next = new_link;
      list->last = new_link;
    }
  list->size +=1;
  return;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{
  list->first = link_new(list->first, value);
  list->size += 1;
  return;
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, size_t index)
{
  struct elem zero = {0};
  link_t *prev_link = find_previous_link(list, (index));
  if(prev_link == NULL)
    {
      return zero;
    }

  if(prev_link == list->first && index == 0)
    {
      link_t *next_link = prev_link->next->next;
      link_t *link = prev_link->next;
      prev_link->next = next_link;

      elem_t value = link->element;
      free(prev_link);
      list->first = link;
      list->size -= 1;
      return value;
    }
  else
    {
      link_t *next_link = prev_link->next->next;
      link_t *link = prev_link->next;
      prev_link->next = next_link;

      elem_t value = link->element;
      free(link);
      list->size -= 1;
      return value;
    }
  
  
  return zero;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  return (ioopm_linked_list_size(list) == 0);
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
  link_t *cursor = list->first;

  while(cursor != NULL)
    {
      if(cursor->element.i == element.i)
        {
          return true;
        }
      cursor = cursor->next;
    }
  
  return false;  
}

bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x)

{
  link_t *cursor = list->first;
  elem_t *elem_compare = x;

  if(cursor == NULL)
    {
      return false;
    }
  else
    {
      while(cursor != NULL)
        {
          if (prop(cursor->element, *elem_compare))
            {
              cursor = cursor->next;
            }
          else
            {
              return false;
            }
        }
    }
  
  return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x)

{
  link_t *cursor = list->first;
  elem_t *elem_compare = x;
  while(cursor != NULL)
    {
      if (prop(cursor->element, *elem_compare))
        {
          return true;
        }
      else
        {
          cursor = cursor->next;
        }
    }
  return false;
}

void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(elem_t *, elem_t *), void *x)
{
  link_t *cursor = list->first;
  elem_t *elem = x;
  while(cursor != NULL)
    {
      fun(&(cursor->element), elem);
      cursor = cursor->next;
    }
  return;
}

/**************************************

// ITERATOR

***************************************/

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
  ioopm_list_iterator_t *result = calloc(1, sizeof(ioopm_list_iterator_t));

  result->list = list;
  result->current = list->first;
  result->prev = list->first;
  return result;  
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
  if(iter->current == NULL)
    {
      return false;
    }
  return iter->current->next != NULL; 
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
  //if (iter->list->first == iter->current && iter->current->next->next == NULL)
  if(iter->prev == iter->current)
    {
      iter->current = iter->current->next;
      return iter->current->element;
    }
  iter->prev = iter->current;
  iter->current = iter->current->next;
  return iter->current->element; 
}

elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{
  link_t *to_remove = iter->current;
  iter->prev->next = to_remove->next;
  iter->current = to_remove->next;
  elem_t value = to_remove->element;

  free(to_remove);
  return value;
}
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t elem)
{
  if (iter->current == NULL)
    {
      iter->current = insert_aux(NULL, elem);
      iter->list->first = iter->current;
      iter->prev = iter->current;
      return;
      
    }
  // && iter->current->next == NULL
  else if (iter->current == iter->list->first)
    {
      //link_t *next_link = iter->current;
      iter->current = insert_aux(iter->current, elem);
      iter->list->first = iter->current;
      iter->prev = iter->current;
      return;
    }
  iter->current = insert_aux(iter->current, elem);
  iter->prev->next = iter->current;
  return;
}

static link_t *insert_aux(link_t *link , elem_t elem)
{

  link_t *new_link = calloc(1, sizeof(link_t));
  new_link->element = elem;
  new_link->next = link;
  return new_link;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
  iter->current = iter->list->first;
  return;
}
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  struct elem zero = {0};
  
  if(iter->current == NULL)
    {
      return zero; //TODO: Lägg till error
    }
  
  return iter->current->element; 
}

//FREES ALL ELEMENTS AFTER LINK ARGUMENT
void destroy_aux(link_t *link)
{
  if(link == NULL)
    {
      return;
    }
  while (link->next != NULL)
    {
      link_t *var = link->next;
      free(link);
      link = var;
    }
  free(link);
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
  free(iter);
  return;
}
/*
int main(void)
{
  
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  ioopm_iterator_insert(iter, 1);
    printf("current elem is: %d\n",iter->current->element);
  ioopm_iterator_insert(iter, 12);
  printf("current elem is: %d\n",iter->current->element);
  ioopm_iterator_current(iter);
  ioopm_iterator_next(iter);
  printf("current elem is: %d\n",iter->current->element);
  ioopm_iterator_current(iter);
  ioopm_iterator_insert(iter, 123);
  printf("current elem is: %d\n",iter->current->element);
  ioopm_iterator_reset(iter);
  printf("current elem is: %d\n",iter->current->element);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
  return 0;
  
    ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_insert(iterator, 5);
  //  CU_ASSERT_EQUAL(ioopm_iterator_current(iterator), 5);


  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(list);
  return 0;
}
   
*/

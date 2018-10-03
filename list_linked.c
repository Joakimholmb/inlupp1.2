#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list_linked.h"
#include "iterator.h"
#include <errno.h>

extern int errno;

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
  link_t *current;
  ioopm_list_t *list;
};

// ************** LIST_LINKED FUNC DECLARATIONS ************

static link_t *link_new(link_t *next, int value);
static link_t *find_previous_link(ioopm_list_t *list, int index);
ioopm_list_t *ioopm_linked_list_create();
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value);
int ioopm_linked_list_get(ioopm_list_t *list, int index);
void ioopm_linked_list_append(ioopm_list_t *list, int value);
void ioopm_linked_list_prepend(ioopm_list_t *list, int value);
void ioopm_linked_list_clear(ioopm_list_t *list);
elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index);

int ioopm_linked_list_size(ioopm_list_t *list);
bool ioopm_linked_list_is_empty(ioopm_list_t *list);
bool ioopm_linked_list_contains(ioopm_list_t *list, int element);
bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(int, int), void *x);
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(int, int), void *x);
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(int *, int *), void *x);


// ************** ITERATOR FUNC DECLARATIONS ************

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_next(ioopm_list_iterator_t *iter);
int ioopm_iterator_remove(ioopm_list_iterator_t *iter);
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, int element);
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);
int ioopm_iterator_current(ioopm_list_iterator_t *iter);
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);

/*

  FUNKTIONER

*/

static link_t *link_new(link_t *next, int value)
{
  link_t *link_new = calloc(1, sizeof(link_t));
  link_new->next = next;
  link_new->element = value;
  
  return link_new;
}

static link_t *find_previous_link(ioopm_list_t *list, int index)
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
      for(int i = 0; i < (index-1); ++i)
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

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
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

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  if(list->size < index)
    {
      errno = EINVAL;
      return 0;
    }
  else
    {
      link_t *link = find_previous_link(list, (index+1));
      if(link == NULL)
        {
          errno = EINVAL;
          return 0;
        }
      return link->element;
    }
  
  
  return 0;
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
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

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
  list->first = link_new(list->first, value);
  list->size += 1;
  return;
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  link_t *prev_link = find_previous_link(list, (index));
  if(prev_link == NULL)
    {
      return 0;
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
  
  
  return 0;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  return (ioopm_linked_list_size(list) == 0);
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
  link_t *cursor = list->first;

  while(cursor != NULL)
    {
      if(cursor->element == element)
        {
          return true;
        }
      cursor = cursor->next;
    }
  
  return false;  
}

bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(int, int), void *x)

{
  link_t *cursor = list->first;
  int *elem_compare = x;

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

bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(int, int), void *x)

{
  link_t *cursor = list->first;
  int *elem_compare = x;
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

void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(int *, int *), void *x)
{
  link_t *cursor = list->first;
  int *elem = x;
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

  result->current = list->first;
  
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

int ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
  iter->current = iter->current->next;
  return iter->current->element; 
}

int ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{

  link_t *to_remove = iter->current;

  iter->current = to_remove->next;
  int value = to_remove->element;

  free(to_remove);
  return value;
}
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
  if (iter->current == NULL)
    {
      iter->current = calloc(1, sizeof(link_t));
      iter->current->element = element;
      iter->current->next = NULL;
      iter->list->first = iter->current;
    }
  iter->current->next = calloc(1, sizeof(link_t));
  link_t *next_link = iter->current;
  iter->current->element = element;
  iter->current->next = next_link;
  return;
}
void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
  iter->current = iter->list->first;
  return;
}
int ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  return iter->current->element; 
}
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
  ioopm_iterator_reset(iter);
  while(iter->current != NULL)
    {
      ioopm_iterator_remove(iter);
      iter->current = iter->current->next;
    }
  free(iter);
  return;
}

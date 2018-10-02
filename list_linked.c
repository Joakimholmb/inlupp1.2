#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list_linked.h"

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

// ADD ERROR HANDLING

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
  /*
  link_t *link = list->first;

  while(link->next != NULL)
    {
      link_t *var = link->next;
      free(link);
      link = var;
      list->size -= 1;
    }
  free(link);
  */
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
  if (list->first == NULL) // KAN HA APPEND HÄR, MEN MÅSTE ÄNDRA APPEND
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
  /*
  link_t *cursor = list->first;

  for(int i = 0; i < index; ++i)
  {
  if(cursor == NULL)
  {
  return 0;
  }
  cursor = cursor->next;
  }
  */
  if(list->size < index)
    {
      return 0;
    }
  else
    {
      link_t *link = find_previous_link(list, (index+1));
      if(link == NULL)
        {
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
      return value;
    }
  else
    {
      link_t *next_link = prev_link->next->next;
      link_t *link = prev_link->next;
      prev_link->next = next_link;

      elem_t value = link->element;
      free(link);
      return value;
    }
  
  
  return 0;
}


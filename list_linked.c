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
};

ioopm_list_t *ioopm_linked_list_create();
void ioopm_linked_list_destroy(ioopm_list_t *list);
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value);
int ioopm_linked_list_get(ioopm_list_t *list, int index);
  
/*

  FUNKTIONER

*/

ioopm_list_t *ioopm_linked_list_create()
{
  ioopm_list_t *result = calloc(1, sizeof(ioopm_list_t));

  return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  link_t *link = list->first;

  while(link->next != NULL)
    {
      link_t *var = link->next;
      free(link);
      link = var;
      list->size -= 1;
    }
  free(list);
  return;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
  link_t *new_link = calloc(1, sizeof(link_t));
  new_link->element = value;
  link_t *cursor = list->first;
  for(int i = 0; i <= index; ++i)
    {
      if(cursor == NULL)
        {
          cursor = new_link;
          new_link->next = NULL;
          return;
        }
      cursor = cursor->next;
      printf("i = %d\n", i);
    }
  link_t *prev_link = cursor;
  link_t *next_link = cursor->next;
  prev_link->next = new_link;
  new_link->next = next_link;
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  link_t *cursor = list->first;

  for(int i = 0; i <= index; ++i)
    {
       if(cursor == NULL)
        {
          return 0;
        }
      cursor = cursor->next;
    }
  printf("%d\n", cursor->element);
  return cursor->element;
}

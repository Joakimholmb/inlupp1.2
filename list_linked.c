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
};

ioopm_list_t *ioopm_linked_list_create()
{
    ioopm_list_t *result = calloc(1, sizeof(ioopm_list_t));

  return result;
}

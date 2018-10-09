#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef union 
{
  int32_t i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *c;
  char buf[50];
  int32_t* ip;
  unsigned int* up;
  float* fp;
  
} elem_t;

struct option
{
  bool defined;
  elem_t *value;
};

typedef bool(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef void(*ioopm_apply_function2)(elem_t key, elem_t **value, void *extra);

typedef elem_t(*hash_func)(elem_t *str);


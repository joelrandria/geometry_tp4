#include "int_list.h"

#include <stdlib.h>

int_list* int_list_create(int value)
{
  int_list* item;

  item = malloc(sizeof(*item));
  item->value = value;
  item->next = 0;

  return item;
}
int_list* int_list_enqueue(int_list* list, int value)
{
  int_list* last;
  int_list* new_item;

  new_item = int_list_create(value);

  last = int_list_last(list);
  if (!last)
    return new_item;

  last->next = new_item;

  return list;
}

unsigned int int_list_size(int_list* list)
{
  unsigned int size = 0;

  while (list)
  {
    ++size;
    list = list->next;
  }

  return size;
}
int_list* int_list_last(int_list* list)
{
  if (!list)
    return 0;

  while (list->next)
    list = list->next;

  return list;
}

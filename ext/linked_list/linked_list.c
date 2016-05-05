#include <ruby.h>
#include "rb_linked_list.h"

#define DEFINE_LINKED_LIST_METHOD(method_name, argc)                           \
  rb_define_method(LinkedList, #method_name, LinkedList_##method_name, argc);  \

void Init_linked_list() {
  VALUE LinkedList = rb_define_class("LinkedList", rb_cObject);
  rb_define_alloc_func(LinkedList, LinkedList_allocate);
  DEFINE_LINKED_LIST_METHOD(initialize, -1);
  DEFINE_LINKED_LIST_METHOD(length, 0);
  DEFINE_LINKED_LIST_METHOD(each, 0);
  DEFINE_LINKED_LIST_METHOD(first, 0);
  DEFINE_LINKED_LIST_METHOD(shift, 0);
  DEFINE_LINKED_LIST_METHOD(unshift, 1);
  DEFINE_LINKED_LIST_METHOD(last, 0);
  DEFINE_LINKED_LIST_METHOD(push, 1);
  DEFINE_LINKED_LIST_METHOD(pop, 0);
  DEFINE_LINKED_LIST_METHOD(get, 1);
  DEFINE_LINKED_LIST_METHOD(set, 2);
}

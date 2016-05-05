#ifndef RB_LINKED_LIST_H
#define RB_LINKED_LIST_H

#include <ruby.h>

VALUE LinkedList_allocate(VALUE klass);
VALUE LinkedList_initialize(int argc, VALUE *argv, VALUE self);
VALUE LinkedList_length(VALUE self);
VALUE LinkedList_each(VALUE self);
VALUE LinkedList_first(VALUE self);
VALUE LinkedList_shift(VALUE self);
VALUE LinkedList_unshift(VALUE self, VALUE new_value);
VALUE LinkedList_last(VALUE self);
VALUE LinkedList_push(VALUE self, VALUE new_value);
VALUE LinkedList_pop(VALUE self);
VALUE LinkedList_get(VALUE self, VALUE index);
VALUE LinkedList_set(VALUE self, VALUE index, VALUE new_value);

#endif

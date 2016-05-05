#include <ruby.h>
#include "rb_linked_list_intern.h"

VALUE LinkedList_allocate(VALUE list_class) {
  Node* node = LinkedList_intern_init_node();
  return Data_Wrap_Struct(list_class, LinkedList_intern_gc_mark, LinkedList_intern_gc_mark, node);
}

VALUE LinkedList_initialize(int argc, VALUE *argv, VALUE self) {
  Node *node;
  Node *prev_node = NULL;

  Data_Get_Struct(self, Node, node);
  LinkedList_intern_set_owner(node, self);
  LinkedList_intern_set_length(node, argc);

  if (argc) {
    LinkedList_intern_set_value(node, argv[0]);
    int i;
    for(i = 1; i < argc; i++) {
      node = LinkedList_intern_append(node, argv[i]);
    }
  }

  return self;
}

VALUE LinkedList_length(VALUE self) {
  Node *node;
  Data_Get_Struct(self, Node, node);
  return INT2NUM(LinkedList_intern_get_length(node));
}

VALUE LinkedList_each(VALUE self) {
  Node *node;

  if (!rb_block_given_p()) {
    rb_raise(rb_eArgError, "Expected block");
  }

  Data_Get_Struct(self, Node, node);
  int i;
  int length = LinkedList_intern_get_length(node);

  for(i = 1; i <= length; i++) {
    rb_yield(LinkedList_intern_get_value(node));
    node = LinkedList_intern_get_next(node);
  }

  return Qnil;
}

VALUE LinkedList_first(VALUE self) {
  Node *node;
  Data_Get_Struct(self, Node, node);
  return LinkedList_intern_get_value(node);
}

VALUE LinkedList_shift(VALUE self) {
  Node *node;
  int length;
  VALUE LinkedList;
  Data_Get_Struct(self, Node, node);
  length = LinkedList_intern_get_length(node);

  if (!length) {
    return self;
  } else if (length == 1) {
    LinkedList = rb_define_class("LinkedList", rb_cObject);
    return rb_class_new_instance(0, NULL, LinkedList);
  } else {
    return LinkedList_intern_get_owner(self, LinkedList_intern_get_next(node));
  }
}

VALUE LinkedList_unshift(VALUE self, VALUE new_value) {
  Node *node;
  Node *head_node;

  Data_Get_Struct(self, Node, node);
  head_node = LinkedList_intern_prepend(node, new_value);
  return LinkedList_intern_get_owner(self, head_node);
}

VALUE LinkedList_last(VALUE self) {
  int length;
  Node *node;
  Data_Get_Struct(self, Node, node);
  length = LinkedList_intern_get_length(node);
  if (length == 0) {
    return Qnil;
  } else {
    node = LinkedList_intern_get_index(node, length - 1);
    return LinkedList_intern_get_value(node);
  }
}

VALUE LinkedList_push(VALUE self, VALUE new_value) {
  Node *node;
  Node *copied_head_node;
  Node *copied_tail_node;
  Node *appended_tail_node;
  int length;
  VALUE LinkedList;

  Data_Get_Struct(self, Node, node);
  length = LinkedList_intern_get_length(node);

  if (length == 0) {
    LinkedList = rb_define_class("LinkedList", rb_cObject);
    return rb_class_new_instance(1, &new_value, LinkedList);
  } else {
    copied_head_node = LinkedList_intern_copy(node, length, 1);
    copied_tail_node = LinkedList_intern_get_index(copied_head_node, length - 1);
    appended_tail_node = LinkedList_intern_append(copied_tail_node, new_value);
    return LinkedList_intern_get_owner(self, copied_head_node);
  }
}

VALUE LinkedList_pop(VALUE self) {
  Node *node;
  Node *copied_head_node;
  Node *copied_tail_node;
  int length;

  Data_Get_Struct(self, Node, node);
  length = LinkedList_intern_get_length(node);
  if (length == 0) {
    return self;
  } else {
    copied_head_node = LinkedList_intern_copy(node, length - 1, -1);
    copied_tail_node = LinkedList_intern_get_index(copied_head_node, length - 2);
    LinkedList_intern_set_next(copied_tail_node, NULL);
    return LinkedList_intern_get_owner(self, copied_head_node);
  }
}

VALUE LinkedList_get(VALUE self, VALUE rb_index) {
  Node* node;
  int length;
  int index;
  Data_Get_Struct(self, Node, node);
  index = NUM2INT(rb_index);
  length = LinkedList_intern_get_length(node);

  if (length == 0 || index >= length) {
    return Qnil;
  }

  if(index < 0) {
    index = length + index;
  }

  node = LinkedList_intern_get_index(node, index);
  return LinkedList_intern_get_value(node);
}

VALUE LinkedList_set(VALUE self, VALUE rb_index, VALUE new_value) {
  Node *node;
  int length;
  int index;
  int i;
  int final_length;
  int length_change;
  Node *copied_head_node;
  Node *copied_tail_node;
  Node *new_node;
  Node *rest;
  VALUE LinkedList;

  Data_Get_Struct(self, Node, node);
  length = LinkedList_intern_get_length(node);
  index = NUM2INT(rb_index);
  if (index < 0) {
    index = length + index;
  }

  if (index > length) {
    final_length = index + 1;
  } else {
    final_length = length;
  }

  length_change = final_length - length;

  if (final_length == 0 || final_length == 1) {
    LinkedList = rb_define_class("LinkedList", rb_cObject);
    return rb_class_new_instance(1, &new_value, LinkedList);
  } else {
    copied_head_node = LinkedList_intern_copy(node, index, length_change);
    copied_tail_node = LinkedList_intern_get_index(copied_head_node, index - 1);

    new_node = LinkedList_intern_append(copied_tail_node, new_value);

    rest = LinkedList_intern_get_index(node, length - index - 1);
    LinkedList_intern_set_next(new_node, rest);

    return LinkedList_intern_get_owner(self, copied_head_node);
  }
}

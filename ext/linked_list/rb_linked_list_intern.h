#ifndef RB_LINKED_LIST_INTERN_H
#define RB_LINKED_LIST_INTERN_H

#include <ruby.h>

typedef struct Node Node;

Node* LinkedList_intern_init_node();
void LinkedList_intern_free_node(Node* node);
void LinkedList_intern_mark_node(Node *node);
void LinkedList_intern_gc_mark(void *node);
void LinkedList_intern_deallocate(void *node);

Node* LinkedList_intern_append(Node* node, VALUE new_value);
Node* LinkedList_intern_prepend(Node* node, VALUE new_value);

VALUE LinkedList_intern_get_owner(VALUE self, Node* node);
void LinkedList_intern_set_owner(Node* node, VALUE new_owner);

VALUE LinkedList_intern_get_value(Node* node);
void LinkedList_intern_set_value(Node* node, VALUE new_value);

Node* LinkedList_intern_get_next(Node* node);
void LinkedList_intern_set_next(Node* node, Node* next);

int LinkedList_intern_get_length(Node *node);
void LinkedList_intern_set_length(Node *node, int new_length);

Node* LinkedList_intern_get_index(Node* node, int index);
Node* LinkedList_intern_copy(Node* node, int length, int length_change);

#endif

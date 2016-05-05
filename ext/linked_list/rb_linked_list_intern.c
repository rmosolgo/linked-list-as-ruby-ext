#include <ruby.h>

typedef struct Node {
  struct Node *next;
  int length;
  VALUE value;
  VALUE owner;
} Node;

void LinkedList_intern_free_node(Node *node) {
  if (node->next && !(node->next->owner)) {
    LinkedList_intern_free_node(node->next);
  }
  free(node);
}

void LinkedList_intern_mark_node(Node *node) {
  if (node->value) {
    rb_gc_mark(node->value);
  }
  if (node->owner) {
    rb_gc_mark(node->owner);
  }
  if (node->next) {
    LinkedList_intern_mark_node(node->next);
  }
}

void LinkedList_intern_gc_mark(void *node_void) {
  LinkedList_intern_mark_node((Node *)node_void);
}

void LinkedList_intern_deallocate(void *node_void) {
  LinkedList_intern_free_node((Node *)node_void);
}

Node* LinkedList_intern_init_node() {
  Node *node = ALLOC(Node);
  node->next = NULL;
  node->owner = 0;
  node->value = Qnil;
  node->length = 0;
  return node;
}

Node* LinkedList_intern_append(Node *node, VALUE value) {
  Node *following_node = LinkedList_intern_init_node();
  node->next = following_node;
  following_node->value = value;
  following_node->length = node->length - 1;
  return following_node;
}

Node* LinkedList_intern_prepend(Node *node, VALUE value) {
  Node *leading_node = LinkedList_intern_init_node();
  leading_node->next = node;
  leading_node->length = node->length + 1;
  leading_node->value = value;
  return leading_node;
}

VALUE LinkedList_intern_get_owner(VALUE self, Node* node) {
  VALUE list_class, node_owner;
  if (node->owner) {
    node_owner = node->owner;
  } else {
    // TODO: is there a better way to get a class?
    list_class = rb_funcall(self, rb_intern("class"), 0, NULL);
    node_owner = Data_Wrap_Struct(list_class, LinkedList_intern_gc_mark, LinkedList_intern_deallocate, node);
    node->owner = node_owner;
  }
  return node_owner;
}

void LinkedList_intern_set_owner(Node* node, VALUE new_owner) {
  node->owner = new_owner;
}

int LinkedList_intern_get_length(Node *node) {
  return node->length;
}

void LinkedList_intern_set_length(Node *node, int new_length) {
  node->length = new_length;
}

VALUE LinkedList_intern_get_value(Node *node) {
  return node->value;
}

VALUE LinkedList_intern_set_value(Node *node, VALUE new_value) {
  return node->value = new_value;
}

Node* LinkedList_intern_get_next(Node *node) {
  return node->next;
}

void LinkedList_intern_set_next(Node *node, Node *new_next) {
  node->next = new_next;
}

Node* LinkedList_intern_dup_node(Node *existing, int length_change) {
  Node *new = LinkedList_intern_init_node();
  // Don't copy `owner`, it will be a new ruby obj
  new->value = existing->value;
  new->length = existing->length + length_change;
  new->next = existing->next;
  return new;
}

Node* LinkedList_intern_copy(Node *head, int length, int length_change) {
  int i;
  Node* copied_head_node;
  Node* copied_prev_node;
  Node* copied_next_node;

  copied_head_node = LinkedList_intern_dup_node(head, length_change);
  copied_prev_node = copied_head_node;

  for (i = 1; i < length; i++) {

    if (copied_prev_node->next) {
      copied_next_node = LinkedList_intern_dup_node(copied_prev_node->next, length_change);
    } else {
      copied_next_node = LinkedList_intern_init_node();
      copied_next_node->length = length - i;
      copied_next_node->value = Qnil;
    }
    copied_prev_node->next = copied_next_node;
    copied_prev_node = copied_next_node;
  }

  return copied_head_node;
}

Node* LinkedList_intern_get_index(Node *head, int index) {
  int i;
  for(i = 0; i < index; i++) {
    head = head->next;
  }
  return head;
}

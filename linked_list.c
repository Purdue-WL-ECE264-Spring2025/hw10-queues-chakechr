#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *newNode = malloc(sizeof(struct list_node));
  if (newNode != NULL) {
    // Malloc Success, Set Value
    newNode->value = value;
    newNode->next = NULL; // Node Is Not Connected To A Tail Node & Next Points To Nothing
  }
  return newNode;
}

void insert_at_head(struct linked_list *list, size_t value) {
  if (list == NULL) {
    return;
  }
  struct list_node *addNode = new_node(value);
  if (addNode) {
    // New Node Should Point To Previous Head Node & Become New Head Node
    addNode->next = list->head;
    list->head = addNode;
  }
}

void insert_at_tail(struct linked_list *list, size_t value) {
  if (list == NULL) {
    return;
  }
  struct list_node *addNode = new_node(value);
  if (addNode) { // Ensure Malloc Success
    if (!list->head) {
      // If First Node Addition To List, Node Automatically Becomes Head
      list->head = addNode;
    } else {
      // List Exists, Place Node At Tail
      struct list_node *traceNode = list->head;
      while (traceNode->next != NULL) {
        // Loop Through List While There Exists A Node Next
        traceNode = traceNode->next;
      }
      // Add New Node As Final Tail Node
      traceNode->next = addNode;
    }
  }
}

size_t remove_from_head(struct linked_list *list) {
  if (list == NULL || list->head == NULL) {
    return -1;
  }
  struct list_node *headNode = list->head;
  size_t value = headNode->value;

  // Free Head Node & Set Next To New Head
  list->head = headNode->next;
  free(headNode);

  // Return Freed Head Nodes Value
  return value;
}

size_t remove_from_tail(struct linked_list *list) {
  if (list == NULL || list->head == NULL) {
    return -1;
  }
  struct list_node *traceNode = list->head;

  if (!traceNode->next) {
    // Head Node Is Only Node In Sequence, Free This As Only Node
    size_t value = traceNode->value;
    free(traceNode);
    // Set List Node To Null & Return Freed Node's Value
    list->head = NULL;
    return value;
  }

  // If There Exists Multiple Nodes In List, Trace Through To Find Tail
  while (traceNode->next && traceNode->next->next) {
    traceNode = traceNode->next;
  }

  // Once The Second Last Node Is Found, Free The Tail Node From The TraceNode Next Reference
  size_t value = traceNode->next->value;
  free(traceNode->next);
  traceNode->next = NULL;

  return value;
}

void free_list(struct linked_list list) {
  // Begin With Head Node
  struct list_node *freeNode = list.head;
  // Loop Until End Of List Reached
  while (freeNode != NULL) {
    // Create Pointer To Next Node From Current & Free
    struct list_node *nextNode = freeNode->next;
    free(freeNode);
    freeNode = nextNode;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}

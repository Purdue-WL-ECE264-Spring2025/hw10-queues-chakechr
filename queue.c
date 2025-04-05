#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

// enqueue inserts at the head and dequeue removes from the tail.
void enqueue(struct queue *q, struct game_state state) {
  insert_at_head(&q->data, serialize(state));
}
struct game_state dequeue(struct queue *q) {
  return deserialize(remove_from_tail(&q->data));
}


// Check whether a state is the goal
bool big_winner(struct game_state state) {
  int correctNum = 1;
  if (state.tiles[3][3] != 0) {
    // Bottom Right Is Not Zero, Can't Be Correct
    return false;
  }
  for (int i = 0; i < 4; i++) { // Row Loop
    for (int j = 0; j < 4; j++) { // Column Loop
      if (!(i == 3 && j == 3) && state.tiles[i][j] != correctNum++) {
        // Incorrect Number Ordering
        return false;
      }
    }
  }
  // No Issues Found, Correct Sequence
  return true;
}
bool seen_state(struct linked_list *list, size_t value) {
  // Is Current Game State In List Of Explored States?
  struct list_node *check = list->head;
  while (check) {
    if (check->value == value) {
      // Found
      return true;
    }
    check = check->next;
  }
  // Not Found
  return false;
}
int number_of_moves(struct game_state start) {
  // Following Psuedo Code Structure
  struct queue q = {0}; // queue q = new_queue();
  enqueue(&q, start);
  struct linked_list seen = {0}; // List Of Previously Seen Game States

  while (q.data.head != NULL) { // while (!empty(s)) {
    struct game_state cur = dequeue(&q); // node cur = dequeue(&q);

    long long serCur = serialize(cur);
    if (seen_state(&seen, serCur)) {
      // Already Explored Game State, Ignore
      continue;
    }
    insert_at_head(&seen, serCur); // New Game State, Mark As Explored

    if (big_winner(cur)) { // if (equals(cur, search)) {
      // Successful Solution Found, Return Number Of Steps In This Path
      free_list(q.data);
      free_list(seen);
      return cur.num_steps;
    }

    // for (node child in children(cur)) { enqueue(&q, child); }
    struct game_state child; // Possible Game State, Cloned & Enqued For Each Path
    // Up Move Valid?
    if (cur.empty_row < 3) {
      child = cur;
      move_up(&child);
      enqueue(&q, child);
    }
    // Down Move Valid?
    if (cur.empty_row > 0) {
      child = cur;
      move_down(&child);
      enqueue(&q, child);
    }
    // Left Move Valid?
    if (cur.empty_col < 3) {
      child = cur;
      move_left(&child);
      enqueue(&q, child);
    }
    // Right Move Valid?
    if (cur.empty_col > 0) {
      child = cur;
      move_right(&child);
      enqueue(&q, child);
    }
  }
  free_list(q.data);
  free_list(seen);
  return -1; // No Solution
}
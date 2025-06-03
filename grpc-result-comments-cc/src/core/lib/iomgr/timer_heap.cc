Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/timer_heap.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/useful.h"

// Adjusts the position of a timer in the heap by moving it upwards
// to maintain the min-heap property (parent <= children)
// first: pointer to the start of the heap array
// i: current index of the timer being adjusted
// t: pointer to the timer being adjusted
static void adjust_upwards(grpc_timer** first, uint32_t i, grpc_timer* t) {
  while (i > 0) {
    uint32_t parent = static_cast<uint32_t>((static_cast<int>(i) - 1) / 2);
    if (first[parent]->deadline <= t->deadline) break;
    first[i] = first[parent];
    first[i]->heap_index = i;
    i = parent;
  }
  first[i] = t;
  t->heap_index = i;
}

// Adjusts the position of a timer in the heap by moving it downwards
// to maintain the min-heap property (parent <= children)
// first: pointer to the start of the heap array
// i: current index of the timer being adjusted
// length: current size of the heap
// t: pointer to the timer being adjusted
static void adjust_downwards(grpc_timer** first, uint32_t i, uint32_t length,
                             grpc_timer* t) {
  for (;;) {
    uint32_t left_child = 1u + (2u * i);
    if (left_child >= length) break;
    uint32_t right_child = left_child + 1;
    uint32_t next_i = right_child < length && first[left_child]->deadline >
                                                  first[right_child]->deadline
                          ? right_child
                          : left_child;
    if (t->deadline <= first[next_i]->deadline) break;
    first[i] = first[next_i];
    first[i]->heap_index = i;
    i = next_i;
  }
  first[i] = t;
  t->heap_index = i;
}

// Minimum number of elements required before considering shrinking
#define SHRINK_MIN_ELEMS 8
// Factor used to determine when to shrink the heap
#define SHRINK_FULLNESS_FACTOR 2

// Shrinks the heap capacity if the current count is between 8 and
// half of the current capacity divided by the fullness factor
// heap: pointer to the timer heap structure
static void maybe_shrink(grpc_timer_heap* heap) {
  if (heap->timer_count >= 8 &&
      heap->timer_count <= heap->timer_capacity / SHRINK_FULLNESS_FACTOR / 2) {
    heap->timer_capacity = heap->timer_count * SHRINK_FULLNESS_FACTOR;
    heap->timers = static_cast<grpc_timer**>(
        gpr_realloc(heap->timers, heap->timer_capacity * sizeof(grpc_timer*)));
  }
}

// Adjusts the position of a timer in the heap when its priority changes
// heap: pointer to the timer heap structure
// timer: pointer to the timer whose priority changed
static void note_changed_priority(grpc_timer_heap* heap, grpc_timer* timer) {
  uint32_t i = timer->heap_index;
  uint32_t parent = static_cast<uint32_t>((static_cast<int>(i) - 1) / 2;
  if (heap->timers[parent]->deadline > timer->deadline) {
    adjust_upwards(heap->timers, i, timer);
  } else {
    adjust_downwards(heap->timers, i, heap->timer_count, timer);
  }
}

// Initializes a timer heap structure
// heap: pointer to the timer heap structure to initialize
void grpc_timer_heap_init(grpc_timer_heap* heap) {
  memset(heap, 0, sizeof(*heap));
}

// Destroys a timer heap structure and frees allocated memory
// heap: pointer to the timer heap structure to destroy
void grpc_timer_heap_destroy(grpc_timer_heap* heap) { gpr_free(heap->timers); }

// Adds a timer to the heap
// heap: pointer to the timer heap structure
// timer: pointer to the timer to add
// Returns true if the added timer becomes the new top element
bool grpc_timer_heap_add(grpc_timer_heap* heap, grpc_timer* timer) {
  if (heap->timer_count == heap->timer_capacity) {
    heap->timer_capacity =
        std::max(heap->timer_capacity + 1, heap->timer_capacity * 3 / 2);
    heap->timers = static_cast<grpc_timer**>(
        gpr_realloc(heap->timers, heap->timer_capacity * sizeof(grpc_timer*)));
  }
  timer->heap_index = heap->timer_count;
  adjust_upwards(heap->timers, heap->timer_count, timer);
  heap->timer_count++;
  return timer->heap_index == 0;
}

// Removes a timer from the heap
// heap: pointer to the timer heap structure
// timer: pointer to the timer to remove
void grpc_timer_heap_remove(grpc_timer_heap* heap, grpc_timer* timer) {
  uint32_t i = timer->heap_index;
  if (i == heap->timer_count - 1) {
    heap->timer_count--;
    maybe_shrink(heap);
    return;
  }
  heap->timers[i] = heap->timers[heap->timer_count - 1];
  heap->timers[i]->heap_index = i;
  heap->timer_count--;
  maybe_shrink(heap);
  note_changed_priority(heap, heap->timers[i]);
}

// Checks if the timer heap is empty
// heap: pointer to the timer heap structure
// Returns true if the heap is empty, false otherwise
bool grpc_timer_heap_is_empty(grpc_timer_heap* heap) {
  return heap->timer_count == 0;
}

// Gets the top timer from the heap (the one with the earliest deadline)
// heap: pointer to the timer heap structure
// Returns pointer to the top timer
grpc_timer* grpc_timer_heap_top(grpc_timer_heap* heap) {
  return heap->timers[0];
}

// Removes the top timer from the heap
// heap: pointer to the timer heap structure
void grpc_timer_heap_pop(grpc_timer_heap* heap) {
  grpc_timer_heap_remove(heap, grpc_timer_heap_top(heap));
}
```

The comments explain:
1. The purpose of each function
2. The parameters and their meanings
3. The return values where applicable
4. The key operations being performed
5. The heap maintenance operations (adjust_upwards/downwards)
6. The memory management strategy (maybe_shrink)
7. The overall min-heap structure and its properties

The comments are concise yet informative, helping future developers understand both the high-level purpose and the implementation details of each component.
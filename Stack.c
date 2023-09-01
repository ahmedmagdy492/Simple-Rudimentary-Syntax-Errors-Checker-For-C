
#include "Stack.h"

static char arr[ARR_SIZE];

static int top = 0;

void push(char value) {
  arr[top] = value;
  ++top;
}

char peak() {
  if(top-1 < 0)
    return -1;

  return arr[top - 1];
}

char pop() {
  if(top < 0)
    return -1;
  --top;
  return arr[top];
}

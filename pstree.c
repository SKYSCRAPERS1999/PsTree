#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < argc; i++) {
    assert(argv[i]); // specification
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]); // specification
  return 0;
}

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main() {
    assert(false && "TDD!!!");
    
    printf("Tests Passed.\n");
    return 0;
}
#include "stack.h"

int main() {
    
    stack_t* stk = new_stack();

    push_stack(10, stk);
    push_stack(20, stk);
    push_stack(30, stk);
    
    free_stack(stk);

    return 0;
}

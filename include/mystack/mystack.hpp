#pragma once

namespace mystack {
    template <typename T>
    struct stack;

    /**
     * @author Diego Graziati
     * @version V1.0
     */
    int init_stack (mystack::stack<int> &stack, int capacity);

    /**
     * @author Diego Graziati
     * @version V1.0
     */
    int destroy_stack (mystack::stack<int> &stack);

    /**
     * @author Diego Graziati
     * @version V1.0
     */
    int s_pop (mystack::stack<int> &stack, int &elem);

    /**
     * @author Diego Graziati
     * @version V1.0
     * @details This is a ***Thread-safe*** mystack::stack push operation.
     * @return 0 = everything went as expected and the operation was a ***SUCCESS***.
     *         1 = the input element type is different from the mystack::stack inner elements' array type, thus making it impossible to successfully push the input element into the stack.
     */
    int s_push (mystack::stack<int> &stack, int elem);

    bool is_stack_full (mystack::stack<int> &stack);
}

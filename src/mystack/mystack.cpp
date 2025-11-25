#include <mystack/mystack.hpp>

void mystack::init_stack(mystack::stack<int> &stack, int capacity)
{
    stack.elems = new int[capacity];
    stack.size = 0;
    stack.capacity = capacity;
    pthread_mutex_init(&stack.can_access, nullptr);
    stack.full = new sem_t;
    stack.empty = new sem_t;
    sem_init(stack.full, 0, 0);
    sem_init(stack.empty, 0, capacity);
}

void mystack::destroy_stack (mystack::stack<int> &stack)
{
    delete[] stack.elems;
    pthread_mutex_destroy(&stack.can_access);
    sem_close(stack.full);
    sem_close(stack.empty);
    delete stack.full;
    delete stack.empty;
}

int mystack::s_pop (mystack::stack<int> &stack, int &elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return 1;
    }

    sem_wait(stack.full);
    pthread_mutex_lock(&stack.can_access);
    elem = stack.elems[--stack.size];
    pthread_mutex_unlock(&stack.can_access);
    sem_post(stack.empty);

    return 0;
}

int mystack::s_push (mystack::stack<int> &stack, int elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return 1;
    }

    sem_wait(stack.empty);
    pthread_mutex_lock(&stack.can_access);
    stack.elems[stack.size++]=elem;
    pthread_mutex_unlock(&stack.can_access);
    sem_post(stack.full);

    return 0;
}
#include <mystack/mystack.hpp>

template<typename T> void mystack::init_stack(mystack::stack<T> &stack, int capacity)
{
    stack.elems = new T[capacity];
    stack.size = 0;
    stack.capacity = capacity;
    pthread_mutex_init(&stack.can_access, nullptr);
    stack.full = new sem_t;
    stack.empty = new sem_t;
    sem_init(stack.full, 0, 0);
    sem_init(stack.empty, 0, capacity);
}

template<typename T> void mystack::destroy_stack (mystack::stack<T> &stack)
{
    delete[] stack.elems;
    pthread_mutex_destroy(&stack.can_access);
    sem_close(stack.full);
    sem_close(stack.empty);
    delete stack.full;
    delete stack.empty;
}

template<typename T> int mystack::s_pop (mystack::stack<T> &stack, T &elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return 1;
    }

    sem_wait(stack.empty);
    pthread_mutex_lock(stack.can_access);
    elem = stack.elems[stack.size];
    stack.size--;
    pthread_mutex_unlock(stack.can_access);
    sem_post(stack.full);

    return 0;
}

template<typename T> int mystack::s_push (mystack::stack<T> &stack, T elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return 1;
    }

    sem_wait(stack.full);
    pthread_mutex_lock(stack.can_access);
    stack.size++;
    stack.elems[stack.size]=elem;
    pthread_mutex_unlock(stack.can_access);
    sem_post(stack.empty);

    return 0;
}
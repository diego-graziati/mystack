#include <mystack/mystack.hpp>
#include <mystack/pthread/mystack_pthread_types.hpp>
#include <mystack/pthread/mystack_pthread_errors.hpp>

int mystack::init_stack(mystack::stack<int> &stack, int capacity)
{
    stack.elems = new int[capacity];

    if (stack.elems == nullptr)
    {
        return MYSTACK_ERROR_STACK_INIT_ELEMS_NULLPTR;
    }

    stack.size = 0;
    stack.capacity = capacity;
    stack.can_access = new pthread_mutex_t;

    if (stack.can_access == nullptr)
    {
        return MYSTACK_ERROR_STACK_INIT_MUTEX_NULLPTR;
    }

    if (pthread_mutex_init(stack.can_access, nullptr)) 
    {
        return MYSTACK_ERROR_STACK_INIT_MUTEX_INIT_FAIL;
    }
    

    stack.full = new sem_t;
    if (stack.full == nullptr)
    {
        return MYSTACK_ERROR_STACK_INIT_FULL_NULLPTR;
    }

    stack.empty = new sem_t;

    if (stack.empty == nullptr)
    {
        return MYSTACK_ERROR_STACK_INIT_EMPTY_NULLPTR;
    }

    if (sem_init(stack.full, 0, 0))
    {
        return MYSTACK_ERROR_STACK_INIT_FULL_INIT_FAIL;
    }

    if (sem_init(stack.empty, 0, capacity))
    {
        return MYSTACK_ERROR_STACK_INIT_EMPTY_INIT_FAIL;
    }

    return 0;
}

int mystack::destroy_stack (mystack::stack<int> &stack)
{
    delete[] stack.elems;

    if (pthread_mutex_destroy(stack.can_access))
    {
        return MYSTACK_ERROR_STACK_DESTROY_MUTEX_DESTROY;
    }
    
    if (sem_close(stack.full))
    {
        return MYSTACK_ERROR_STACK_DESTROY_FULL_CLOSE;
    }

    if (sem_close(stack.empty))
    {
        return MYSTACK_ERROR_STACK_DESTROY_EMPTY_CLOSE;
    }

    delete stack.full;
    delete stack.empty;

    return 0;
}

int mystack::s_pop (mystack::stack<int> &stack, int &elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return MYSTACK_ERROR_STACK_POP_DIFFERENT_TYPES;
    }

    if (sem_wait(stack.full))
    {
        return MYSTACK_ERROR_STACK_POP_FULL_WAIT_FAIL;
    }
    
    if (pthread_mutex_lock(stack.can_access))
    {
        return MYSTACK_ERROR_STACK_POP_MUTEX_LOCK_FAIL;
    }

    elem = stack.elems[--stack.size];
    
    if (pthread_mutex_unlock(stack.can_access))
    {
        return MYSTACK_ERROR_STACK_POP_MUTEX_UNLOCK_FAIL;
    }

    if (sem_post(stack.empty))
    {
        return MYSTACK_ERROR_STACK_POP_EMPTY_POST_FAIL;
    }

    return 0;
}

int mystack::s_push (mystack::stack<int> &stack, int elem)
{
    if (sizeof(elem) != sizeof(stack.elems[0])) 
    {
        return MYSTACK_ERROR_STACK_PUSH_DIFFERENT_TYPES;
    }

    if (sem_wait(stack.empty))
    {
        return MYSTACK_ERROR_STACK_PUSH_EMPTY_WAIT_FAIL;
    }

    if (pthread_mutex_lock(stack.can_access))
    {
        return MYSTACK_ERROR_STACK_PUSH_MUTEX_LOCK_FAIL;
    }

    stack.elems[stack.size++]=elem;
    
    if (pthread_mutex_unlock(stack.can_access))
    {
        return MYSTACK_ERROR_STACK_PUSH_MUTEX_UNLOCK_FAIL;
    }

    if (sem_post(stack.full))
    {
        return MYSTACK_ERROR_STACK_PUSH_FULL_POST_FAIL;
    }
    
    return 0;
}
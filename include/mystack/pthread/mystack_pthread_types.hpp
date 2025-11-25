#pragma once
#include <pthread.h>
#include <semaphore.h>

namespace mystack {
    template <typename T>
    struct stack
    {
        T *elems;
        int size;
        int capacity;
        pthread_mutex_t* can_access;
        sem_t *full, *empty;
    };
}
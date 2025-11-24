#include <mytest/test_suit_tools.hpp>
#include <mystack/mystack.hpp>
#include <test_mystack.hpp>

void mytest::test_list()
{
    int num_successfull_tests = 0;
    num_successfull_tests += mytest::can_the_stack_be_initialized<int>();
    num_successfull_tests += mytest::can_the_stack_push_an_element<int>();
    num_successfull_tests += mytest::can_the_stack_pop_an_element<int>();
}

template<typename T> int mytest::can_the_stack_be_initialized()
{
    int success = 1;

    std::fprintf(stdout, "\tName: \"can_the_stack_be_initialized\"\n\tType size: %ld bytes\n\tResult:\n\t\t", sizeof(T));
    mystack::stack<T> stack;
    mystack::init_stack(stack, 5);
    success = assert
        (
            (stack.elems != nullptr && stack.full != nullptr && stack.empty != nullptr),
            "Stack successfully initialized!",
            "The stack failed to initialize!"
        );
    mystack::destroy_stack<T>(stack);

    return !success ? 1 :  0;
}

template<typename T> int mytest::can_the_stack_push_an_element()
{
    int success = 1;
    T push_element = 4;

    std::fprintf(stdout, "\tName: \"can_the_stack_push_an_element\"\n\tType size: %ld bytes\n\tResult:\n\t\t", sizeof(T));
    mystack::stack<T> stack;
    mystack::init_stack<T>(stack, 5);
    success = assert
        (
            (!mystack::s_push<T>(stack, push_element) && stack.size == 1 && stack.elems[0] == push_element),
            "Element successfully pushed into the stack!",
            "Element push into the stack failed!"
        );
    mystack::destroy_stack<T>(stack);

    return !success ? 1 :  0;
}

template<typename T> int mytest::can_the_stack_pop_an_element()
{
    int success = 1;
    T push_element = 4;
    T pop_element;

    std::fprintf(stdout, "\tName: \"can_the_stack_pop_an_element\"\n\tType size: %ld bytes\n\tResult:\n\t\t", sizeof(T));
    mystack::stack<T> stack;
    mystack::init_stack<T>(stack, 5);
    mystack::s_push<T>(stack, push_element);

    success = assert
        (
            (!mystack::s_pop<T>(stack, pop_element) && stack.size == 0 && pop_element == push_element),
            "Element successfully popped from the stack!",
            "Element pop from the stack failed!"
        );
    mystack::destroy_stack<T>(stack);
    
    return !success ? 1 :  0;
}
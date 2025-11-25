#include <mytest/test_suit_tools.hpp>
#include <mystack/mystack.hpp>
#include <test_mystack.hpp>

void mytest::test_list()
{
    int num_successfull_tests = 0;
    num_successfull_tests += mytest::can_the_stack_be_initialized();
    num_successfull_tests += mytest::can_the_stack_push_an_element();
    num_successfull_tests += mytest::can_the_stack_pop_an_element();
}

int mytest::can_the_stack_be_initialized()
{
    int success = 1;

    std::fprintf(stdout, "\tName: \"can_the_stack_be_initialized\"\n\tType size: %ld bytes\n\tResult:\n", sizeof(int));
    mystack::stack<int> stack;
    mystack::init_stack(stack, 5);
    success = assert
        (
            (stack.elems != nullptr && stack.full != nullptr && stack.empty != nullptr),
            "Stack successfully initialized!",
            "The stack failed to initialize!"
        );
    mystack::destroy_stack(stack);

    return !success ? 1 :  0;
}

int mytest::can_the_stack_push_an_element()
{
    int success = 1;
    int push_element = 4;

    std::fprintf(stdout, "\tName: \"can_the_stack_push_an_element\"\n\tType size: %ld bytes\n\tResult:\n", sizeof(int));
    mystack::stack<int> stack;
    mystack::init_stack(stack, 5);
    int state = mystack::s_push(stack, push_element);
    //std::fprintf(stdout, "\t\tDEBUG: \n\t\t- Stack.elems: %d\n-Stack.elems[0] = %d\n", stack.size, stack.elems[0]);
    success = assert
        (
            (!state && stack.size == 1 && stack.elems[0] == push_element),
            "Element successfully pushed into the stack!",
            "Element push into the stack failed!"
        );
    mystack::destroy_stack(stack);

    return !success ? 1 :  0;
}

int mytest::can_the_stack_pop_an_element()
{
    int success = 1;
    int push_element = 4;
    int pop_element;

    std::fprintf(stdout, "\tName: \"can_the_stack_pop_an_element\"\n\tType size: %ld bytes\n\tResult:\n", sizeof(int));
    mystack::stack<int> stack;
    mystack::init_stack(stack, 5);
    mystack::s_push(stack, push_element);
    //std::fprintf(stdout, "\t\tDEBUG: \n\t\t- Stack.elems[0]: %d\n", stack.elems[0]);
    int state = mystack::s_pop(stack, pop_element);
    //std::fprintf(stdout, "\t\tDEBUG: \n\t\t- Stack.elems: %d\n\t\t- pop_elem = %d\n", stack.size, pop_element);

    success = assert
        (
            (!state && stack.size == 0 && pop_element == push_element),
            "Element successfully popped from the stack!",
            "Element pop from the stack failed!"
        );
    mystack::destroy_stack(stack);
    
    return !success ? 1 :  0;
}
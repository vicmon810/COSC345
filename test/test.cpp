#include <iostream>

bool funcion(int a)
{
    return a > 5;
}

// If parameter is not true, test fails
// This check function would be provided by the test framework
#define IS_TRUE(x)
{
    if (!(x))
        std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;
}

// Test for function1()
// You would need to write these even when using a framework
void test_function1()
{
    IS_TRUE(!function1(0));
    IS_TRUE(!function1(5));
    IS_TRUE(function1(10));
}

int main(void)
{
    // Call all tests. Using a test framework would simplify this.
    test_function1();
}
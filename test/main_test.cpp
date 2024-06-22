#include "all.h"
#include <iostream>
#include <memory>

using namespace cldl_std;

int main() {
    Object obj = newobj<Object>();
    Stack<int> stk = newobj<Stack<int>>();
    stk->ele = -1;
    std::cout << stk->ele << std::endl;
    stk->ele = 2;
    std::cout << stk->ele << std::endl;
    return 0;
}

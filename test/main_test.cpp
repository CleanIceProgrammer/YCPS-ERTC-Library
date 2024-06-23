#include <iostream>
#include <string>
#include <exception>

#define __ERTC_NULL
#include "all.h"

using namespace ertc_std;

sys_int main() {
    std::cout << "test ERTC library" << std::endl;
    std::cout << "creating an object" << std::endl;
    Object obj = newobj<Object>();
    std::cout << "object id: " << obj->id() << std::endl;
    std::cout << "creating a stack" << std::endl;
    Stack<int32> temp_stk = newobj<Stack<int32>>();
    std::cout << "stack id: " << temp_stk->id() << std::endl;
    std::cout << "cast to an object" << std::endl;
    Object stk_obj = temp_stk;
    std::cout << "object of stack id: " << stk_obj->id() << std::endl;
    std::cout << "try to cast to a stack" << std::endl;
    Stack<int32> stk = objcast<Stack<int32>>(stk_obj);
    std::cout << "try to cast an invalid object to a stack" << std::endl;
    Stack<int32> stk_fail = objcast<Stack<int32>>(newobj<Object>());
    std::cout << "failed: " << std::boolalpha << (stk_fail == null) << std::endl;
    std::cout << "control stack" << std::endl;
    while (true) {
        std::cout << std::endl << "choose one: " << std::endl;
        std::cout << "1. exit" << std::endl;
        std::cout << "2. push" << std::endl;
        std::cout << "3. pop" << std::endl;
        std::cout << "4. top" << std::endl;
        std::cout << "5. size" << std::endl;
        std::cout << "6. empty" << std::endl;
        std::cout << "7. clear" << std::endl;
        std::cout << "8. iterate ERTC" << std::endl;
        std::cout << "9. iterate LANG" << std::endl;
        std::string choice_str;
        std::getline(std::cin, choice_str);
        int32 choice;
        try {
            choice = std::stoi(choice_str);
        } catch (const std::exception& exc) {
            std::cout << "invalid: " << exc.what() << std::endl;
            continue;
        }
        bool break_while = false;
        switch (choice) {
            case 1: {
                break_while = true;
                break;
            }
            case 2: {
                std::cout << "element: ";
                std::string ele_str;
                std::getline(std::cin, ele_str);
                int32 ele;
                try {
                    ele = std::stoi(ele_str);
                } catch (const std::exception& exc) {
                    std::cout << "invalid: " << exc.what() << std::endl;
                    break;
                }
                stk->push(ele);
                std::cout << "push: " << ele << std::endl;
                break;
            }
            case 3: {
                int32 res;
                try {
                    res = stk->pop();
                } catch (OutOfRangeException exc) {
                    std::cout << "out of range exception: " << exc->what() << std::endl;
                }
                std::cout << "pop: " << res << std::endl;
                break;
            }
            case 4: {
                int32 res;
                try {
                    res = stk->top();
                } catch (OutOfRangeException exc) {
                    std::cout << "out of range exception: " << exc->what() << std::endl;
                }
                std::cout << "top: " << res << std::endl;
                break;
            }
            case 5: {
                size_type size = stk->size();
                std::cout << "size: " << size << std::endl;
                break;
            }
            case 6: {
                bool empty = stk->empty();
                std::cout << "empty: " << std::boolalpha << empty << std::endl;
                break;
            }
            case 7: {
                stk->clear();
                std::cout << "clear" << std::endl;
                break;
            }
            case 8: {
                std::cout << "out of range? [y/n]";
                std::string choice;
                std::getline(std::cin, choice);
                if (choice.size() != 1uz) {
                    std::cout << "invalid" << std::endl;
                    break;
                }
                switch (std::tolower(choice[0])) {
                    case 'y': {
                        std::cout << "iterate ERTC: ";
                        auto iter = stk->iterator();
                        while (true) {
                            try {
                                std::cout << iter->get_value() << " ";
                                iter->next();
                            } catch (NoNextIteratorException exc) {
                                std::cout << std::endl << "no next iterator exception: " << exc->what() << std::endl;
                                break;
                            } catch (OutOfRangeException exc) {
                                std::cout << std::endl << "out of range exception: " << exc->what() << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 'n': {
                        std::cout << "iterate ERTC: ";
                        auto iter = stk->iterator();
                        try {
                            std::cout << iter->get_value() << " ";
                        } catch (OutOfRangeException exc) {
                            std::cout << std::endl;
                            break;
                        }
                        while (iter->has_next()) {
                            iter->next();
                            std::cout << iter->get_value() << " ";
                        }
                        std::cout << std::endl;
                        break;
                    }
                    default: {
                        std::cout << "invalid choice" << std::endl;
                        break;
                    }
                }
                break;
            }
            case 9: {
                std::cout << "iterate LANG: ";
                for (int32 ele : *stk) {
                    std::cout << ele << " ";
                }
                std::cout << std::endl;
                break;
            }
            default: {
                std::cout << "invalid choice" << std::endl;
                break;
            }
        }
        if (break_while) {
            break;
        }
    }
    std::cout << "exited" << std::endl;
    return 0;
}

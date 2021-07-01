#pragma once

// stack test : ���� stack �Ľӿ� �� push ������

#include <stack>

#include "../stack.h"
#include "test.h"

namespace LT
{
    namespace test
    {
        namespace stack_test
        {

            void stack_print(LT::stack<int> s)
            {
                while (!s.empty())
                {
                    std::cout << " " << s.top();
                    s.pop();
                }
                std::cout << std::endl;
            }

            // stack �ı������
#define STACK_COUT(s) do {                       \
    std::string s_name = #s;                     \
    std::cout << " " << s_name << " :";          \
    stack_print(s);                              \
} while(0)

#define STACK_FUN_AFTER(con, fun) do {           \
  std::string fun_name = #fun;                   \
  std::cout << " After " << fun_name << " :\n";  \
  fun;                                           \
  STACK_COUT(con);                               \
} while(0)

            void stack_test()
            {
                std::cout << "[===============================================================]" << std::endl;
                std::cout << "[----------------- Run container test : stack ------------------]" << std::endl;
                std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
                int a[] = { 1,2,3,4,5 };
                LT::deque<int> d1(5);
                LT::stack<int> s1;
                LT::stack<int> s2(5);
                LT::stack<int> s3(5, 1);
                LT::stack<int> s4(a, a + 5);
                LT::stack<int> s5(d1);
                LT::stack<int> s6(std::move(d1));
                LT::stack<int> s7(s2);
                LT::stack<int> s8(std::move(s2));
                LT::stack<int> s9;
                s9 = s3;
                LT::stack<int> s10;
                s10 = std::move(s3);
                LT::stack<int> s11{ 1,2,3,4,5 };
                LT::stack<int> s12;
                s12 = { 1,2,3,4,5 };

                STACK_FUN_AFTER(s1, s1.push(1));
                STACK_FUN_AFTER(s1, s1.push(2));
                STACK_FUN_AFTER(s1, s1.push(3));
                STACK_FUN_AFTER(s1, s1.pop());
                STACK_FUN_AFTER(s1, s1.emplace(4));
                STACK_FUN_AFTER(s1, s1.emplace(5));
                std::cout << std::boolalpha;
                FUN_VALUE(s1.empty());
                std::cout << std::noboolalpha;
                FUN_VALUE(s1.size());
                FUN_VALUE(s1.top());
                while (!s1.empty())
                {
                    STACK_FUN_AFTER(s1, s1.pop());
                }
                STACK_FUN_AFTER(s1, s1.swap(s4));
                STACK_FUN_AFTER(s1, s1.clear());
                PASSED;
#if PERFORMANCE_TEST_ON
                std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                std::cout << "|         push        |";
#if LARGER_TEST_DATA_ON
                CON_TEST_P1(stack<int>, push, rand(), LEN1 _LL, LEN2 _LL, LEN3 _LL);
#else
                CON_TEST_P1(stack<int>, push, rand(), LEN1 _L, LEN2 _L, LEN3 _L);
#endif
                std::cout << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                PASSED;
#endif
                std::cout << "[----------------- End container test : stack ------------------]" << std::endl;
            }

        } // namespace stack_test
    } // namespace test
} // namespace LT
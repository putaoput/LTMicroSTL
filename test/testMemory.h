//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
#include "../memory.h"
#include "test.h"



namespace  LT
{
    namespace test
    {
        namespace memory_test {
            void memory_test() {
                {
                    LT::shared_ptr<int> spIntPtr(new int(10));
                    auto spIntPtr2 = spIntPtr;
                }       
            }
        }
    }
}
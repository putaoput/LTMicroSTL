#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <atomic>
#include <thread>
#include "../thread_safe_vector.h"

#define TESTNUM 10000000
#define EXPAN__TEST 0.1
namespace LT {
    namespace test {
        using namespace std;
        static int i;
        static vector<int>ret1, ret2;
        static thread_safe_vector<int, int(TESTNUM * EXPAN__TEST)> arr;
        

        void increase(vector<int>* _arr)
        {

            for (int j = 0; j < TESTNUM; ++j) {
                ++(*_arr)[++i];
            }
            return;
        }

        void testAtomic()
        {
            //atomic多线程测试
            i = 0;
            vector<int> arr(2 * TESTNUM);
            thread thread1(increase, &arr);
            thread thread2(increase, &arr);
            thread1.join();
            thread2.join();
            bool isSeccess = true;
            for (int j = 0; j < 2 * TESTNUM; ++j) {
                if (arr[j] == 2)
                {
                    isSeccess = true;
                    cout << j << "  " << arr[j] << endl;
                }
            }
            cout << "atomic test is " << (isSeccess ? "" : "not" ) << "ideal" << '\n';
        }
       
        namespace thread_safe_vector_test {

            
            void get(vector<int>* _ret, thread_safe_vector<int,int(EXPAN__TEST * TESTNUM)>* _arr)
            {
                for (int i = 0; i < TESTNUM; ++i)
                {
                    int tmp = _arr->pop_front_choke();                    
                    _ret->push_back(tmp);
                }

            }

            void push(int _initValue, thread_safe_vector<int, int(EXPAN__TEST * TESTNUM)>* _arr)
            {
                for (int i = 0; i < TESTNUM; ++i)
                {
                    int tmp =  _initValue  + i;
                    _arr->push_back_choke(tmp);
                }
            }

            void test_thread_safe_vactor()
            {
                std::cout << "[===============================================================]" << std::endl;
                std::cout << "[----------------- Run container test : thread_safe_vector ------------------]" << std::endl;
                std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
                
                
                thread produceThread1(push, 0, &arr);
                thread produceThread2(push, TESTNUM, &arr);
                thread costThread1(get, &ret1, &arr);
                thread costThread2(get, &ret2, &arr);
                
                costThread2.join();
                produceThread1.join();
                
                costThread1.join();

                produceThread2.join();

                vector<int> ret(ret1.size() + ret2.size());
                for (int val : ret1)
                {
                    ++ret[val];
                }
                for (int val : ret2)
                {
                    ++ret[val];
                }
                bool isSuccess = true;
                for (int i = 0; i < 2 * TESTNUM; ++i)
                {
                    if (ret[i] != 1) {
                        cout << "异常元素:" << i  << "  异常值:" << ret[i]<< "\n";
                        isSuccess = false;
                    }
                }
                cout << "test thread_safe_vector " << (isSuccess ? "pass" : "failed" ) << '\n' ;
       
                //验证循环溢出正确性
               /* unsigned char a = 0;
                for (int i = 0; i < pow(2, 10); ++i)
                {
                    cout << int(a++) << endl;
                }*/
                return;
            }  
        }
    }
}




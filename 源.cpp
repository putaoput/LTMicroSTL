//#include "test/testThreadSafeVector.h"
#include "test/testVector.h"
#include "test/testList.h"
#include "test/testDeque.h"
#include "test/testString.h"
#include "test/testAlgo.h"

#include "stl_algo.h"
#include <string>
#include "iterator.h"
#include "allocator.h"
#include <iostream>


using namespace std;
int main()
{
	LT::test::algorithm_test::sort_test();
	LT::test::vector_test::vector_test();
	LT::test::list_test::list_test();
	//LT::test::deque_test::deque_test();
	LT::test::string_test::string_test();
	//LT::test::thread_safe_vector_test::test_thread_safe_vactor();

	return 0;
}
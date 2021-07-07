//#include "test/testVector.h"
//#include "test/testList.h"
#include "test/testDeque.h"
//#include "test/testString.h"
#include "stl_algo.h"
#include <string>
#include "iterator.h"
#include "allocator.h"
#include <iostream>



using namespace std;

  struct p
  {
	  int pp;
  };

  struct c :public p
  {
	  int cc;
  };
int main()
{
	//LT::test::vector_test::vector_test();
	//LT::test::list_test::list_test();
	LT::test::deque_test::deque_test();
	//LT::test::string_test::string_test();

	return 0;
}
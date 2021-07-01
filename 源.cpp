#include "test/testVector.h"
#include "test/testList.h"
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
	//int* a = 0;
	LT::vector<int> arr  = { 4,2,7,9,1,323,612,241,6,4,75,57 };
	LT::sort(arr.begin(), arr.end());
	const char* str = "abcde";
	c* aaa = new c;
	aaa->pp = 0;

	return 0;
}
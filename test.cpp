#include <iostream>
#include <vector>
#include "algorithm.h"
#include "util.h"
using namespace std;

int main() {

	//测试模板函数实例化,发现c++的模板函数可以自动实例化(在不会引起歧义的场合)
	//long _a = 0, _b = 1;
	//cout << " &_a = " << &_a << " &_b = " << &_b << endl;
	//long &a = _a; long &b = _b;
	//cout << a + b << endl;
	//long&& tmp = move(a);
	//cout << "&tmp = " << &tmp << " &a = " << &a << " &b = " << &b << endl;

	//a = move(b);
	//cout << "tmp = " << tmp << endl;
	//cout << " &a = " << &a << " &b = " << &b << endl;
	//b = move(tmp);
	//cout << " &tmp = " << &tmp << " &b = " << &b << endl;

	vector<int> arr = { 1,5,6,48,8,46,1,6,4,9,9,5,64,46,46,45,789,66,41,46,456,46,13,46,48964141,461,13,6,163,46523,16532,456,2635,162 };
	LT::sort(arr.begin(), arr.end());

	return 0;
}
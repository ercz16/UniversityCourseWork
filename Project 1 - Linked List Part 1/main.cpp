#include <iostream>
#include <vector>

#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList<int> list;

	for(int i = 0; i < 10; ++i)
		list.AddHead(i);

	auto p = list.GetNode(15);


	cout << endl;

	return 0;
}
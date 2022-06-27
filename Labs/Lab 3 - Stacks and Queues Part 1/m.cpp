#include <iostream>
#include "ABS.h"
#include "ABQ.h"

#include "leaker.h"

using namespace std;

int main() {
  ABS<int> a(10);

  for(int i = 0; i < 10; ++i) a.push(i);

  ABQ<int> b(5);

  for(int i = 0; i < 5; ++i) b.enqueue(i);

  b.Print();

  cout << "dequeue: " << b.dequeue() << endl;
  cout << "dequeue: " << b.dequeue() << endl;
  b.Print();
  cout << "dequeue: " << b.dequeue() << endl;
  cout << "dequeue: " << b.dequeue() << endl;
  b.Print();
  cout << "dequeue: " << b.dequeue() << endl;
  b.Print();

  return 0;
} //EOM
//EOF


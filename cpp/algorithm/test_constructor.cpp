
#include <iostream>



namespace Arr {template <class T> class Arr {
public:
  Arr() : data(0), sz(0) {}
  Arr(unsigned size) : sz(size), data(new T[size]) {}
  ~Arr() { delete[] data; }
  const T &operator[](unsigned n) const {
    if (n >= sz || data == 0) {
      throw "Array subscript out of range";
    }
    return data[n];
  }
  T &operator[](unsigned n) {
    if (n >= sz || data == 0) {
      throw "Array subscript out of range";
    }
    return data[n];
  }
  operator const T *() const { return data; }
  operator T *() { return data; }

private:
  T *data;
  unsigned sz;
  Arr(const Arr &a);
  Arr &operator=(const Arr &);
};
}

class Test {
public:
  Test();
  Test(const Test &);
  ~Test();
  Test &operator=(const Test &);

private:
  static int count;
  int id;
};
int Test::count = 0;
Test::Test() {
  id = ++count;
  std::cout << "Test " << id << " default constructor " << std::endl;
}
Test::Test(const Test &t) {
  id = ++count;
  std::cout << "Test " << id << " copied from " << t.id << std::endl;
}
Test &Test::operator=(const Test &t) {
  std::cout << "Test " << id << " assigned from " << t.id << std::endl;
}
Test::~Test() {std:: cout << "Test " << id << " destroyed" << std::endl; }
// Test 1 default constructor
// Test 2 copied from 1
// Test 1 assigned from 2
// Test 2 destroyed
// Test 1 destroyed
int main() {
  Arr::Arr<int> x(10);
  int i;
  for(i = 0; i < 10; i++){
    x[i] = i;
  }

  Test s;
  Test t(s);
  s = t;
}
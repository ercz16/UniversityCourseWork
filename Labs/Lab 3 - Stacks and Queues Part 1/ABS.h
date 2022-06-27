#pragma once 

template <typename T>
class ABS {

  T* arr;
  unsigned int size;
  unsigned int capacity;

public:
  const float scale_factor = 2.0f;
  
  //constructors
  ABS();
  ABS(int capacity);
  ABS(const ABS &d);

  //Copy Assignment Operator
  ABS<T>& operator=(const ABS<T> &d);

  //Destructor
  ~ABS();

  //Mutators
  void push(T data);
  T pop();
  T peek();
  
  //Get Methods
  unsigned int getSize();
  unsigned int getMaxCapacity();
  T* getData();

  //Print
  void Print();

};

template <typename T>
ABS<T>::ABS() {
  this->size = 0;
  this->capacity = 1;
  this->arr = new T[1];
}

template <typename T>
ABS<T>::ABS(int capacity) {
  this->size = 0;
  this->capacity = capacity;
  this->arr = new T[capacity];
}

template <typename T>
ABS<T>::ABS(const ABS &d) {
  this->size = d.size;
  this->capacity = d.capacity;
  this->arr = new T[capacity];
  for(int i = 0; i < size; ++i)
    this->arr[i] = d.arr[i];
}

template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T> &d) {
  //member to member copy
  this->size = d.size;
  this->capacity = d.capacity;
  //delete old arr
  delete[] this->arr;
  //copy new arr
  this->arr = new T[d.capacity];
  for(int i = 0; i < size; ++i)
    this->arr[i] = d.arr[i];

  return *this;
}

template<typename T>
ABS<T>::~ABS() {
  delete[] this->arr;
}

template<typename T>
void ABS<T>::push(T data) {
  if(size == capacity) {
    //update capacity
    capacity = capacity * scale_factor;

    //create new array and copy values
    T* newArray = new T[capacity];
    for(unsigned int i = 0; i < size; ++i)
      newArray[i] = this->arr[i];

    //delete old array
    delete[] this->arr;

    //redirect pointer to new array and add new data
    this->arr = newArray;
    this->arr[size] = data;

    //update size
    ++size;
  } else {
    this->arr[size] = data;
    ++size;
  }
}

template<typename T>
T ABS<T>::pop() {
  if(size == 0)
    throw std::runtime_error("cannot pop empty stack");

  T result = this->arr[size - 1];
  --size;

  if(capacity > 1 && static_cast<float>(size) / capacity < (1 / scale_factor)) {
    capacity /= 2;
    T* newArray = new T[capacity];
    for(unsigned int i = 0; i < size; ++i)
      newArray[i] = this->arr[i];
    
    delete[] this->arr;
    this->arr = newArray;
  }
  return result;
}

template<typename T>
T ABS<T>::peek() {
  if(size == 0)
    throw std::runtime_error("cannot peek empty stack");
  return this->arr[size-1];
}

template<typename T>
unsigned int ABS<T>::getSize() {
  return size;
}

template<typename T>
unsigned int ABS<T>::getMaxCapacity() {
  return capacity;
}

template<typename T>
T* ABS<T>::getData() {
  return arr;
}

template<typename T>
void ABS<T>::Print() {
  for(unsigned int i = 0; i < size; ++i)
    std::cout << arr[i] << std::endl;
}

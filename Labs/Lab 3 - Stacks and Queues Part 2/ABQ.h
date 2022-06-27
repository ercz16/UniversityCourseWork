#pragma once 

template <typename T>
class ABQ {

  T* arr;
  unsigned int front;
  unsigned int size;
  unsigned int capacity;

public:
  const float scale_factor = 2.0f;

  //constructors
  ABQ();
  ABQ(int capacity);
  ABQ(const ABQ &d);

  //Copy Assignment Operator
  ABQ<T>& operator=(const ABQ<T> &d);

  //Destructor
  ~ABQ();

  //Mutators
  void enqueue(T data);
  T dequeue();
  T peek();
  
  //Get Methods
  unsigned int getSize();
  unsigned int getMaxCapacity();
  T* getData();

  //Print
  void Print();

};

template <typename T>
ABQ<T>::ABQ() {
  this->front = 0;
  this->size = 0;
  this->capacity = 1;
  this->arr = new T[1];
}

template <typename T>
ABQ<T>::ABQ(int capacity) {
  this->front = 0;
  this->size = 0;
  this->capacity = capacity;
  this->arr = new T[capacity];
}

template <typename T>
ABQ<T>::ABQ(const ABQ &d) {
  this->front = 0;
  this->size = d.size;
  this->capacity = d.capacity;
  this->arr = new T[d.capacity];
  for(unsigned int i = 0; i < d.size; ++i)
    this->arr[i] = d.arr[front + i];
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T> &d) {
  //member to member copy
  this->front = 0;
  this->size = d.size;
  this->capacity = d.capacity;
  //delete old arr
  delete[] this->arr;
  //copy new arr
  this->arr = new T[d.capacity];
  for(unsigned int i = 0; i < d.size; ++i)
    this->arr[i] = d.arr[front + i];

  return *this;
}

template<typename T>
ABQ<T>::~ABQ() {
  delete[] this->arr;
}

template<typename T>
void ABQ<T>::enqueue(T data) {

  if (size == capacity) {
    //update capacity
    capacity = capacity * scale_factor;

    //create new array and copy values
    T* newArray = new T[capacity];
    for(unsigned int i = 0; i < size; ++i)
      newArray[i] = this->arr[front + i];

    //delete old array
    delete[] this->arr;

    //redirect pointer to new array
    this->arr = newArray;
    front = 0;
  } 

  //add new data
  this->arr[front + size] = data;
  ++size;
}

template<typename T>
T ABQ<T>::dequeue() {
  T result;
  if(size == 0)
    throw std::runtime_error("queue is empty");
  if(size == 1 && capacity == 1) {
    --size;
    result = this->arr[front];
  } else {
    ++front;
    --size;
    result =  this->arr[front-1];
  }
  if(capacity > 1 && static_cast<float>(size) / capacity < 1 / scale_factor) {
    capacity /= 2;
    T* newArray = new T[capacity];
    for(unsigned int i = 0; i < size; ++i)
      newArray[i] = this->arr[front + i];

    delete[] this->arr;
    this->arr = newArray;
    front = 0;
  }
  return result;
}

template<typename T>
T ABQ<T>::peek() {
  if(size == 0)
    throw std::runtime_error("queue is empty");
  return this->arr[front];
}

template<typename T>
unsigned int ABQ<T>::getSize() {
  return size;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity() {
  return capacity;
}

template<typename T>
T* ABQ<T>::getData() {
  return arr + front;
}

template<typename T>
void ABQ<T>::Print() {
  for(unsigned int i = 0; i < size; ++i)
    std::cout << arr[front + i] << std::endl;
  std::cout << "size: " << size << " capacity: " << capacity << std::endl;
}


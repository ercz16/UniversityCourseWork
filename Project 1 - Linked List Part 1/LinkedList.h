#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		LinkedList<T>::Node* next;
		LinkedList<T>::Node* prev;
	};
private:
	// Vars
	LinkedList<T>::Node* HeadPtr;
	LinkedList<T>::Node* TailPtr;
	int ListSize;

public:
	/*=== Behaviors ===*/
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	/*=== Accessors ===*/
	unsigned int NodeCount() const;
	void FindAll(std::vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	LinkedList<T>::Node* Head();
	//const LinkedList<T>::Node* Head();
	LinkedList<T>::Node* Tail();
	//const LinkedList<T>::Node* Tail();

	/*=== Insertion ===*/
	void AddHead(const T& data);
	void AddTail(T val);
	void AddNodesHead(T* arr, int size);
	void AddNodesTail(T* arr, int size);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	/*=== Removal ===*/
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	/*=== Operators ===*/
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	/*=== Construction / Destruction ===*/
	LinkedList();
	LinkedList(const LinkedList &other);
	~LinkedList();
};

/*=== Behaviors ===*/
template <typename T>
void LinkedList<T>::PrintForward() const {
	LinkedList<T>::Node* nextPtr = HeadPtr;
	while (nextPtr != nullptr) {
		std::cout << nextPtr->data << std::endl;
		nextPtr = nextPtr->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	LinkedList<T>::Node* prevPtr = TailPtr;
	while (prevPtr != nullptr) {
		std::cout << prevPtr->data << std::endl;
		prevPtr = prevPtr->prev;
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {

	std::cout << node->data << std::endl;

	if (node->next == nullptr) return;

	PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {

	std::cout << node->data << std::endl;

	if (node->prev == nullptr) return;

	PrintReverseRecursive(node->prev);
}

/*=== Accessor ===*/
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return ListSize;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& output, const T& val) const {
	LinkedList<T>::Node* nodePtr = HeadPtr;
	while (nodePtr != nullptr) {
		if( nodePtr->data == val)
			output.push_back(nodePtr);

		nodePtr = nodePtr->next;
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	LinkedList<T>::Node* nodePtr = HeadPtr;
	while (nodePtr != nullptr) {
		if (nodePtr->data == data)
			return nodePtr;

		nodePtr = nodePtr->next;
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	LinkedList<T>::Node* nodePtr = HeadPtr;
	while (nodePtr != nullptr) {
		if( nodePtr->data == data)
			return nodePtr;

		nodePtr = nodePtr->next;
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return HeadPtr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return TailPtr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	if (index < 0 || index >= static_cast<unsigned int>(ListSize))
		throw std::out_of_range("Index out of range!");

	LinkedList<T>::Node* nodePtr = HeadPtr;
	for (int i = 0; i < index; ++i)
		nodePtr = nodePtr->next;

	return nodePtr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	if (index < 0 || index >= static_cast<unsigned int>(ListSize))
		throw std::out_of_range("Index out of range!");

	LinkedList<T>::Node* nodePtr = HeadPtr;
	for (int i = 0; i < index; ++i)
		nodePtr = nodePtr->next;

	return nodePtr;
}

/*=== Insertion ===*/
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	// Make new node
	LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
	newNode->data = data;
	newNode->next = HeadPtr;
	newNode->prev = nullptr;
	// Let old head point prev to new node
	if (HeadPtr != nullptr)
		HeadPtr->prev = newNode;
	// Set new head
	HeadPtr = newNode;
	// Set tail if first element in
	if (ListSize == 0)
		TailPtr = newNode;
	// Update Node Count
	ListSize++;
}

template <typename T>
void LinkedList<T>::AddTail(T val) {
	// Make new node
	LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
	newNode->data = val;
	newNode->next = nullptr;
	newNode->prev = TailPtr;
	// Append to last node
	if (TailPtr == nullptr) {
		HeadPtr = newNode;
	} else {
		TailPtr->next = newNode;
	}
	TailPtr = newNode;
	// Update Node Count
	ListSize++;
}
	
template <typename T>
void LinkedList<T>::AddNodesHead(T* arr, int size) {
	for (int i = size - 1; i >= 0; --i)
		AddHead(arr[i]);
}

template <typename T>
void LinkedList<T>::AddNodesTail(T* arr, int size) {
	for (int i = 0; i < size; ++i)
		AddTail(arr[i]);
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
	newNode->data = data;

	// If Node exists after given node change prev value
	if (node->next != nullptr) {
		node->next->prev = newNode;
		newNode->next = node->next;
	} else {
		newNode->next = nullptr;
		TailPtr = newNode;
	}

	newNode->prev = node;
	node->next = newNode;

	ListSize++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
	newNode->data = data;

	if (node->prev != nullptr) {
		node->prev->next = newNode;
		newNode->prev = node->prev;
	} else {
		newNode->prev = nullptr;
		HeadPtr = newNode;
	}

	newNode->next = node;
	node->prev = newNode;

	ListSize++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index < 0 || index > static_cast<unsigned int>(ListSize))
		throw std::out_of_range("Index out of range!");

	if (index == static_cast<unsigned int>(ListSize)) {
		InsertAfter(TailPtr, data);
	} else {
		LinkedList<T>::Node* nodePtr = HeadPtr;
		for (unsigned int i = 0; i < index; ++i)
			nodePtr = nodePtr->next;

		InsertBefore(nodePtr, data);
	}
}

/*=== Removal ===*/
template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (ListSize == 0)
		return false;

	// Save next node
	LinkedList<T>::Node* nodePtr = HeadPtr->next;
	// Delete old head
	delete HeadPtr;
	//Set new head
	if (nodePtr != nullptr)
		nodePtr->prev = nullptr;
	else
		TailPtr = nullptr;

	HeadPtr = nodePtr;

	ListSize--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (ListSize == 0)
		return false;

	// Save prev node
	LinkedList<T>::Node* nodePtr = TailPtr->prev;
	// Delete old head
	delete TailPtr;
	//Set new head
	if (nodePtr != nullptr)
		nodePtr->next = nullptr;
	else
		HeadPtr = nullptr;

	TailPtr = nodePtr;

	ListSize--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	if (index < 0 || index >= static_cast<unsigned int>(ListSize))
		return false;

	if (index == 0)
		RemoveHead();
	else if (index == static_cast<unsigned int>(ListSize) - 1)
		RemoveTail();
	else {
		LinkedList<T>::Node* nodePtr = HeadPtr;
		for (unsigned int i = 0; i < index; ++i)
			nodePtr = nodePtr->next;

		nodePtr->prev->next = nodePtr->next;
		nodePtr->next->prev = nodePtr->prev;

		delete nodePtr;
	}

	ListSize--;
	return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	unsigned int total = 0;
	int index = 0;
	LinkedList<T>::Node* nodePtr = HeadPtr;
	while (nodePtr != nullptr) {
		if (nodePtr->data == data) {
			nodePtr = nodePtr->next;
			RemoveAt(index);
			total++;
		} else {
			nodePtr = nodePtr->next;
			index++;
		}
	}

	return total;
}

template <typename T>
void LinkedList<T>::Clear() {
	LinkedList<T>::Node* nextPtr = HeadPtr;
	while (nextPtr != nullptr) {
		LinkedList<T>::Node* tmpPtr= nextPtr->next;
		delete nextPtr;
		nextPtr = tmpPtr;
	}

	HeadPtr = nullptr;
	TailPtr = nullptr;
	ListSize = 0;
}

/*=== Operators ===*/
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	if (index < 0 || index >= ListSize)
		throw std::out_of_range("Index out of range!");

	LinkedList<T>::Node* nodePtr = HeadPtr;
	for (int i = 0; i < index; ++i)
		nodePtr = nodePtr->next;
	
	return nodePtr->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	if (index < 0 || index >= ListSize)
		throw std::out_of_range("Index out of range!");

	LinkedList<T>::Node* nodePtr = HeadPtr;
	for (int i = 0; i < index; ++i)
		nodePtr = nodePtr->next;
	
	return nodePtr->data;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	if (this->ListSize != rhs.ListSize)
		return false;
	if (this->ListSize == 0 && rhs.ListSize == 0)
		return true;
	if (this->ListSize == 0 || rhs.ListSize == 0)
		return false;

	LinkedList<T>::Node* lPtr = this->HeadPtr;
	LinkedList<T>::Node* rPtr = rhs.HeadPtr;

	while (lPtr != nullptr && rPtr != nullptr) {
		if(lPtr->data != rPtr->data)
			return false;

		lPtr = lPtr->next;
		rPtr = rPtr->next;
	}

	return true;
}

/*=== Construction / Desctruction ===*/
template <typename T>
LinkedList<T>::LinkedList() {
	HeadPtr = nullptr;
	TailPtr = nullptr;
	ListSize = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
	this->ListSize = other.ListSize;

	LinkedList<T>::Node* nodePtr = other.HeadPtr;
	LinkedList<T>::Node* prevPtr = nullptr;
	while (nodePtr != nullptr) {
		LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
		newNode->data = nodePtr->data;
		newNode->prev = prevPtr;

		// If prevPtr exists let it point to new node
		if (prevPtr != nullptr)
			prevPtr->next = newNode;
		else
			this->HeadPtr = newNode;

		// Update prvPtr and nodePtr
		prevPtr = newNode;
		nodePtr = nodePtr->next;
	}
	prevPtr->next = nullptr;
	this->TailPtr = prevPtr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
	this->ListSize = other.ListSize;

	// Delete old data
	LinkedList<T>::Node* nextPtr = HeadPtr;
	while (nextPtr != nullptr) {
		LinkedList<T>::Node* tmpPtr= nextPtr->next;
		delete nextPtr;
		nextPtr = tmpPtr;
	}
	this->HeadPtr = nullptr;
	this->TailPtr = nullptr;

	// Copy new data
	LinkedList<T>::Node* nodePtr = other.HeadPtr;
	LinkedList<T>::Node* prevPtr = nullptr;
	while (nodePtr != nullptr) {
		LinkedList<T>::Node* newNode = new LinkedList<T>::Node();
		newNode->data = nodePtr->data;
		newNode->prev = prevPtr;

		// If prevPtr exists let it point to new node
		if (prevPtr != nullptr)
			prevPtr->next = newNode;
		else
			this->HeadPtr = newNode;

		// Update prvPtr and nodePtr
		prevPtr = newNode;
		nodePtr = nodePtr->next;
	}
	prevPtr->next = nullptr;
	this->TailPtr = prevPtr;

	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	LinkedList<T>::Node* nextPtr = HeadPtr;
	while (nextPtr != nullptr) {
		LinkedList<T>::Node* tmpPtr= nextPtr->next;
		delete nextPtr;
		nextPtr = tmpPtr;
	}
}

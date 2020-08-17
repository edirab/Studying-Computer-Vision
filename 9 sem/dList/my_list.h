#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
	T data = 0;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
};


template <typename T>
class my_list {

public:
	my_list();
	~my_list() {};

	Node<T>* node;
	Node<T>* head = nullptr;
	int capacity = 0;

	//Интерфейс класса
	void push_front(T);
	void push_back(T);
	Node<T>* getElem(int) const;
	void insertElem(int, T);
	T deleteElem(int);
	Node<T>* deleteElem_2(int);
	void replaceElems(int, int);

	void mergeSort(Node<T>**);
	void bubbleSort();

	void print() const;
	void printReversed() const;

private:

	Node<T>* tail = nullptr;

	void split(Node<T>* source, Node<T>** left, Node<T>** right);
	Node<T>* sortedMerge(Node<T>* a, Node<T>* b);
	//size_t realSize = 0;
};


template <typename T>
my_list<T>::my_list() {
	capacity = 0;
}

template <typename T>
void my_list<T>::print() const {
	Node<T>* temp = head;
	while (temp) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "\n";
	//cout << "Размер списка: " << capacity << "\n";
}

template <typename T>
void my_list<T>::printReversed() const {
	Node<T>* temp = tail;
	while (temp) {
		cout << temp->data << " ";
		temp = temp->prev;
	}
	cout << "\n";
	//cout << "Размер списка: " << capacity << "\n";
}


template <typename T>
void my_list<T>::push_back(T value) {
	Node<T>* temp = new Node<T>;
	temp->data = value;
	temp->next = nullptr;
	//temp->prev = tail;
	//tail = temp;

	// если элементы уже есть
	if (capacity == 0) {
		temp->prev = nullptr;
		tail = temp;
		head = temp;
	}
	else if (tail != nullptr) {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	capacity++;
	//delete temp;
}

template <typename T>
void my_list<T>::push_front(T value) {
	Node<T>* temp = new Node<T>;
	temp->data = value;
	//temp->next = head;
	temp->prev = nullptr;

	if (capacity == 0) {
		head = temp;
		tail = temp;
		temp->next = nullptr;
	}
	else if (head != nullptr) {
		head->prev = temp;
		temp->next = head;
		head = temp;
	}
	capacity++;
	//delete temp;
}

template <typename T>
Node<T>* my_list<T>::getElem(int index) const {
	Node<T>* temp = new Node<T>;
	//temp = nullptr;
	if (capacity == 0)
		return nullptr;

	int i;
	if (index >= 0 && index <= capacity - 1) {
		if (index < capacity / 2) {

			temp = head;
			for (i = 0; i < index; i++) {
				temp = temp->next;
			}
		}
		else {
			temp = tail;
			for (i = capacity - 1; i > index; i--) {
				temp = temp->prev;
			}
		}
	}
	else {
		return nullptr;
	}
	return temp;
}

template <typename T>
void my_list<T>::insertElem(int index, T data) {

	if (index >= 0 && index <= capacity) {

		if (index == 0) {
			this->push_front(data);
			return;
		}
		else if (index == capacity) {
			this->push_back(data);
			return;
		}
		else {
			Node<T>* temp = new Node<T>;

			Node<T>* new_node = new Node<T>;
			new_node->data = data;

			if (index < capacity / 2) {

				temp = head;
				for (int i = 0; i < index; i++) {
					temp = temp->next;
				}
			}
			else {
				temp = tail;
				for (int i = capacity - 1; i > index; i--) {
					temp = temp->prev;
				}
			}
			new_node->next = temp;
			new_node->prev = temp->prev;

			temp->prev->next = new_node;
			temp->prev = new_node;

			capacity++;
			//delete temp;
		}
	}
	else
		return;

	return;
}

template <typename T>
Node<T>* my_list<T>::deleteElem_2(int index) {

	if (index >= 0 && index <= capacity - 1) {

		Node<T>* temp = new Node<T>;

		if (index == 0 && capacity == 1) {
			temp = head;
			head = tail = nullptr;
			capacity--;
			return temp;
		}
		else if (index == 0) {
			temp = head;
			head = head->next;
			head->prev = nullptr;
			capacity--;
			//delete temp;
			return temp;
		}
		else if (index == capacity - 1) {
			temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			capacity--;
			//delete temp;
			return temp;
		}
		else if (index < capacity / 2) {
			temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
		}
		else {
			temp = tail;
			for (int i = capacity - 1; i > index; i--) {
				temp = temp->prev;
			}
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		capacity--;
		//delete temp;
		return temp;
	}
	else
		return nullptr;
}

// возвращает значение, а не указатель
// bug with d /0 when capacity == 1
template <typename T>
T my_list<T>::deleteElem(int index) {

	if (index >= 0 && index <= capacity - 1) {

		Node<T>* temp = new Node<T>;
		int data = 0;

		if (index == 0) {
			temp = head;
			data = temp->data;
			head = temp->next;
			head->prev = nullptr;
			capacity--;
			delete temp;
			return data;
		}
		else if (index == capacity - 1) {
			temp = tail;
			data = temp->data;
			tail = temp->prev;
			tail->next = nullptr;
			capacity--;
			delete temp;
			return data;
		}

		if (index < capacity / 2) {

			temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
		}
		else {
			temp = tail;
			for (int i = capacity - 1; i > index; i--) {
				temp = temp->prev;
			}
		}
		data = temp->data;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		capacity--;
		delete temp;
		return data;
	}
	else
		return -1000;
}

template <typename T>
void my_list<T>::replaceElems(int index_a, int index_b) {

	if (index_a >= 0 && index_a < capacity && index_b >= 0 && index_b < capacity) {
		Node<T>* a = new Node<T>;
		Node<T>* b = new Node<T>;

		a = getElem(index_a);
		b = getElem(index_b);

		deleteElem_2(index_a);
		insertElem(index_a, b->data);
		deleteElem_2(index_b);
		insertElem(index_b, a->data);
	}
	else
		return;
}


template <typename T>
void my_list<T>::mergeSort(Node<T>** headRef) {

	Node<T>* new_head = *headRef;
	Node<T>* a;
	Node<T>* b;

	if ((new_head == nullptr) || (new_head->next == nullptr)) {
		return;
	}

	split(new_head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*headRef = sortedMerge(a, b);
	(*headRef)->prev = nullptr;

	Node<T>* temp = *headRef;

	while (temp->next != nullptr) {
		temp->next->prev = temp;
		temp = temp->next;
	}
	tail = temp;
}


template <typename T>
Node<T>* my_list<T>::sortedMerge(Node<T>* a, Node<T>* b) {
	Node<T>* result = nullptr;

	if (a == nullptr)
		return (b);
	else if (b == nullptr)
		return (a);

	if (a->data <= b->data) {
		result = a;
		result->next = sortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return (result);
}


template <typename T>
void my_list<T>::bubbleSort() {
	Node<T>* i = new Node<T>;
	Node<T>* j = new Node<T>;
	for (int i = 0; i < capacity - 1; i++) {
		for (int j = 0; i < capacity - 1; i++) {
		}
	}
}


template <typename T>
void my_list<T>::split(Node<T>* source, Node<T>** left, Node<T>** right) {
	Node<T>* fast;
	Node<T>* slow;
	slow = source;
	fast = source->next;

	while (fast != nullptr) {
		fast = fast->next;
		if (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*left = source;
	*right = slow->next;
	slow->next = nullptr;
}
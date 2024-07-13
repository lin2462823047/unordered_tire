#include "list.h"

// #pragma region list<T>::iterator
template<typename T>
list<T>::iterator::iterator(list_node* ptr) {
	_ptr = ptr;
}

template<typename T>
typename::list<T>::iterator& list<T>::iterator::operator++() {
	_ptr = _ptr->_next;
	return *this;
}

template<typename T>
typename::list<T>::iterator& list<T>::iterator::operator--() {
	_ptr = _ptr->_prev;
	return *this;
}

template<typename T>
bool list<T>::iterator::operator== (const list<T>::iterator& it) {
	// TBD 其它信息比较
	return _ptr == it._ptr;
}

template<typename T>
bool list<T>::iterator::operator!= (const list<T>::iterator& it) {
	return !(*this == it);
}
// #pragma endregion

// #pragma region list<T>
template<typename T>
list<T>::list() : dummy(&dummy, &dummy) {};

template<typename T>
typename::list<T>::iterator list<T>::begin() { return list<T>::iterator(head->_next); }

template<typename T>
typename::list<T>::iterator list<T>::end() { return list<T>::iterator(head); }

template<typename T>
typename::list<T>::iterator list<T>::rbegin() { return list<T>::iterator(tail->_prev); }

template<typename T>
typename::list<T>::iterator list<T>::rend() { return list<T>::iterator(tail); }

template<typename T>
typename::list<T>::iterator& list<T>::operator[] (int index) {
	list_node* curr = head;
	for (; index >= 0; --index) {
		if (curr == nullptr) {
			return end();
		}
		curr = curr->next;
	}
	return iterator(curr);
}

template<typename T>
typename::list<T>& list<T>::operator+= (const T& value) {
	list_node* node = new list_node(value, tail->_prev, tail);
	tail->_prev->_next = node;
	tail->_prev = node;
	return *this;
}
// #pragma endregion


















#ifdef __DEBUG_LIST__
struct Test {
	int num;
	std::string str;
	Test() {}
	Test(const Test& t) {
		*this = t;
	}
};

int main() {
	list<Test> l1;
	for (int i = 0; i < 255; ++i) {
		Test t;
		t.str = std::to_string(i + 1);
		t.num = i + 1;
		l1 += t;
	}

	for (auto item : l1) {
		std::cout << "str:" << item.str << ". num:" << item.num << ". " << std::endl;
	}
	return 0;
}
#endif
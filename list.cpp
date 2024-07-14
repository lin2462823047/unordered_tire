#include "list.h"

#define HOLDER
#define __TEMPLATE template<typename Type>
#define TEMPLATE(rtype) __TEMPLATE rtype

#define ADT List<Type>
#define NODE ADT::Node
#define ITERATOR ADT::iterator

// #pragma region List<Type>::iterator
TEMPLATE(HOLDER) ITERATOR::iterator(Node* ptr) {
	_ptr = ptr;
}

TEMPLATE(typename ITERATOR&) ITERATOR::operator++() {
	_ptr = _ptr->_next;
	return *this;
}

TEMPLATE(typename ITERATOR&) ITERATOR::operator--() {
	_ptr = _ptr->_prev;
	return *this;
}

TEMPLATE(bool) ITERATOR::operator== (const ITERATOR& it) {
	// TBD 其它信息比较
	return _ptr == it._ptr;
}

TEMPLATE(bool) ITERATOR::operator!= (const ITERATOR& it) {
	return !(*this == it);
}
// #pragma endregion

// #pragma region List<Type>
TEMPLATE(HOLDER) ADT::List() : dummy(&dummy, &dummy) {};

TEMPLATE(typename ITERATOR) ADT::begin() { return ADT::iterator(head->_next); }

TEMPLATE(typename ITERATOR) ADT::end() { return ADT::iterator(head); }

TEMPLATE(typename ITERATOR) ADT::rbegin() { return ADT::iterator(tail->_prev); }

TEMPLATE(typename ITERATOR) ADT::rend() { return ADT::iterator(tail); }

TEMPLATE(typename ITERATOR&) ADT::operator[] (int index) {
	Node* curr = head;
	for (; index >= 0; --index) {
		if (curr == nullptr) {
			return end();
		}
		curr = curr->next;
	}
	return iterator(curr);
}

TEMPLATE(ADT&) ADT::operator+= (Type& value) {
	Node* node = new Node(value, tail->_prev, tail);
	tail->_prev->_next = node;
	tail->_prev = node;
	return *this;
}

TEMPLATE(typename ITERATOR) ADT::append(Type& value) {
	Node* node = new Node(value, tail->_prev, tail);
	tail->_prev->_next = node;
	tail->_prev = node;
	return iterator(node);
}
// #pragma endregion

#undef HOLDER
#undef __TEMPLATE
#undef TEMPLATE
#undef ADT
#undef NODE
#undef ITERATOR

// #define __DEBUG_LIST__ 
#ifdef __DEBUG_LIST__

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Test {
	int num;
	std::string str;
	Test() {}
	Test(const Test& t) {
		*this = t;
	}
};

int main() {
	List<Test> list;
	for (int i = 0; i < 255; ++i) {
		Test t;
		t.str = std::to_string(i + 1);
		t.num = i + 1;
		list += t;
	}

	for (auto item : list) {
		std::cout << "str:" << item.str << ". num:" << item.num << ". " << std::endl;
	}
	return 0;
}
#endif
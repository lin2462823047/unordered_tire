#include "tire.h"

#define HOLDER
#define __TEMPLATE template<typename Type, typename Container>
#define TEMPLATE(rtype) __TEMPLATE rtype

#define ADT Tire<Type, Container>
#define NODE ADT::Node
#define ITERATOR ADT::iterator

// #pragma region Tire<Type>::Node
TEMPLATE(HOLDER) NODE::Node() {

}

TEMPLATE(HOLDER) NODE::~Node() {
	for (int i = 0; i < TIRE_NODE_NUMBER; ++i) {
		if (_next[i] != nullptr) {
			delete _next[i];
			_next[i] = nullptr;
		}
	}
	_value = nullptr;
}
// #pragma endregion

// #pragma region Tire<Type>
TEMPLATE(HOLDER) ADT::Tire() {

}

TEMPLATE(HOLDER) ADT::~Tire() {
	for (int i = 0; i < TIRE_NODE_NUMBER; ++i) {
		delete _root._next[i];
		_root._next[i] = nullptr;
	}
	_root._value = nullptr;
}

TEMPLATE(typename ITERATOR) ADT::find(const std::string& key) {
	Node* curr = &_root;
	Node* next = nullptr;
	for (const char& ch : key) {
		next = curr->_next[INDEX(ch)];
		if (next == nullptr) {
			return end();
		}
		curr = next;
	}
	return curr->_value == nullptr ? end() : iterator(curr->_value);
}

TEMPLATE(Type&) ADT::operator[](const std::string& key) {
	return *find(key);
}

TEMPLATE(typename ITERATOR) ADT::insert(const std::string& key, Type& value) {
	Node* curr = &_root;
	Node* next = nullptr;
	for (const char& ch : key) {
		next = curr->_next[INDEX(ch)];
		if (next != nullptr) {
			curr = next;
			continue;
		}
		curr = curr->_next[(int)ch] = new Node();
	}
	iterator it = _container.append(value);
	curr->_value = &it;
	return it;
}

TEMPLATE(typename ITERATOR) ADT::erase(const std::string& key) {
	return false; // TBD
}

TEMPLATE(typename ITERATOR) ADT::begin() { return _container.begin(); }

TEMPLATE(typename ITERATOR) ADT::end() { return _container.end(); }

TEMPLATE(typename ITERATOR) ADT::rbegin() { return _container.rbegin(); }

TEMPLATE(typename ITERATOR) ADT::rend() { return _container.rend(); }

// #pragma endregion

#undef HOLDER
#undef __TEMPLATE
#undef TEMPLATE
#undef ADT
#undef NODE
#undef ITERATOR
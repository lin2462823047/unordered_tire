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

TEMPLATE(HOLDER) NODE::Node(Type& value) {
	_value = typename Container::Node(value);
}
// #pragma endregion

// #pragma region Tire<Type>
TEMPLATE(HOLDER) ADT::Tire() {

}

TEMPLATE(typename ITERATOR) ADT::find(const std::string& key) {
	Node* curr = &_root;
	Node* next = nullptr;
	for (char ch : key) {
		next = curr[ch];
		if (next == nullptr) {

		}
		curr = next;
	}
	return curr->is_word() ? curr : nullptr;
}

TEMPLATE(Type&) ADT::operator[](const std::string& key) {
	return *find(key);
}

TEMPLATE(typename ITERATOR) ADT::insert(const std::string& key, Type& value) {
	Node* curr = &_root;
	Node* next = nullptr;
	for (const char& ch : key) {
		next = curr->_next[(int)ch];
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
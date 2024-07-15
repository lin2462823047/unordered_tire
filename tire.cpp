#include "tire.h"

#define HOLDER
#define __TEMPLATE template<typename Type, typename Container>
#define TEMPLATE(rtype) __TEMPLATE rtype

#define ADT Tire<Type, Container>
#define NODE ADT::Node
#define ITERATOR ADT::iterator


#define INDEX(x) ((const int)(x))
inline unsigned int lowbit(unsigned int x) {
	return x & -x;
}

inline int bit_weight(unsigned int x) {
	x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
	x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
	x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
	return (int)x;
}

// #pragma region Tire<Type>::Node
TEMPLATE(HOLDER) NODE::Node() {

}

TEMPLATE(HOLDER) NODE::~Node() {
	int index = 0;
	for (int i = 0; i < BITMAP_NUMBER; ++i) {
		unsigned int bmap = bitmap[i];
		// lowbit 取最低非零位
		// 汉明重量 计算最低非零位位置
		for (; bmap != 0;) {
			unsigned int x = lowbit(bmap);
			int y = bit_weight(x - 1u);
			delete next[index + y];
			next[index + y] = nullptr;
			bmap -= x;
		}
		index += (2 << UINT_SIZE);
	}
	value = nullptr;
}
// #pragma endregion

// #pragma region Tire<Type>
TEMPLATE(HOLDER) ADT::Tire() {

}

TEMPLATE(HOLDER) ADT::~Tire() {
	delete _root;
}

TEMPLATE(typename ITERATOR) ADT::find(const std::string& key) {
	Node* curr = _root;
	Node* next = nullptr;
	for (const char& ch : key) {
		next = curr->next[INDEX(ch)];
		if (next == nullptr) {
			return end();
		}
		curr = next;
	}
	return curr->value == nullptr ? end() : iterator(curr->value);
}

TEMPLATE(Type&) ADT::operator[](const std::string& key) {
	return *find(key);
}

TEMPLATE(typename ITERATOR) ADT::insert(const std::string& key, Type& value) {
	Node* curr = _root;
	Node* next = nullptr;
	for (const char& ch : key) {
		next = curr->next[INDEX(ch)];
		if (next != nullptr) {
			curr = next;
			continue;
		}
		curr->bitmap[(int)((unsigned int)ch >> (UINT_SIZE + 1))] |= 0x01u << ((unsigned int)ch & 0x1fu);
		curr = curr->next[INDEX(ch)] = new Node();
	}
	iterator it = _container.append(value);
	curr->value = &it;
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
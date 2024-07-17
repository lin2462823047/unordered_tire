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
	// x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
	return (int)x;
}

// #pragma region Tire<Type>::Node
TEMPLATE(HOLDER) NODE::Node() {

}

TEMPLATE(HOLDER) NODE::~Node() {
	// lowbit 取最低非零位
	// 汉明重量 计算最低非零位位置
	for (unsigned int bmap = bitmap; bmap != 0;) {
		unsigned int x = lowbit(bmap);
		int y = bit_weight(x - 1u);
		delete next[y];
		next[y] = nullptr;
		bmap -= x;
	}
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
		{
			// 高 4 位
			unsigned int h = ((unsigned char)ch >> 4) & 0x0fu;
			next = curr->next[h];
			if (next == nullptr) {
				return end();
			}
			curr = next;
		}
		{
			// 低 4 位
			unsigned int l = ch & 0x0fu;
			next = curr->next[l];
			if (next == nullptr) {
				return end();
			}
			curr = next;
		}
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
		{
			// 高 4 位
			unsigned int h = ((unsigned char)ch >> 4) & 0x0fu;
			next = curr->next[h];
			if (next == nullptr) {
				curr->bitmap |= 0x01u << h;
				curr = curr->next[h] = new Node();
			}
			else {
				curr = next;
			}
		}
		{
			// 低 4 位
			unsigned int l = ch & 0x0fu;
			next = curr->next[l];
			if (next == nullptr) {
				curr->bitmap |= 0x01u << l;
				curr = curr->next[l] = new Node();
			}
			else {
				curr = next;
			}
		}
	}
	iterator it = _container.append(value);
	curr->value = &it;
	return it;
}

TEMPLATE(size_t) ADT::erase(const std::string& key) {
	Node* curr = _root;
	Node* next = nullptr;
	for (const char& ch : key) {
		{
			// 高 4 位
			unsigned int h = ((unsigned char)ch >> 4) & 0x0fu;
			next = curr->next[h];
			if (next == nullptr) {
				return 0;
			}
			curr = next;
		}
		{
			// 低 4 位
			unsigned int l = ch & 0x0fu;
			next = curr->next[l];
			if (next == nullptr) {
				return 0;
			}
			curr = next;
		}
	}
	size_t res = curr->value == nullptr ? 0 : 1;
	_container.erase(curr->value);
	curr->value = nullptr;
	return res;
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
#ifndef __UNORDERED_TIRE_H__
#define __UNORDERED_TIRE_H__

#include "list.h"

template<class T>
class unordered_tire {
private:
	class tire_node {
	private:
		tire_node* _next[256] { nullptr };
		list_node<T>* _value = nullptr;
	public:
		tire_node() {}
		tire_node(T value) { _value = new list_node(value); }
		tire_node* operator[](const unsigned char ch) { return _next[ch]; }
		T& operator*() { return **_value; }
		bool is_word() { retrun _value != nullptr; }
	};

	// #pragma region iterator
public:
	typedef list<T>::iterator iterator;

	iterator begin() {
		_list.begin();
	}

	iterator end() {
		_list.end();
	}
	// #pragma endregion

private:
	// list_node npos;
	tire_node _root;
	list _list;
public:
	iterator find(const string& key) {
		tire_node* curr = &_root;
		tire_node* next = nullptr;
		for (char ch : key) {
			next = curr[ch];
			if (next == nullptr) {
				return end();
			}
			curr = next;
		}
		return curr.is_word() ? *curr : end();
	}

	const T& operator[](const string& key) {
		iterator it = find(key);
		// TBD exception
		return *it;
	}
};
#endif
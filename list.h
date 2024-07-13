#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <string>
#include <vector>
#include <memory>

template<typename T>
class list {
public:
	struct list_node {
		T* _value;
		list_node* _prev, * _next;
		list_node() : _prev(nullptr), _next(nullptr) { _value = nullptr; }
		list_node(list_node* prev, list_node* next) : _prev(prev), _next(next) { _value = nullptr; }
		list_node(const T& value, list_node* prev = nullptr, list_node* next = nullptr) : _prev(prev), _next(next) { _value = new T(value); }
		T& operator*() { return *_value; }
	};

	class iterator {
	private:
		list_node* _ptr;
		// TBD 其它信息
	public:
		iterator(list_node* ptr);
		iterator& operator++();
		iterator& operator--();
		bool operator== (const iterator& it);
		bool operator!= (const iterator& it);
		T& operator*() { return **_ptr; }
	};

private:
	list_node dummy;
	list_node* head = &dummy;
	list_node* tail = &dummy;
public:
	list();
public:
	iterator& operator[] (int index);
	list& operator+= (const T& value);
public:
	iterator begin();
	iterator end();
	iterator rbegin();
	iterator rend();
};


#endif
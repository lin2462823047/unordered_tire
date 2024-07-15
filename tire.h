#ifndef __L87_TIRE_H__
#define __L87_TIRE_H__

#include "list.h"
#include <string>

const int TIRE_NODE_NUMBER = 128;
const int UINT_SIZE = sizeof(unsigned int);
const int BITMAP_NUMBER = TIRE_NODE_NUMBER / UINT_SIZE / 8;

template<typename Type,
	typename Container = List<Type>>
	class Tire {
	public:
		struct Node {
			Node();
			~Node();
			Node* operator[](const int ch);
			Node* next[TIRE_NODE_NUMBER] { nullptr };
			unsigned int bitmap[BITMAP_NUMBER] = { 0 };
			typename Container::Node* value = nullptr;
		};

		typedef typename Container::iterator iterator;

	private:
		Node* _root = new Node();
		Container _container;
	public:
		Tire();
		~Tire();
		Type& operator[](const std::string& key);
		iterator find(const std::string& key);
		iterator insert(const std::string& key, Type& value);
		iterator erase(const std::string& key);
	public:
		iterator begin();
		iterator end();
		iterator rbegin();
		iterator rend();
};

#endif
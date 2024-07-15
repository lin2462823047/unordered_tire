#ifndef __L87_TIRE_H__
#define __L87_TIRE_H__

#include "list.h"
#include "list.cpp"
#include <string>

#define TIRE_NODE_NUMBER 128
#define INDEX(x) ((const int)(x))

template<typename Type,
	typename Container = List<Type>>
	class Tire {
	public:
		struct Node {
			Node();
			~Node();
			Node* operator[](const int ch);
			Node* _next[TIRE_NODE_NUMBER] { nullptr };
			typename Container::Node* _value = nullptr;
		};

		typedef typename Container::iterator iterator;

	private:
		Node _root;
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
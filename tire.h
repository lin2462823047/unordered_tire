#ifndef __L87_TIRE_H__
#define __L87_TIRE_H__

#include "list.h"
#include "list.cpp"
#include <string>

template<typename Type,
	typename Container = List<Type>>
	class Tire {
	public:
		struct Node {
			Node();
			Node(Type& value);
			Node* operator[](const int ch);
			Node* _next[256] { nullptr };
			typename Container::Node* _value = nullptr;
		};

		typedef typename Container::iterator iterator;

	private:
		Node _root;
		Container _container;
	public:
		Tire();
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
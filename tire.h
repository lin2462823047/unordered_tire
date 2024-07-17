#ifndef __L87_TIRE_H__
#define __L87_TIRE_H__

#include "list.h"
#include <string>

template<typename Type,
	typename Container = List<Type>>
	class Tire {
	public:
		struct Node {
			unsigned int bitmap = 0;
			typename Container::Node* value = nullptr;
			Node* next[16] { nullptr };
			Node();
			~Node();
			Node* operator[](const int ch);
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
		size_t erase(const std::string& key);
	public:
		iterator begin();
		iterator end();
		iterator rbegin();
		iterator rend();
};

#include "tire.inl"

#endif
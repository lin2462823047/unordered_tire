#ifndef __L87_LIST_H__
#define __L87_LIST_H__

template<typename Type>
class List {
public:
	struct Node {
		Type* _value;
		Node* _prev, * _next;
		Node() : _prev(nullptr), _next(nullptr) { _value = nullptr; }
		Node(Node* prev, Node* next) : _prev(prev), _next(next) { _value = nullptr; }
		Node(Type& value, Node* prev = nullptr, Node* next = nullptr) : _prev(prev), _next(next) { _value = &value; }
		~Node() { _prev = _next = nullptr, _value = nullptr; }
		Type& operator*() { return *_value; }
	};

	class iterator {
	private:
		Node* _ptr;
		// TBD 其它信息
	public:
		iterator(Node* ptr);
		iterator& operator++();
		iterator& operator--();
		bool operator== (const iterator& it);
		bool operator!= (const iterator& it);
		Type& operator*() { return **_ptr; }
		Node* operator&() { return _ptr; }
	};

private:
	Node dummy;
	Node* head = &dummy;
	Node* tail = &dummy;
public:
	List();
	~List();
public:
	iterator& operator[] (int index);
	List& operator+= (Type& value);
	iterator append(Type& value);
public:
	iterator begin();
	iterator end();
	iterator rbegin();
	iterator rend();
};


#endif
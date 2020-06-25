#include "../header/I2P2_List.h"
#include <algorithm> //swap max copy

/* useful function */
namespace owo {
	using I2P2::Node;

	Node* get_Node_ptr_from_data_ptr(I2P2::value_type* ptr) {
		Node* tmp;
		tmp = reinterpret_cast<Node*>(
			reinterpret_cast<size_t>(ptr) - offsetof(Node, data)
			);
		return tmp;
	}

}// namespace I2P2

/* list basic  */
namespace I2P2 {
	
	/* swap function */
	void List::swap(List& rhs) {
		std::swap(_head, rhs._head);
		std::swap(_tail, rhs._tail);
		std::swap(_size, rhs._size);
	}

	/* destructor */
	List::~List() {
		Node* cur = _head;
		while (_size--) {
			Node* tmp = cur;
			cur = cur->next;
			delete tmp;
		}
	}

	/* default constructor */
	List::List() {
		_head = new Node();
		_head->prev = _head;
		_head->next = _head;
		_tail = _head;
		_size = 0;
	}

	/* copy constructor */
	List::List(const List &rhs) {
		size_type size_count = rhs._size;
		Node* cur = rhs._head;
		while (size_count--)
		{
			push_back(cur->data);
			++_size;
			cur = cur->next;
		}
	}

	/* copy assignment constructor */
	List& List::operator=(const List &rhs) {
		List tmp(rhs);
		swap(tmp);
		return *this;
	}

	size_type List::size() const{
		return _size;
	}

	bool List::empty() const {
		return _size == 0;
	}

	void List::clear() {
		Node* cur = _head;
		Node* tmp;
		while (_size--) {
			tmp = cur;
			cur = cur->next;
			delete tmp;
		}
	}

}

/* list iterator */
namespace I2P2 {

	/* iterator begin */
	iterator List::begin() {
		list_iterator p(_head);
		iterator itr(&p);
		return itr;
	}
	const_iterator List::begin() const {
		list_iterator p(_head);
		iterator itr(&p);
		return itr;
	}

	/* iterator end */
	iterator List::end() {
		list_iterator p(_tail);
		iterator itr(&p);
		return itr;
	}
	const_iterator List::end() const {
		list_iterator p(_tail);
		iterator itr(&p);
		return itr;
	}

	/* the first element */
	reference List::front() {
		return _head->data;
	}
	const_reference List::front() const {
		return _head->data;
	}
	/* the last element */
	reference List::back() {
		return _tail->prev->data;
	}
	const_reference List::back() const {
		return _tail->prev->data;
	}



}// namespace I2P2 list iterator

/* list operation without iterator */
namespace I2P2 {
	void List::pop_back() {
		if (_size <= 1)
			clear();
		else {
			Node* tmp = _tail;
			_tail = _tail->prev;
			_tail->next = _head;
			_head->prev = _tail;
			delete tmp;
			--_size;
		}
	}

	void List::pop_front() {
		if (_size <= 1)
			clear();
		else {
			Node* tmp = _head;
			_head = _head->next;
			_head->prev = _tail;
			_tail->next = _head;
			delete tmp;
			--_size;
		}
	}

	void List::push_back(const_reference val) {
		Node* new_node = new Node(val);
		if (empty()){
			_head = new_node;
			_head->next = _tail;
			_head->prev = _tail;
			_tail->next = _head;
			_tail->prev = _head;
		}
		else{
			new_node->prev = _tail->prev;
			new_node->next = _tail;
			_tail->prev->next = new_node;
			_tail->prev = new_node;
		}
		++_size;
	}

	void List::push_front(const_reference val) {
		Node* new_node = new Node(val);
		if (empty()) {
			_head = new_node;
			_head->next = _tail;
			_head->prev = _tail;
			_tail->next = _head;
			_tail->prev = _head;
		}
		else {
			new_node->next = _head;
			new_node->prev = _tail;
			_tail->next = new_node;
			_head->prev = new_node;
			_head = new_node;
		}
		++_size;
	}
}

/* list operation with iterator */
namespace I2P2 {

	/* list erase */
	void List::erase(const_iterator pos) {
		Node* target_node = owo::get_Node_ptr_from_data_ptr(&(*pos));
		if (_size <= 1)
			clear();
		else
		{
			Node* l = target_node->prev, *r = target_node->next;
			target_node->next = r;
			target_node->prev = l;
			delete target_node;
			--_size;
		}
	}

	void List::erase(const_iterator begin, const_iterator end) {
		Node* cur_node = owo::get_Node_ptr_from_data_ptr(&(*begin));
		Node* end_node = owo::get_Node_ptr_from_data_ptr(&(*end));
		while (cur_node != end_node) {
			cur_node->next->prev = cur_node->prev;
			cur_node->prev->next = cur_node->next;
			Node* tmp = cur_node;
			cur_node = cur_node->next;
			delete tmp;
			_size--;
		}
	}

	/* list insert */
	void List::insert(const_iterator pos, size_type count, const_reference val) {
		Node* target_node = owo::get_Node_ptr_from_data_ptr(&(*pos));
		for (int i = 0; i < count; i++) {
			Node* new_node = new Node(val);
			new_node->prev = target_node->prev;
			target_node->prev->next = new_node;
			new_node->next = target_node;
			target_node->prev = new_node;
		}
		_size += count;
	}
	
	void List::insert(const_iterator pos, const_iterator begin, const_iterator end) {
		Node* begin_node = owo::get_Node_ptr_from_data_ptr(&(*begin));
		Node* end_node = owo::get_Node_ptr_from_data_ptr(&(*begin));
		auto count = end - begin;
		// copy a tmp list to store [begin,end)
		value_type* tmp_list = new value_type(count);
		Node* cur_node = begin_node;
		for (int i = 0; i < count; i++) {
			tmp_list[i] = cur_node->data;
			cur_node = cur_node->next;
		}
		// copy data from tmp list
		for (int i = 0; i < count; i++) {
			insert(pos, 1, tmp_list[count - 1 - i]);
		}
		delete[] tmp_list;
	}

		
}
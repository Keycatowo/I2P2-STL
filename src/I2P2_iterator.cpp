#include "../header/I2P2_iterator.h"

/* typedef */
namespace I2P2 {
	/* Your definition for the iterator class goes here */
	using base_itr = iterator_impl_base;
	using base_itr_ref = iterator_impl_base & ;
}// namespace I2P2

/* implement of list_iterator */
namespace I2P2 {

	list_iterator::list_iterator()
		: _node(nullptr) {}

	list_iterator::list_iterator(Node* n)
		: _node(n) {}

base_itr_ref list_iterator::operator++() {
	// move list_iterator to next
	if (_node != nullptr)
		_node = _node->next;
	return *this;
}

base_itr_ref list_iterator::operator--() {
	// move to prev
	if (_node != nullptr)
		_node = _node->prev;
	return *this;
}

base_itr_ref list_iterator::operator+=(difference_type offset) {
	while (offset--)
		++(*this);
	return *this;
}

base_itr_ref list_iterator::operator-=(difference_type offset) {
	while (offset--)
		--(*this);
	return *this;
}

bool list_iterator::operator==(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node == tmp->_node;
}

bool list_iterator::operator!=(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node != tmp->_node;
}

bool list_iterator::operator<(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node < tmp->_node;
}

bool list_iterator::operator>(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node > tmp->_node;
}

bool list_iterator::operator<=(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node <= tmp->_node;
}

bool list_iterator::operator>=(const iterator_impl_base &rhs) const {
	auto tmp = dynamic_cast<const list_iterator*>(&rhs);
	return _node >= tmp->_node;
}

difference_type list_iterator::operator-(const iterator_impl_base &rhs) const {
	difference_type count = 0;
	auto tmp = *this;
	if ((*this) >= rhs) {
		while (tmp != rhs) {
			--tmp;
			++count;
		}
	}
	else {
		while (tmp != rhs) {
			++tmp;
			--count;
		}
	}
	return count;
}

pointer list_iterator::operator->()const {
	/// I'm super not sure for this 
	return &(_node->data);
}

reference list_iterator::operator*() const {
	return _node->data;
}

reference list_iterator::operator[](difference_type offset) const {
	auto tmp = (*this);
	while (offset--) {
		++tmp;
	}
	return _node->data;
}

iterator_impl_base* list_iterator::clone() const {
	return new list_iterator(_node);
}

}  // namespace I2P2

/* implement of vector_iterator */
namespace I2P2 {
	/* constructor */
	vector_iterator::vector_iterator()
		: index(nullptr) {}
	vector_iterator::vector_iterator(value_type* d)
		: index(nullptr) {}


	base_itr_ref vector_iterator::operator++() {
		index++;
		return *this;
	}

	base_itr_ref vector_iterator::operator--() {
		index--;
		return *this;
	}

	base_itr_ref vector_iterator::operator+=(difference_type offset) {
		index += offset;
		return *this;
	}

	base_itr_ref vector_iterator::operator-=(difference_type offset) {
		index -= offset;
		return *this;
	}

	bool vector_iterator::operator==(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index == tmp->index;
	}
	bool vector_iterator::operator!=(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index != tmp->index;
	}
	bool vector_iterator::operator>(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index > tmp->index;
	}
	bool vector_iterator::operator<(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index < tmp->index;
	}
	bool vector_iterator::operator>=(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index >= tmp->index;
	}
	bool vector_iterator::operator<=(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index <= tmp->index;
	}


	difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const {
		auto tmp = dynamic_cast<const vector_iterator*>(&rhs);
		return index - tmp->index;
	}

	pointer vector_iterator::operator->() const {
		return index;
	}
	reference vector_iterator::operator*() const {
		return *index;
	}
	reference vector_iterator::operator[](difference_type offset) const {
		return *(index + offset);
	}

	iterator_impl_base* vector_iterator::clone() const {
		return new vector_iterator(index);
	}
}		// namesapce I2P2




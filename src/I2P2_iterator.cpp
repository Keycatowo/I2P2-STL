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
	if (offset == 0)
		return tmp._node->data;
	if (offset > 0) {
		while (offset--) {
			++tmp;
		}
	}
	else {
		while (offset++) {
			--tmp;
		}
	}
	return tmp._node->data;
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
	vector_iterator::vector_iterator(value_type* ptr)
		: index(ptr) {}


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


/* implement of const_iterator */
namespace I2P2 {

	const_iterator::~const_iterator() {
		// destroy iterator base pointer
		delete p_;
		p_ = 0;
	}

	const_iterator::const_iterator()
		: p_(nullptr) {}

	const_iterator::const_iterator(const const_iterator &rhs)
		: p_(rhs.p_->clone()) {}// copy_const using clone function from iterator base

	const_iterator::const_iterator(iterator_impl_base *p)
		: p_(p->clone()) {}// const using clone from iterator base

	const_iterator& const_iterator::operator=(const const_iterator &rhs) {
		// assignment
		if (rhs == *this)
			return *this; // self assignment
		// delete old and clone new
		if (p_)
			delete p_;
		p_ = rhs.p_->clone();
	}

	const_iterator& const_iterator::operator++() {
		// itr++
			// const_iterator points to the const value
			// but const_iterator can be moved
		++(*p_);
		return *this;
	}
	const_iterator const_iterator::operator++(int) {
		auto tmp = *this;
		++(*p_);
		return tmp;
	}
	const_iterator& const_iterator::operator--() {
		--(*p_);
		return *this;
	}
	const_iterator const_iterator::operator--(int) {
		auto tmp = *this;
		--(*p_);
		return tmp;
	}
	const_iterator& const_iterator::operator+=(difference_type offset) {
		// += just move forward multi steps
		
		if (offset == 0)	// deal with zero steps
			return *this;
		
		if (offset > 0) { // deal with postive steps
			while (offset--) {
				++(*p_);
			}
		}
		
		else { // deal with negative steps
			while (offset++)
			{
				--(*p_);
			}
		}
		return *this;
		
	}
	const_iterator const_iterator::operator+(difference_type offset) const {
		// can't just move
			// because it's const function
			// should build a temp element to deal with and return
			/// not sure should just use tmp= or new a object
		auto tmp = *this;
		while (offset--) {
			++tmp;
		}
		return tmp;
	}
	const_iterator& const_iterator::operator-=(difference_type offset) {
		// -= is also just move backward multi steps
		/// can only deal with postive offset now
		while (offset--) {
			--(*p_);
		}
		return *this;
	}
	const_iterator const_iterator::operator-(difference_type offset) const {
		// give the distance to calculate the iterator
		auto tmp = *this;
		if (offset == 0) // zero steps
			return *this;
		if (offset>0){	 // postive steps
			while (offset--) {
				--tmp;
			}
		}
		else{						 // negative steps
			while(offset++){
				++tmp;
			}
		}
		return *this;
	}

	difference_type const_iterator::operator-(const const_iterator &rhs) const {
		// give two const_iterator to calculate the distance
		auto tmp = *this;
		difference_type count = 0;
		if (tmp == rhs)
			return 0;
		if (tmp > rhs) {
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

	const_pointer const_iterator::operator->() const {
		/// not sure for this
		return &(**p_);
	}

	const_reference const_iterator::operator*() const {
		return **p_;
	}

	const_reference const_iterator::operator[](difference_type offset) const {
		auto tmp = (*this);
		tmp += offset;
		return *tmp;
	}

	bool const_iterator::operator==(const const_iterator &rhs) const {
		return *(p_) == *(rhs.p_);
	}
	bool const_iterator::operator!=(const const_iterator &rhs) const {
		return *(p_) != *(rhs.p_);
	}
	bool const_iterator::operator<(const const_iterator &rhs) const {
		return *(p_) <  *(rhs.p_);
	}
	bool const_iterator::operator>(const const_iterator &rhs) const {
		return *(p_) >  *(rhs.p_);
	}
	bool const_iterator::operator<=(const const_iterator &rhs) const {
		return *(p_) <= *(rhs.p_);
	}
	bool const_iterator::operator>=(const const_iterator &rhs) const {
		return *(p_) >= *(rhs.p_);
	}


}	// namespace I2P2 const_iterator

/* implement of iterator */
namespace I2P2 {

	

	iterator::iterator()
		: const_iterator() {}

	iterator::iterator(const iterator &rhs){
		p_ = (rhs.p_->clone());
		// copy_const using clone function from iterator base
	}

	iterator::iterator(iterator_impl_base *p) {
		p_ = (p->clone());
		// using clone from iterator base
	}
		
	iterator& iterator::operator++() {
		// itr++
		++(*p_);
		return *this;
	}
	iterator iterator::operator++(int) {
		auto tmp = *this;
		++(*p_);
		return tmp;
	}
	iterator& iterator::operator--() {
		--(*p_);
		return *this;
	}
	iterator iterator::operator--(int) {
		auto tmp = *this;
		--(*p_);
		return tmp;
	}
	iterator& iterator::operator+=(difference_type offset) {
		// += just move forward multi steps

		if (offset == 0)	// deal with zero steps
			return *this;

		if (offset > 0) { // deal with postive steps
			while (offset--) {
				++(*p_);
			}
		}

		else { // deal with negative steps
			while (offset++)
			{
				--(*p_);
			}
		}
		return *this;

	}
	iterator iterator::operator+(difference_type offset) const {
		// can't just move
			// because it's const function
			// should build a temp element to deal with and return
			/// not sure should just use tmp= or new a object
		auto tmp = *this;
		while (offset--) {
			++tmp;
		}
		return tmp;
	}
	iterator& iterator::operator-=(difference_type offset) {
		// -= is also just move backward multi steps
		/// can only deal with postive offset now
		while (offset--) {
			--(*p_);
		}
		return *this;
	}
	iterator iterator::operator-(difference_type offset) const {
		// give the distance to calculate the iterator
		auto tmp = *this;
		if (offset == 0) // zero steps
			return *this;
		if (offset > 0) {	 // postive steps
			while (offset--) {
				--tmp;
			}
		}
		else {						 // negative steps
			while (offset++) {
				++tmp;
			}
		}
		return *this;
	}

	difference_type iterator::operator-(const iterator &rhs) const {
		// give two const_iterator to calculate the distance
		auto tmp = *this;
		difference_type count = 0;
		if (tmp == rhs)
			return 0;
		if (tmp > rhs) {
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

	pointer iterator::operator->() const {
		/// not sure for this
		return &(**p_);
	}

	reference iterator::operator*() const {
		return **p_;
	}

	reference iterator::operator[](difference_type offset) const {
		auto tmp = (*this);
		tmp += offset;
		return *tmp;
	}

	// keep using the 
		// ~()
		// =
		// bool

}	// namespace I2P2 iterator


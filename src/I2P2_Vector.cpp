#include "../header/I2P2_Vector.h"
#include <iostream>

/* useful function*/
namespace owo {

	template <typename T> void swap(T& a, T&b){
		T c = a;
		a = b;
		b = c;
	}

	template<typename InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first != last) {
			*result = *first;
			++result; ++first;
		}
		return result;
	}

	template< typename BidirIt1, typename BidirIt2 >
	BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
	{
		while (first != last) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}

	template <typename T> const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, T val)
	{
		while (first != last) {
			*first = val;
			++first;
		}
	}

	I2P2::difference_type size2difference(I2P2::size_type size) {
		I2P2::difference_type rtv = 0;
		while (size--)
			rtv++;
		return rtv;
	}
}


/* vector basic cuntion */
namespace I2P2 {

	/* swap two vector */
	void Vector::swap(Vector &rhs) {
		owo::swap(_begin, rhs._begin);
		owo::swap(_last, rhs._last);
		owo::swap(_end, rhs._end);
	}

	/* destrucor */
	Vector::~Vector() {
		if(_begin!=nullptr)
			delete[] _begin;
		_begin = nullptr;
		_last = nullptr;
		_end = nullptr;
	}

	/* default constructor */
	Vector::Vector()
		:	_begin(new value_type[1]){
		_last = _begin;
		_end = _begin;
	}

	/* copy constructor */
	Vector::Vector(const Vector &rhs)
		: _begin(new value_type[rhs.capacity()]){
		_last = _begin + rhs.size();
		_end = _begin + rhs.capacity();
		owo::copy(rhs._begin, rhs._end, _begin);
	}

	/* copy assignment */
	Vector& Vector::operator=(const Vector &rhs) {
		// copy and swap
		Vector tmp(rhs);
		swap(tmp);
		return *this;
	}

	size_type Vector::capacity() const {
		return _end - _begin;
	}

	size_type Vector::size() const {
		return _last - _begin;
	}

	reference Vector::operator[](size_type pos) {
		return _begin[pos];
	}

	const_reference Vector::operator[](size_type pos) const{
		return _begin[pos];
	}

	bool Vector::empty() const {
		return size() == 0;
	}

	/// option: move

}  // namespace I2P2

/* vector operation function without iterator */
namespace I2P2 {

	void Vector::push_back(const_reference val) {
		if (_end == _last) {
			reserve(owo::max(
				capacity() + 1,
				capacity() * 3
			));
		}
		*_last = val;
		_last++;
	}
	void Vector::push_front(const_reference val) {
		// push back and move the place
		if (empty()) {
			push_back(val);
			return;
		}
		else
			push_back(val);
		owo::copy_backward(begin(), end()-1, end());
		*_begin = val;
	}


	void Vector::pop_back() {
		if (size() > 0)
			_last--;
	}
	void Vector::pop_front() {
		if (empty())
			return;
		else if (size() == 1)
			_last--;
		else {
			owo::copy(_begin + 1, _last, _begin);
			_last--;
		}

	}


	void Vector::reserve(size_type new_capacity) {
		if (capacity() < new_capacity) {
			auto* new_begin = new value_type[new_capacity];
			auto old_sise = size();
			owo::copy(_begin, _last, new_begin);
			delete[] _begin;

			_begin = new_begin;
			_last = new_begin + old_sise;
			_end = new_begin + new_capacity;
		}
	}

	void Vector::clear() {
		Vector tmp;
		swap(tmp);
	}

	void Vector::shrink_to_fit() {
		// let the capacity fit the size
		if (empty())
			clear();
		else {
			auto old_size = size();
			auto* new_begin = new value_type[old_size];
			owo::copy(_begin, _last, new_begin);
			delete[] _begin;

			_begin = new_begin;
			_last = new_begin + old_size;
			_end = new_begin + old_size;
		}
	}
}

/* vector iterator */
namespace I2P2 {

	/* iterator begin */
	iterator Vector::begin() {
		vector_iterator p(_begin);
		iterator itr(&p);
		return itr;
	}
	const_iterator Vector::begin() const {
		/// same to no-const
		vector_iterator p(_begin);
		const_iterator itr(&p);
		return itr;
	}

	/* iterator end */
	iterator Vector::end() {
		vector_iterator p(_last);
		iterator itr(&p);
		return itr;
	}
	const_iterator Vector::end() const {
		vector_iterator p(_last);
		const_iterator itr(&p);
		return itr;
	}

	/* the first element */
	reference Vector::front() {
		/// not sure for checking empty is necessery
		return *_begin;
	}
	const_reference Vector::front() const {
		return *_begin;
	}

	/* the last element */
	reference Vector::back() {
		return *(_last - 1);
	}

	const_reference Vector::back() const{
		return *(_last - 1);
	}

}

/* vector operation function*/
/* with iterator */
namespace I2P2 {
	void Vector::erase(const_iterator pos) {
		//std::cout << "erase\n";
		// erase an empty vector is a no-op
		if (empty())
			return;
		// replacement by forward
		pointer pos_ptr = const_cast<pointer> (&*pos);
		owo::copy(pos_ptr + 1, &*end(), pos_ptr);
		_last--;
	}

	void Vector::erase(const_iterator begin, const_iterator end) {
		//std::cout << "erase_range\n";
		// erase an empty range is a no-op
		if (begin == end)
			return;
		
		// replacement by forward
		auto reduce_size = end - begin;
		pointer begin_ptr = const_cast<pointer> (&*begin);
		pointer end_ptr = const_cast<pointer> (&*end);
		owo::copy(end_ptr, &*(this->end()), begin_ptr);
		_last -= reduce_size;
	}

	
	void Vector::insert(const_iterator pos, size_type count, const_reference val) {
		auto d_pos = pos - begin();
		for (auto i = 0; i < count; i++) 
			push_back(val);
		owo::copy_backward(begin() + d_pos, end() - count, end());
		owo::fill(begin() + d_pos, begin() + d_pos + count, val);
	}

		
	void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end) {
		//std::cout << "insert range\n";
		auto d_pos = pos - this->begin();
		auto count = end - begin;
		Vector tmp;
		tmp.clear();
		while (begin != end) {
			tmp.push_back(*begin);
			push_back(*begin);
			begin++;
		}
		owo::copy_backward(this->begin() + d_pos, this->end() - count, this->end());
		owo::copy(tmp.begin(), tmp.end(), this->begin() + d_pos);
	}

}// namespace I2P2



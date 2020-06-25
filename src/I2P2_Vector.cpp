#include "../header/I2P2_Vector.h"
#include <algorithm> //swap max copy

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

	template<typename BidirectionalIterator1, typename BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
		BidirectionalIterator1 last,
		BidirectionalIterator2 result)
	{
		while (last != first) 
			*(--result) = *(--last);
		return result;
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
		delete[] _begin;
		_begin = nullptr;
		_last = nullptr;
		_end = nullptr;
	}

	/* default constructor */
	Vector::Vector()
		:	_begin(nullptr), _last(nullptr), _end(nullptr){}

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

/* vector operation function*/
/* without iterator */
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
		/// same to none_const, but I'm not sure for this
		vector_iterator p(_begin);
		iterator itr(&p);
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
		iterator itr(&p);
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
		// erase an empty vector is a no-op
		if (empty())
			return;
		// replacement by forward
		owo::copy(pos + 1 , static_cast<const_iterator> (end()), pos);
		_last--;
	}

	void Vector::erase(const_iterator begin, const_iterator end) {
		// erase an empty range is a no-op
		if (begin == end)
			return;

		// replacement by forward
		auto reduce_size = end - begin;
		//std::copy(*end, *(this->end()), *begin);
		owo::copy(end, static_cast<const_iterator>(this->end()), begin);
		_last -= reduce_size;
	}

	void Vector::insert(const_iterator pos, size_type count, const_reference val) {
		reserve(size() + count);
		const_iterator tmp_end = end();
		const_iterator pos_plus_count = pos + count;
		owo::copy_backward(pos, tmp_end, tmp_end + count);
		owo::fill(pos, pos_plus_count, val);
		_last += count;
	}
	void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end) {
		/// not finished yet
		auto count = (end - begin);
		reserve(size() + count);
		value_type* tmp_head = new value_type[count+1];
		owo::copy(begin, end, tmp_head);
		const_iterator tmp_end = this->end();
		vector_iterator ptr(tmp_head);
		const_iterator tmp_begin(&ptr);
		const_iterator begin_plus_count = tmp_begin + count;
		std::copy_backward(pos, tmp_end, tmp_end + count);
		owo::copy(tmp_begin, begin_plus_count, pos);
		_last += count;
		delete[] tmp_head;
	}
}// namespace I2P2



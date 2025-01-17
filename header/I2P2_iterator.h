#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include "I2P2_def.h"

namespace I2P2 {

struct Node {
	Node *prev;
	Node *next;
	value_type data;
	Node(value_type new_data = 0)
		: prev(nullptr), next(nullptr), data(new_data) {}
};

struct iterator_impl_base {
  virtual reference operator*() const = 0;
  virtual reference operator[](difference_type offset) const = 0;
  virtual pointer operator->() const = 0;
  virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base &operator++() = 0;
  virtual iterator_impl_base &operator--() = 0;
  virtual iterator_impl_base &operator+=(difference_type offset) = 0;
  virtual iterator_impl_base &operator-=(difference_type offset) = 0;
  virtual bool operator==(const iterator_impl_base &rhs) const = 0;
  virtual bool operator!=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>=(const iterator_impl_base &rhs) const = 0;
	virtual iterator_impl_base* clone() const  = 0;
  /* This is the base class of all the container-specialized iterators
   * In order to invoke a derived function from this class
   * you may have to either do a downcast or invoke from a virtual function */
};

class vector_iterator : public iterator_impl_base {
 protected:
  // You may want to declare what your vector_iterator stores here
	 value_type* index;

 public:
  using self_type = vector_iterator;
  vector_iterator();
	vector_iterator(value_type* d);
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
	iterator_impl_base* clone() const;
};

class list_iterator : public iterator_impl_base {
 protected:
  // You may want to declare what your list_iterator stores here
  Node* _node;

 public:
	using self_type = list_iterator;
  list_iterator();
	list_iterator(Node* n);
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
	iterator_impl_base* clone() const;
};

class const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::const_pointer;
  using reference = I2P2::const_reference;
  using iterator_category = std::random_access_iterator_tag;
	using self_type = const_iterator;

 protected:
  iterator_impl_base *p_;

 public:
  ~const_iterator();
  const_iterator();
  const_iterator(const const_iterator &rhs);
  const_iterator(iterator_impl_base *p);
  const_iterator &operator=(const const_iterator &rhs);
  const_iterator &operator++();
  const_iterator operator++(int);
  const_iterator &operator--();
  const_iterator operator--(int);
  const_iterator &operator+=(difference_type offset);
  const_iterator operator+(difference_type offset) const;
  const_iterator &operator-=(difference_type offset);
  const_iterator operator-(difference_type offset) const;
  difference_type operator-(const const_iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  bool operator==(const const_iterator &rhs) const;
  bool operator!=(const const_iterator &rhs) const;
  bool operator<(const const_iterator &rhs) const;
  bool operator>(const const_iterator &rhs) const;
  bool operator<=(const const_iterator &rhs) const;
  bool operator>=(const const_iterator &rhs) const;
  /* This class holds an iterator_impl_base
   * and you may want to have some ways to 
   * invoke a container-specialized method from here
   * for insert/erase methods (look at their parameters if you are not sure) */
	//const_iterator operator+(size_type offset) const;
};

class iterator : public const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::pointer;
  using reference = I2P2::reference;
  using iterator_category = std::random_access_iterator_tag;
	using self_type = iterator;

 public:
  iterator();
  iterator(iterator_impl_base *p);
  iterator(const iterator &rhs);
  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  iterator &operator+=(difference_type offset);
  iterator operator+(difference_type offset) const;
  iterator &operator-=(difference_type offset);
  iterator operator-(difference_type offset) const;
  difference_type operator-(const iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
};
}  // namespace I2P2

#endif


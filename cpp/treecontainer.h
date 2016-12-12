#ifndef TREECONTAINER_H
#define TREECONTAINER_H

#include <iterator>
#include <iostream>

#include "node.h"

/**
 * @class binary tree-based container
 */
template <class T>
class TreeContainer: public Node {
public:
  TreeContainer();

  TreeContainer(const T& data);

  TreeContainer(const TreeContainer<T>* other);

  TreeContainer(const TreeContainer<T>& other);

  virtual ~TreeContainer();

  TreeContainer<T>& operator=(const TreeContainer<T>& rhs);

  bool operator==(const TreeContainer<T>& rhs) const;

  bool operator!=(const TreeContainer<T>& rhs) const;

  void setData(const T& data);

  T& data();

  /**
   * @class Forward iterator that implements tree traversal in DFS order
   */
  class dfs_iterator
  {
  public:
    typedef dfs_iterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    dfs_iterator(TreeContainer<value_type>* ptr) : ptr_(ptr) { }
    self_type operator++() {
      self_type i = *this;
      if (ptr_)
        ptr_ = dynamic_cast<TreeContainer<value_type>*>(ptr_->dfs_next());
      return i;
    }
    self_type operator++(int junk) {
      if (ptr_)
        ptr_ = dynamic_cast<TreeContainer<value_type>*>(ptr_->dfs_next());
      if (!ptr_) {
        return end_iterator();
      }
      return *this;
    }
    reference operator*() { return ptr_->data(); }
    pointer operator->() { return &(ptr_->data()); }
    bool operator==(const self_type& rhs) { 
      return (ptr_ == rhs.ptr_);
    }
    bool operator!=(const self_type& rhs) { return (ptr_ != rhs.ptr_); }
    static dfs_iterator end_iterator() {
      return dfs_iterator(nullptr);
    }
  private:
    TreeContainer<value_type>* ptr_;
  };

  dfs_iterator begin() noexcept {
    return dfs_iterator(this);
  };

  dfs_iterator end() noexcept {
    return dfs_iterator::end_iterator();
  };

private:
//  dfs_iterator dfs_end_iterator;
  //! Container data
  T data_;
};

template <class T>
TreeContainer<T>::TreeContainer() : Node() {
}

template <class T>
TreeContainer<T>::TreeContainer(const T& data): Node(), data_(data) {
}

template <class T>
TreeContainer<T>::TreeContainer(const TreeContainer<T>* other) {
  if (other) {
    if (other->llink_) {
      llink_ = new TreeContainer<T>(other->llink_);
    }
    if (other->rlink_) {
      rlink_ = new TreeContainer<T>(other->rlink_);
    }
    data_ = other->data_;
  }
}

template <class T>
TreeContainer<T>::TreeContainer(const TreeContainer<T>& other) {
  if (other.llink_) {
    llink_ = new TreeContainer<T>(other.llink_);
  }
  if (other.rlink_) {
    rlink_ = new TreeContainer<T>(other.rlink_);
  }
  data_ = other.data_;
}

template <class T>
TreeContainer<T>::~TreeContainer() {}

template <class T>
TreeContainer<T>& TreeContainer<T>::operator=(const TreeContainer<T>& rhs) {
  // Self assignment check (Scott Meyers)
  if (this == &rhs) return *this;
  llink_ = nullptr;
  rlink_ = nullptr;
  data_ = rhs.data_;
  if (rhs.llink_) {
    llink_ = new TreeContainer<T>(rhs.llink_);
  }
  if (rhs.rlink_) {
    rlink_ = new TreeContainer<T>(rhs.rlink_);
  }
  return *this;
}

template <class T>
bool TreeContainer<T>::operator==(const TreeContainer<T>& rhs) const {
  return Node::operator==(rhs) && (data_ == rhs.data_);
}

template <class T>
bool TreeContainer<T>::operator!=(const TreeContainer<T>& rhs) const {
  return !(operator==(rhs));
}

template <class T>
void TreeContainer<T>::setData(const T& data) {
  data_ = data;
}

template <class T>
T& TreeContainer<T>::data() {
  return data_;
}

#endif //TREECONTAINER_H

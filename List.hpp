#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //Default Constructor
  List(): first(nullptr), last(nullptr), num_nodes(0) {}

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return(num_nodes == 0);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return(num_nodes);
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    return(first->datum);
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    return(last->datum);
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *p = new Node;
    p->datum = datum;
    p->next = first;
    p->prev = nullptr;

    if (empty()) {first = last = p;}
    else {
      first->prev = p;
      first = p;
    }
    num_nodes++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;
    p->prev = last;

    if (empty()) {first = last = p;}
    else {
      last->next = p;
      last = p;
    }
    num_nodes++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    if (empty()) { return; }
    Node *to_delete = first;
    //why can't I do first == last, this feels more safe than num_nodes == 1;=
    if (num_nodes != 1) {first = first->next;}
    delete to_delete;
    num_nodes--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    if (empty()) { return; }
    Node *to_delete = last;
    last = last->prev;
    delete to_delete;
    num_nodes--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while(!empty()) { pop_front(); }
    num_nodes = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  //Copy Constructor
  List(const List &other): first(nullptr), last(nullptr), num_nodes(0) 
      {copy_all(other);}

  //Assignment operator overload
  List& operator=(const List &rhs) {
    if(this == &rhs) { return *this; }
    clear();
    copy_all(rhs);
    return *this;
  }

  //Destructor
  ~List() { clear(); }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    for (Node *np = other.first; np; np = np->next) {
      push_back(np->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int num_nodes;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    friend class List;
    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    public: Iterator() :list_ptr(nullptr), node_ptr(nullptr) {}

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    //DO NOT NEED BIG 3 FOR ITERATORS

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



  public:
    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

    //Created function overloads

    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() { // prefix -- (e.g. ++it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->next;
      }// else { // incrementing an end Iterator moves it to the last element
      //   node_ptr = list_ptr->first;
      // }
      return *this;
    }
  
    Iterator operator++(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator==(Iterator rhs) const {
      return(list_ptr == rhs.list_ptr && node_ptr == rhs.node_ptr);
    }

    bool operator!=(Iterator rhs) const {
      return(!operator==(rhs));
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    
    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) { }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(this, nullptr);
  }
  //0,1 (ok to ++ on 1[end iter], but -- on 0 is not preferred)

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i) {
    num_nodes--;
    if (i == end()) { assert(false); }
    else if (i.node_ptr == last) {
      //end refers to one past the actual end so account for that
      last = i.node_ptr->prev;
      last->next = nullptr;
      delete i.node_ptr;
      return(Iterator(i.list_ptr, nullptr));
    }
    else if (i.node_ptr == first) {
      first = i.node_ptr->next;
      first->prev = nullptr;
      Iterator temp(i.list_ptr,  i.node_ptr->next);
      delete i.node_ptr;
      return(temp);
    }
    else {
      //points to the previous node's previous pointer to 
      Node *i_prev = i.node_ptr->prev;
      Node *i_next = i.node_ptr->next;
      i_prev->next = i.node_ptr->next;
      i_next->prev = i.node_ptr->prev;
      Iterator temp(i.list_ptr,  i.node_ptr->next);
      delete i.node_ptr;
      return(temp);
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum) {
    Node *n = new Node;
    n->datum = datum;
    if (empty()) {
      n->prev = nullptr;
      n->next = nullptr;
      first = last = n;
    }
    else if (i == begin()) {
      n->prev = nullptr;
      n->next = first;
      first->prev = n;
      first = n;
    }
    else if (i == end()) {
      n->next = nullptr;
      n->prev = last;
      last->next = n;
      last = n;
    }
    else {
        n->next = i.node_ptr;
        n->prev = i.node_ptr->prev;
        n->prev->next = n;
        i.node_ptr->prev = n;
    }
    num_nodes++;
    return(Iterator(this, n));
  }

};//List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
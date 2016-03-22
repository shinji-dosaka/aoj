// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_3-C: Doubly Linked List

#include <cstdio>

template <typename T>
class DoublyLinkedList {
  struct Node {
    Node* prev_;
    Node* next_;
    T x_;
  };
  Node sentinel_;
public:
  DoublyLinkedList()
  {
    sentinel_.prev_ = sentinel_.next_ = &sentinel_;
  }

  void insert_elem_to_first(const T& x)
  {
    Node* np = new Node();
    np->x_ = x;
    np->prev_ = &sentinel_;
    np->next_ = sentinel_.next_;
    np->prev_->next_ = np;
    np->next_->prev_ = np;
  }

  void delete_first_elem(const T& x)
  {
    delete_node(search_first_elem(x));
  }

  void delete_first_node()
  {
    delete_node(sentinel_.next_);
  }

  void delete_last_node()
  {
    delete_node(sentinel_.prev_);
  }
private:
  void delete_node(Node* np)
  {
    if (np) {
      np->next_->prev_ = np->prev_;
      np->prev_->next_ = np->next_;
      delete np;
    }
  }

  Node* search_first_elem(const T& x) const
  {
    Node* np = sentinel_.next_;
    for (;np != &sentinel_; np = np->next_) {
      if (np->x_ == x) return np;
    }
    return nullptr;
  }
public:
  void print(const char* sep=" ") const
  {
    const char* out_sep = "";
    for (const Node* np = sentinel_.next_; np != &sentinel_; np = np->next_) {
      printf("%s%d", out_sep, np->x_);
      out_sep = sep;
    }
    puts("");
  }
};

int main()
{
  unsigned int n;
  std::scanf("%d", &n);
  DoublyLinkedList<int> list;

  for (auto i = 0U; i < n; ++i) {
    char buf[11+1]; // max_length == "deleteFirst".size()+1('\0')
    int x;
    std::scanf("%11s", buf);
    if (buf[0] == 'i') { // insert x
      std::scanf("%d", &x);
      list.insert_elem_to_first(x);
    } else if (buf[6] == 'F') { // deleteFirst
      list.delete_first_node();
    } else if (buf[6] == 'L') { // deleteLast
      list.delete_last_node();
    } else { // (buf[6] == '\0') // delete x 
      std::scanf("%d", &x);
      list.delete_first_elem(x);
    }
  }
  list.print();
}

// eof

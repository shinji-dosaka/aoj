// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_8_A: Binary Search Tree I

#include <cstdio>

#define NDEBUG
#include <cassert>

class BinaryTree {
  struct Node {
    int key;
    Node* parent;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const int key, Node* parent) : key(key), parent(parent) { }
  };

  Node* root_ = nullptr;;
  
public:
  void insert_node(const int key)
  {
    Node** node_p = &root_;
    Node* parent = nullptr;
    while (*node_p) {
      parent = *node_p;
      if ((*node_p)->key > key) {
        node_p = &(*node_p)->left;
      } else if ((*node_p)->key < key) {
        node_p = &(*node_p)->right;
      } else {
        assert(!"duplicate key?");
      }
    }
    (*node_p) = new Node(key, parent);
  }

  void print_nodes() const
  {
    print_in_order(root_);
    std::puts("");
    print_pre_order(root_);
    std::puts("");
  }

private:
  void print_in_order(const Node* node) const
  {
    if (node == nullptr)
      return;
    print_in_order(node->left);
    std::printf(" %d", node->key);
    print_in_order(node->right);
  }

  void print_pre_order(const Node* node) const
  {
    if (node == nullptr)
      return;
    std::printf(" %d", node->key);
    print_pre_order(node->left);
    print_pre_order(node->right);
  }
};

int main()
{
  unsigned int n;
  std::scanf("%u", &n);
  BinaryTree tree;

  for (auto i = 0u; i < n; ++i) {
    char buf[6+1]; // "insert".size() + 1('\0')
    int k;
    std::scanf("%6s", buf);
    if (buf[0] == 'p') { // print
      tree.print_nodes();
    } else { // insert k
      std::scanf("%d", &k);
      tree.insert_node(k);
    }
  }
}

// eof

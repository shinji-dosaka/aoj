// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_8_C: Binary Search Tree III

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

  Node* find_node(const int key) const
  {
    Node* node = root_;
    while (node) {
      if (node->key > key) {
        node = node->left;
      } else if (node->key < key) {
        node = node->right;
      } else { // found
        break;
      }
    }
    return node;
  }

  void delete_node(const int key)
  {
    auto node = find_node(key);
    if (node) {
      node = detach_node(node);
      delete node;
    }
  }

  void print_nodes() const
  {
    print_in_order(root_);
    std::puts("");
    print_pre_order(root_);
    std::puts("");
  }

private:
  Node* detach_leftmost_node(Node* right)
  {
    if (right->left == nullptr) {
      return right;
    }
    auto node = right->left;
    while (node->left) {
      node = node->left;
    }
    node->parent->left = node->right;
    node->right = right;
    return node;
  }

  Node* detach_node(Node* node)
  {
    Node* replace_node;
    if (node->left && node->right) {
      replace_node = detach_leftmost_node(node->right);
      replace_node->left = node->left;
      replace_node->parent = node->parent;
    } else if (node->left) {
      replace_node = node->left;
      replace_node->parent = node->parent;
    } else if (node->right) {
      replace_node = node->right;
      replace_node->parent = node->parent;
    } else { // has no leaves
      replace_node = nullptr;
    }
    if (node->parent == nullptr) {
      root_ = replace_node;
    } else if (node->parent->left == node) {
      node->parent->left = replace_node;
    } else {
      node->parent->right = replace_node;
    }
    return node;
  }

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
    } else {
      std::scanf("%d", &k);
      if (buf[0] == 'i') { // insert k
        tree.insert_node(k);
      } else if (buf[0] == 'f') { // find k
        const auto node = tree.find_node(k);
        std::puts(node ? "yes" : "no");
      } else if (buf[0] == 'd') { // delete k
        tree.delete_node(k);
      } else {
        assert(!"unknown command?");
      }
    }
  }
}

// eof

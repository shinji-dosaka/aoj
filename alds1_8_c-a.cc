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
  void insert_node(const int key) { root_ = insert_tree(root_, key, nullptr); }

  Node* find_node(const int key) const { return find_tree(root_, key); }

  void delete_node(const int key) { root_ = delete_tree(root_, key); }

  void print_nodes() const
  {
    print_in_order(root_);
    std::puts("");
    print_pre_order(root_);
    std::puts("");
  }

private:
  Node* insert_tree(Node* node, int key, Node* parent)
  {
    if (node == nullptr) {
      node = new Node(key, parent);
    } else if (key < node->key) {
      node->left = insert_tree(node->left, key, node);
    } else if (node->key < key) {
      node->right = insert_tree(node->right, key, node);
    } else {
      assert(!"duplicate key?");
    }
    return node;
  }

  Node* find_tree(Node* node, int key) const
  {
    if (node == nullptr) {
      return nullptr;
    } else if (key < node->key) {
      return find_tree(node->left, key);
    } else if (node->key < key) {
      return find_tree(node->right, key);
    } else {
      return node;
    }
  }

  Node* leftmost_node_to_top(Node* right)
  {
    if (right->left == nullptr) {
      return right;
    } else {
      auto node = right->left;
      while (node->left) {
        node = node->left;
      }
      node->parent->left = node->right;
      node->right = right;
      return node;
    }
  }

  Node* delete_tree(Node* node, int key)
  {
    if (node == nullptr) {
      return nullptr;
    } else if (key < node->key) {
      node->left = delete_tree(node->left, key);
    } else if (node->key < key) {
      node->right = delete_tree(node->right, key);
    } else { // delete this node!
      Node* replace_node;
      if (node->left == nullptr && node->right == nullptr) {
        replace_node = nullptr;
      } else {
        if (node->right == nullptr) {
          replace_node = node->left;
        } else if (node->left == nullptr) {
          replace_node = node->right;
        } else {
          replace_node = leftmost_node_to_top(node->right);
          replace_node->left = node->left;
        }
        replace_node->parent = node->parent;
      }
      delete node;
      node = replace_node;
    }
    return node;
  }

  void print_in_order(const Node* node) const
  {
    if (node == nullptr) {
      return;
    }
    print_in_order(node->left);
    std::printf(" %d", node->key);
    print_in_order(node->right);
  }

  void print_pre_order(const Node* node) const
  {
    if (node == nullptr) {
      return;
    }
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

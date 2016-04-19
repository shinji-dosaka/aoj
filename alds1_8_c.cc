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
    Node* parent;
    auto node_p = find_node_p(key, &parent);
    assert(*node_p == nullptr); // not duplicate key
    *node_p = new Node(key, parent);
  }

  Node* find_node(const int key)
  {
    auto node_p = find_node_p(key);
    return *node_p;
  }

  void delete_node(const int key)
  {
    auto node_p = find_node_p(key);
    if (*node_p == nullptr) {
      return;
    }
    auto* replace_node = detach_node(*node_p);
    delete *node_p;
    *node_p = replace_node;
  }

  void print_nodes() const
  {
    print_in_order(root_);
    std::puts("");
    print_pre_order(root_);
    std::puts("");
  }

private:
  Node** find_node_p(const int key, Node** parent_p = nullptr)
  {
    Node** node_p = &root_;
    Node* parent = nullptr;
    while (*node_p) {
      parent = *node_p;
      if (key < (*node_p)->key) {
        node_p = &(*node_p)->left;
      } else if ((*node_p)->key < key) {
        node_p = &(*node_p)->right;
      } else { // found
        break;
      }
    }
    if (parent_p) {
      *parent_p = parent;
    }
    return node_p;
  }

  Node* leftmost_node_to_top(Node* right)
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
    return replace_node;
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

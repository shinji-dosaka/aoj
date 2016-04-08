// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_B: Binary Trees

#include <algorithm>
#include <cstdio>

class BinaryTree {
public:
  static const int NIL = -1;

  struct Node {
    // id is index of nodes_
    int parent = NIL;
    int left = NIL;
    int right = NIL;
    unsigned int depth = 0u;
    unsigned int height = 0u;
  };

private:
  unsigned int n_;
  Node* nodes_;
  
public:
  BinaryTree(unsigned int n) : n_(n), nodes_(new Node[n]) { }

  ~BinaryTree() { delete[] nodes_; }

  Node& operator[](unsigned int id) { return nodes_[id]; }

  void set_depth_and_height()
  {
    (void)set_depth_and_height_internal(root(), 0u);
  }

  void print_nodes() const
  {
    for (auto id = 0u; id < n_; ++id) {
      print_node(id);
    }
  }

private:
  unsigned int set_depth_and_height_internal(int id, unsigned int depth)
  {
    if (id == NIL) {
      return 0u;
    }
    auto& node = nodes_[id];
    node.depth = depth;
    const auto left_height = set_depth_and_height_internal(node.left, depth + 1);
    const auto right_height = set_depth_and_height_internal(node.right, depth + 1);
    auto height = std::max(left_height, right_height);
    node.height = height;
    return height + 1;
  }

  int root() const
  {
    for (auto id = 0u; id < n_; ++id) {
      const auto& node = nodes_[id];
      if (node.parent == NIL) {
        return id;
      }
    }
    return NIL;
  }

  void print_node(unsigned int id) const
  {
    const auto& node = nodes_[id];
    std::printf("node %u: parent = %d, ", id, node.parent);
    std::printf("sibling = %d, degree = %u, ", sibling(id), degree(id));
    std::printf("depth = %u, height = %u, ", node.depth, node.height);
    std::printf("%s\n", type(id));
  }

  int sibling(unsigned int id) const
  {
    const auto& node = nodes_[id];
    if (node.parent == NIL) {
      return NIL;
    }
    auto left = nodes_[node.parent].left;
    auto right = nodes_[node.parent].right;
    auto sibling =
      (left != NIL && static_cast<unsigned int>(left) != id) ? left :
      (right != NIL && static_cast<unsigned int>(right) != id) ? right :
      NIL;
    return sibling;
  }

  int degree(unsigned int id) const
  {
    const auto& node = nodes_[id];
    auto degree = 0u;
    if (node.left != NIL) ++degree;
    if (node.right != NIL) ++degree;
    return degree;
  }

  const char* type(unsigned int id) const
  {
    const auto& node = nodes_[id];
    auto type =
      node.parent == NIL ? "root" :
      node.left == NIL && node.right == NIL ? "leaf" :
      "internal node";
    return type;
  }    
};

int main()
{
  unsigned int n;
  std::scanf("%u", &n);
  BinaryTree tree(n);

  for (auto i = 0u; i < n; ++i) {
    unsigned int id;
    int left, right;
    std::scanf("%u %d %d", &id, &left, &right);

    tree[id].left = left;
    if (left != BinaryTree::NIL) {
      tree[left].parent = id;
    }
    tree[id].right = right;
    if (right != BinaryTree::NIL) {
      tree[right].parent = id;
    }
  }
  tree.set_depth_and_height();

  tree.print_nodes();
}

// eof

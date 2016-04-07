// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_A: Rooted Trees

#include <cstdio>

struct Node {
  // id is index of nodes
  int parent = -1;
  int left_child = -1;
  int right_sibling = -1;
  unsigned int depth = 0;

  const char* type() const
  {
    auto type =
      parent == -1 ? "root" :
      left_child == -1 ? "leaf" :
      "internal node";
    return type;
  }    
};

class RootedTree {
  unsigned int n_;
  Node* nodes_;

public:
  RootedTree(unsigned int n) : n_(n), nodes_(new Node[n]) { }

  ~RootedTree() { delete[] nodes_; }

  Node& operator[](unsigned int id) { return nodes_[id]; }

  void set_depth()
  {
    set_depth_internal(root(), 0u);
  }

  void print_nodes() const
  {
    for (auto i = 0u; i < n_; ++i) {
      auto node = nodes_[i];
      std::printf("node %u: parent = %d, depth = %u, ", i, node.parent, node.depth);
      std::printf("%s, [", node.type());
      int next_c = node.left_child;
      auto sep = "";
      while (next_c != -1) {
        std::printf("%s%d", sep, next_c);
        sep = ", ";
        next_c = nodes_[next_c].right_sibling;
      }
      std::printf("]\n");
    }
  }

private:
  unsigned int root() const
  {
    for (auto i = 0u; i < n_; ++i) {
      if (nodes_[i].parent == -1) {
        return i;
      }
    }
    return -1;
  }

  void set_depth_internal(unsigned int i, unsigned int depth)
  {
    nodes_[i].depth = depth;
    if (nodes_[i].right_sibling != -1) {
      set_depth_internal(nodes_[i].right_sibling, depth);
    }
    if (nodes_[i].left_child != -1) {
      set_depth_internal(nodes_[i].left_child, depth+1);
    }
  }
};

int main()
{
  unsigned int n;
  std::scanf("%u", &n);
  RootedTree tree(n);

  for (auto i = 0u; i < n; ++i) {
    unsigned int id, k, c;
    std::scanf("%u %u", &id, &k);

    int* next_p = &tree[id].left_child;
    for (auto j = 0u; j < k; ++j) {
      std::scanf("%u", &c);
      tree[c].parent = id;
      *next_p = c;
      next_p = &tree[c].right_sibling;
    }
  }

  tree.set_depth();
  tree.print_nodes();
}

// eof

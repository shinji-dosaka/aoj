// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_A: Rooted Trees

#include <cstdio>

const int NIL = -1;

struct Node {
  // id is index of nodes
  int parent = NIL;
  int left_child = NIL;
  int right_sibling = NIL;
  unsigned int depth = 0u;

  const char* type() const
  {
    auto type =
      parent == NIL ? "root" :
      left_child == NIL ? "leaf" :
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
      print_node(i);
    }
  }

private:
  int root() const
  {
    for (auto i = 0u; i < n_; ++i) {
      if (nodes_[i].parent == NIL) {
        return i;
      }
    }
    return NIL;
  }

  void set_depth_internal(unsigned int i, unsigned int depth)
  {
    nodes_[i].depth = depth;
    if (nodes_[i].right_sibling != NIL) {
      set_depth_internal(nodes_[i].right_sibling, depth);
    }
    if (nodes_[i].left_child != NIL) {
      set_depth_internal(nodes_[i].left_child, depth+1);
    }
  }

  void print_node(unsigned int i) const
  {
    auto node = nodes_[i];
    std::printf("node %u: parent = %d, depth = %u, ", i, node.parent, node.depth);
    std::printf("%s, [", node.type());
    int next_c = node.left_child;
    auto sep = "";
    while (next_c != NIL) {
      std::printf("%s%d", sep, next_c);
      sep = ", ";
      next_c = nodes_[next_c].right_sibling;
    }
    std::printf("]\n");
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

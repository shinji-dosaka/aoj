// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_A: Rooted Trees

#include <cstdio>

class RootedTree {
  static const int NIL = -1;

  struct Node {
    // id is index of nodes_
    int parent = NIL;
    int sibling = NIL;
    int first_child = NIL;
    unsigned int depth = 0u;
  };

private:
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
    for (auto id = 0u; id < n_; ++id) {
      print_node(id);
    }
  }

private:
  void set_depth_internal(int id, unsigned int depth)
  {
    if (id == NIL) {
      return;
    }
    auto& node = nodes_[id];
    node.depth = depth;
    set_depth_internal(node.sibling, depth);
    set_depth_internal(node.first_child, depth + 1);
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
    std::printf("node %u: parent = %d, depth = %u, ", id, node.parent, node.depth);
    std::printf("%s, [", type(id));
    int next_c = node.first_child;
    auto sep = "";
    while (next_c != NIL) {
      std::printf("%s%d", sep, next_c);
      sep = ", ";
      next_c = nodes_[next_c].sibling;
    }
    std::printf("]\n");
  }

  const char* type(unsigned int id) const
  {
    const auto& node = nodes_[id];
    auto type =
      node.parent == NIL ? "root" :
      node.first_child == NIL ? "leaf" :
      "internal node";
    return type;
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

    int* next_p = &tree[id].first_child;
    for (auto j = 0u; j < k; ++j) {
      std::scanf("%u", &c);
      tree[c].parent = id;
      *next_p = c;
      next_p = &tree[c].sibling;
    }
  }
  tree.set_depth();

  tree.print_nodes();
}

// eof

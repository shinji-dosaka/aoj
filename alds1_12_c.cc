// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_12_C: Single Source Shortest Path II

#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using uint = unsigned int;

class Graph {
  using vc_t = std::pair<uint, uint>;
  std::vector<std::vector<vc_t>> g_;

public:
  Graph(const uint n) { g_.resize(n); }

  void push_to(const uint u, const uint v, const uint c)
  {
    g_[u].push_back(std::make_pair(v, c));
  }

  void dijkstra(uint* dist)
  {
    auto n = g_.size();
    const uint INFINIT = 100000*(n-1)+1;
    std::fill_n(dist, n, INFINIT);
    auto cmp = [](vc_t left, vc_t right) { return left.second > right.second; };
    std::priority_queue<vc_t, std::vector<vc_t>, decltype(cmp)> q(cmp);
    
    q.push(vc_t(0, 0));
    dist[0] = 0u;
    while (!q.empty()) {
      auto bvc = q.top();
      q.pop();
      auto v = bvc.first, c = bvc.second;
      if (dist[v] < c) {
        continue;
      }
      for (auto vc : g_[v]) {
        auto nv = vc.first, nc = vc.second+c;
        if (dist[nv] < nc) {
          continue;
        }
        dist[nv] = nc;
        q.push(std::make_pair(nv, nc));
      }
    }
  }
};

int main()
{
  uint n;
  std::scanf("%u", &n);

  Graph g(n);

  uint u, k, v, c;
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u %u", &u, &k);
    for (auto j = 0u; j < k; ++j) {
      std::scanf("%u %u", &v, &c);
      g.push_to(u, v, c);
    }
  }

  uint dist[n];
  g.dijkstra(dist);
  for (auto i = 0u; i < n; ++i) {
    std::printf("%u %u\n", i, dist[i]);
  }
}

// eof

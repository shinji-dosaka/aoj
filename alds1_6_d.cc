// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_6-D: Minimum Cost Sort

#include <algorithm>
#include <cstdio>

using uint = unsigned int;

static void make_indices(const uint as[], const uint n, uint indices[])
{
  uint bs[n];
  std::copy(as, as+n, bs);
  std::sort(bs, bs+n);
  for (auto i = 0u; i < n; ++i) {
    indices[bs[i]] = i;
  }
}

static const uint MAX_VALUE = 10000;

static uint minimum_cost_sort(const uint as[], const uint n)
{
  auto cost = 0u;

  uint indices[MAX_VALUE+1];
  make_indices(as, n, indices);

  bool visited[n];
  std::fill(visited, visited+n, false);

  auto min = *std::min_element(as, as+n);

  for (auto i = 0u; i < n; ++i) {
    if (visited[i]) continue;
    auto c_n = 0u, c_min = MAX_VALUE, c_sum = 0u;
    auto j = i;
    while (!visited[j]) {
      visited[j] = true;
      auto a = as[j];
      ++c_n;
      c_min = std::min(c_min, a);
      c_sum += a;
      j = indices[a];
    }
    cost += std::min(c_sum + (c_n-2) * c_min,
                     c_sum + (c_n+1) * min + c_min);
  }
  return cost;
}

int main()
{
  uint n;
  std::scanf("%u", &n);
  uint as[n];
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u", &as[i]);
  }

  auto cost = minimum_cost_sort(as, n);
  std::printf("%u\n", cost);
}

// eof

// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_D: Reconstruction of a Tree

#include <cstdio>
using uint = unsigned int;

static void solve(const uint preorders[], const uint inorders[], const uint indices[],
                  const uint p_index, const uint i_begin, const uint i_end)
{
  if (i_begin >= i_end) {
    return;
  }
  const auto root = preorders[p_index];
  const auto i_index = indices[root];
  const auto len = i_index - i_begin;
  solve(preorders, inorders, indices, (p_index+1), i_begin, i_index);
  solve(preorders, inorders, indices, (p_index+len+1), (i_index+1), i_end);
  std::printf("%u", root);
  std::printf("%s", (p_index == 0) ? "\n" : " ");
}

int main()
{
  uint n;
  std::scanf("%u", &n);
  uint preorders[n];
  uint inorders[n];
  uint indices[n+1]; // 0 not used.
  uint k;
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u", &k);
    preorders[i] = k;
  }
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u", &k);
    inorders[i] = k;
    indices[k] = i;
  }

  solve(preorders, inorders, indices, 0, 0, n);
}

// eof

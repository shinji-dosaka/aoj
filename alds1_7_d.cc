// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_7_D: Reconstruction of a Tree

#include <cstdio>

using uint = unsigned int;
using uintp = uint*;

static void solve(const uintp i_begin, const uintp i_end,
                  const uintp p_begin, const uintp indices[],
                  const char* sep = "\n")
{
  if (i_begin >= i_end) {
    return;
  }
  const auto i_index = indices[*p_begin];
  const auto len = i_index-i_begin;
  auto i_begin1 = i_begin,   i_end1 = i_index, p_begin1 = p_begin+1;
  auto i_begin2 = i_index+1, i_end2 = i_end,   p_begin2 = p_begin+1+len;
  solve(i_begin1, i_end1, p_begin1, indices, " ");
  solve(i_begin2, i_end2, p_begin2, indices, " ");
  std::printf("%u%s", *i_index, sep);
}

int main()
{
  uint n;
  std::scanf("%u", &n);
  uint preorders[n];
  uint inorders[n];
  uintp indices[n+1]; // 0 not used.
  uint k;
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u", &k);
    preorders[i] = k;
  }
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%u", &k);
    inorders[i] = k;
    indices[k] = &(inorders[i]);
  }

  solve(inorders, inorders+n, preorders, indices);
}

// eof

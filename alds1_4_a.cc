// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_4-A: Linear Search

#include <cstdio>

static int linear_search(const int as[], const int target)
{
  auto i = 0;
  while (as[i] != target) {
    ++i;
  }
  return i;
}

int main()
{
  int n;
  std::scanf("%d", &n);
  int ss[n+1]; // n+1(sentinel)
  for (auto i = 0; i < n; ++i) {
    std::scanf("%d", &ss[i]);
  }

  int q;
  std::scanf("%d", &q);
  auto c = 0u;
  for (auto i = 0; i < q; ++i) {
    int t;
    std::scanf("%d", &t);
    ss[n] = t; // sentinel
    auto j = linear_search(ss, t);
    if (j != n) ++c;
  }

  std::printf("%u\n", c);
}

// eof

// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_10_C: Longest Common Subsequence

#include <algorithm>
#include <cstdio>
#include <cstring>

static unsigned int lcs(const char* x, const char* y)
{
  auto m = static_cast<int>(std::strlen(x));
  auto n = static_cast<int>(std::strlen(y));
  unsigned int c1[m+1][n+1]; // extend for -1
  auto c = reinterpret_cast<int(*)[n+1]>(&c1[1][1]); // tricky?

  for (auto i = -1; i < m; ++i) c[i][-1] = 0u;
  for (auto j = 0; j < n; ++j) c[-1][j] = 0u;
  for (auto i = 0; i < m; ++i) {
    for (auto j = 0; j < n; ++j) {
      c[i][j] = (x[i] == y[j])
        ? c[i-1][j-1] + 1
        : std::max(c[i][j-1], c[i-1][j]);
    }
  }
  return c[m-1][n-1];
}

int main()
{
  unsigned int q;
  std::scanf("%u", &q);
  const unsigned int MAX_LEN = 1000;
  char x[MAX_LEN+1], y[MAX_LEN+1];
  for (auto i = 0u; i < q; ++i) {
    std::scanf("%1000s", x);
    std::scanf("%1000s", y);
    auto l = lcs(x, y);
    std::printf("%u\n", l);
  }
}

// eof

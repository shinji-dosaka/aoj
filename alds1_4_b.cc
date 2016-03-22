// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_4-B: Binary Search

#include <cstdio>

const int NOT_FOUND = -1;
static int binary_search(const int as[], int f, int t, const int target)
{
  while (f < t) {
    int m = (f+t)/2; // f+(t-f)/2
    if (target < as[m]) {
      t = m;
    } else if (as[m] < target) {
      f = m+1;
    } else { // as[m] == target
      return m;
    }
  }
  return NOT_FOUND;
}

int main()
{
  int n;
  std::scanf("%d", &n);
  int ss[n];
  for (auto i = 0; i < n; ++i) {
    std::scanf("%d", &ss[i]);
  }

  int q;
  std::scanf("%d", &q);
  auto c = 0u;
  for (auto i = 0; i < q; ++i) {
    int t;
    std::scanf("%d", &t);
    auto j = binary_search(ss, 0, n, t);
    if (j != NOT_FOUND) ++c;
  }

  std::printf("%u\n", c);
}

// eof

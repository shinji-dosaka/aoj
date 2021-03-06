// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_5-D: The Number of Inversions

#include <cstdio>
#include <cstring>

static void print_long(const unsigned long n)
{
  std::printf("%lu\n", n);
}

static unsigned long inversion_count = 0ul;

static void merge(int* const ss, const unsigned int n)
{
  auto n1 = n/2, n2 = n-n1;
  int tmp[n1];
  std::memcpy(tmp, ss, sizeof(tmp));
  auto ss1 = tmp, ss2 = ss+n1;
  auto i = 0u, i1 = 0u, i2 = 0u;
  while (i1 < n1 && i2 < n2) {
    if (ss1[i1] < ss2[i2]) {
      ss[i++] = ss1[i1++];
    } else {
      inversion_count += n1 - i1;
      ss[i++] = ss2[i2++];
    }
  }
  while (i1 < n1) {
    ss[i++] = ss1[i1++];
  }
  while (i2 < n2) {
    ss[i++] = ss2[i2++];
  }
}

static void merge_sort(int* const ss, const unsigned int n)
{
  if (n > 1) {
    auto n1 = n/2, n2 = n-n1;
    auto ss1 = ss, ss2 = ss+n1;
    merge_sort(ss1, n1); // ss[0..n/2-1] is sorted
    merge_sort(ss2, n2); // ss[n/2..n-1] is sorted
    merge(ss, n);
  }
}

int main()
{
  unsigned int n;
  std::scanf("%d", &n);
  int ss[n];
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%d", &ss[i]);
  }

  merge_sort(ss, n);
  print_long(inversion_count);
}

// eof

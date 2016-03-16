// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_2-D: Shell Sort

#include <algorithm>
#include <iostream>

static void print_ints(const int as[], const unsigned int n, const char* sep = " ")
{
  auto out_sep = "";
  for (auto i = 0u; i < n; ++i) {
    std::cout << out_sep << as[i];
    out_sep = sep;
  }
  std::cout << std::endl;
}

static void print_int(const unsigned int n)
{
  std::cout << n << std::endl;
}

static unsigned int cnt = 0u;

static void insert(int as[], const unsigned int i, const unsigned int d)
{
  const auto asi = as[i];
  auto j = i;
  while (j >= d && asi < as[j-d]) {
    as[j] = as[j-d];
    j -= d;
    ++cnt;
  }
  as[j] = asi;
}

static void insertion_sort(int as[], const unsigned int n, const unsigned int d)
{
  for (auto i = d; i < n; ++i) {
    insert(as, i, d);
  }
}

unsigned int next_g(const unsigned int g) { return 3*g + 1; }

unsigned int gen_m(const unsigned int n)
{
  auto m = 1u;
  for (auto g = 1u;;) {
    g = next_g(g);
    if (n < g) break;
    ++m;
  }
  return m;
}

static void shell_sort(int as[], const unsigned int n)
{
  cnt = 0;

  auto m = gen_m(n);
  int gs[m];
  for (auto g = 1u, i = 0u; i < m; ++i) {
    gs[m-1-i] = g;
    g = next_g(g);
  }
  print_int(m);
  print_ints(gs, m);

  for (auto i = 0u; i < m; ++i) {
    insertion_sort(as, n, gs[i]);
  }
  
  print_int(cnt);
}

int main()
{
  unsigned int n;
  std::cin >> n;
  int as[n];
  for (auto i = 0u; i < n; ++i) {
    std::cin >> as[i];
  }

  shell_sort(as, n);
  print_ints(as, n, "\n");
}

// eof

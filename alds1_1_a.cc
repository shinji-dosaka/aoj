// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_1-A: Insertion Sort

#include <iostream>

static void print_ints(const int as[], const unsigned int n)
{
  const char* sep = "";
  for (unsigned int i = 0; i < n; ++i) {
    std::cout << sep << as[i];
    sep = " ";
  }
  std::cout << std::endl;
}

static void insert(int as[], const unsigned int i)
{
  // as[0..i-1] is sorted
  const auto asi = as[i];
  auto j = i;
  while (j >= 1 && asi < as[j-1]) {
    as[j] = as[j-1];
    --j;
  }
  as[j] = asi;
}

static void insertion_sort(int as[], const unsigned int n)
{
  for (auto i = 1u; i < n; ++i) {
    print_ints(as, n);
    insert(as, i);
  }
}

int main()
{
  unsigned int n;
  std::cin >> n;
  int as[n];
  for (auto i = 0u; i < n; ++i) {
    std::cin >> as[i];
  }

  insertion_sort(as, n);
  print_ints(as, n);
}

// eof

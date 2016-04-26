// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_10_A: Fibonacci Number

#include <algorithm>
#include <cstdio>

#define NDEBUG
#include <cassert>

class Fibonnacci {
  static const unsigned int N = 44u;
  unsigned int n_;
  unsigned long* f_;

public:
  Fibonnacci(unsigned int n = N) : n_(std::max(1u, n))
  {
    f_ = new unsigned long[n_+1];
    f_[0] = f_[1] = 1;
    for (auto i = 2u; i <= n; ++i) {
      f_[i] = f_[i-1] + f_[i-2];
    }
  }

  ~Fibonnacci() { delete[] f_; }
  
  unsigned long operator () (unsigned int n) const
  {
    assert(n <= n_);
    return f_[n];
  }
};

int main()
{
  unsigned int n;
  std::scanf("%u", &n);
  Fibonnacci fib;
  std::printf("%lu\n", fib(n));
}

// eof

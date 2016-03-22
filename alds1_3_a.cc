// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_3-A: Stack

#include <cstdio>
#include <cstdlib>

#define NDEBUG
#include <cassert>

template <int N>
class Stack {
  unsigned int top_ = 0u;
  int ds_[N];
public:
  int pop()
  {
    assert(!is_empty());
    return ds_[--top_];
  }
  void push(int i)
  {
    assert(!is_full());
    ds_[top_++] = i;
  }
  bool is_empty() const { return top_ == 0; }
  bool is_full() const { return top_ == N; }
};

template <int N>
class calc {
  Stack<N> stack_;
public:
  void add()
  {
    int b = stack_.pop();
    int a = stack_.pop();
    stack_.push(a+b);
  }

  void sub()
  {
    int b = stack_.pop();
    int a = stack_.pop();
    stack_.push(a-b);
  }

  void mul()
  {
    int b = stack_.pop();
    int a = stack_.pop();
    stack_.push(a*b);
  }    

  int pop() { return stack_.pop(); }
  void push(int i) { stack_.push(i); }
  bool is_empty() { return stack_.is_empty(); }
};

int main()
{
  calc<100> calc; // ns <= 100
  char buf[6+1]; // n <= 10**6 or '+',etc == 1
  
  while (std::scanf("%6s", buf) != EOF) {
    switch (buf[0]) {
    case '+':
      calc.add(); break;
    case '-':
      calc.sub(); break;
    case '*':
      calc.mul(); break;
    default:
      calc.push(std::atoi(buf)); break;
    }
  }

  printf("%d\n", calc.pop());
  assert(calc.is_empty());
}

// eof

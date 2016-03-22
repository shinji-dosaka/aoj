// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_5-C: Koch Curve

#include <cstdio>
#include <cmath>

struct Point {
  const double x, y;
  Point(double x, double y) : x(x), y(y) { }
  Point rotate(double degree) const;
};

Point Point::rotate(double degree) const
{
  auto sin = std::sin(M_PI*degree/180.0);
  auto cos = std::cos(M_PI*degree/180.0);
  return Point(x*cos - y*sin, x*sin + y*cos);
}

Point operator +(const Point& a, const Point& b) { return Point(a.x+b.x, a.y+b.y); }
Point operator -(const Point& a, const Point& b) { return Point(a.x-b.x, a.y-b.y); }
Point operator *(const double a, const Point& b) { return Point(a*b.x, a*b.y); }
Point operator /(const Point& a, const double b) { return Point(a.x/b, a.y/b); }

void print_point(const Point& p) { std::printf("%.8f %.8f\n", p.x, p.y); }

void print_koch(unsigned int n, const Point& a, const Point& b)
{
  if (n == 0) return;

  Point s = (2.0*a + 1.0*b)/3.0;
  Point t = (1.0*a + 2.0*b)/3.0;
  Point u = (t-s).rotate(60) + s;

  print_koch(n-1, a, s); print_point(s);
  print_koch(n-1, s, u); print_point(u);
  print_koch(n-1, u, t); print_point(t);
  print_koch(n-1, t, b);
}

int main()
{
  unsigned int n;
  std::scanf("%d", &n);

  auto a = Point(0.0, 0.0);
  auto b = Point(100.0, 0.0);

  print_point(a);
  print_koch(n, a, b);
  print_point(b);
}

// eof

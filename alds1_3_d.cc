// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_3-D: Areas on the Cross-Section Diagram

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using uint = unsigned int;

struct Area {
  const uint from;
  const uint area;
  Area(const uint from, const uint to) : from(from), area(to-from) { }
};
                     
static stack<Area> prepare_areas(const string& str)
{
  stack<Area> areas;
  stack<uint> s;
  for (auto i = 0u; i < str.size(); ++i) {
    auto c = str[i];
    if (c == '\\') {
      s.push(i);
    } else if (c == '/') {
      if (!s.empty()) {
        areas.push(Area(s.top(), i));
        s.pop();
      }
    } else {
      // nop
    }
  }
  return move(areas);
}

static pair<uint, vector<uint>> accumulate_areas(stack<Area> areas) {
  auto sum = 0u;
  vector<uint> accs;
  while (!areas.empty()) {
    auto p = areas.top();
    areas.pop();
    auto acc = p.area;
    while (!areas.empty() && p.from < areas.top().from) {
      acc += areas.top().area;
      areas.pop();
    }
    sum += acc;
    accs.push_back(acc);
  }
  reverse(accs.begin(), accs.end());
  return move(make_pair(sum, accs));
}

int main()
{
  string str;
  getline(cin, str);
  auto areas = prepare_areas(str);

  auto sum_accs = accumulate_areas(move(areas));
  auto sum = sum_accs.first;
  auto accs = sum_accs.second;

  cout << sum << endl;
  cout << accs.size();
  for (auto acc : accs) {
    cout << " " << acc;
  }
  cout << endl;
}

// eof

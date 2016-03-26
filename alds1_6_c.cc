// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_6-C: Quick Sort

#include <algorithm>
#include <cstring>
#include <iostream>

using uint = unsigned int;

struct Card {
  char suit;
  uint rank;
  uint index; // for stable check
};

std::ostream& operator<<(std::ostream& os, const Card& card)
{
  return os << card.suit << " " << card.rank;
}

std::istream& operator>>(std::istream& is, Card& card)
{
  return is >> card.suit >> card.rank;
}

static void print_cards(const Card cards[], const uint n)
{
  for (auto i = 0u; i < n; ++i) {
    std::cout << cards[i] << std::endl;
  }
}

static bool is_stable(const Card cards[], const uint n)
{
  for (auto i = 0u; i< n-1; ++i) {
    if (cards[i].rank == cards[i+1].rank &&
        cards[i].index > cards[i+1].index) {
      return false;
    }
  }
  return true;
}

static uint partition(Card cards[], uint begin, uint end)
{
  auto last = end-1;
  auto gt = begin;
  for (auto i = begin; i < last; ++i) {
    if (cards[i].rank <= cards[last].rank) {
      std::swap(cards[gt++], cards[i]);
    }
  }
  std::swap(cards[gt], cards[last]);
  return gt;
}

static void quick_sort(Card cards[], uint begin, uint end)
{
  if (end - begin > 1) {
    auto middle = partition(cards, begin, end);
    quick_sort(cards, begin, middle);
    quick_sort(cards, middle+1, end);
  }
}

int main()
{
  uint n;
  std::cin >> n;
  Card cards[n];
  for (uint i = 0; i < n; ++i) {
    cards[i].index = i;
    std::cin >> cards[i];
  }

  quick_sort(cards, 0u, n);

  std::cout << (is_stable(cards, n) ? "Stable" : "Not stable") << std::endl;
  print_cards(cards, n);
}

// eof

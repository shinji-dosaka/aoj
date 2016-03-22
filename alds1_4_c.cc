// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_4-C: Dictionary

#include <cstdio>
#include <cstring>

#define NDEBUG
#include <cassert>

template <unsigned int N>
class Dictionary {
  char** data_;
  unsigned int size_ = 0; // for assert
public:
  Dictionary()
  {
    data_ = new char*[N];
    for (auto i = 0u; i < N; ++i) {
      data_[i] = nullptr;
    }
  }

  ~Dictionary()
  {
    for (auto i = 0u; i < N; ++i) {
      delete_chars(data_[i]);
    }
    delete[] data_;
  }

  void insert(const char* cp)
  {
    assert(size_ < N-1); // at least one vacancy entry needed for not found
    auto i = find_index(cp);
    if (data_[i]) return; // cp was already inserted
    data_[i] = new_chars(cp);
    ++size_;
  }

  bool find(const char* cp) const
  {
    auto i = find_index(cp);
    return data_[i] ? true : false;
  }
private:
  unsigned int find_index(const char* cp) const
  {
    auto h1 = hash1(cp), h2 = hash2(h1);
    auto h = h1 % N;
    for (auto i = 0U; ; ++i) {
      if (data_[h] == nullptr || std::strcmp(data_[h], cp) == 0) {
        return h;
      }
      h = (h+h2) % N; // (h + i*h2(h)) % N;
    }
  }

  unsigned int hash1(const char* cp) const
  {
    auto h = 0U;
    for (; *cp; ++cp) {
      h = 31*h + *cp;
    }
    return h % N;
  }

  unsigned int hash2(int h1) const
  {
    return h1 ? (N-h1) : 1;
  }

  char* new_chars(const char* cp) const
  {
    auto buf = new char[std::strlen(cp)+1];
    std::strcpy(buf, cp);
    return buf;
  }

  char* delete_chars(const char* cp) const
  {
    delete[] cp; // delete nullptr is ok!
  }

};

int main()
{
  const unsigned int M = 1250437; // (prime number) * 0.8 > 1000000
  Dictionary<M> dict;

  int n;
  std::scanf("%d", &n);
  
  for (auto i = 0; i < n; ++i) {
    char buf1[6+1]; // "insert".size() + 1('\0')
    char buf2[12+1]; // 12(max)+1('\0')
    std::scanf("%6s %12s", buf1, buf2);
    if (buf1[0] == 'i') { // insert ...
      dict.insert(buf2);
    } else { // find ...
      bool found = dict.find(buf2);
      puts(found ? "yes" : "no");
    }
  }
}

// eof

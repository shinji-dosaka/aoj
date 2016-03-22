// -*- mode:c++; coding:utf-8; c-basic-offset:2; -*-
// ALDS1_3-B: Queue

#include <cstdio>

#define NDEBUG
#include <cassert>

template <typename T>
class Queue {
  unsigned int head_ = 0u;
  unsigned int size_ = 0u;
  const unsigned int max_;
  T* dp_;
public:
  Queue(unsigned int max) : max_(max) { dp_ = new T[max]; }
  ~Queue() { delete[] dp_; }
  void enqueue(T d)
  {
    assert(!is_full());
    const unsigned int tail = mod_by_max(head_+size_);
    dp_[tail] = d;
    ++size_;
  }

  T dequeue()
  {
    assert(!is_empty());
    T d = dp_[head_];
    head_ = mod_by_max(head_+1);
    --size_;
    return d;
  }

  inline bool is_empty() const { return size_ == 0; }
  inline bool is_full() const { return size_ == max_; }
private:
  inline int mod_by_max(unsigned int i) const { return i < max_ ? i : i -max_; }
};

struct Process {
  char name_[10+1];
  unsigned int time_;
  Process() = default;
  Process(const Process&) = delete;
  Process& operator=(const Process&) = delete;
  unsigned int exec(unsigned int quantum)
  {
    const unsigned int elapse = time_ > quantum ? quantum : time_;
    time_ -= elapse;
    return elapse;
  }
  bool is_finished() const { return time_ == 0; }
};

int main()
{
  unsigned int n, q;
  std::scanf("%d %d", &n, &q);

  Process processes[n];
  Queue<Process*> process_queue(n);
  for (auto i = 0u; i < n; ++i) {
    std::scanf("%10s %d", processes[i].name_, &processes[i].time_);
    process_queue.enqueue(&processes[i]);
  }

  const unsigned int quantum = q;
  unsigned int elapse = 0;
  while (!process_queue.is_empty()) {
    Process* current_process = process_queue.dequeue();
    elapse += current_process->exec(quantum);
    if (current_process->is_finished()) {
      printf("%s %d\n", current_process->name_, elapse);
    } else {
      process_queue.enqueue(current_process);
    }
  }
}

// eof

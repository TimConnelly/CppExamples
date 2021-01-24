#include <iostream>
#include <coroutine>
#include <thread>
#include <cassert>
static constexpr char newline = '\n';

/*
For reference:
https://en.cppreference.com/w/cpp/language/coroutines

Raymond Chen covers TS basics
https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195

https://blog.panicsoftware.com/your-first-coroutine/
*/

class resumable {
  public:
    struct promise_type;
    using coro_handle = std::coroutine_handle<promise_type>;
    
    resumable(coro_handle handle) : m_handle(handle) { assert(handle);}
    resumable(resumable&) = delete;
    resumable(resumable&&) = delete;
    ~resumable() { m_handle.destroy(); }

    bool resume() {
      if (!m_handle.done())
        m_handle.resume();
      return !m_handle.done();
    }
  private:
    coro_handle m_handle;
};

struct resumable::promise_type{
  using coro_handle =  std::coroutine_handle<promise_type>;

  resumable get_return_object() {
    return coro_handle::from_promise(*this);
  }
  auto initial_suspend() {
    return std::suspend_always();
  }
  auto final_suspend() noexcept {
    return std::suspend_always();
  }
  void return_void() {}
  void unhandled_exception() {
    std::terminate();
  }
};

resumable hello_coworld()
{
  std::cout << "Hello " << newline;
  co_await std::suspend_always();
  std::cout << "World" << newline;
}

void first_test()
{
  resumable res = hello_coworld();
  while(res.resume());
}

int main(int argc, const char **argv)
{
    first_test();
    return 0;
}
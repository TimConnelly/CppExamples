#include <iostream>
#include <coroutine>
#include <thread>
#include <cassert>
static constexpr char newline = '\n';

/*
A generator example. 

Adapted from this article on panicsoftware blog:
https://blog.panicsoftware.com/your-first-coroutine/

For reference:
https://en.cppreference.com/w/cpp/language/coroutines

Raymond Chen covers TS basics
https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195
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
    const char* return_val();
    const char* recent_val();
  private:
    coro_handle m_handle;
};

struct resumable::promise_type{
  const char* m_string = "promise";
  using coro_handle =  std::coroutine_handle<promise_type>;

  resumable get_return_object() {
    return coro_handle::from_promise(*this);
  }
  auto initial_suspend() {
    std::cout << "initial suspend" << newline;
    return std::suspend_always();
  }
  auto final_suspend() noexcept {
    std::cout << "final suspend" << newline;
    return std::suspend_always();
  }
  void return_value(const char* string) { m_string = string; } 
  auto yield_value(const char* string) {
    m_string = string;
    return std::suspend_always();
  }
  void unhandled_exception() {
    std::terminate();
  }
};

const char* resumable::return_val() 
{
  return m_handle.promise().m_string;
}

const char* resumable::recent_val()
{
  return m_handle.promise().m_string;
}

resumable generate_foo()
{
  while(true) {
    co_yield "Hello";
    co_yield "Coroutine";
  }
}

void first_test()
{
  resumable res = generate_foo();
  size_t idx = 10;
  while(idx--){
    res.resume();
    std::cout << res.recent_val() << newline;
  }
}

int main(int argc, const char **argv)
{
    first_test();
    return 0;
}

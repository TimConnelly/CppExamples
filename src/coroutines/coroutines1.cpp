#include <iostream>
#include <coroutine>
#include <thread>
#include <cassert>
static constexpr char newline = '\n';

/*
A basic example, if there is such thing as a basic example of coroutines 
right now. 

The idea is to for the coroutine to wait for a specific input before continuing.

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
      std::cout << "resuming" << newline;
      if (!m_handle.done()) {
        char temp;
        std::cin >> temp;
        if (temp == 'x')
          m_handle.resume();
      }
      return !m_handle.done();
    }
    const char* return_val();
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
    return std::suspend_never();
  }
  auto final_suspend() noexcept {
    std::cout << "final suspend" << newline;
    return std::suspend_always();
  }
  void return_value(const char* string) { m_string = string; } 
  void unhandled_exception() {
    std::terminate();
  }
};

const char* resumable::return_val() 
{
  return m_handle.promise().m_string;
}

resumable hello_coworld()
{
  std::cout << "Hello " << newline;
  co_await std::suspend_always();
  std::cout << "World" << newline;
  co_return "Coroutine";
}

void first_test()
{
  resumable res = hello_coworld();
  std::cout << "Press 'x' to end coroutine." << newline;
  while(res.resume())
    ;
  std::cout << res.return_val() << newline;
}

int main(int argc, const char **argv)
{
    first_test();
    return 0;
}

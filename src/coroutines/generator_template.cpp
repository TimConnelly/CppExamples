#include <iostream>
#include <coroutine>
#include <thread>
#include <cassert>

/*
A generator example. 

Adapted from this article on panicsoftware blog:
https://blog.panicsoftware.com/your-first-coroutine/

For reference:
https://en.cppreference.com/w/cpp/language/coroutines

Raymond Chen covers TS basics
https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195
*/
template<class T>
class resumable;

template <class P>
struct promise_type
{
  P m_value = 0;
  using coro_handle = std::coroutine_handle<promise_type>;

  resumable<P> get_return_object()
  {
    return coro_handle::from_promise(*this);
  }
  auto initial_suspend()
  {
    std::cout << "initial suspend" << '\n';
    return std::suspend_always();
  }
  auto final_suspend() noexcept
  {
    std::cout << "final suspend" << '\n';
    return std::suspend_always();
  }
  void return_value(const P value) { m_value = value; }
  auto yield_value(const P value)
  {
    m_value = value;
    return std::suspend_always();
  }
  void unhandled_exception()
  {
    std::terminate();
  }
};

template<class T>
class resumable {
  public:

    using coro_handle = std::coroutine_handle<promise_type<T>>;
    
    resumable(coro_handle handle) : m_handle(handle) { assert(handle);}
    resumable(resumable&) = delete;
    resumable(resumable&&) = delete;
    ~resumable() { m_handle.destroy(); }

    bool resume() {
      if (!m_handle.done())
        m_handle.resume();
        
      return !m_handle.done();
    }
    const T return_val();
    const T recent_val();
  private:
    coro_handle m_handle;
};

template <class T>
const T resumable<T>::return_val() 
{
  return m_handle.promise().m_value;
}

template <class T>
const T resumable<T>::recent_val()
{
  return m_handle.promise().m_value;
}

template <std::incrementable G>
resumable<G> generate_foo()
{
  G value = 0;
  while(true) {
    co_yield value++;
  }
}

void first_test()
{
  resumable<int> res = generate_foo<int>();
  size_t idx = 10;
  while(idx--){
    res.resume();
    std::cout << res.recent_val() << '\n';
  }
}

int main(int argc, const char **argv)
{
    first_test();
    return 0;
}

#include <iostream>
#include <coroutine>

/*
Generator coroutine.
For available off the shelf concepts see:
https://en.cppreference.com/w/cpp/language/coroutines
*/
generator<int> iota(int n = 0) {
  while(true)
    co_yield n++;
}

int main(int argc, const char **argv)
{
    // Basic
    std::cout << "First call: " << iota() <<std::endl;

    return 0;
}
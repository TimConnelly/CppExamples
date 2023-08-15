#include <coroutine>
#include <iostream>
// #include <filesystem>
// #include <vector>
// #include <regex>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

namespace fs = std::filesystem;
static constexpr char NEWLINE {'\n'};

httplib::Result make_request(const std::string uri)
{
    // HTTP
    // httplib::Client cli("http://localhost:18080");
    httplib::Client cli("https://reqres.in");

    // HTTPS
    // httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");

    return cli.Get(uri);
}

struct promise;
 
struct coroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};
 
struct promise
{
    coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    // void return_value() {}
    void unhandled_exception() {}
};
 
struct S
{
    int i;
    coroutine f()
    {
        std::cout << i;
        co_return;
    }
};

void good(const std::string val)
{
    coroutine h = [](const std::string uri) -> coroutine // make i a coroutine parameter
    {
        const auto result = make_request(uri);
        std::cout << result->status << NEWLINE;
        std::cout << result->body << NEWLINE;

        std::cout << uri << NEWLINE;
        co_return;
    }(val);
    std::cout << "doing things" << NEWLINE;

    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
                // frame as a by-value parameter
    h.destroy();
}

int main() {
    good("/api/users/2");
}

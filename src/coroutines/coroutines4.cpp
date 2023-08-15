#include <coroutine>
#include <iostream>
// #include <filesystem>
// #include <vector>
// #include <regex>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

namespace fs = std::filesystem;
static constexpr char NEWLINE {'\n'};

httplib::Result make_request(const std::string& host, const std::string& uri)
{
    // HTTP
    httplib::Client cli(host);
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

void get(const std::string& host, const std::string& val)
{
    coroutine h = [](const std::string& host, const std::string& uri) -> coroutine //
    {
        const auto result = make_request(host, uri);
        std::cout << result->status << NEWLINE;
        std::cout << result->body << NEWLINE;

        std::cout << uri << NEWLINE;
        co_return;
    }(host, val);
    std::cout << "doing things" << NEWLINE;

    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
                // frame as a by-value parameter
    h.destroy();
}

int main() {
    // get("https://reqres.in","/api/users/2");
    get("http://localhost:18080",R"(/)");
    get("http://localhost:18080",R"(/about)");
    get("http://localhost:18080",R"(/json)");
    get("http://localhost:18080",R"(/json_list)");
}

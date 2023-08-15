#include <coroutine>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

namespace fs = std::filesystem;
static constexpr char NEWLINE {'\n'};

std::vector<std::string> glob(const fs::path& path, const std::regex filter)
{
    std::vector<std::string> files;
    for( const auto& dir_entry : fs::recursive_directory_iterator{path}) {
        if (std::regex_search(dir_entry.path().string(), filter)) {
            files.emplace_back(dir_entry.path().string());
        }
    }

    return files;
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

void good(int val)
{
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        const auto pwd = fs::current_path();
        std::cout << pwd << NEWLINE;
        const auto files = glob(pwd, std::regex(R"(.*\.(cpp))"));
        for (const auto& f : files )
        {
            std::cout << f << NEWLINE;
        }
        std::cout << i << NEWLINE;
        co_return;
    }(val);
    std::cout << "doing things" << NEWLINE;
    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
                // frame as a by-value parameter
    h.destroy();
}

int main() {
    good(3);

}

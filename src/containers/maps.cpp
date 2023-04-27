#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <list>

struct thing {
    int b;
};

enum class id {
    one,
    two
};

int main() 
{
    auto t = thing();
    std::map<id, thing> m = {{id::one, t}};

    std::vector<std::reference_wrapper<thing>> v = {t};
    std::cout << v[0].get().b << '\n';

    std::list<thing> l = {t};

}
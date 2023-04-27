// Type your code here, or load an example.
#include <iostream>
#include <memory>
#include <string>
#include <any> 
#include <variant>

class Base {
    public:
        virtual std::string getName() {return "Base";};
};

class Derived1 : Base {
    public:
        std::string getName() override { return "Derived1"; };  
};

class Derived2 : Base {
    public:
        std::string getName() override { return "Derived2"; };  
};

template <typename T>
T make_class() {
    return T();
}

using TVar = std::variant<Derived1, Derived2>;
TVar make_variant_class(std::string s)
{
    TVar val;
    if (s == "Derived1") {
        auto d = Derived1();
        return d;
    }
    return val;
}


class Runner {
    public:
    template <typename R>
    void process (R r) {
        std::cout << "default Runner::process" <<std::endl;
    }
};

template <>
void Runner::process<Derived1> (Derived1 r) {
    std::cout << r.getName() << '\n';
}

template <>
void Runner::process<Derived2> (Derived2 r) {
    std::cout << r.getName() << '\n';
}




int main(void)
{
    // Base b;
    auto a = make_variant_class("Derived1");
    auto b = make_class<Base>();
    Runner r;
    r.process(b);

    // auto c = std::visit([](auto& arg){ 
    //     using T = std::decay_t<decltype(arg)>;
    //     if constexpr (std::is_same_v<T, Derived1>)
    //         auto Runner<Derived1>(arg);
    //     return dynamic_cast<Derived1*>(&arg);
    // }, a);

    // std::visit([](auto arg){std::cout<<arg.getName()<<'\n';}, a);

    // std::cout << c->getName() << std::endl;

    std::visit([&](auto& arg){r.process(arg);}, a);


    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <memory>

// struct S {
//     size_t a = 1;
//     int cols = 10;
//     int rows = 20;
// };

// class Thing {
// public:
//     virtual void run() = 0;
// };

// class Thing2 : public Thing {
//     public:
//     void run() override
//     {
//         interpret();
//     }
//     protected:
//     virtual void interpret() = 0;
// };

// class Thing3 : public Thing2 {
//     void interpret() override {

//     }
// };

template <typename T>
void parseBEArray(const std::vector<uint8_t>& ba, T& parsed)
{
    size_t shift = 0;
    size_t temp = 0;
    std::for_each(ba.crbegin(), ba.crend(), [&](const uint8_t b) {
        size_t b_wide = static_cast<size_t>(b);
        temp |= (b_wide << shift);
        shift += 8;
    });
    // std::cout << "temp = " << temp <<std::endl;
    parsed = static_cast<T>(temp);
}

template <>
void parseBEArray(const std::vector<uint8_t>& ba, double& parsed)
{
    std::vector<uint8_t> temp(8);
    std::reverse_copy(ba.cbegin(), ba.cend(), temp.begin());

    double* ptr = (double*)(temp.data());
    // double rv = (double)(*ptr);
    // double* ptr = static_cast<double*>(&temp[0]);
    double rv = static_cast<double>(*ptr);
    std::cout << "rv = " << rv<<std::endl;
    parsed = rv;
}

int main() {
    // auto t = Thing3();

    // t.run();
    // S card;
    // std::cout << card.a<< std::endl;

    // std::string isTrue = true ? "yes" : "no";
    // std::cout << isTrue << std::endl;
    uint32_t x = 1<<8;
    std::cout << x << std::endl;

    uint32_t result;
    parseBEArray({0,0,1,0}, result);
    std::cout << result << std::endl;

    double fResult;
    parseBEArray({63,248,50,87, 114, 123, 202, 48}, fResult);
    std::cout << fResult << std::endl;

    parseBEArray({64, 16 , 196, 89, 132, 22, 41, 215 }, fResult);
    std::cout << fResult << std::endl;

    // fResult = 15.0;
    // std::cout << std::hex << std::bitset<8>(fResult) <<std::endl;
    // printf("%X\n", fResult);
    std::vector<double> vec = {0.5,0.5,.5, 0.1};
    auto test = std::make_shared<std::vector<double>>(vec);

    // std::vector<double> vec = ;
    auto test_i = std::make_shared<std::vector<double>>(std::initializer_list<double>{0.5,0.5,.5, 0.1});
    for(auto& t : *test_i) {
        std::cout << t << '\n';
    }
}

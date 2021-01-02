#include <iostream>
#include <concepts>

/*
Most basic usage of a standard concept.
For available off the shelf concepts see:
https://en.cppreference.com/w/cpp/concepts
https://en.cppreference.com/w/cpp/iterator#Algorithm_concepts_and_utilities
https://en.cppreference.com/w/cpp/ranges#Range_concepts
*/
template <typename T, typename U>
T f(T t, U u) requires std::same_as<T, U>
{
    return t + u;
}

/*
Define our own concept.
*/
template <typename T>
concept Unsigned = std::is_unsigned<T>::value;

template <typename U> 
U g(U u) requires Unsigned<U>
{
    return u / 2;
}

/*
Conjunctions
*/
template <typename T>
concept SignedIntegral = std::is_signed<T>::value && std::is_integral<T>::value;

template <typename T>
T k(T t) requires SignedIntegral<T>
{
    return -1*t;
}

/*
Requirement sequence
*/
template <typename T>
concept UnsignedAddable = requires(T a) {
    a + a;
    Unsigned<T>;
};

template <UnsignedAddable T>
T ua(T x)
{
    return x + x;
}

/*
Compund Requirements
*/
// TODO

int main(int argc, const char **argv)
{
    // Basic
    std::cout << "Basic concept output: " << f(1l, 2l) << '\n';

    // Self defined concepts
    unsigned int u = 10;
    std::cout << "Self defined concept: " << g(u) << '\n';

    // Combining Concepts
    int t = 10;
    std::cout << "Combining concepts: " << k(t) << '\n';

    // Requirement Sequence
    std::cout << "Requirement sequence: " << ua(u) << '\n';

    return 0;
}
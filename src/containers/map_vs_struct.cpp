#include <cstdio>
#include <map>
#include <string>
#include <vector>

struct Scalar {
  double one;
  double two;
  double three;
};

enum class Elements {
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten
};

struct StructData {
  Scalar one;
  Scalar two;
  Scalar three;
  Scalar four;
  Scalar five;
  Scalar six;
  Scalar seven;
  Scalar eight;
  Scalar nine;
  Scalar ten;
};

static void makeStringMap(benchmark::State& state) {
  for(auto _ : state){
    std::map<std::string, Scalar> stringMap = {
        {"first", {}},
        {"second", {}},
        {"third", {}},
        {"fourth", {}},
        {"fifth", {}},
        {"sixth", {}},
        {"seventh", {}},
        {"eighth", {}},
        {"ninth", {}},
        {"tenth", {}},
    };
    benchmark::DoNotOptimize(stringMap);
  }
}
BENCHMARK(makeStringMap);

// We can't run all these benchmarks at the same time
// static void makeEnumMap(benchmark::State& state) {
//   for(auto _ : state){
//     std::map<Elements, Scalar> enumMap = {
//       {Elements::one, {}},
//       {Elements::two, {}},
//       {Elements::three, {}},
//       {Elements::four, {}},
//       {Elements::five, {}},
//       {Elements::six, {}},
//       {Elements::seven, {}},
//       {Elements::eight, {}},
//       {Elements::nine, {}},
//       {Elements::ten, {}}
//     };
//     benchmark::DoNotOptimize(enumMap);
//   }
// }
// BENCHMARK(makeEnumMap);

static void makeStruct(benchmark::State& state) {
  for(auto _ : state){
    StructData sd;
    benchmark::DoNotOptimize(sd);
  }
}
BENCHMARK(makeStruct);

// static void makeVec(benchmark::State& state) {
//   for(auto _ : state){
//     std::vector<Scalar> vec = {
//       {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
//     };
//     benchmark::DoNotOptimize(vec);
//   }
// }
// BENCHMARK(makeVec);

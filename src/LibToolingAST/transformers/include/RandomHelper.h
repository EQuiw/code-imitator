
#ifndef AUTHORSHIP_EVASION_RANDOMHELPER_H
#define AUTHORSHIP_EVASION_RANDOMHELPER_H
#include <random>

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g) {
  std::uniform_int_distribution<long> dis(0, std::distance(start, end) - 1);
  std::advance(start, dis(g));
  return start;
}

template <typename Iter> Iter select_randomly(Iter start, Iter end, int seed) {
  static std::mt19937 gen(seed);
  return select_randomly(start, end, gen);
}

template <typename Elem> const Elem &select_randomly(const std::vector<Elem> &List, int Seed) {
    return *select_randomly(List.begin(), List.end(), Seed);
}
#endif //AUTHORSHIP_EVASION_RANDOMHELPER_H

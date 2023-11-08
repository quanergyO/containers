#ifndef CPP2_S21_CONTAINERS_1_UTILS_CONDITIONAL_H
#define CPP2_S21_CONTAINERS_1_UTILS_CONDITIONAL_H

namespace S21 {

template <bool B, typename T1, typename T2>
struct conditional {
  using type = T1;
};

template <typename T1, typename T2>
struct conditional<true, T1, T2> {
  using type = T2;
};

template <bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

}  // namespace S21

#endif  // CPP2_S21_CONTAINERS_1_UTILS_CONDITIONAL_H

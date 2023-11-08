#ifndef CPP2_S21_CONTAINERS_1_UTILS_COMPARE_FOR_MAP_H_
#define CPP2_S21_CONTAINERS_1_UTILS_COMPARE_FOR_MAP_H_

namespace s21 {
template <typename T, typename Compare>
struct MapCompare {
  bool operator()(const T &rhs, const T &lhs) const {
    return Compare{}(rhs.first, lhs.first);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_UTILS_COMPARE_FOR_MAP_H_
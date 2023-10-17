#ifndef CPP2_S21_CONTAINERS_1_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_1_MAP_MAP_H_

#include <functional>
#include <memory>
#include <utility>

namespace s21 
{

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>>
class map
{
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pait<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    // using iterator =
    // using const_iterator =
    using size_type = size_t;
    
};

} // namespace s21


#endif // CPP2_S21_CONTAINERS_1_MAP_MAP_H_
#ifndef CONDITIONAL_H
#define CONDITIONAL_H

template<bool B, typename T, typename F>
struct conditional
{
    using type = F;
};

template<typename T, typename F>
struct conditional<true, T, F>
{
    using type = T;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

#endif // CONDITIONAL_H

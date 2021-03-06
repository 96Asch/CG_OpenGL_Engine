#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <vector>

namespace Util{

    char* resourceToChar(const std::string &resource);

    std::string resourceToString(const std::string &resource);

    size_t split(const std::string &string,
                 const char &delim,
                 std::vector<std::string> &list);

    bool isNearlyEqual(const float &a, const float &b);

    /**
    * Code courteously granted from Robin Voetter
    */
    template <typename F>
    constexpr void pack_foreach(F&&) {}

    template <typename F, typename T, typename... Ts>
    constexpr void pack_foreach(F&& f, T&& h, Ts&&... tail) {
        f(h);
        pack_foreach(std::forward<F>(f), tail...);
    }
    /**
    */

    template <typename T>
    T lerp(const T &start, const T &end, const float &alpha) {
        return (start * (1 - alpha) + end * alpha);
    }

}

#endif

#include <type_traits>
#include <tuple>
#include <iostream>
#include <utility>

struct true_type {
    static constexpr bool value = true;
};

struct false_type {
    static constexpr bool value = false;
};

template<int N>
struct is_non_negative : true_type {};

template<>
struct is_non_negative<-1> : false_type {};

template<int index, typename... T>
typename std::enable_if<!is_non_negative<index>::value,int>::type
Iterate(std::tuple<T...>& t) {
    return 0;
}

template<int index, typename... T>
typename std::enable_if<is_non_negative<index>::value,int>::type
Iterate(std::tuple<T...>& t) {
    return std::get<index>(t) + Iterate<index-1>(t);
}

int main() {
    std::tuple<int,int,int> t{1,2,3};
    auto result = Iterate<2>(t);
    std::cout << "result " << result << std::endl;
}

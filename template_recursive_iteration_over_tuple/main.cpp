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

template<int index, typename F, typename... T>
typename std::enable_if<!is_non_negative<index>::value>::type
IterateBackward(F f,std::tuple<T...>& t) {}

template<int index, typename F,typename... T>
typename std::enable_if<is_non_negative<index>::value>::type
IterateBackward(F f,std::tuple<T...>& t) {
    f(std::get<index>(t));
    IterateBackward<index-1>(f,t);
}

template<typename T>
void print(T x) {
    std::cout << x << std::endl;
}

template<typename T>
void multimply(T x) {
    std::cout << (x*2) << std::endl;
}

int main() {
    std::tuple<int,int,int> t{1,2,3};
    constexpr auto max_tuple_index = std::tuple_size<decltype(t)>{}-1;
    using SelectedType = std::tuple_element_t<max_tuple_index, decltype(t)>;
    IterateBackward<max_tuple_index>(print<SelectedType>,t);
    IterateBackward<max_tuple_index>(multimply<SelectedType>,t);
}

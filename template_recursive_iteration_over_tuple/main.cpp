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

template<int N,int M>
struct is_same_value : std::false_type {};

template<int N>
struct is_same_value<N,N> : std::true_type {};

template<int index, int max_index, typename F, typename... T>
typename std::enable_if<is_same_value<index,max_index>::value>::type
IterateForward(F f,std::tuple<T...>& t) {}

template<int index, int max_index, typename F, typename... T>
typename std::enable_if<!is_same_value<index,max_index>::value>::type
IterateForward(F f,std::tuple<T...>& t) {
    f(std::get<index>(t));
    IterateForward<index+1,max_index>(f,t);
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
    constexpr auto tuple_size = max_tuple_index + 1;
    using SelectedType = std::tuple_element_t<max_tuple_index, decltype(t)>;
    std::cout << "Iterate backward" << std::endl;
    IterateBackward<max_tuple_index>(print<SelectedType>,t);
    std::cout << "Iterate backward, multiply elements by 2" << std::endl;
    IterateBackward<max_tuple_index>(multimply<SelectedType>,t);
    std::cout << "Iterate forward" << std::endl;
    IterateForward<0,tuple_size>(print<SelectedType>,t);
    std::cout << "Iterate forward, multiply elements by 2" << std::endl;
    IterateForward<0,tuple_size>(multimply<SelectedType>,t);
}

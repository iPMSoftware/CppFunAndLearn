#include <iostream>

template<typename T>
#if __cplusplus > 201402
typename std::enable_if_t<std::is_same_v<int,decltype(std::declval<T>().foo())>,int>
#elif __cplusplus > 201103
typename std::enable_if_t<std::is_same<int,decltype(std::declval<T>().foo())>::value,int>
#else
typename std::enable_if<std::is_same<int,decltype(std::declval<T>().foo())>::value,int>::type
#endif
InvokeFoo(T t) {
    return t.foo();
}

template<typename T>
#if __cplusplus > 201402
typename std::enable_if_t<!std::is_same_v<int,decltype(std::declval<T>().foo())>>
#elif __cplusplus > 201103
typename std::enable_if_t<!std::is_same<int,decltype(std::declval<T>().foo())>::value>
#else
typename std::enable_if<!std::is_same<int,decltype(std::declval<T>().foo())>::value>::type
#endif
InvokeFoo(T t) {
    std::cout << "Calling " << __func__ << " from struct WithIntFoo" << std::endl;
}

struct WithIntFoo {
    int foo() {
        std::cout << "Calling " << __func__ << " from struct WithIntFoo" << std::endl;
        return 1;
    }
};

struct WithVoidFoo {
    void foo() {
        std::cout << "Calling " << __func__ << " from struct WithVoidFoo" << std::endl;
    }
};

int main() {
    std::cout << "C++ version: " << __cplusplus << std::endl;
    WithIntFoo with_foo;
    WithVoidFoo without_foo;

    InvokeFoo(with_foo);
    InvokeFoo(without_foo);
}


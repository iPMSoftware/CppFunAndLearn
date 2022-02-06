#include <iostream>

int main() {
    auto x {1};
    std::cout << "x jest typem int: " << std::boolalpha << std::is_same<decltype(x),int>::value << std::endl;
    std::cout << "x jest typem std::initializer_list<int>: " << std::boolalpha << std::is_same<decltype(x),std::initializer_list<int>>::value << std::endl;
}
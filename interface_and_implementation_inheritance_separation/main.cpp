#include <iostream>


class Interface {
    public:
    virtual void foo() = 0;

    virtual ~Interface() = default;
};

class InterfaceImpl : virtual public Interface {
    public:
    void foo() override {
        std::cout << __func__ << std::endl;
    }
};

class InterfaceExtended : virtual public Interface {
    public:
    virtual void bar() = 0;
};

class InterfaceExtendedImpl : public InterfaceImpl, public InterfaceExtended {
    public:
    void bar() override {
        std::cout << __func__ << std::endl;
    }
};

int main() {
    InterfaceExtendedImpl iei;
    iei.foo();
    iei.bar();
}
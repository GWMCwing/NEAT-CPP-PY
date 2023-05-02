#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

class Foo {
public:
    void bar() {
        std::cout << "Hello" << std::endl;
    }
};

extern "C" {
    Foo* Foo_new() { return new Foo(); }
    void Foo_bar(Foo* foo) { foo->bar(); }
}
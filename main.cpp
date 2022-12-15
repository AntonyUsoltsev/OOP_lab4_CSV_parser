
#include <iostream>
#include <tuple>

struct Point {
    int x;
    int y;
};
struct Point_float {
    float x;
    float y;
    // Bad
};

// Patterns :

template<typename T>
struct Point_t {
    T x;
    T y;
};

// unique ptr ------ ?

// Шаблоны определяются на фазе компиляции
int main() {
    Point_t<int> pt;
    std::tuple<int,int> tp(2,3);
    std::tuple<int, double, const char*> tup {42, 10.5, "hello"};
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
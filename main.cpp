
#include <iostream>

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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
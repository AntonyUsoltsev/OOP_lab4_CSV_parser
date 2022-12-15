
#include <iostream>
#include <tuple>
#include <string>
#include <cstdint>
#include <vector>

//struct Point {
//    int x;
//    int y;
//};
//struct Point_float {
//    float x;
//    float y;
//    // Bad
//};
//
//// Patterns :
//
//template<typename T>
//struct Point_t {
//    T x;
//    T y;
//};
//
//// unique ptr ------ ?
//
//// Шаблоны определяются на фазе компиляции

//auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t){
//
//}


//variadic templates

template<class...Args>
void print(Args...args) {}

template<class Head, class ...Args>
void print(Head head, Args...args) {
    std::cout << head << " ";
    print(args...);
}

auto get_student() {
    return std::make_tuple(20, "Ivan");
}

int main() {

    //  print(1, 2, "C++", 4400, "kejfekjfk", '\n', 9984);
    std::tuple<int, std::string> tp(2, "eeid");
    std::tuple<int, std::string> tp2{2, "eeid"};
    std::tuple<int, std::string> tp3 = {2, "eeid"};
    std::tuple tp6(2, "eeid");

    std::tuple<int, std::string> tp4 = std::make_tuple(42, "C++");
    auto tp5 = std::make_tuple(42, "C++");

    //  print(std::get<0> (tp5));
    // print(std::get<1> (tp5));

    int a;
    std::string b;
    std::tie(a, b) = std::make_tuple(33, "c++");
    auto tp7 = std::tie(a, b);
    // print('\n',a,b);

    int age;
    std::string name;
    std::tie(age, name) = get_student();
   // print(age, name);

    auto get_student2 = []() {
        return std::make_tuple(23, "katya");
    };
    std::tie(age, name) = get_student2();
   // print(age, name);
    if (std::make_tuple(39, "a") < std::make_tuple(40, "b")) {
       // print("true");
    }
    struct Man {
        uint16_t age;
        uint16_t langs;
        uint16_t jobs;
    };
    Man m1{22, 1, 1};
    Man m2{20, 1, 2};
    Man m3{25, 5, 1};
    std::vector<Man> mans{m1, m2, m3};
    std::sort(mans.begin(),mans.end(),[](const Man&m1, const Man&m2){
        if (m1.jobs < m2.jobs)
            return true;
        if (m1.langs < m2.langs)
            return true;
        if (m1.age < m2.age)
            return true;
        return false;
    });
    std::for_each(mans.begin(),mans.end(),[](const Man&man){
        std::cout<<"jobs:"<<man.jobs<<" lang "<< man.langs<<" age "<<man.age << std::endl;
    });

//    std::tuple<int, double, const char *> tup{42, 10.5, "hello"};
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
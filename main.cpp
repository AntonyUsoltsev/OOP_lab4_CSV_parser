#include <iostream>
#include <tuple>
#include <string>
#include <vector>

//auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t){
//
//}

//variadic templates

//template int
template<std::size_t>
struct str_int {
};

template<class Tuple>
std::ostream& print_tuple(std::ostream &os, const Tuple &tp, str_int<1>){
    std::cout<< std::get<std::tuple_size<Tuple>::value-1>(tp);
    return os;
}

template<class Tuple, std::size_t Pos>
std::ostream& print_tuple(std::ostream &os, const Tuple &tp, str_int<Pos>){
    std::cout<< std::get<std::tuple_size<Tuple>::value-Pos>(tp)<<" , ";
    return print_tuple(os,tp,str_int<Pos-1>());
}

template<class...Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &tp) {
    os << "(";
    print_tuple(os, tp, str_int<sizeof...(Args)>());
    return os << ")";
}


int main() {

    auto super_tp = std::tuple_cat(std::make_tuple(1, 2, 3), std::make_tuple(4, 5, 6));
    std::cout << super_tp;

    return 0;
}



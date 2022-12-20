//
// Created by Antony on 18.12.2022.
//
#ifndef LAB4_CSV_PARSER_TUPLE_PRINT_H
#define LAB4_CSV_PARSER_TUPLE_PRINT_H

#include <iostream>
#include <tuple>
#include "CSV_parser.h"

// Template int.
template<std::size_t>
struct str_int {
};

template<class Tuple, typename Ch, typename Tr>
std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<1>) {
    os << std::get<std::tuple_size<Tuple>::value - 1>(tp);
    return os;
}

template<class Tuple, typename Ch, typename Tr, std::size_t Pos>
std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<Pos>) {
    os << std::get<std::tuple_size<Tuple>::value - Pos>(tp) << ", ";
    return print_tuple(os, tp, str_int<Pos - 1>());
}

template<typename ...Args, typename Ch, typename Tr>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &tp) {
    os << "(";
    print_tuple(os, tp, str_int<sizeof...(Args)>());
    os << ")";
    return;
}

template<typename ...Args, typename Ch, typename Tr>
auto operator<<(std::basic_ostream<Ch, Tr> &os, CSV_parser<Args...> &parser) {
    return os << parser.get_tuple();
}

#endif //LAB4_CSV_PARSER_TUPLE_PRINT_H

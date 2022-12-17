//
// Created by Antony on 17.12.2022.
//


#ifndef LAB4_CSV_PARSER_CSV_PARSER_H
#define LAB4_CSV_PARSER_CSV_PARSER_H

#include <iostream>

#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Exceptions.h"

//template int
template<std::size_t>
struct str_int {
};

template<class Tuple, typename Ch, typename Tr>
std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<1>) {
    std::cout << std::get<std::tuple_size<Tuple>::value - 1>(tp);
    return os;
}

template<class Tuple, typename Ch, typename Tr, std::size_t Pos>
std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<Pos>) {
    std::cout << std::get<std::tuple_size<Tuple>::value - Pos>(tp) << ", ";
    return print_tuple(os, tp, str_int<Pos - 1>());
}

template<typename ...Args, typename Ch, typename Tr>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &tp) {
    os << "(";
    print_tuple(os, tp, str_int<sizeof...(Args)>());
    os << ")";
    return;
}

template<std::size_t>
struct str_int_1 {
};

template<typename ...Args>
class CSV_parser {
private:
    // int skip_lines;
    //  std::basic_ifstream<char> &csv_file;
public:
    std::vector<std::tuple<Args...>> tp_vect;
   // std::tuple<Args ...> super_tp;

    CSV_parser(std::basic_ifstream<char> &fin, int skip) {
        parse_csv(fin, skip);
    }

    void parse_csv(std::basic_ifstream<char> &fin, int skip) {
        std::string data;
        for (int i = 0; i < skip; i++) {
            if (!std::getline(fin, data, '\n')) {
                throw Exceptions("to few strings to skip", 1);
            }
        }
        while (std::getline(fin, data, '\n')) {
            int cur_pos = 0;
            //Head a;
          auto res =  str_to_tuple<Args...>(cur_pos, data, str_int_1<sizeof...(Args)>());
         //    std::cout << super_tp;
             std::cout << '\n';
        }

    }

    template<typename Head, typename ...Params, std::size_t Pos>
    std::tuple<Head> str_to_tuple(int cur_pos, std::string data, str_int_1<Pos>) {
        int comma_pos = static_cast<int>( data.find(',', cur_pos));
        std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
        cur_pos = comma_pos + 1;
        std::istringstream ist(elem);
        Head a;
        ist >> a;
        std::tuple<Head> tp(a);
       // std::cout <<tp;
        //super_tp =  std::tuple_cat(super_tp,tp);
       //return std::tuple_cat(tp, str_to_tuple<Params...>(cur_pos, data, str_int_1<Pos - 1>()));
        str_to_tuple<Params...>(cur_pos, data, str_int_1<Pos - 1>());
        //std::cout << '\n';
        return tp;
    }

    template<typename Head>
    std::tuple<Head> str_to_tuple(int cur_pos, std::string data, str_int_1<1>) {
        int comma_pos = static_cast<int>( data.find(',', cur_pos));
        std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
        std::istringstream ist(elem);
        Head a;
        ist >> a;
        std::tuple<Head> tp(a);
        //std::cout <<tp;
        //std::cout <<'\n';
       // super_tp =  std::tuple_cat(super_tp,tp);
        return tp;
    }

};

//template<typename Head, typename ...Args>
//std::tuple<Head> str_to_tuple(int cur_pos, std::string data) {
//    int comma_pos = static_cast<int>( data.find(',', cur_pos));
//    if (comma_pos == -1) {
//        comma_pos = data.size() - 1;
//    }
//    std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
//    cur_pos = comma_pos;
//    std::istringstream ist(elem);
//    Head a;
//    ist >> a;
//    std::tuple<Head> tp(a);
//    auto res = std::tuple_cat(tp, str_to_tuple<Args...>(cur_pos, data));
//    return res;
//}

#endif //LAB4_CSV_PARSER_CSV_PARSER_H

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
#include "Tuple_print.h"


template<std::size_t>
struct str_pos {
};

template<typename ...Args>
class CSV_parser {
public:
    std::vector<std::tuple<Args...>> tp_vect;
    std::tuple<Args ...> res_tp;

    CSV_parser(std::basic_ifstream<char> &fin, int skip) {
        std::string data;
        for (int i = 0; i < skip; i++) {
            if (!std::getline(fin, data, '\n')) {
                throw Exceptions("To few strings to skip", BAD_FILE);
            }
        }
        while (std::getline(fin, data, '\n')) {
            int cur_pos = 0;
            str_to_tuple<Args...>(cur_pos, data, str_pos<0>());
            // std::cout << super_tp;
            tp_vect.push_back(res_tp);
            //std::cout << '\n';
        }
    }

    template<typename Head, typename ...Params, std::size_t Pos>
    void str_to_tuple(int cur_pos, std::string data, str_pos<Pos>) {
        int comma_pos = static_cast<int>( data.find(',', cur_pos));
        std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
        cur_pos = comma_pos + 1;
        std::istringstream ist(elem);
        Head a;
        ist >> a;
        std::get<Pos>(res_tp) = a;
        str_to_tuple<Params...>(cur_pos, data, str_pos<Pos + 1>());
    }


    template<typename ...Params>
    void str_to_tuple(int cur_pos, const std::string &data, str_pos<sizeof...(Args)>) {}

    ~CSV_parser() = default;
};

#endif //LAB4_CSV_PARSER_CSV_PARSER_H

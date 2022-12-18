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
#include <cstring>
#include <typeinfo>
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
    char separator;
    char end_line;
    char shield;
    int row;

    void prog_args(char **argv) {
        separator = *argv[1];
        end_line = *argv[2];
        if (end_line == '\\')
            end_line = '\n';
        if (argv[3] != nullptr) {
            shield = *argv[3];
            if (shield == '\000')
                shield = '"';
        } else
            shield = '"';
    }

   CSV_parser(char **argv, std::basic_ifstream<char> &fin, int skip) {
        prog_args(argv);

        std::string data;
        for (int i = 0; i < skip; i++)
            if (!std::getline(fin, data, end_line))
                throw Exceptions("To few strings to skip", BAD_FILE_DATA);

        row = skip + 1;

        while (std::getline(fin, data, end_line)) {
            int cur_pos = 0;
            str_to_tuple<Args...>(cur_pos, data, str_pos<0>());
            row++;
            // std::cout << super_tp;
            tp_vect.push_back(res_tp);
            //std::cout << '\n';
        }
    }

    template<typename Head, typename ...Params, std::size_t Pos>
    void str_to_tuple(int cur_pos, std::string data, str_pos<Pos>) {
        Head a;
        if (data[cur_pos] == shield) {
            int comma_pos = static_cast<int>(data.find(shield, cur_pos + 1));
            std::string elem = data.substr(cur_pos + 1, comma_pos - cur_pos - 1);
            std::istringstream ist(elem);
            ist >> a;
            Head b;
            if(typeid(Head) == typeid(std::string))
                while (!ist.eof()) {
                    ist >> b;
                    a = a + ' ' + b;
                }
            else if (!ist.eof())
                throw Exceptions(
                        "Bad data in " + std::to_string(row) + " row, in " + std::to_string(cur_pos + 1) + '-' +
                        std::to_string(comma_pos) + " columns", BAD_FILE_DATA);

            cur_pos = comma_pos + 2;
        } else {
            int comma_pos = static_cast<int>(data.find(separator, cur_pos));
            std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
            std::istringstream ist(elem);

            ist >> a;
            if (!ist.eof()) {
                throw Exceptions(
                        "Bad data in " + std::to_string(row) + " row, in " + std::to_string(cur_pos + 1) + '-' +
                        std::to_string(comma_pos) + " columns", BAD_FILE_DATA);
            }
            cur_pos = comma_pos + 1;
        }

        std::get<Pos>(res_tp) = a;
        str_to_tuple<Params...>(cur_pos, data, str_pos<Pos + 1>());
    }


    template<typename ...Params>
    void str_to_tuple(int cur_pos, const std::string &data, str_pos<sizeof...(Args)>) {}

    ~CSV_parser() = default;
};

#endif //LAB4_CSV_PARSER_CSV_PARSER_H

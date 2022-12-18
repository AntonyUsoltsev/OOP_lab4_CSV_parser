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

    // Some kostyl :)
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

    // Parse CSV to tuples.s
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

    // Convert string to required tuple.
    template<typename Head, typename ...Params, std::size_t Pos>
    void str_to_tuple(int cur_pos, std::string data, str_pos<Pos>) {
        try {
            Head a, b;
            int comma_pos;
            std::istringstream ist;

            if (data[cur_pos] == shield) {
                ist = get_substr(shield, cur_pos + 1, comma_pos, data);
                ist >> a;
                if (typeid(Head) == typeid(std::string))
                    while (!ist.eof()) {
                        ist >> b;
                        a = a + ' ' + b;
                    }
                comma_pos++;

            } else {
                ist = get_substr(separator, cur_pos, comma_pos, data);
                ist >> a;
            }

            if (!ist.eof())
                throw Exceptions(bad_data(cur_pos, comma_pos), BAD_FILE_DATA);

            std::get<Pos>(res_tp) = a;

            cur_pos = comma_pos + 1;
            str_to_tuple<Params...>(cur_pos, data, str_pos<Pos + 1>());
        }
        catch (const std::exception &ex) {
            throw Exceptions("Wrong length of" + std::to_string(row) + " string (too short)", BAD_FILE_DATA);
        }
    }

    // Return a substring as an input stream
    std::istringstream get_substr(char sep, int cur_pos, int &comma_pos, const std::string& data) {
        comma_pos = static_cast<int>(data.find(sep, cur_pos));
        std::string elem = data.substr(cur_pos, comma_pos - cur_pos);
        if ( elem.empty()){
            throw Exceptions(empty_data(cur_pos), BAD_FILE_DATA);
        }
        std::istringstream ist(elem);
        return ist;
    }

    // Return position of bad interval.
    std::string bad_data(int a, int b) {
        return "Bad data in " + std::to_string(row) + " row, in " + std::to_string(a + 1) + '-' +
               std::to_string(b) + " columns";
    }

    // Return position of empty interval.
    std::string empty_data(int a) {
        return "Empty data in " + std::to_string(row) + " row, in " + std::to_string(a )  + " column";
    }

    // Recursion bottom.
    template<typename ...Params>
    void str_to_tuple(int cur_pos, const std::string &data, str_pos<sizeof...(Args)>) {
        if (cur_pos != 0) {
            throw Exceptions("Wrong length of " + std::to_string(row) + " string ", BAD_FILE_DATA);
        }
    }

    ~CSV_parser() = default;
};

#endif //LAB4_CSV_PARSER_CSV_PARSER_H

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
        //std::cout << argv[1] << " " << argv[2] << " "<< argv[3] << '\n';
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

        //std::cout << separator << " " <<end_line << " "<<shield << '\n';
    }

    CSV_parser(char **argv, std::basic_ifstream<char> &fin, int skip) {
        prog_args(argv);
        row = 1;
        std::string data;
        for (int i = 0; i < skip; i++) {
            row++;
            if (!std::getline(fin, data, end_line)) {
                throw Exceptions("To few strings to skip", BAD_FILE);
            }
        }

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
        std::cout << data[cur_pos] << "  "<< shield << '\n';

        if (data[cur_pos] == shield){
            int comma_pos = static_cast<int>( data.find(shield, cur_pos + 1));
            std::string elem = data.substr(cur_pos+1, comma_pos - cur_pos-1);
            std::istringstream ist(elem);
            Head a,b;
            ist>>a;
            while (!ist.eof()){
                ist>>b;
                a = a + ' ' + b;
            }
            std::get<Pos>(res_tp) = a;
            cur_pos = comma_pos+2;
        }
        else {
        int comma_pos = static_cast<int>( data.find(separator, cur_pos));
        std::string elem = data.substr(cur_pos, comma_pos - cur_pos);


        std::istringstream ist(elem);
        Head a;
        ist >> a;
//        auto size = ist.gcount();
//        std::cout <<size;
//        if(ist.fail()){
//            throw Exceptions("fdg",4);
//        }
        //td::string ghhg = std::str

        if (!ist.eof()) {
            auto size = ist.gcount();
            std::cout << size;
            throw Exceptions(
                    "Bad data in " + std::to_string(row) + " row, " + std::to_string(cur_pos+size) + " column", 1);
        }
        std::get<Pos>(res_tp) = a;
        cur_pos = comma_pos + 1;
       }

        str_to_tuple<Params...>(cur_pos, data, str_pos<Pos + 1>());

    }


    template<typename ...Params>
    void str_to_tuple(int cur_pos, const std::string &data, str_pos<sizeof...(Args)>) {}

    ~CSV_parser() = default;
};

#endif //LAB4_CSV_PARSER_CSV_PARSER_H

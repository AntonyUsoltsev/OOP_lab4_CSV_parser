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

template<std::size_t>
struct str_pos {
};

template<typename ...Args>
class CSV_parser {
private:

    template<class Iterator>
    class CSV_iterator {
    public:
        typedef Iterator iterator_type;
        typedef iterator_type &reference;

        iterator_type *value;

        bool operator!=(CSV_iterator const &other) const {
            return value != other.value;
        }

        typename CSV_iterator::reference operator*() const {
            return *value;
        }

        CSV_iterator &operator++() {
            if (value->file.eof()) {
                *this = nullptr;
                return *this;
            }
            std::getline(value->file, value->cur_line, value->end_line);
            value->template str_to_tuple<Args...>(0, str_pos<0>());
            value->line_num++;
            return *this;
        }

        friend class CSV_parser;

        CSV_iterator(Iterator *iter) : value(iter) {};

        CSV_iterator(const CSV_iterator &it) : value(it.value) {}
    };


public:
    char separator;              // Data separator value.
    char end_line;               // End of line value.
    char shield;                 // Shielding value.
    int line_num;                // Number of current line.
    std::ifstream file;          // Current csv file.
    std::string cur_line;        // Current line.
    std::tuple<Args ...> res_tp; // Result tuple.

    CSV_iterator<CSV_parser> begin() {
        CSV_parser<Args...> *csv_parser = this;
        return iterator(csv_parser);
    }

    CSV_iterator<CSV_parser> end() {
        return nullptr;
    }

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

    CSV_parser() = default;

    // Parse CSV to tuples.s
    CSV_parser(char **argv, std::basic_ios<char> &fin, int skip) {
        file.basic_ios<char>::rdbuf(fin.rdbuf());
        prog_args(argv);

        std::string data;
        for (int i = 0; i < skip; i++)
            if (!std::getline(file, cur_line, end_line))
                throw Exceptions("To few strings to skip", BAD_FILE_DATA);

        line_num = skip + 1;
        std::getline(file, cur_line, end_line);
        str_to_tuple<Args...>(0, str_pos<0>());
        line_num++;
    }

    // Convert string to required tuple.
    template<typename Head, typename ...Params, std::size_t Pos>
    void str_to_tuple(int cur_pos, str_pos<Pos>) {
        try {
            Head head;
            int comma_pos;
            std::string data;
            if (cur_line[cur_pos] == shield) {
                data = get_substr(shield, cur_pos + 1, comma_pos);
                comma_pos++;
            } else
                data = get_substr(separator, cur_pos, comma_pos);

            str_to_head(cur_pos, comma_pos, data, head);

            std::get<Pos>(res_tp) = head;

            cur_pos = comma_pos + 1;
            str_to_tuple<Params...>(cur_pos, str_pos<Pos + 1>());
        }
        catch (const std::exception &ex) {
            throw Exceptions("Wrong length of " + std::to_string(line_num) + " string (too short)", BAD_FILE_DATA);
        }
    }

    // Convert substring to Head elem.
    template<typename Head>
    Head str_to_head(int cur_pos, int comma_pos, const std::string &data, Head &head) {
        std::istringstream ist(data);
        std::cout << data.length();
        ist >> head;
        std::cout << head;
        if (!ist.eof())
            throw Exceptions(bad_data(cur_pos, comma_pos), BAD_FILE_DATA);
        return head;
    }

    // Convert substring to Head elem.
    std::string str_to_head(int cur_pos, int comma_pos, const std::string &data, std::string &head) {
        head = data;
        return head;
    }

    // Return a substring.
    std::string get_substr(char sep, int cur_pos, int &comma_pos) {
        comma_pos = static_cast<int>(cur_line.find(sep, cur_pos));
        std::string elem = cur_line.substr(cur_pos, comma_pos - cur_pos);
        if (elem.empty())
            throw Exceptions(empty_data(cur_pos), BAD_FILE_DATA);
        return elem;
    }

    // Return position of bad interval.
    std::string bad_data(int a, int b) {
        return "Bad data in " + std::to_string(line_num) + " row, in " + std::to_string(a + 1) + '-' +
               std::to_string(b % cur_line.size()) + " columns";
    }

    // Return position of empty interval.
    std::string empty_data(int a) {
        return "Empty data in " + std::to_string(line_num) + " row, in " + std::to_string(a) + " column";
    }

    // Recursion bottom.
    template<typename ...Params>
    void str_to_tuple(int cur_pos, str_pos<sizeof...(Args)>) {
        if (cur_pos != 0) {
            throw Exceptions("Wrong length of " + std::to_string(line_num) + " string ", BAD_FILE_DATA);
        }
    }

    ~CSV_parser() = default;
};


#endif //LAB4_CSV_PARSER_CSV_PARSER_H

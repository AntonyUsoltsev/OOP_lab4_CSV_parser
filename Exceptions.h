//
// Created by Antony on 17.12.2022.
//

#ifndef LAB4_CSV_PARSER_EXCEPTIONS_H
#define LAB4_CSV_PARSER_EXCEPTIONS_H

#include<iostream>

enum {
    FILE_NOT_OPEN = 2,
    BAD_PROG_ARGS = 3,
    BAD_FILE_DATA = 4
};

class Exceptions : std::exception {
private:
    std::string reason;
    int return_code;
public:
    explicit Exceptions(std::string reas, int code) : reason(std::move(reas)), return_code(code) {}

    std::string what_err() {
        return this->reason;
    }

   int ret_code() const {
        return this->return_code;
    }
};

#endif //LAB4_CSV_PARSER_EXCEPTIONS_H

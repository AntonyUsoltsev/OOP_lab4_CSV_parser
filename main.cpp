#include "CSV_parser.h"

int main() {
    try {
        std::ifstream file("test.csv");
        if (!file.is_open())
            throw Exceptions("file isn't open", 2);
        CSV_parser<int, int, std::string> parser(file, 0);
        for (std::tuple<int, int, std::string> rs: parser.tp_vect) {
            std::cout << rs;
            std::cout << std::endl;
        }

    }
    catch (const std::string &ex) {
        std::cerr << ex;
    }
    return 0;
}



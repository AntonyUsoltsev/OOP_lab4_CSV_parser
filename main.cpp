#include "Tuple_print.h"
#include <ctime>
// Work with non-empty data

int main(int argc, char **argv) {
    clock_t beg = clock();
    try {
        if (argc < 3)
            throw Exceptions("Too few args in command line", BAD_PROG_ARGS);

        std::ifstream file("test.csv");
        if (!file.is_open())
            throw Exceptions("File isn't open", FILE_NOT_OPEN);

        std::ofstream file_out("out.txt");

        CSV_parser<std::string, int, std::string, std::string,std::string, std::string> parser(argv, file, 0);
        for (CSV_parser<std::string, int, std::string, std::string,std::string, std::string>&it : parser) {
            //std::get<5>(it.res_tp) -=100;
            file_out << it;
            file_out << std::endl;
        }
        clock_t end = clock();
        std::cout << end-beg;
        return 0;
    }
    catch (Exceptions &ex) {
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what_err();
        return ex.ret_code();
    }
    catch (std::exception &ex) {
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what();
        return 1;
    }
}

//int, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string
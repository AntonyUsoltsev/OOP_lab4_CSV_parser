#include "CSV_parser.h"

int main() {
    try {
        std::ifstream file("test.csv");
        if (!file.is_open())
            throw Exceptions("File isn't open", FILE_NOT_OPEN);
        CSV_parser<int, int, std::string> parser(file, 0);
        for (const auto& rs: parser.tp_vect) {
            std::cout << rs;
            std::cout << std::endl;
        }
        file.close();
        return 0;
    }
    catch (Exceptions &ex) {
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what_err();
        return ex.ret_code();
    }
    catch(std::exception &ex){
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what();
        return 1;
    }
}



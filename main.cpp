#include <iostream>

#include <tuple>
#include <string>
#include <vector>
#include <fstream>

#include "CSV_parser.h"
#include "Exceptions.h"

////variadic templates
////template int
//template<std::size_t>
//struct str_int {
//};
//
//template<class Tuple, typename Ch, typename Tr>
//std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<1>) {
//    std::cout << std::get<std::tuple_size<Tuple>::value - 1>(tp);
//    return os;
//}
//
//template<class Tuple, typename Ch, typename Tr, std::size_t Pos>
//std::ostream &print_tuple(std::basic_ostream<Ch, Tr> &os, const Tuple &tp, str_int<Pos>) {
//    std::cout << std::get<std::tuple_size<Tuple>::value - Pos>(tp) << ", ";
//    return print_tuple(os, tp, str_int<Pos - 1>());
//}
//
//template<typename ...Args, typename Ch, typename Tr>
//auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &tp) {
//    os << "(";
//    print_tuple(os, tp, str_int<sizeof...(Args)>());
//    os << ")";
//    return;
//}

int main() {
    try {
//    auto super_tp = std::tuple_cat(std::make_tuple(1, 2, 3), std::make_tuple(4, 5, 6));
//    std::cout << super_tp;

        std::ifstream file("test.csv");
        if (!file.is_open())
            throw Exceptions("file isn't open",2);
        CSV_parser<int, int,std::string> parser(file, 0 );
//        for (std::tuple<int, std::string> rs: parser) {
//            std::cout << rs << std::endl;
//        }
//
//        std::string test = "avd,dndn,dddlld";
//        int cur_pos = 0;
//        int comma_pos = static_cast<int>( test.find(',', cur_pos));
//        std::string elem = test.substr(cur_pos, comma_pos - cur_pos);
//        std::cout <<elem << "\n";
//        cur_pos = comma_pos+1;
//         comma_pos = static_cast<int>( test.find(',', cur_pos));
//         elem = test.substr(cur_pos, comma_pos - cur_pos);
//        std::cout <<elem << "\n";
//        cur_pos = comma_pos+1;
//         comma_pos = static_cast<int>( test.find(',', cur_pos));
//         elem = test.substr(cur_pos, comma_pos - cur_pos);
//        std::cout <<elem << "\n";
//
//        if (comma_pos == -1) {
//            comma_pos = test.size();
//        }
//         elem = test.substr(cur_pos, comma_pos - cur_pos);
//        std::cout <<elem << "\n";

         auto tp1 = std::make_tuple(1, 2, 3);
        auto super_tp = std::tuple_cat(tp1, std::make_tuple(4, 5, 6));
      //  std::cout<<super_tp ;
        //std::cout<<tp1 ;

    }
    catch (const std::string &ex) {
        std::cerr << ex;
    }


    return 0;
}



#include <iostream>
#include "yaclip.hpp"

using namespace std;

//template<size_t size>
//bool parse(yaclip::map&map, char const * (&argv)[size]) {
    //return map.parse(size, argv);
//}
template <class T> using magic_method = std::function<int(T*,int)>;

struct option_checks {
    int desc;

    int check_desc(int i) {
        return 0;
    }
};


struct check2 {
    int operator()(int i) {
        return 0;
    }
};

int main() {

    //compact declaration
    yaclip::map map;

    map["d"].opt<int>("d", 0, "desc..", [](int i) { std::cout << "I like " << i ; return i;});
    map["d"].opt<int>("d", 0, "desc..", &option_checks::check_desc);

    map["shoot"]["x"].opt<bool>("x", false, "desc...");
    map["shoot"]["y"].opt<bool>("y", true, "desc...");
    map["shoot"]["z"].req<bool>("z", "desc...");
    map["shoot"][1].req<int>("pos1","desc...");
    map["shoot"][2].req<yaclip::file>("pos2","desc...");

    map["host"].req<string>("h", "target host");
    map["port"].opt<int>("h", 80, "target host");

    const char * argv[] = {"program", "--host=80"};
    //parse(map, argv);

//    map["shoot"][yaclip::all].set<yaclip::_strings>(yaclip::required, "desc...");
//    map["shoot"]["val1"].set<int, yaclip::range(1,100)>("f", yaclip::required, "desc...");
//    map["shoot"]["val2"].set<int, yaclip::range(1,100)>("f", yaclip::required, "desc...");
//    map["shoot"]["func"].set<int, func>("f", yaclip::required, "desc...");
//
//    map["atlas"]["k"].set<bool>("k", yaclip::Option, "desc...");
//
//
//    map["operation"].set<std::string, yaclip::oneof_map({"shoot", "atlas"})>("op", yaclip::required, "desc...");
//    map["level"].set<int, yaclip::oneof({1,3,5})>("", yaclip::required, "desc...");
//
//    yaclip::exclude(map["shoot"]["x"], map["shoot"]["y"]);
//    yaclip::exclude(map["shoot"]["x"], map["shoot"]["y"]);
//    yaclip::include(map["x"],map["y"]);
//    map["string:host:h:host name:required"];
//    map["int:port:p:network port:optional:range()"];
//
//    yaclip::parse(map);
//    yaclip::parse(map, yaclip::using_posix);
//    yaclip::parse(map, yaclip::using_x).with(argc,argv);
//
//    map["host"]["submodule"] = {};
//    map["host"] << yaclip::desc << "Here I put my long..long description";
//    map["host"] << yaclip::check <<
//    map["host"] >> yaclip::call >> yac::run([&](){ std::cout << "Host is " << map["host"]; });

/*
 *
 * --op=shoot -x -y
 *
 *
 *  --operation=shoot -x -y f.txt g.jpg A1.xml B1.vtk A2.xml B2.vtk
 *  --
 *
 * */


    //il piu semplice:

//    for (auto arg : yaclip::parse(argc,argv)) {
//        std::cout << arg << " at pos " << arg.position();
//    }
//
//    yaclip::map input;
//    input = yaclip::parse(argc,argv);
//
//    for (int i = 0; i < input.size(); ++i) {
//        std::cout << input[i].as<string>() << " at pos " << i;
//    }
//
//

    std::cout << map["host"];

    return 0;
}

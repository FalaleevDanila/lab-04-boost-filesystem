//
// Created by danila on 16.10.2019.
//

#include <boost/filesystem.hpp>
#include <iostream>
#include "../include/broker.h"

using namespace boost;

int main(int argc, char *argv[]){
    boost::filesystem::path path = ".";
    if (argc > 1) {
        path = argv[1];
    }

    //std::getline(std::cin, *argv);

    DirectoryAnalyzer test(path);

    return 0;
}
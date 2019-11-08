//
// Created by danila on 16.10.2019.
//

#ifndef TEMPLATE_BROKER_H
#define TEMPLATE_BROKER_H


#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "../include/header.hpp"
#include <iterator>

class DirectoryAnalyzer
{
public:
    DirectoryAnalyzer(boost::filesystem::path _path);

    void spacePower(size_t tab);

    void is_laster(std::vector <int> _new_date, boost::filesystem::path _new_p, FileInfo &data);

    bool correctDate(std::vector <int> _date);

    void _DirectoryAnalyzer(boost::filesystem::path p, size_t tab, std::string const &pth);


    static std::vector <int> checkNameFile(std::string name);


private:
    std::vector <FileInfo> _value;

};
#endif //TEMPLATE_BROKER_H

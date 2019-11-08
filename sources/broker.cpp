
//
// Created by danila on 16.10.2019.
//

#include "../include/broker.h"

DirectoryAnalyzer::DirectoryAnalyzer(boost::filesystem::path _path) {
    if (_path == " ") {
        _path = "/home/danila/CLionProjects/lab-04-boost-filesystem/";
    }
    std::string pth = _path.stem().string();
    _DirectoryAnalyzer(_path, 0, pth);

    for (std::vector<FileInfo>::iterator i = _value.begin(); i != _value.end(); ++i) {
//broker:ib account:00001234 files:10 lastdate:20181017
        std::cout << " broker: " << i->_new.branch_path().string()<< "        account:  " << i->date[0] <<
        "             files:  " << i->counter << "         last date:  " <<
                  i->date[1] <<".";
        if(i->date[2]<10)
            std::cout<<"0";

        std::cout <<i->date[2] <<".";
        if(i->date[3]<10)
            std::cout<<"0";
        std::cout << i->date[3] << std::endl;
    }


}

void DirectoryAnalyzer::spacePower(size_t tab){
    for(size_t i=0; i<tab; ++i){}
    std::cout << "     ";
}

void DirectoryAnalyzer::is_laster(std::vector <int> _new_date, boost::filesystem::path _new_p, FileInfo &data){

    if(_new_date[1]> data.date[1]){
        data.date[0] = _new_date[0];
        data.date[1] = _new_date[1];
        data.date[2] = _new_date[2];
        data.date[3] = _new_date[3];
        data._new = _new_p;
        data._new = _new_p;
    }
    else if(_new_date[1]==data.date[1] ||_new_date[2]>data.date[2] ){
        data.date[0] = _new_date[0];
        data.date[1] = _new_date[1];
        data.date[2] = _new_date[2];
        data.date[3] = _new_date[3];

        data._new = _new_p;
        data._new = _new_p;
    }
    else if( _new_date[1]==data.date[1] || _new_date[2]==data.date[2] || _new_date[3] > data.date[3] ){
        data.date[0] = _new_date[0];
        data.date[1] = _new_date[1];
        data.date[2] = _new_date[2];
        data.date[3] = _new_date[3];

        data._new = _new_p;
        data._new = _new_p;
    }

}

bool DirectoryAnalyzer::correctDate(std::vector <int> _date){
    if(_date.size()!=4){
        return false;
    }
    if(_date[0]==-1 || _date[1]==-1 || _date[2]==-1 || _date[3]==-1){
        return false;
    }
    return true;
}

void DirectoryAnalyzer::_DirectoryAnalyzer(boost::filesystem::path p, size_t tab, std::string const &pth){

    FileInfo value;
    value.date.push_back(-1);
    value.date.push_back(-1);
    value.date.push_back(-1);
    value.date.push_back(-1);
    value.counter=0;

    try {

        //const boost::filesystem::path p{path_to_file};
        for (const boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator{p}) {
            if (boost::filesystem::is_regular_file(x)) {
                std::vector <int> _create_data = DirectoryAnalyzer::checkNameFile(x.path().stem().string());

                if(correctDate(_create_data)) {

                    DirectoryAnalyzer::spacePower(tab);
                    std::cout << pth << "  " << x.path().stem().string() <<".txt" << std::endl;
                    is_laster(DirectoryAnalyzer::checkNameFile(x.path().stem().string()), x,value);
                    value.counter++;
                }
            } else if (boost::filesystem::is_directory(x)) {

                _DirectoryAnalyzer(x.path(), ++tab, x.path().string());
            } else if (boost::filesystem::is_symlink(x)) {
                boost::filesystem::path symlink = read_symlink(x);
                if (symlink != nullptr) {
                    _DirectoryAnalyzer(symlink, ++tab, x.path().string());
                }
            } else {
                std::cout << "Error";
                break;
            }

        }
        if(value.counter!=0){
            _value.push_back(value);
        }

        std::cout<<std::endl<<std::endl<<std::endl;
    }
    catch(const boost::filesystem::filesystem_error& e){
        throw e;
    }

}


std::vector <int> DirectoryAnalyzer::checkNameFile(std::string name){



    std::vector <int> value;
    if(name.size()!=25){
        value.push_back(-1);
        return value;
    }
    if(name.find(".old") != std::string::npos){
        value.push_back(-1);
        return value;
    }

    if(!(name.find("balance_") != std::string::npos)){
        value.push_back(-1);
        return value;
    }


    std::string accountNumber_;
    for(auto i = name.begin()+8; i != name.end(); ++i){
        if(*i >'9' || *i <'0'){
            break;
        }
        accountNumber_+= *i;
    }
    if(accountNumber_.size()!=8){
        value.push_back(-1);
        return value;
    }

    value.push_back(boost::lexical_cast<int>(accountNumber_));

    std::string _date_year;
    for(auto i = name.begin()+17; i != name.begin()+21; ++i) {
        if(*i >'9' || *i <'0'){
            break;
        }
        _date_year+= *i;
    }

    if(_date_year.size()!=4){
        value.push_back(-1);
        return value;
    }
    value.push_back(boost::lexical_cast<int>(_date_year));

    std::string _date_month;
    for(auto i = name.begin()+21; i != name.begin()+23; ++i) {
        if(*i >'9' || *i <'0'){
            break;
        }
        _date_month+= *i;
    }

    if(_date_month.size()!=2){
        value.push_back(-1);
        return value;
    }
    value.push_back(boost::lexical_cast<int>(_date_month));


    std::string _date_day;
    for(auto i = name.begin()+23; i != name.end(); ++i) {
        if(*i >'9' || *i <'0'){
            break;
        }
        _date_day+= *i;
    }

    if(_date_day.size()!=2){
        value.push_back(-1);
        return value;
    }
    value.push_back(boost::lexical_cast<int>(_date_day));

    return value;
}
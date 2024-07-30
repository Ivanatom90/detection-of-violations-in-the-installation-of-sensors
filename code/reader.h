#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>

#include "domain.h"
#include "map"


namespace reader{

class RSA{
    public:
        RSA(std::string name_main_file, std::string name_names_file);

        void SetNames();
        std::vector<Parameter>& GetParameters();

    private:
        std::vector<Parameter> parameters_;
        std::map<std::string, std::string> names_;
        std::vector<double> NumReader(std::string_view sv);
        std::vector<std::string> KKSreader(std::string_view sv);

        void CreateParameters(std::string& k, std::vector<double>& num);
        void SetParametrs(std::string name_main_file);
        void ParseKKSnames(std::string name_names_file);
        std::pair<std::string, std::string> GetPair(std::string_view sv);
};



}

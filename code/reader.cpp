#include "reader.h"

namespace reader{

    RSA::RSA(std::string name_main_file, std::string name_names_file) {
        parameters_.reserve(200);
        ParseKKSnames(name_names_file);
        SetParametrs(name_main_file);
    }

    void RSA::SetParametrs(std::string name_main_file){
        using Numbers = std::vector<double>;
        std::vector<std::string> KKS;
        std::vector<Numbers> param;
        std::ifstream file(name_main_file);
        std::string str;
                for(int i = 0; i<5; i++){
                    std::getline(file, str);
                }
                KKS = KKSreader(str);
                param.resize(KKS.size());
                while(std::getline(file, str)){
                    Numbers num =  NumReader(str);
                        for(size_t i = 0; i < KKS.size(); i++){
                            param[i].push_back(num[i]);
                        }
                }

                for(size_t i = 0; i < KKS.size(); i++){
                    CreateParameters(KKS[i], param[i]);
                }



    }

    void RSA::SetNames(){

    }

    std::vector<double> RSA::NumReader(std::string_view sv){
        int pos = 1;
        std::vector<double> numbers;
        numbers.reserve(200);
        std::string_view svv;
        while(pos != -1){
            pos = sv.find('|');
            sv.remove_prefix(pos+1);
            pos = sv.find(' ');
                if(pos == -1){
                    break;
                }
            svv = sv;
            svv.remove_suffix(svv.size() - pos);
            std::string s = std::string(svv);
            double num = std::stod(s);
            numbers.push_back(num);
        }

        return numbers;
    }

    std::vector<std::string> RSA::KKSreader(std::string_view sv){
        std::vector<std::string> KKSvec;
        std::string_view svn;
        int pos = 0;
        while (pos != -1) {
            pos = sv.find('|');
            sv.remove_prefix(pos+1);
            svn = sv;
            pos = svn.find('|');
            if(pos == -1){
                break;
            }
            svn.remove_suffix(svn.size() - pos);
            std::string s = std::string(svn);
            KKSvec.push_back(s);
        }

        return KKSvec;
    }

    void RSA::CreateParameters(std::string& k, std::vector<double>& num){
        Parameter par;
        par.KKS = k;
        par.name = names_.at(k);
        par.numbers = std::move(num);
        parameters_.push_back(std::move(par));
    }



    void RSA::ParseKKSnames(std::string name_names_file){

        std::ifstream file(name_names_file);
        std::string str;
        for(int i = 0; i<5; i++){
            std::getline(file, str);
        }

         while(std::getline(file, str)){
            names_.insert(GetPair(str));
         }
    }

    std::pair<std::string, std::string> RSA::GetPair(std::string_view sv){

            std::pair<std::string, std::string> result;
            int pos = sv.find(' ');
            std::string_view svn = sv;
            svn.remove_suffix(svn.size() - pos);
            std::string s = std::string(svn);
            result.first = s;
            pos = sv.find('|');
            sv.remove_prefix(pos+1);
            pos = sv.find('|');
            sv.remove_suffix(sv.size() - pos);
            s = std::string(sv);
            result.second = s;

            std::cout<<result.first<<"     "<<result.second<<std::endl;

     return result;

    }


    std::vector<Parameter>& RSA::GetParameters(){
        return parameters_;
    }

}

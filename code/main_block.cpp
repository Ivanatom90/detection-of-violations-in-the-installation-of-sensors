#include "main_block.h"

Searcher::Searcher(std::vector<Parameter>& suz, std::vector<Parameter>& dpz){
    suz_= std::make_unique<std::vector<Parameter>>(suz);
    dpz_ = std::make_unique<std::vector<Parameter>>(dpz);
    CreateElectro();
}


void Searcher::CreateElectro(){

    std::for_each(suz_->begin(), suz_->end(), [&](const Parameter& par){

        auto min_it = std::min_element(par.numbers.begin(), par.numbers.end());
        int point = min_it - par.numbers.begin();
        Suz suz{par.KKS, par.name, GetMindI(point)};
        suz_down_.push_back(suz);
    });


}


std::vector<Dpz> Searcher::GetMindI(int time){
    std::vector<Dpz> result;
        std::for_each(dpz_->begin(), dpz_->end(), [&time, &result](const Parameter& par){
            double dI = par.numbers[time-20] - par.numbers[time];
            Dpz dpz{par.KKS, par.name, dI};
            result.push_back(dpz);
        });

        std::sort(result.begin(), result.end(), [](const Dpz& dpz1, const Dpz& dpz2){
            return dpz1.dI > dpz2.dI;
        });
    return result;
}

void Searcher::PrintAllSuz() const{
    std::ofstream out("out.txt");
    for(const Suz& sz:suz_down_){
        out<<sz.KKS<<"     "<<sz.name<<std::endl;
            if(sz.dpz.at(0).dI < 0.001){continue;}
            int counter = 0;

            for(const Dpz& dp:sz.dpz){
                out<<"        "<<dp.KKS<<"      "<<dp.name<<"    "<<dp.dI<<std::endl;
                counter++;
                if(counter>7){break;}
            }
    }
}

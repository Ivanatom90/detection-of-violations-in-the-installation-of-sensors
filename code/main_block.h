#pragma once

#include <memory>
#include "reader.h"


struct Dpz{
  std::string KKS;
  std::string name;
  double dI;
};

struct Suz{
    std::string KKS;
    std::string name;
    std::vector<Dpz> dpz;
};

class Searcher{
  public:
    Searcher(std::vector<Parameter>& suz, std::vector<Parameter>& dpz);

    void CreateElectro();
    void PrintAllSuz() const;

    private:
        std::unique_ptr<std::vector<Parameter>> suz_;
        std::unique_ptr<std::vector<Parameter>> dpz_;
        std::vector<Suz> suz_down_;

        std::vector<Dpz> GetMindI(int time);
};

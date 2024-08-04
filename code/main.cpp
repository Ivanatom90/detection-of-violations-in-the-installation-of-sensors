#include <iostream>
#include "reader.h"
#include "main_block.h"

using namespace std;

int main()
{
    reader::RSA Suz("OR_suz.txt", "OR_suz_names.txt");
    reader::RSA DPZ("7sloy_dpz.txt","7sloy_dpz_names.txt");
    Searcher Ser(Suz.GetParameters(), DPZ.GetParameters());
    Ser.PrintAllSuz();
    return 0;
}

//
// Created by alex_ on 28.12.2018.
//

#include "ListOfWarriors.h"
using namespace std;

ListOfWarriors* ListOfWarriors::mainList;

string ListOfWarriors::slitF(string line) {
    while (line.size() != 3)
        line.pop_back();
    std::cout<<"    "<<"function name : "<< line<<std::endl;
    return line;
}

string ListOfWarriors::slitA(string line) {
    while (*(line.end()-1) == 32 )
        line.pop_back();
    for(int i = 0; i < 4 && !line.empty(); i++ ){
        line.erase(line.begin());
    }
    while (*line.begin() == 32 )
        line.erase(line.begin());
    std::cout<<"        "<<"arguments : "<< line<<std::endl;
    return line;
}

void ListOfWarriors::eraisefromlist(int num) {
    for(int i = num; i < CountOfWarrirs - 1 ; i++){
        IPListofWarriors[i] = IPListofWarriors[i+1];
    }
    IPListofWarriors.pop_back();
}
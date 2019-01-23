#include <utility>

///Watch to
//
// Created by alex_ on 01.12.2018.
//

#include "Field.h"

#include "ListOfWarriors.h"

using namespace std;
///FIELD

Field *Field::FLd;

int Field::addWarrior(Warrior &warrior){

    vector<HgInstruction> source = warrior.InstCode;
    cursor = findfree((int)source.size());

    int to_ret = cursor;

    for(auto it : source){
        if (it.type().empty()){
            FLD[cursor].addNumber(0);
            FLD[cursor].last_visit = ListOfWarriors::getInstance()->giveIP_current();
            cursor++;
            cursor%=size;
        }else{
            FLD[cursor].addInstruction(it);
            FLD[cursor].last_visit = ListOfWarriors::getInstance()->giveIP_current();
            cursor++;
            cursor%=size;
        }
    }
    cout<<"complete : [FIELD:: NEW WARRIOR ADDED] : at "<<to_ret<<endl;

    countofWarriors ++;
    return to_ret;
}

int Field::findfree(int sizep) {     //TODO: Needs another
    cursor = rand()%size;
    //while(size - cursor < sizep)
    //cursor = rand()%size;
    return cursor;
}

///FIELDPOINT

void FieldPoint::addInstruction(HgInstruction source) {
    tp = "instruction";
    instruction = std::move(source);
}
void FieldPoint::addNumber(int num) {
    tp = "number";
    number = num;
}

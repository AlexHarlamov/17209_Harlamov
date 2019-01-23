//
// Created by alex_ on 13.12.2018.
//

#ifndef LAB2_INSTRPOINTER_H
#define LAB2_INSTRPOINTER_H

#pragma once

#include "Field.h"

class InstrPointer {
private:
    int number;
    int position;
    HgInstruction* point;

public:
    InstrPointer(int pos,int num){
        position = pos;
        number = num;
        std::cout<<"complete : [IP_CONSTRUCTOR:: INSTRUCTIONPOINT("<<num<<") CREATED] : at "<<pos<<std::endl;
    }
    int Number(){ return number;}
    int Position(){ return position;}

    bool changePos(int newpos){ position = newpos; return true;}

    bool run(){
        if(Field::getGlobal()->type_at(position) != "instruction")
            return false;
        if(Field::getGlobal()->Command_at(position).run()){
            position++;
            position %= Field::getGlobal()->give_size();
            return true;
        }
        return false;
    }
};


#endif //LAB2_INSTRPOINTER_H

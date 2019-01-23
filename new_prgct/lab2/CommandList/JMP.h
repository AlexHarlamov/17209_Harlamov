//
// Created by progr on 18.01.2019.
//

#ifndef LAB2_JMP_H
#define LAB2_JMP_H
#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"

class  JMP : public Command{
public:
    JMP(){
        name = "JMP";
        number_of_args = 1;
    }
    bool Process(Arguments arguments) override{
        pmi jmp(name);
        if(!jmp.find_source(arguments.giveOne_A()))
            return false;
        if(!jmp.change_position())
            return false;
        return true;
    }
};

bool b3 = CmFactory::getGlobalInstance()->CmRegister("JMP",registerCl<JMP>);
#endif //LAB2_JMP_H

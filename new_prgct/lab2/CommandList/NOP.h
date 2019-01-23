//
// Created by progr on 20.01.2019.
//

#ifndef LAB2_NOP_H
#define LAB2_NOP_H


#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class NOP : public Command{
public:
    NOP(){
        //std::cout<<"(MOV constructed)"<<std::endl;
        name = "NOP";
        number_of_args = 0;
    };
    bool Process(Arguments arguments) override {
        return true;}
    std::string giveName() override { return name;}
};

bool b4 = CmFactory::getGlobalInstance()->CmRegister("NOP", registerCl<NOP>);


#endif //LAB2_NOP_H

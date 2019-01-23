//
// Created by progr on 20.01.2019.
//

#ifndef LAB2_SLT_H
#define LAB2_SLT_H

#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class SLT : public Command{
public:
    SLT(){
        //std::cout<<"(MOV constructed)"<<std::endl;
        name = "SLT";
        number_of_args = 2;
    };
    bool Process(Arguments arguments) override {
        pmi slt(name);
        if(!slt.find_source(arguments.giveA()))
            return false;
        if(!slt.find_purpose(arguments.giveB()))
            return false;
        if(!slt.get_op1_A())
            return false;
        if(!slt.get_op2_B())
            return false;
        if(slt.a_more_than_b() == 2)
            if(!slt.skip_next())
                return false;
        return true;
    }
    std::string giveName() override { return name;}
};

bool f_slt = CmFactory::getGlobalInstance()->CmRegister("SLT", registerCl<SLT>);

#endif //LAB2_SLT_H

//
// Created by progr on 20.01.2019.
//

#ifndef LAB2_SNE_H
#define LAB2_SNE_H

#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class SNE : public Command{
public:
    SNE(){
        //std::cout<<"(MOV constructed)"<<std::endl;
        name = "SNE";
        number_of_args = 2;
    };
    bool Process(Arguments arguments) override {
        pmi sne(name);
        if(!sne.find_source(arguments.giveA()))
            return false;
        if(!sne.find_purpose(arguments.giveB()))
            return false;
        if(!sne.get_op1_A())
            return false;
        if(!sne.get_op2_B())
            return false;
        if(sne.a_more_than_b() != 0)
            if(!sne.skip_next())
                return false;
        return true;
    }
    std::string giveName() override { return name;}
};

bool f_sne = CmFactory::getGlobalInstance()->CmRegister("SNE", registerCl<SNE>);

#endif //LAB2_SNE_H

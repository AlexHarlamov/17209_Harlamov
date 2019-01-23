//
// Created by progr on 20.01.2019.
//

#ifndef LAB2_SEQ_H
#define LAB2_SEQ_H

#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class SEQ : public Command{
public:
    SEQ(){
        //std::cout<<"(MOV constructed)"<<std::endl;
        name = "SEQ";
        number_of_args = 2;
    };
    bool Process(Arguments arguments) override {
        pmi seq(name);
        if(!seq.find_source(arguments.giveA()))
            return false;
        if(!seq.find_purpose(arguments.giveB()))
            return false;
        if(!seq.get_op1_A())
            return false;
        if(!seq.get_op2_B())
            return false;
        if(seq.a_more_than_b() == 0)
            if(!seq.skip_next())
                return false;
        return true;
    }
    std::string giveName() override { return name;}
};

bool f_seq = CmFactory::getGlobalInstance()->CmRegister("SEQ", registerCl<SEQ>);


#endif //LAB2_SEQ_H

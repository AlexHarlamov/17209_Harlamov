///Watch to 23
//
// Created by alex_ on 12.12.2018.
//

#ifndef LAB2_MOV_H
#define LAB2_MOV_H

#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class MOV : public Command{
public:
    MOV(){
        //std::cout<<"(MOV constructed)"<<std::endl;
        name = "MOV";
        number_of_args = 2;
    };
    bool Process(Arguments arguments) override {
        pmi mov(name);
        if(!mov.find_source(arguments.giveA()))
            return false;
        if (!mov.get())
            return false;
        if (!mov.find_purpose(arguments.giveB()))
            return false;
        if (!mov.put())
            return false;
        return true;}
    std::string giveName() override { return name;}
};

bool b = CmFactory::getGlobalInstance()->CmRegister("MOV", registerCl<MOV>);


#endif //LAB2_MOV_H




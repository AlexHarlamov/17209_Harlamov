//
// Created by alex_ on 17.01.2019.
//

#ifndef LAB2_SPL_H
#define LAB2_SPL_H
#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class SPL : public Command{
public:
    SPL(){
        name = "SPL";
        number_of_args = 1;
    };
    bool Process(Arguments arguments) override {
        pmi spl(name);
        if(!spl.find_source(arguments.giveOne_A()))
            return false;
        return spl.start_new_stream();}
    std::string giveName() override { return name;}
};

bool b1 = CmFactory::getGlobalInstance()->CmRegister("SPL", registerCl<SPL>);
#endif //LAB2_SPL_H

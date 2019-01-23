//
// Created by alex_ on 17.01.2019.
//

#ifndef LAB2_DAT_H
#define LAB2_DAT_H
#pragma once

#include <iostream>

#include "Command.h"
#include "../CmFactory.h"

#include "PrimitiveInstructions.h"


class DAT : public Command{
public:
    DAT(){
        name = "DAT";
        number_of_args = 0;
    };
    bool Process(Arguments arguments) override {
        pmi dat(name);
        return dat.stop_stream();}
    std::string giveName() override { return name;}
};

bool b2 = CmFactory::getGlobalInstance()->CmRegister("DAT", registerCl<DAT>);
#endif //LAB2_DAT_H

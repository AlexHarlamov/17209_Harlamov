//
// Created by alex_ on 01.12.2018.
//

#ifndef LAB2_COMMAND_H
#define LAB2_COMMAND_H

#pragma once

#include <string>
#include <iostream>
#include <map>

#include "../Arguments.h"

typedef void(*RetF)();




class Command {

public:
    std::string name;
    int number_of_args;
    Command(){};
    virtual bool Process( Arguments arguments){std::cout<<"something happened ..."<<std::endl;
        return true;}
    virtual std::string giveName(){ return name;}

};

template <class T>
Command* registerCl(){return new T();}
#endif //LAB2_COMMAND_H

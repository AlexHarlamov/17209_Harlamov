#include <utility>

#include <utility>

//
// Created by alex_ on 28.12.2018.
//

#ifndef LAB2_HGINSTRUCTION_H
#define LAB2_HGINSTRUCTION_H

#pragma once

#include "CmFactory.h"
#include "CommandList/Command.h"


class HgInstruction {
    Arguments argument;
    Command* command;

    string line_type;
public:
    bool addCommand(Command* inp){
        if (inp == nullptr)
            return false;
        command = inp;
        return true;
    }

    bool addArgument(std::string inp){
        argument.savearg(std::move(inp));
        return true;
    }

    bool run(){
        return command->Process(argument);
    }

    int numofArgs(){ return command->number_of_args;}
    std::string giveName() const { return command->giveName();}
    Arguments giveArgument(){ return argument;}

    HgInstruction(string empty_type){
        line_type.clear();
    }
    HgInstruction(){
        line_type = "not empty";
    }
    string type(){ return line_type;}

    HgInstruction& operator=(HgInstruction const& other){
        line_type = other.line_type;
        argument = other.argument;
        command = CmFactory::getGlobalInstance()->toCommand(other.giveName());
        return *this;
    }
    bool operator==(HgInstruction other){
        if(line_type != other.line_type)
            return false;
        if(line_type == "empty")
            return true;
        if(command->giveName() == other.command->giveName())
            if(argument.giveBody() == other.argument.giveBody())
                return true;
        return false;
    }
};


#endif //LAB2_HGINSTRUCTION_H

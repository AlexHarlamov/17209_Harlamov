//
// Created by alex_ on 28.12.2018.
//

#ifndef LAB2_ARGUMENTS_H
#define LAB2_ARGUMENTS_H

#include <string>
#include <iostream>

using namespace std;

class Arguments {
private:
    std::string arguments;

    string getA_a(){
        string argument = arguments;
        while(*(argument.end()-1) != 32 && !argument.empty())
            argument.pop_back();
        if (argument.empty()){
            return "no_B";
        }
        while(*(argument.end()-1) == 32)
            argument.pop_back();
        return argument;
    }

    string getB_a(){
        string argument = arguments;
        while(*argument.begin() != 32 && !argument.empty())
            argument.erase(argument.begin());
        if (argument.empty()){
            return "no_B";
        }
        while(*argument.begin() == 32)
            argument.erase(argument.begin());
        return argument;
    }

public:
    Arguments(){
        arguments.clear();
    }
    string giveA(){ return getA_a();}
    string giveB(){ return getB_a();}
    string giveOne_A(){ return arguments; }

    void savearg(std::string arg){
        arguments = arg;
    }
    std::string giveBody(){ return arguments;}

    Arguments&operator=(Arguments const &other){
        arguments = other.arguments;
        return *this;
    }
};


#endif //LAB2_ARGUMENTS_H

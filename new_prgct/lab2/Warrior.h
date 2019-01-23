
//
// Created by alex_ on 12.12.2018.
//

#ifndef LAB2_WARRIOR_H
#define LAB2_WARRIOR_H

#define MAX_FREE_LINES 15

#pragma once

#include <vector>

#include "HgInstruction.h"

class Warrior {
public:
    std::vector<HgInstruction> InstCode;
    Warrior(){
        InstCode.clear();
    }
    bool works(){
        std::cout<<"start : [WRR:: CHECK WARRIOR FOR WORKING]"<<std::endl;
        int number_of_args;
        int number_of_free_lines=0;
        string to_check;
        Arguments step2;
        for(int i = 0; i < InstCode.size(); i++){
            if (InstCode[i].type().empty()) {
                if (number_of_free_lines > MAX_FREE_LINES){
                    return false;
                }
                number_of_free_lines++;
                continue;
            }
            number_of_args = InstCode[i].numofArgs();
            for(auto it : InstCode[i].giveArgument().giveBody())
                if((it > 57 && it != 64) || (it < 48 && it != 42 && it != 32 && it != 45 && it != 35)){
                    std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong symbol found"<<std::endl;
                    return false;
                }
            switch (number_of_args){
                case 0:
                    if(!InstCode[i].giveArgument().giveOne_A().empty()){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : more than 0 arguments"<<std::endl;
                        return false;
                    }
                    break;
                case 1:
                    if(InstCode[i].giveArgument().giveOne_A().empty()){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : less than 1 argument"<<std::endl;
                        return false;
                    }
                    if(InstCode[i].giveArgument().giveA() != "no_B"){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : more than 1 argument"<<std::endl;
                        return false;
                    }
                    to_check = InstCode[i].giveArgument().giveOne_A();
                    for(int j = 0; j < to_check.size() ; j++) {
                        if (j > 0 && (to_check[j] == 64 || to_check[j] == 32 || to_check[j] == 42 || to_check[j] == 35)) {
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                        if (j > 1 && to_check[j] == 45){
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                    }
                    break;
                case 2:
                    if(InstCode[i].giveArgument().giveOne_A().empty()){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : less than 2 arguments"<<std::endl;
                        return false;
                    }
                    if(InstCode[i].giveArgument().giveA() == "no_B"){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : less than 2 arguments"<<std::endl;
                        return false;
                    }
                    step2.savearg(InstCode[i].giveArgument().giveA());
                    if(step2.giveA() != "no_B"){
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : less than 2 arguments"<<std::endl;
                        return false;
                    }
                    to_check = InstCode[i].giveArgument().giveA();
                    for(int j = 0; j < to_check.size() ; j++) {
                        if (j > 0 && (to_check[j] == 64 || to_check[j] == 32 || to_check[j] == 42 || to_check[j] == 35)) {
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                        if (j > 1 && to_check[j] == 45){
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                    }
                    to_check = InstCode[i].giveArgument().giveB();
                    for(int j = 0; j < to_check.size() ; j++) {
                        if (j > 0 && (to_check[j] == 64 || to_check[j] == 32 || to_check[j] == 42 || to_check[j] == 35)) {
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                        if (j > 1 && to_check[j] == 45){
                            std::cout << "error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong argument found"
                                      << std::endl;
                            return false;
                        }
                    }
                    break;
            }
        }
        std::cout<<"complete : [WRR:: WARRIROR CODE IS NORMAL]"<<std::endl;
        return true;
    }
};


#endif //LAB2_WARRIOR_H


////
// Created by alex_ on 01.12.2018.
//

#ifndef LAB2_FIELD_H
#define LAB2_FIELD_H

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "CommandList/Command.h"
#include "Warrior.h"
//#include "ListOfWarriors.h"

class FieldPoint{
private:
    HgInstruction instruction;
    int number;
    std::string tp;        ///aviable : "instruction","number"

public:
    int last_visit=-1;
    FieldPoint(){
        tp = "number";
        number = (int)rand()%5;
    }
    void addInstruction(HgInstruction source);
    void addNumber(int num);
    void print(){
        if(tp == "number")
            std::cout<<number<<std::endl;
        if(tp == "instruction")
            std::cout<<instruction.giveName()<<" "<<instruction.giveArgument().giveBody()<<std::endl;
    }
    std::string type(){ return tp; }
    HgInstruction giveBody(){ return instruction;}

    int giveNumber(){ return number;}

    FieldPoint&operator=(FieldPoint const&other){
        tp = other.tp;
       if (tp == "number"){
           number = other.number;
           return *this;
       }
       if (tp == "instruction"){
           instruction = other.instruction;
           return *this;
       }
       throw "error : [FIELD::FIELDPOINT] : undef point assignment";
    }
};

class Field {
private:
    static Field *FLd;
    ///data
    std::vector<FieldPoint> FLD;

    ///info
    int countofWarriors ;
    int size;

    ///control
    int cursor ;

    int findfree(int size);

public:
    int addWarrior(Warrior &warrior);

    void RestoreField(int sz){
        FLD.clear();
        size = sz;
        FLD.resize(size);
        cursor = 0;
        countofWarriors = 0;

    }
    void RestoreField(){
        FLD.clear();
        size=500;
        FLD.resize(size);
        cursor = 0;
        countofWarriors = 0;
    }

    Field(){ RestoreField(); }
    Field(int sz){ RestoreField(sz); }

    Field&operator=(Field&) = delete;
    Field(Field&)= delete;

    static Field* getGlobal(){
        if(FLd == nullptr)
            FLd = new Field(250);
        return FLd;
    }

    int last_visit_at(int pos){
        return FLD[pos].last_visit;
    }

    void printField(){
        std::cout<<"[FIELD] : field points :"<<std::endl;
        for(int i=0;i<size;i++){

                std::cout<<"("<<i<<"): "<<FLD[i].type()<<std::endl;
                std::cout<<" ";
                FLD[i].print();
        }
    }

    int give_last_visit(int position){
        return FLD[position].last_visit;
    }

    ///FOR InstructonPointers && PrimitiveInstructions
    std::string type_at(int position){return FLD[position].type();}
    HgInstruction Command_at(int position){ return FLD[position].giveBody();}
    int Number_at(int position){ return FLD[position].giveNumber();}

    int give_size(){return size;}

    friend class PrimitiveInstructions;
};


#endif //LAB2_FIELD_H

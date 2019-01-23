//
// Created by alex_ on 28.12.2018.
//

#include "PrimitiveInstructions.h"

#include <math.h>

bool pmi::find_source(string argument){
    int tmp_adrress;
    switch (argument[0]){
        case 35:    //#
            source = "number";
            argument.erase(argument.begin());
            source_int =  stoi(argument);
            return true;

        case 42:    //* A
            argument.erase(argument.begin());
            tmp_adrress = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            if(Field::getGlobal()->FLD[tmp_adrress].type() == "instruction" && Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() > 0)
                if(Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() == 1)
                    return find_source(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveOne_A());
                else
                    return find_source(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveA());
            else {
                source = "undef";
                return false;
            }

        case 64:    //@ B
            argument.erase(argument.begin());
            tmp_adrress = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            if(Field::getGlobal()->FLD[tmp_adrress].type() == "instruction" && Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() == 2 )
                return find_source(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveB());
            else {
                source = "undef";
                return false;
            }

        default:
            source = "adress";
            source_int = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            return true;
    }
    source = "undef";
    return  false;
}

bool pmi::find_purpose(string argument){
    int tmp_adrress;
    switch (argument[0]){
        case 35:    //#
            purpose = "number";
            argument.erase(argument.begin());
            purpose_int =  ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;;
            return true;
        case 42:    //* A
            argument.erase(argument.begin());
            tmp_adrress = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            if(Field::getGlobal()->FLD[tmp_adrress].type() == "instruction" && Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() > 0)
                if(Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() == 1)
                    return find_purpose(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveOne_A());
                else
                    return find_purpose(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveA());
            else {
                purpose = "undef";
                return false;
            }

        case 64:    //@ B
            argument.erase(argument.begin());
            tmp_adrress = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            if(Field::getGlobal()->FLD[tmp_adrress].type() == "instruction" && Field::getGlobal()->FLD[tmp_adrress].giveBody().numofArgs() == 2 )
                return find_purpose(Field::getGlobal()->FLD[tmp_adrress].giveBody().giveArgument().giveB());
            else {
                purpose = "undef";
                return false;
            }

        default:
            purpose = "adress";
            purpose_int = ((ListOfWarriors::getInstance()->giveIP_pos_current() + stoi(argument))+Field::getGlobal()->size)%Field::getGlobal()->size;
            return true;
    }
    purpose = "undef";
    return  false;
}



//string get(string arguments) { return arguments;}
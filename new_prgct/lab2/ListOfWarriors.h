//
// Created by alex_ on 28.12.2018.
//

#ifndef LAB2_LISTOFWARRIORS_H
#define LAB2_LISTOFWARRIORS_H

#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Warrior.h"
#include "Field.h"
#include "InstrPointer.h"

std::string decrease(std::string str,int pos);

class ListOfWarriors {
private:
    static ListOfWarriors* mainList;
    int CountOfWarrirs;
    std::vector<InstrPointer> IPListofWarriors;
    std::vector<InstrPointer> IPListofNEWWarriors;

    std::string slitF(std::string line);
    std::string slitA(std::string line);

    void eraisefromlist(int num);

    ///process
    int cur_IP;

public:
    ListOfWarriors(){
        CountOfWarrirs = 0;
    }
    ListOfWarriors(const ListOfWarriors&) = delete;
    ListOfWarriors& operator=(const ListOfWarriors& ) = delete;

    int Num_of_WRR(){return CountOfWarrirs;}

    static ListOfWarriors* getInstance(){
        if(mainList == nullptr){
            mainList = new ListOfWarriors;
            mainList->CountOfWarrirs = 0;
            mainList->IPListofWarriors.clear();
        }
        return  mainList;
    }
    bool addToList(Warrior* warrior) {
        cur_IP = CountOfWarrirs;
        InstrPointer *IP = new InstrPointer(/*position*/Field::getGlobal()->addWarrior(*warrior),/*number*/CountOfWarrirs);
        IPListofWarriors.push_back(*IP);
        delete IP;
        CountOfWarrirs++;
        return true;
    }
    bool deleteFromList(int number){
        int count = 0;
        for(auto & it: IPListofWarriors)
            if(it.Number()==IPListofWarriors[cur_IP].Number())
                count++;
        if(count == 1)
            CountOfWarrirs--;
        eraisefromlist(cur_IP);
        std::cout<<"complete : [LISTOFWARRIORS::DELETEFROMLIST] : ("<<number<<") dead :("<<std::endl;
        return true;
    }
    bool CreateWarrior(std::ifstream& source){
        std::cout<<"start : [NEW WARRIROR CREATING]"<<std::endl;

        Warrior* WRR = new Warrior;

        int i = 0;
        std::string toslit;
        toslit.clear();
        char *s = new char[10];
        while(getline(source,toslit)){

                HgInstruction* NW;

                if(toslit.empty()){
                    NW = new HgInstruction("empty");

                    std::cout<<"    ^free line^"<<std::endl;
                }
                else{
                    NW = new HgInstruction;

                    if(!NW->addCommand(CmFactory::getGlobalInstance()->toCommand(slitF(toslit)))){
                        delete NW;
                        delete WRR;
                        std::cout<<"error : [WRR:: WARRIOR CODE OUT OF CONDITION] : wrong function name"<<std::endl;
                        return false;
                    }

                    NW->addArgument(slitA(toslit));
                }


                WRR->InstCode.push_back(*NW);

                delete NW;

                i++;

            std::cout<<"    --------"<<std::endl;
        }
        if(WRR->works())
            return addToList(WRR);
        else{
            delete WRR;
            return false;
        }
    }

    int first_warrior(){
        return IPListofWarriors[0].Number();
    }
    void kill_all_warriors(){
        IPListofWarriors.clear();
        IPListofNEWWarriors.clear();
    }

    void printAll(){
        std::cout<<"all Pointers(warriors streams) :"<<" "<<IPListofWarriors.size()<<std::endl;
        for (int i = 0 ; i < CountOfWarrirs ; i++){
            std::cout<<IPListofWarriors[i].Number()<<" InstrPtr at "<<IPListofWarriors[i].Position()<<std::endl;
        }
    }
///process
    void runAll(){
        cur_IP = 0;
        for (int i = 0; i < IPListofWarriors.size() ; i++){
            if(!IPListofWarriors[i].run()){
                deleteFromList(IPListofWarriors[i].Number());
            }
            cur_IP++;
        }
        for(auto it : IPListofNEWWarriors)
            IPListofWarriors.push_back(it);
    }
    bool addIP_current(int position){
        InstrPointer *IP = new InstrPointer(position,/*number*/IPListofWarriors[cur_IP].Number());
        IPListofNEWWarriors.push_back(*IP);
        delete IP;
        return true;
    }
    bool delIP_current(){
        return deleteFromList( IPListofWarriors[cur_IP].Number());
    }
    bool moveIP_current(int newpos){
        return IPListofWarriors[cur_IP].changePos(newpos);
    }
    int giveIP_pos_current(){
        return IPListofWarriors[cur_IP].Position();
    }
    int giveIP_current(){
        return cur_IP;
    }
};


#endif //LAB2_LISTOFWARRIORS_H

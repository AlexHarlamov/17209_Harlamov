//
// Created by alex_ on 28.12.2018.
//

#ifndef LAB2_PRIMITIVEINSTRUCTIONS_H
#define LAB2_PRIMITIVEINSTRUCTIONS_H

#include <string>

#include "../Field.h"
#include "../ListOfWarriors.h"

using namespace std;

class Container{
    FieldPoint data;
public:
    string give_type(){ return data.type();}
    Container&operator=(FieldPoint const& source){
        data = source;
        return *this;
    }
    Container&operator=(int inp){
        data.addNumber(inp);
        return *this;
    }
    void operator>>(FieldPoint & other){
        other = data;
    }

    int operator>(Container & other){
        if(this->give_type() != other.give_type())
            return -1;
        if(data.type() == "command"){
            if(data.giveBody() == other.data.giveBody())
                return 0;
            return -1;
        }
        if(data.giveNumber() > other.data.giveNumber())
            return 1;
        if(data.giveNumber() == other.data.giveNumber())
            return 0;
        return 2;
    }
};

    typedef class PrimitiveInstructions {
        static PrimitiveInstructions *instance;

        string source;  ///aviable : "number","adress"(of point),"undef"
        string purpose; ///aviable : "adress"(of point),"undef"

        int source_int;
        int purpose_int;

        Container operand1; ///needs to be prepared
        Container operand2;

        string name;

    public:

        ///SEARCH
        bool find_source(string arguments);  ///needs pmi::init->A(argument);
        bool find_purpose(string arguments);

        ///STREAMS
        bool start_new_stream() {
            return ListOfWarriors::getInstance()->addIP_current(source_int);
        }

        bool stop_stream() {
            return ListOfWarriors::getInstance()->delIP_current();
        }

        bool change_position() {         ///jump to source
            if (source != "adress")
                return false;
            return ListOfWarriors::getInstance()->moveIP_current(source_int - 1);
        }
        bool skip_next(){
            int next_adress = (ListOfWarriors::getInstance()->giveIP_pos_current() + 1) % Field::getGlobal()->size;
            return ListOfWarriors::getInstance()->moveIP_current(next_adress);
        }

        ///OPERATORS

        bool get_op1_A(){
            if (source == "number"){
                operand1 = source_int;
                return true;
            }

            if (source != "adress")
                return false;
            try{
                operand1 = Field::getGlobal()->FLD[source_int];
            }
            catch (...){
                std::cout<<"error : [FIELD::FIELDPOINT] : undef point assignment"<<std::endl;
                return false;
            }
            return true;
        }
        bool get_op2_B(){
            if (purpose == "number"){
                operand2 = purpose_int;
                return true;
            }

            if (purpose != "adress")
                return false;
            try{
                operand2 = Field::getGlobal()->FLD[purpose_int];
            }
            catch (...){
                std::cout<<"error : [FIELD::FIELDPOINT] : undef point assignment"<<std::endl;
                return false;
            }
            return true;
        }
        /* return values of comparator:
         * -1 cant be compared
         * 0 ==
         * 1 >
         * 2 <
         * */
        int a_more_than_b(){
            return operand1 > operand2;
        }
        int compare_numbers(){
            if(operand1.give_type() != "number")
                return -1;
            if (operand1.give_type() != operand2.give_type())
                return -1;
            return operand1 > operand2;
        }

        ///DATA
        bool get() {                 ///get from source
        if (source == "number"){
            operand1 = source_int;
            return true;
        }

        if (source != "adress")
            return false;
        try{
            operand1 = Field::getGlobal()->FLD[source_int];
        }
        catch (...){
            std::cout<<"error : [FIELD::FIELDPOINT] : undef point assignment"<<std::endl;
            return false;
        }
            return true;
        }

        bool put() {                 ///put by purpose
            if (purpose != "adress")
                return false;
            try{
                operand1>>Field::getGlobal()->FLD[purpose_int];
                Field::getGlobal()->FLD[purpose_int].last_visit = ListOfWarriors::getInstance()->giveIP_current();
            }
            catch (...){
                std::cout<<"error : [FIELD::FIELDPOINT] : undef point assignment"<<std::endl;
                return false;
            }
            return true;
        }

        PrimitiveInstructions(string const & fname){
            source = "undef";
            purpose = "undef";
            name = fname;
        }
        PrimitiveInstructions (PrimitiveInstructions &) = delete;
        PrimitiveInstructions &operator=(PrimitiveInstructions &) = delete;
        ~PrimitiveInstructions() = default;

        void info(){
            std::cout<<"------"<<name<<"------"<<std::endl;
            if(source == "undef")
                std::cout<<"source : "<<source<<std::endl;
            else
                std::cout
                        <<"source : "<<source<<" || value : "<<source_int<<std::endl;

            if(purpose == "undef")
                std::cout<<"purpose : "<<purpose<<std::endl;
            else
                std::cout<<"purpose : "<<purpose<<" || value: "<<purpose_int<<std::endl;

                cout<<"operand2 type : "<<operand2.give_type()<<std::endl;
                cout<<"operand1 type : "<< operand1.give_type()<<std::endl;
            std::cout<<"---------------"<<std::endl;
        }

    } pmi;


#endif //LAB2_PRIMITIVEINSTRUCTIONS_H

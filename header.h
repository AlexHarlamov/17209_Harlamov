//
// Created by alex_ on 8.10.2018.
//

#ifndef INC_1_LAB_HEADER_H
#define INC_1_LAB_HEADER_H

#define START_NUM 10
#define LARGEST_NAME 30

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};
struct CHS {
    Value* main;
    struct CHS *next;
    bool init;
    Key word;
    CHS(){
        word.resize(LARGEST_NAME);
        next = nullptr;
        init = false;
        word = "undef";
        main = nullptr;
    }
};
/*(Description)
 *(Definition) The organization of methods of this class guarantees the absence of a null pointer in any cell of the table.
 * When accessing a specific table address, it is necessary to check whether the given cell of the table is defined.
 * This is done by checking the field "init" (true -defined, "false" - undefined).
 * If this field of the table cell is "false", then further processing of the cell data is not advisable.
 *
 *(Memory)The "clear" method frees the memory occupied by the hash-table and creates a 0-hash-table, because the "Table" field must be defined in this class.
 *
 *(Collision)To resolve collisions uses the chain method. A pointer to the next element of the list is the field "next_ifc" (next if collision).
 * For the correct definition of the required data, each element of the list contains the field "word" (std :: string word).
 * The methods of searching for the desired table element use this field to accurately determine the desired cell in the list.
 *
 *(Insert elements) If a collision occurs, this insertion element becomes at the end of the list.
 * Inserting a new element may result in using the "ExpandTable" method to increase the size of the table (if 50% of the table is occupied),
 * and all values ​​will be recalculated and the new table populated, which may lead to a slowdown of the "insert" method.*/
class HashTable{
private:
    int Size;
    int numEl;
    CHS *Chains;

public:
    /*tested*/HashTable();
    /*tested*/HashTable(const HashTable& b){

        Size = b.Size;
        numEl = b.numEl;

        Chains = new CHS [Size]; //method CopyTable needs initialization of field "Table"

        Value *b_main;
        CHS *bc_now;
        CHS *b_now;

        for(int i=0; i< Size;i++){//copying fields of Table elements
            if(!b.Chains[i].init){
                Chains[i].init = false;
                Chains[i].word = "undef";
                Chains[i].main = nullptr;
                Chains[i].next = nullptr;
            }
            else{
                bc_now = &Chains[i];
                b_now = &b.Chains[i];

                while(b_now != nullptr){
                    bc_now->init = true;
                    bc_now->word = b_now->word;

                    b_main = new Value;     //generate copy of main

                    b_main->age = b_now->main->age;
                    b_main->weight = b_now->main->age;

                    bc_now->main = b_main;      //add copy of main

                    if(b_now->next != nullptr) //add new Chain if needed
                        bc_now->next = new CHS;

                    b_now = b_now->next;
                    bc_now = bc_now->next;
                }
            }


        }
    }
    ~HashTable();

/*tested*/
    void CopyTable(HashTable b);        //copy hash-table
    void swap(HashTable& b);
    void clear();                       //clean container
    void ExpandTable();                 //increase the size of the table

    HashTable& operator=(const HashTable& b);
    Value& operator[](const Key& k);    //returns value by key. An unsafe method.
    Value& at(const Key& k);            //returns value by key
    const Value& at(const Key& k) const;//returns value by key
    bool contains(const Key& k) const;  //Checking the presence of a value for a given key

    bool erase(const Key& k);                    //removes the element for a given key
    bool insert(const Key& k, const Value& v);  //Insert into the container. The return value is the success of the insertion
    bool add_elem(const Key& k,const Value& v);
    static bool compareElements(Value* a, Value* b){
        if(a->weight != b->weight)return false;
        return a->age == b->age;
    }

    int hash(Key word) const;           //returns a hash-value for a given key
    size_t size() const{
        return (size_t)Size;
    }
    bool empty() const{
        return (numEl == 0);
    }
    int numof(){
        return numEl;
    }

    //friends
    friend bool operator==(const HashTable & a, const HashTable & b){
        if(a.numEl != b.numEl) return false;
        int n = (int)a.size();
        for(int i =0 ; i < n; i++){
            if(a.Chains[i].init)
                if(!b.contains(a.Chains[i].word))
                    return false;
        }
        return false;
    }
    friend bool operator!=(const HashTable & a, const HashTable & b){
        return !(a == b);
    }
};


#endif //INC_1_LAB_HEADER_H

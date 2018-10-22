//
// Created by alex_ on 8.10.2018.
//

#ifndef INC_1_LAB_HEADER_H
#define INC_1_LAB_HEADER_H

#define START_NUM 10
#define LARGEST_NAME 30

#include <iostream>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
    void CopyValue (const Value &v);
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
    void ToDeafault();
    void CopyByCHS(CHS *b);
    void CopyByInstr(const Value &v, const Key &k);
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

    bool add_elem(const Key& k,const Value& v);         //Insert into the container. Dont update numEl field
    int hash(Key word) const;                           //returns a hash-value for a given key
    bool ReloadData(int NewSize, HashTable &Source);    //replaces this table with transfused data from the source
    void ExpandTable();                                  //increase the size of the table

public:
    ///Constructors && Destructor

    /*tested*/HashTable();
    explicit HashTable(int size);                       //another size
    /*tested*/HashTable(const HashTable& b);
    ~HashTable();

    ///Data retrieval

    Value& at(const Key& k);                             //returns value by key
    const Value& at(const Key& k) const;                 //returns value by key
    Value& operator[](const Key& k);                     //returns value by key. An unsafe method.

    ///Data operators

    bool erase(const Key& k);                           //removes the element for a given key
    bool insert(const Key& k, const Value& v);          //Insert into the container. Update numEl field .The return value is the success of the insertion
    void CopyTable(HashTable b);                         //copy hash-table
    void swap(HashTable& b);
    static bool compareElements(Value* a, Value* b);
    void clear();                                        //clean container

   ///Comparator
    friend bool operator==(const HashTable &a, const HashTable &b){
       if(a.numEl != b.numEl) return false;
       int n = (int)a.size();
       for(int i =0 ; i < n; i++){
           if(a.Chains[i].init)
               if(!b.contains(a.Chains[i].word))
                   return false;
       }
       return false;
   }
    friend bool operator!=(const HashTable &a, const HashTable &b){
        return !(a == b);
    }

    HashTable& operator=(const HashTable& b);



    bool contains(const Key& k) const;                   //Checking the presence of a value for a given key

    size_t size() const{
        return (size_t)numEl;
    }
    bool empty() const{
        return (numEl == 0);
    }
    int tablesize(){
        return Size;
    }

    //friends

};


#endif //INC_1_LAB_HEADER_H

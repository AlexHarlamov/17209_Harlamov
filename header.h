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
    Value();
    Value(unsigned int ag, unsigned int we);
};

struct CHS {
    Value* main;
    struct CHS *next;
    bool init;
    Key word;
    CHS(){
        word.resize(LARGEST_NAME);
        ToDeafault();

    }
    void ToDeafault();
    void CopyByCHS(CHS *b);
    void CopyByInstr(const Value &v, const Key &k);
};

/*(Description)
 *
 * */
class HashTable{
private:
    int Size;
    int numEl;
    CHS *Chains;

    /*tested*/bool add_elem(const Key& k,const Value& v);         //Insert into the container. Dont update numEl field
    /*tested*/int hash(Key word) const;                           //returns a hash-value for a given key
    /*tested*/bool ReloadData(int NewSize,const HashTable &Source);    //replaces this table with transfused data from the source
    /*tested*/void ExpandTable();                                  //increase the size of the table

public:


    ///Constructors && Destructor

    /*tested*/HashTable();
    /*tested*/explicit HashTable(int size);                       //another size
    /*tested*/HashTable(const HashTable& b);
    /*tested*/~HashTable();

    ///Data retrieval

    /*tested*/Value& at(const Key& k);                             //returns value by key
    /*tested*/const Value& at(const Key& k) const;                 //returns value by key
    /*tested*/Value& operator[](const Key& k);                     //returns value by key. An unsafe method.

    ///Data operators

    /*tested*/bool erase(const Key& k);                           //removes the element for a given key
    /*tested*/bool insert(const Key& k, const Value& v);                    //Insert into the container. Update numEl field .The return value is the success of the insertion
    /*tested*/void copyTable(const HashTable& b);                 //copy hash-table
    /*tested*/void swap(HashTable& b);
    /*tested*/static bool compareElements(Value& a, Value& b);
    /*tested*/void clear();                                       //clean container
    /*tested*/HashTable& operator=(const HashTable& b);

   ///Comparators

    /*tested*/friend bool operator==(const HashTable &a, const HashTable &b){
       if(a.numEl != b.numEl) return false;

       for(int i =0 ; i < a.Size; i++){
           if(a.Chains[i].init)
               if(!b.contains(a.Chains[i].word))
                   return false;
       }
        for(int i =0 ; i < b.Size; i++){
            if(b.Chains[i].init)
                if(!a.contains(b.Chains[i].word))
                    return false;
        }
       return true;
   }
    /*tested*/friend bool operator!=(const HashTable &a, const HashTable &b){
        return !(a == b);
    }

    ///Data info
    /*tested*/size_t size() const{
        return (size_t)numEl;
    }
    /*tested*/bool empty() const{
        return (numEl == 0);
    }
    /*tested*/int tablesize(){
        return Size;
    }
    /*tested*/bool contains(const Key& k) const;                   //Checking the presence of a value for a given key

};


#endif //INC_1_LAB_HEADER_H

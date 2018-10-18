//
// Created by alex_ on 18.10.2018.
//
#include "header.h"
HashTable::HashTable() {
    Size = START_NUM;
    Chains = new CHS [Size];
    numEl = 0;
    for(int i=0; i< Size; i++){
        Chains[i].word = "undef";
        Chains[i].main = nullptr;
        Chains[i].next = nullptr;
        Chains[i].init = false;
    }
}

HashTable::~HashTable() {
    delete[] Chains;
}

Value& HashTable::operator[](const Key &k) {
    if(Chains[hash(k)].init) {
        if (Chains[hash(k)].word == k) {
            return *Chains[hash(k)].main;
        }
        else{
            CHS *tmp = &Chains[hash(k)];
            while (tmp->next != nullptr || tmp->word != k)
                tmp = tmp->next;
            if(tmp->word == k)
                return *tmp->main;
        }
    }
    Value *Badres= new Value;//needs to insert it
    Badres->age = 0;
    Badres->weight= 0;
    insert("error",*Badres);
    return *Badres;

}

const Value& HashTable::at(const Key &k) const {
    if(Chains[hash(k)].init) {
        if (Chains[hash(k)].word == k) {
            return *Chains[hash(k)].main;
        }
        else{
            CHS *tmp = &Chains[hash(k)];
            while (tmp->next != nullptr || tmp->word != k)
                tmp = tmp->next;
            if(tmp->word == k)
                return *tmp->main;
        }
    }
    throw false;
}

Value& HashTable::at(const Key &k) {
    if(Chains[hash(k)].init) {
        if (Chains[hash(k)].word == k) {
            return *Chains[hash(k)].main;
        }
        else{
            CHS *tmp = &Chains[hash(k)];
            while (tmp->next != nullptr || tmp->word != k)
                tmp = tmp->next;
            if(tmp->word == k)
                return *tmp->main;
        }
    }
    throw false;
}

HashTable& HashTable::operator=(const HashTable& b){
    if (this == &b)return *this;
    this->CopyTable(b);
    return *this;
}

void HashTable::swap(HashTable &b) {
    CHS *tmp = Chains;
    Chains = b.Chains;
    b.Chains = tmp;
    int tmp1 = Size;
    Size = b.Size;
    b.Size = tmp1;
    tmp1 = numEl;
    numEl = b.numEl;
    b.numEl = tmp1;
}

void HashTable::clear() {
    for (int i = Size; i < Size; i++){

        Chains[i].word = "undef";
        Chains[i].init = false;

        CHS *now = Chains[i].next;
        CHS *tmp_next;
        while (now != nullptr){
            tmp_next = now->next;
            delete now->main;
            delete now;
            now = tmp_next;
        }

        delete Chains[i].main;
        Chains[i].main = nullptr;
        Chains[i].next = nullptr;
    }
}

bool HashTable::erase(const Key &k) {
    if (numEl == 0)return false;                          //if empty Table
    if (!Chains[hash(k)].init)return false;                //if undefined hash-table cell
    if (Chains[hash(k)].word == k){
        CHS *tmp = &Chains[hash(k)];
        Chains[hash(k)] = *tmp->next;
        delete tmp->main;
        delete tmp;
        return true;
    }
    //if cell found by hash-value, but key word incorrect
    CHS *now = &Chains[hash(k)];
    CHS *tmp;
    while(now->next != nullptr){
        if (now->next->word == k){
            tmp = now->next->next;

            delete now->next->main;
            delete now->next;

            now->next = tmp;
            return true;
        }
        now = now->next;
    }
    return false;
}

bool HashTable::insert(const Key& k, const Value& v){
    if (numEl+1 > Size/2) ExpandTable();
    if (add_elem(k,v)){
        numEl ++;
        return true;
    }
    return false;
}

bool HashTable::add_elem(const Key& k,const Value& v){
    int key = hash(k);
    if (Chains[key].init){      //if we have collision
        CHS* now = &Chains[key];
        while (now->next != nullptr)
            now = now->next;        //find last chain element
        now->next = new CHS;
        now->next->init = true;
        now->next->word = k;
        now->next->main = new Value;        //add element
        now->next->main->weight = v.weight;
        now->next->main->age = v.age;
    }
    if(!Chains[key].init){
        Chains[key].main = new Value;
        Chains[key].main->age = v.age;
        Chains[key].main->weight = v.weight;
        Chains[key].init = true;
        Chains[key].word = k;
        Chains[key].next = nullptr;
    }
    return true;
}

bool HashTable::contains(const Key& k) const{
    if(!Chains[hash(k)].init)return false;
    if(Chains[hash(k)].word == k ) return true;
    if(Chains[hash(k)].next == nullptr) return false;
    CHS* now = &Chains[hash(k)];
    while(now->next != nullptr){
        if(now->word == k)return true;
        now = now->next;
    }
    return false;
}

void HashTable::CopyTable(HashTable b){

    Size = b.Size;
    numEl = b.numEl;

    Value *b_main;
    CHS *bc_now;
    CHS *b_now;

    for(int i=0; i< Size;i++){              //copying fields of Table elements
        if(!b.Chains[i].init){
            Chains[i].init = false;
            Chains[i].word = {'u','n','d','e','f'};
            Chains[i].main = nullptr;
            Chains[i].next = nullptr;
        }

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

void HashTable::ExpandTable() {

    CHS* NewTable = new CHS [Size*2];
    CHS* loader;
    CHS* tmp_del;
    CHS* new_chain;
    CHS* tmp_way;
    Value* rld_elem;
    Value* new_elem;
    int key;
        CHS *tmp_DEBUG1;
    for(int i = 0; i< Size; i++){
        key = hash(Chains[i].word);
        tmp_DEBUG1 = &Chains[i];
        if (Chains[i].init){
            NewTable[key].word = Chains[i].word;       //first chain replace
            NewTable[key].init = true;

            rld_elem = Chains[i].main;
            new_elem = new Value;
            new_elem->age = rld_elem->age;
            new_elem->weight = rld_elem->weight;

            NewTable[key].main = new_elem;
            delete rld_elem;

            loader = Chains[i].next;
            while (loader != nullptr){

                tmp_way = &NewTable[hash(loader->word)];        //default way to load

                if(tmp_way->init)      //if collision
                    while(tmp_way->next != nullptr)
                        tmp_way = tmp_way->next;        //find last chain in collision

                new_chain = new CHS;        //new chain creating
                new_chain->init = true;
                new_chain->word = loader->word;

                rld_elem = loader->main;
                new_elem = new Value;
                new_elem->weight = rld_elem->weight;
                new_elem->age = rld_elem->age;

                new_chain->main = rld_elem;     //add main to chain
                delete loader->main;            //free main from previous table

                tmp_way->next = new_chain;      //add elem to the second table

                tmp_del = loader;
                loader = loader->next;

                delete tmp_del;                 //free chain from previous table
            }
        }
    }
    Size *= 2;
    CHS* tmp = Chains;
    Chains = NewTable;
    delete tmp;
}

int HashTable::hash (Key word) const {
    int seed = 1;
    int hash = 0;
    for (char i : word) {
        hash = (hash * seed) + i;
    }
    return (unsigned)hash % Size;
}

//
// Created by alex_ on 18.10.2018.
//
#include "header.h"

HashTable::HashTable() {
    Size = START_NUM;
    Chains = new CHS [Size];
    numEl = 0;
    for(int i=0; i< Size; i++){
        Chains[i].ToDeafault();
    }
}

HashTable::HashTable(int size) {
    Size = size;
    Chains = new CHS [Size];
    numEl = 0;
    for(int i=0; i< Size; i++){
        Chains[i].ToDeafault();
    }
}

HashTable::HashTable(const HashTable& b){
    Size = b.Size;
    Chains = new CHS [Size];
    numEl = 0;

    CopyTable(b);
}

HashTable::~HashTable() {
    clear();
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
    Value *Badres= new Value;
    Badres->age = 0;
    Badres->weight= 0;
    insert("error",*Badres);
    delete Badres;
    return at("error");
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
    int key = hash(k);
    if (numEl == 0)return false;                          //if empty Table
    if (!Chains[key].init)return false;                //if undefined hash-table cell
    if (Chains[key].word == k){
        CHS *tmp = &Chains[key];
        Chains[key] = *tmp->next;
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
        now->next->CopyByInstr(v,k);
    }
    if(!Chains[key].init){
        Chains[key].CopyByInstr(v,k);
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
    ReloadData(b.Size,b);
}

void HashTable::ExpandTable() {
    ReloadData(Size*2,*this);
}

bool HashTable::ReloadData(int NewSize, HashTable &Source) {

    HashTable *NewHashTable = new HashTable(NewSize);
    CHS* tmpIter;

    for(int i = 0; i< Source.Size; i++){
        if(Source.Chains[i].init){
            tmpIter = &Source.Chains[i];
            while (tmpIter != nullptr){
                NewHashTable->add_elem(tmpIter->word,*tmpIter->main);
                NewHashTable->numEl++;
                tmpIter = tmpIter->next;
            }
        }

    }

    swap(*NewHashTable);
    NewHashTable->clear();
    delete NewHashTable;

    return true;
}

int HashTable::hash (Key word) const {
    int seed = 1;
    int hash = 0;
    for (char i : word) {
        hash = (hash * seed) + i;
    }
    return (unsigned)hash % Size;
}

void Value::CopyValue(const Value &v) {
    age = v.age;
    weight = v.weight;
}

void CHS::ToDeafault() {
    next = nullptr;
    init = false;
    word = "undef";
    main = nullptr;
}

void CHS::CopyByCHS(CHS *b) {
    if(!b->init)
        return;
    main = new Value;
    main->CopyValue(*b->main);
    init = true;
    word = b->word;
}

void CHS::CopyByInstr(const Value &v, const Key &k){
    main = new Value;
    main->CopyValue(v);
    init = true;
    word = k;
}

 bool HashTable::compareElements(Value* a, Value* b){
    if(a->weight != b->weight)return false;
    return a->age == b->age;
}

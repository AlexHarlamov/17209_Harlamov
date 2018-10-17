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
        next = nullptr;
        init = false;
        word = "undef";
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
    HashTable();
    ~HashTable();
    HashTable(const HashTable& b){
        Size = 0;
        numEl = 0;
        Chains = new CHS [Size]; //method CopyTable needs initialization of field "Table"
        CopyTable(b);
    }

    void CopyTable(HashTable b);        //copy hash-table
    void swap(HashTable& b);
    void clear();               //clean container
    void ExpandTable();                 //increase the size of the table

    HashTable& operator=(const HashTable& b);
    Value& operator[](const Key& k);    //returns value by key. An unsafe method.
    Value& at(const Key& k);            //returns value by key
    const Value& at(const Key& k) const;//returns value by key
    bool contains(const Key& k) const;  //Checking the presence of a value for a given key

    bool erase(const Key& k);           //removes the element for a given key
    bool insert(const Key& k, const Value& v);  //Insert into the container. The return value is the success of the insertion
    bool add_elem(const Key& k,const Value& v);

    int hash(Key word) const;           //returns a hash-value for a given key
    static bool compareElements(Value* a, Value* b){
        if(a->weight != b->weight)return false;
        if(a->age != b->age)return false;
        return true;
    }
    size_t size() const{
        return (size_t)numEl;
    }
    bool empty() const{
        return (numEl != 0);
    }

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

/*#include <gtest/gtest.h>
    class HashTableTest : public ::testing::Test{
    protected:
        void SetUp(){
            TestTable_1 = new HashTable;
            TestTable_2 = new HashTable;
            TestValueMass = new Value *[60];
            char c[5]={"abcd"};
            for (int i = 0; i<60; i++ ){
                c[4]=(char)i;
                TestValueMass[i]->word = c;
                TestValueMass[i]->init = true;
                TestValueMass[i]->weight = 69;
                TestValueMass[i]->age = 19;
            }
        }
        void TearDown(){
            delete TestTable_1;
            delete TestTable_2;
        }
        HashTable *TestTable_1;
        HashTable *TestTable_2;
        Value** TestValueMass;

};
    TEST_F(HashTableTest, SizeTest){
    for (int i = 0; i<60; i++ ){
            TestTable_1->insert()
        }
    }


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/

HashTable::HashTable() {
    Size = 5;
    Chains = new CHS [Size];
    numEl = 0;
    for(int i=0; i< Size; i++){
        Chains[i].word = {'u','n','d','e','f'};
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

        Chains[i].word = {'u','n','d','e','f'};
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

bool HashTable::add_elem(const Key& k,const Value& v){    ///No optimization because warning
    if (Chains[hash(k)].init){      //if we have collision
        CHS* now = &Chains[hash(k)];
        while (now->next != nullptr)
            now = now->next;        //find last chain element
        now->next = new CHS;
        now->next->init = true;
        now->next->word = k;
        now->next->main = new Value;        //add element
        now->next->main->weight = v.weight;
        now->next->main->age = v.age;
    }
    if(!Chains[hash(k)].init){
        Chains[hash(k)].main = new Value;
        Chains[hash(k)].main->age = v.age;
        Chains[hash(k)].main->weight = v.weight;
        Chains[hash(k)].init = true;
        Chains[hash(k)].word = k;
        Chains[hash(k)].next = nullptr;
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

    for(int i = 0; i< Size; i++){
        if (Chains[i].init){
            NewTable[hash(Chains[i].word)].word = Chains[i].word;       //first chain replace
            NewTable[hash(Chains[i].word)].init = true;

            rld_elem = Chains[i].main;
            new_elem = new Value;
            new_elem->age = rld_elem->age;
            new_elem->weight = rld_elem->weight;

            NewTable[hash(Chains[i].word)].main = new_elem;
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
    int seed = 131;
    int hash = 0;
    for (char i : word) {
        hash = (hash * seed) + i;
    }
    return hash % Size;
}

int main(){
    HashTable H;
    const Key c = {'f'};
    Value b = H[c];
    return 0;
}
///
//
// Created by alex_ on 8.10.2018.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Tests.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test{
    public:
    };
}

void Testing(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
}

TEST_F(ClassDeclaration,Constructors1){
    HashTable b;
    ASSERT_EQ(START_NUM,b.size());
    ASSERT_EQ(true,b.empty());
    Key k = "TEST";
    Value v;
    v.age = 999;
    v.weight = 999;
    ASSERT_EQ(true,b.insert(k,v));
    ASSERT_EQ(1,b.tablesize());
    HashTable b_1(b);
    ASSERT_EQ(1,b.tablesize());
}
TEST_F(ClassDeclaration,Constructors2){     //long tables
    HashTable b;
}

TEST_F(ClassDeclaration,Insert_Expand){
    HashTable b;
    int WT_size = 159;
    Value* v;
    Key k = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    for(int i = 0; i < WT_size ;i++){
        v=new Value;
        v->weight = (unsigned int)i;
        v->age = (unsigned int)i;
        k[i%29] += 1;
        ASSERT_EQ(true,b.insert(k,*v));
    }
}


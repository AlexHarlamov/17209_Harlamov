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

TEST_F(ClassDeclaration,Constructors1) {
    HashTable a;
    HashTable b(5);
    HashTable c(b);
    ASSERT_EQ(5,c.tablesize());
}



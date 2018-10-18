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
        Tests obj;
        ClassDeclaration(){
            obj;
        }
    };
}
TEST_F(ClassDeclaration,initialtest){
    ASSERT_EQ("","");
}
TEST_F(ClassDeclaration,initialtest1){
    ASSERT_EQ("","");
}
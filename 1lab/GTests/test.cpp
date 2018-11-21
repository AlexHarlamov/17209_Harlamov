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

TEST_F(ClassDeclaration,ez_Constructors1) {
    HashTable a;
    ASSERT_EQ(true,a.empty());

    HashTable b(5);
    Value b1(99,99);
    Value c1(100,100);
    Key k = "tested";
    Key k1 = "detset";

    b.insert(k,b1);
    b.insert(k1,c1);
    HashTable copy_b(b);
    ASSERT_EQ(5,copy_b.tablesize());
    ASSERT_EQ(true,copy_b.contains(k1)&&copy_b.contains(k));

}
TEST_F(ClassDeclaration,ez_Data_operators) {

    HashTable a;
    HashTable a0;
    Value b(99,99);
    Value c(100,100);
    Key k = "tested";
    Key k1 = "detset";

    ///Insert/erase

    a.insert(k,b);  //a cont k
    ASSERT_EQ(true, a.contains(k));

    a.erase(k);     //a cont -
    ASSERT_EQ(false, a.contains(k));

    a.insert(k,b);
    a.insert(k1,c);//a cont k , k1
    ASSERT_EQ(true, a.contains(k1));

    a.erase(k);     //a cont - , k1
    ASSERT_EQ(true, a.contains(k1));

    HashTable z(3);
    Value d(1,1);
    Key k2= "another";

    z.insert(k,b);
    z.insert(k1,c);
    z.insert(k2,d);
    ASSERT_EQ(true,z.contains(k)&&z.contains(k1)&&z.contains(k2));

    ///Copy/swap/clear
    a.insert(k,b);
    a.clear();
    ASSERT_EQ(true, a.empty()||(!a.contains(k)));

    a0.clear();
    a.clear();

    a0.insert(k,b);
    a.insert(k1,c);

    a.swap(a0);//a cont k1
    ASSERT_EQ(true, a0.contains(k1));
    ASSERT_EQ(true, a.contains(k));

    a.clear();
    a0.clear();

    a0.insert(k,b);
    a0.insert(k1,c);

    a.copyTable(a0);//a cont k
    ASSERT_EQ(true, a.contains(k1));
    ASSERT_EQ(true, a.contains(k));

    ///operator=
    a.clear();

    a = a0;
    ASSERT_EQ(true, a.contains(k1));
    ASSERT_EQ(true, a.contains(k));

}

TEST_F(ClassDeclaration,ez_Retrieval){
    HashTable a;
    HashTable a0;
    Value b(99,99);
    Value c(100,100);
    Key k = "tested";
    Key k1 = "detset";

    a.insert(k,b);
    a.insert(k1,c);
    a0.insert(k,b);
    a0.insert(k1,c);

    ASSERT_EQ(false,a.compareElements(a.at(k),a.at(k1)));
    ASSERT_EQ(true,a.compareElements(a.at(k1),a.at(k1)));

    ASSERT_EQ(false,a.compareElements(a[k],a[k1]));
    ASSERT_EQ(true,a.compareElements(a[k1],a[k1]));

    ASSERT_ANY_THROW(a.at("no that word"));

    ASSERT_EQ(true,a.compareElements(a["no that word"],a["error"]));

}

TEST_F(ClassDeclaration,ez_Comparators){
    HashTable a;
    HashTable a0;
    Value b(99,99);
    Value c(100,100);
    Value d(101,101);
    Key k = "tested";
    Key k1 = "detset";
    Key k2 = "another";

    a.insert(k,b);
    a.insert(k1,c);
    a0.insert(k,b);
    a0.insert(k1,c);
    ASSERT_EQ(true, a == a0);

    a0.erase(k1);
    ASSERT_EQ(false,a == a0);

    a0.insert(k2,d);
    ASSERT_EQ(false, a == a0);
}

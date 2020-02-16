#include "globals.h"
#include "indexList.h"
#include <cstring>
#include <sstream>
#include <gtest/gtest.h>
using namespace std;

const WORD WORD1 = "apple";
const WORD WORD2 = "alter";
const WORD WORD3 = "bottle";
const WORD WORD4 = "cattle";
const WORD WORD5 = "counter";
const int MAX = 7;

class testIndex : public testing::Test {
protected:
    virtual void SetUp()
    {
	bool success = false;
	single.update(WORD2, MAX, success);
	full.update(WORD2, MAX, success);
	full.update(WORD3, MAX, success);
	full.update(WORD4, MAX, success);
    }
    virtual void TearDown()
    {
// deconstructor

    }
    // intialize object
    indexList empty;
    indexList single;
    indexList full;

};

// 1

TEST_F(testIndex, AddWordEmptyList)
{
    bool success;
    empty.update(WORD2, MAX, success);
    EXPECT_EQ(1, empty.size());
    EXPECT_TRUE(success);
}

// 2

TEST_F(testIndex, AddWordAtHead)
{
    bool success;
    full.update(WORD1, MAX, success);
    EXPECT_EQ(4, full.size());
    EXPECT_TRUE(success);
}


// 3

TEST_F(testIndex, AddWordAtTail)
{
    bool success;
    full.update(WORD5, MAX, success);
    EXPECT_EQ(4, full.size());
    EXPECT_TRUE(success);
}

// 4

TEST_F(testIndex, RemoveWordSingleton)
{
    bool success;
    single.update(WORD2, 2, success);
    EXPECT_EQ(0, single.size());
    EXPECT_FALSE(success);
}

// 5

TEST_F(testIndex, RemoveWord)
{
    bool success;
    full.update(WORD3, 2, success);
    EXPECT_EQ(0, full.size());
    EXPECT_FALSE(success);
}

// 5

TEST_F(testIndex, RemoveWordAtHead)
{
    bool success;
    full.update(WORD2, 2, success);
    EXPECT_EQ(2, full.size());
    EXPECT_FALSE(success);
}


// 6

TEST_F(testIndex, RemoveWordAtTail)
{
    bool success;
    full.update(WORD4, 2, success);
    EXPECT_EQ(2, full.size());
    EXPECT_FALSE(success);
}

// 7

TEST_F(testIndex, WriteList)
{
    full.write(cout);
}


TEST_F(testIndex, CheckCount)
{
    bool success;
    full.update(WORD2, MAX, success);
    EXPECT_EQ(2, full.getCount(WORD2));
    EXPECT_TRUE(success);
}
/*

TEST_F(testIndexList, )
{

}

*/

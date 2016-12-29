//
// Created by Krumpet on 26-Dec-16.
//

#include "MagiHash.h"
#include <iostream>
#include <cstdlib>
#include "forTest.h"

using namespace std;

bool magitest () {
    Magi newguy(1, 1);
    ASSERT_EQUALS(newguy.getRank(), 0);
    Magi newguy2(2, 4);
    ASSERT_EQUALS(newguy.getRank(), 0);
    ASSERT_EQUALS(newguy2.getRank(), 1);
    Magi newguy3(3, 4);
    ASSERT_EQUALS(newguy3.getRank(), 2);
    ASSERT_EQUALS(newguy.getRank(), 0);
    ASSERT_EQUALS(newguy2.getRank(), 1);
    ASSERT_THROW(magiInput, Magi(-1, 2));
    // rank not advanced if exception thrown
    ASSERT_EQUALS(Magi(5, 5).getRank(), 3);
    Magi copy=newguy;
    ASSERT_EQUALS(copy.getRank(),0);
    return true;
}

bool hashTest () {
    magiHash array;
    ASSERT_EQUALS(array.getSize(), 7);
    Magi guy[6] = {{1, 1},
                   {2, 1},
                   {3, 1},
                   {4, 1},
                   {5, 1},
                   {6, 1}};
    for (int i = 0; i < 6; ++i) {
        ASSERT_EQUALS(array.insert(&guy[i]), HASH_SUCCESS);
    }
    ASSERT_EQUALS(array.getSize(), 14);
    Magi more_guys[5] = {{7,  1},
                         {8,  1},
                         {9,  1},
                         {10, 1},
                         {11, 1}};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQUALS(array.insert(&more_guys[i]), HASH_SUCCESS);
    }
    ASSERT_EQUALS(array.getSize(), 28);
    ASSERT_EQUALS(array.getContent(), 11);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQUALS(array.eraseMagi(more_guys[i].getId()), HASH_SUCCESS);
        ASSERT_EQUALS(array.getContent(), 10 - i);
    }
    ASSERT_EQUALS(array.getSize(), 14);
    return true;
}

bool magiHashTests () {
    RUN_TEST(magitest);
    RUN_TEST(hashTest);
    return true;
}

int main () {
    magiHashTests();
    return 0;
}
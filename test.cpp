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
    Magi copy = newguy;
    ASSERT_EQUALS(copy.getRank(), 0); // so far 3 legit magis with ranks 1,2,3
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
    ASSERT_EQUALS(array.getArray()[array.findMagi(guy[0].getId())].magi->getRank(), 4);
    ASSERT_EQUALS(array.getSize(), 14);
    Magi more_guys[5] = {{7,   1},
                         {867, 1},
                         {9,   1},
                         {785, 1},
                         {11,  1}};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQUALS(array.insert(&more_guys[i]), HASH_SUCCESS);
    }
    ASSERT_EQUALS(array.getSize(), 28);
    ASSERT_EQUALS(array.getContent(), 11);
    cout << more_guys[1].getIndex() << endl;
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQUALS(array.eraseMagi(more_guys[i].getId()), HASH_SUCCESS);
        ASSERT_EQUALS(array.getContent(), 10 - i);
    }
    ASSERT_EQUALS(array.getSize(), 14);
    int creature;
//    int index = array.findMagi(guy[0].getId());
//    cout << index << endl;
//    index = array.findMagi(guy[1].getId());
//    cout << index << endl;
//    index = array.findMagi(guy[2].getId());
//    cout << index << endl;
//    index = array.findMagi(guy[3].getId());
//    cout << index << endl;
//    index = array.findMagi(guy[4].getId());
//    cout << index << endl;
//    index = array.findMagi(guy[5].getId());
//    cout << index << endl;
    HashStatus status = array.getCreature(1, &creature);
    ASSERT_EQUALS(array.getCreature(guy[0].getId(), &creature), HASH_FAILURE);
    guy[0].setBeast(5);
    ASSERT_EQUALS(array.getCreature(guy[0].getId(), &creature), HASH_SUCCESS);
    ASSERT_EQUALS(creature, 5);
    ASSERT_EQUALS(array.eraseMagi(guy[0].getId()), HASH_SUCCESS);
    ASSERT_EQUALS(array.eraseMagi(guy[0].getId()), HASH_FAILURE);
    Magi hasBeast(12, 7);
    hasBeast.setBeast(8);
    ASSERT_EQUALS(array.insert(&hasBeast), HASH_SUCCESS);
    ASSERT_EQUALS(array.getCreature(hasBeast.getId(), &creature), HASH_SUCCESS);
    ASSERT_EQUALS(creature, 8);
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
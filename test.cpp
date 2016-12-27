//
// Created by Krumpet on 26-Dec-16.
//

#include "MagiHash.h"
#include <iostream>
#include <cstdlib>
#include "forTest.h"

using namespace std;

bool magitest() {
    Magi newguy(1,1);
    ASSERT_EQUALS(newguy.getRank(),0);
    Magi newguy2(2,4);
    ASSERT_EQUALS(newguy.getRank(),0);
    ASSERT_EQUALS(newguy2.getRank(),1);
}

bool magiHashTests() {
    RUN_TEST(magitest);

    return true;
}

int main() {
    magiHashTests();
    return 0;
}
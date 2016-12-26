//
// Created by Krumpet on 26-Dec-16.
//

#include "MagiHash.h"

int Magi::count=0;

// const Magi * magiHash::deleted=(Magi*)-1;

int Magi::getCount () {
    return count;
}

int Magi::getId () const {
    return id;
}

int Magi::getLevel () const {
    return level;
}

int Magi::getRank () const {
    return rank;
}

int Magi::getBeast () const {
    return beast;
}

void Magi::setBeast (int beast) {
    Magi::beast = beast;
}

//
// Created by Krumpet on 26-Dec-16.
//

#include "MagiHash.h"

int Magi::count = 0;

//Magi * hashCell::magi=0;
//bool hashCell::deleted=false;

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

Magi & Magi::operator= (const Magi & rhs) {
    id = rhs.id;
    level = rhs.level;
    rank = rhs.rank;
    beast = rhs.beast;
}

magiHash::magiHash () : size(init_size), content(0), array(new hashCell[size]) {}

//
// Created by Krumpet on 26-Dec-16.
//

#include "MagiHash.h"

int Magi::count = 0;

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
    index = rhs.index;
    return *this;
}

bool Magi::operator< (const Magi & rhs) const {
    return ((level < rhs.level) || (level == rhs.level && id < rhs.id));
}

bool Magi::operator> (const Magi & rhs) const {
    return rhs < *this;
}

bool Magi::operator<= (const Magi & rhs) const {
    return !(rhs < *this);
}

bool Magi::operator>= (const Magi & rhs) const {
    return !(*this < rhs);
}

int Magi::getIndex () const {
    return index;
}

void Magi::setIndex (int index) {
    Magi::index = index;
}

bool Magi::operator== (const Magi & rhs) const {
    return id == rhs.id;
}

bool Magi::operator!= (const Magi & rhs) const {
    return !(rhs == *this);
}

magiHash::magiHash () : size(init_size), content(0), array(new hashCell[size]) {}

int magiHash::getSize () const {
    return size;
}

int magiHash::getContent () const {
    return content;
}

hashCell * magiHash::getArray () const {
    return array;
}

// TODO: copy c'tor and assignment operator for hash

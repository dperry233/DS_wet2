//
// Created by Krumpet on 29-Dec-16.
//

#include "MagiHash.h"
#include "animalUnionFind.h"

//int Animal::counter = 0;

Animal & Animal::operator= (const Animal & rhs) {
    id = rhs.id;
    level = rhs.level;
    owner = rhs.owner;
    root = rhs.root;
    size = rhs.size;
    return *this;
}

int Animal::getId () const {
    return id;
}

void Animal::setId (int id) {
    Animal::id = id;
}

int Animal::getLevel () const {
    return level;
}

void Animal::setLevel (int level) {
    Animal::level = level;
}

Magi * Animal::getOwner () const {
    return owner;
}

void Animal::setOwner (Magi * owner) {
    Animal::owner = owner;
}

int Animal::getRoot () const {
    return root;
}

void Animal::setRoot (int root) {
    Animal::root = root;
}

int Animal::getSize () const {
    return size;
}

void Animal::setSize (int size) {
    Animal::size = size;
}

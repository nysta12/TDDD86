/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Unit.h"
#include "constants.h"
#include "utilities.h"
#include <cstdlib>
#include <cmath>

Unit::Unit() {
    teleport();
}


Unit::Unit(const Point& p) {
    x = p.x;
    y = p.y;
}

Point Unit::asPoint() const {
    return Point{x, y};
}

bool Unit::at(const Unit& u) const {
    return (x == u.x && y == u.y);
}

bool Unit::isAlive() const{
    return false;
}

void Unit::doCrash(){

}

bool Unit::isToBeJunked() const{
    return false;
}

void Unit::draw(QGraphicsScene *scene) const {

}

Unit* Unit::clone() {
    return new Unit(*this);
}

void Unit::moveTowards(const Point& p) {
    if (x > p.x) x--;
    if (x < p.x) x++;
    if (y > p.y) y--;
    if (y < p.y) y++;
    checkBounds();
}

void Unit::teleport() {
    x = rand_int (MIN_X, MAX_X);
    y = rand_int (MIN_Y, MAX_Y);
}

double Unit::distanceTo(const Unit& u) const {
    double dx = u.x - x;
    double dy = u.y - y;
    return sqrt(dx * dx + dy * dy);
}

/*
 * Put this unit inside playing field if outside
 */
void Unit::checkBounds() {
    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;
}

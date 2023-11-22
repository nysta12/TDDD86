/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Junk.h"
#include "constants.h"


void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Point& p) {

}

bool Junk::isAlive() const{
    return false;
}

void Junk::doCrash(){

}

bool Junk::isToBeJunked() const{
    return false;
}

Junk* Junk::clone() {
   return new Junk(*this);
}

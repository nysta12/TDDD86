/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:
    Junk(const Point& p): Unit(p){}

    /*
     * Draws this junk onto the given QGraphicsScene.
     */
    void draw(QGraphicsScene* scene) const override;

    /*
     * returns false, junk is not alive
     */
    bool isAlive() const override;

    /*
     * can't crash twice
     */
    void doCrash() override;

    /*
     * can't be junked when it's already junk
     */
    bool isToBeJunked() const override;

    /*
     * junk doesn't move
     */
    virtual void moveTowards(const Point&) override;

    /*
     * returns a dynamically allocated new Junk object
     * that's a deep copy of the original object
     */
    virtual Junk* clone() override;

};

#endif // JUNK_H

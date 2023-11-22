/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool toBeJunked = false;

public:

    /*
     * checks if robot is alive
     */
    bool isAlive() const override;

    /*
     * crashes and remembers it
     */
    void doCrash() override;

    /*
     * checks whether the robot has
     * crashed or not
     */
    bool isToBeJunked() const override;

    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    /*
     * returns a dynamically allocated new Robot object
     * that's a deep copy of the original object
     */
    virtual Robot* clone() override;

};

#endif // ROBOT_H

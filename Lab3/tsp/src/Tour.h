/*
 * TDDD86 TSP
 * This file contains the declaration of the Tour class
 * and all its members, public and private.
 * See Tour.cpp for implementation of each member.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    /*
     * Constructor.
     */
    Tour();

    /*
     * Deconstructor.
     */
    ~Tour();

    /*
     * Prints the tour to the standard output.
     */
    void show() const;

    /*
     * Draws the tour on the scene.
     */
    void draw(QGraphicsScene* scene) const;

    /*
     * Returns the total number of points in the tour.
     */
    int size() const;

    /*
     * Returns the total distance of the tour.
     */
    double distance() const;

    /*
     * Inserts the point p using the heuristik nearest neighbour.
     */
    void insertNearest(Point &p);

    /*
     * Inserts the point p using the heuristik smallest increase.
     */
    void insertSmallest(Point &p);

private:
    Node* firstnode = nullptr;
};

#endif // TOUR_H

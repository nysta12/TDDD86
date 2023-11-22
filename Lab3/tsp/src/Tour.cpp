/*
 * TDDD86 TSP
 * This file contains the implementation of the Tour class.
 * See Tour.h for comments about each member.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}

Tour::~Tour()
{
    Node *node = firstnode;
    Node *n = node->next;

    while(node->next != firstnode){
        delete node;
        node = n;
        n = n->next;
    }
    delete node;
}

void Tour::show() const
{
    if(firstnode == nullptr){
        return;
    }

    Node* node = firstnode;

    while(node->next != firstnode){
        cout << node->point.toString() << endl;
        node = node->next;
    }
    cout << node->point.toString() << endl;
}

void Tour::draw(QGraphicsScene *scene) const
{
    if(firstnode == nullptr){
        return;
    }

    Node* node = firstnode;

    while(node->next != firstnode){
        node->point.drawTo(node->next->point, scene);
        node = node->next;
    }
    node->point.drawTo(node->next->point, scene);
}

int Tour::size() const
{
    if(firstnode == nullptr){
        return 0;
    }

    Node* node = firstnode;
    int count = 0;

    while(node->next != firstnode){
        count++;
        node = node->next;
    }
    count++;
    return count;
}

double Tour::distance() const
{
    if(firstnode == nullptr){
        return 0;
    }

    Node* node = firstnode;
    double totalDistance = 0;

    while(node->next != firstnode){
        totalDistance += node->point.distanceTo(node->next->point);
        node = node->next;
    }
    totalDistance += node->point.distanceTo(node->next->point);
    return totalDistance;
}

void Tour::insertNearest(Point &p)
{
    if(firstnode == nullptr) {
        firstnode = new Node(p, nullptr);
        firstnode->next = firstnode;
        return;
    }

    Node* closestNode = firstnode;

    // sets shortest distance as first node to p
    double shortestDistance = firstnode->point.distanceTo(p);
    Node* node = firstnode->next;

    while(node != firstnode){

        // if a new shortest distance is found
        // set it as the new shortestDistance
        if(node->point.distanceTo(p) < shortestDistance) {
            closestNode = node;
            shortestDistance = node->point.distanceTo(p);
        }
        node = node->next;
    }

    // inserts new node into the linked list
    // by closestNode pointing to the new node
    // while the new node points to what closestNode
    // originally pointed to
    closestNode->next = new Node(p, closestNode->next);
}

void Tour::insertSmallest(Point &p)
{
    if(firstnode == nullptr) {
        firstnode = new Node(p, nullptr);
        firstnode->next = firstnode;
        return;
    }

    Node* node = firstnode;
    Node* closestNode = firstnode;

    // sets shortest increase as the distance generated
    // from inserting p between the first node and the node after and subtracting
    // that distance with the distance between the first node and the node after without p inserted
    double shortestIncrease = node->point.distanceTo(p) + p.distanceTo(node->next->point) - node->point.distanceTo(node->next->point);
    node = node->next;

    while(node != firstnode){
        double distance = node->point.distanceTo(p) + p.distanceTo(node->next->point) - node->point.distanceTo(node->next->point);

        // if a new shortest increase is found
        // set it as the new shortestIncrease
        if(distance < shortestIncrease ) {
            closestNode = node;
            shortestIncrease  = distance;
        }
        node = node->next;
    }

    // inserts new node into the linked list
    // by closestNode pointing to the new node
    // while the new node points to what closestNode
    // originally pointed to
    closestNode->next = new Node(p, closestNode->next);
}

























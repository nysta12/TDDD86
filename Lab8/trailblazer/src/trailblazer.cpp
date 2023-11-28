/*
 * TDDD86 Trailblazer
 * This file contains functions for the algorithms depthFirstSearch,
 * breadthFirstSearch, dijkstrasAlgorithm and aStar that are used
 * to find a route from a selected starting vertex to a
 * selected finishing vertex.
 *
 * Author: Victor Nyström
 */

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include "queue.h"
#include <vector>
#include <algorithm>
#include "queue"
#include "pqueue.h"
#include "stack.h"

using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end){
    graph.resetData();

    vector<Vertex*> path;

    // stack for storing vertexes that are being checked
    Stack<Vertex*> s;
    s.push(start);

    while(!s.isEmpty()){
        Vertex* current = s.top();
        current->setColor(GREEN);
        current->visited = true;
        if(current == end){
            end = current;
            break;
        }
        bool neighbours = false;
        for(Vertex* neighbour : graph.getNeighbors(current)){
            if (!neighbour->visited){
                neighbours = true;
                s.push(neighbour);
                neighbour->previous = current;
            }
        }
        if(!neighbours){
            current->setColor(GRAY);
            s.pop();
        }
    }

    // backtrack with previous pointer, from end vertex
    // to start vertex and then reverse to get correct order of path
    Vertex* current = end;
    while(current->previous != nullptr){
        path.push_back(current);
        current = current->previous;
    }
    //path.push_back(current);
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end){
    graph.resetData();
    vector<Vertex*> path;

    // queue for storing vertexes that are being checked
    Queue<Vertex*> q;

    start->visited = true;
    q.enqueue(start);

    while(!q.isEmpty()){
        Vertex* v = q.dequeue();
        v->setColor(GREEN);

        if(v == end){
            end = v;
            break;
        }

        for(Vertex* neighbour : graph.getNeighbors(v)){
            if (!neighbour->visited){
                neighbour->visited = true;
                neighbour->setColor(YELLOW);

                // adds pointer for every neighbour to the previous vertex
                // for backtracking later
                neighbour->previous = v;
                q.enqueue(neighbour);
            }
        }
    }

    // backtrack with previous pointer, from end vertex
    // to start vertex and then reverse to get correct order of path
    Vertex* current = end;
    while(current->previous != nullptr){
        path.push_back(current);
        current = current->previous;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;
    PriorityQueue<Vertex*> pQ;

    // priorityQueue where the prioritisation is based on lowest cost
    pQ.enqueue(start, start->cost);
    Vertex* v;

    while(!pQ.isEmpty()){
        v = pQ.dequeue();
        v->visited = true;
        v->setColor(GREEN);

        if(v == end){
            end = v;
            break;
        }

        // go through all edges going from the vertex v
        for(Arc* edge : v->arcs){
            Vertex* neighbour = edge->finish;

            if(!neighbour->visited){
                // cost of reaching the neighbour from the start vertex
                double cost = v->cost + edge->cost;

                // check if new cost is better than the old cost
                if(cost < neighbour->cost){
                    neighbour->cost = cost;
                    neighbour->previous = v;
                    pQ.changePriority(neighbour, neighbour->cost);
                }

                // cost is initially 0
                if(neighbour->cost == 0){
                    neighbour->cost = cost;
                    neighbour->previous = v;
                    pQ.enqueue(neighbour, neighbour->cost);
                    neighbour->setColor(YELLOW);
                }
            }
        }
    }

    // backtrack with previous pointer, from end vertex
    // to start vertex and then reverse to get correct order of path
    Vertex* current = end;
    while(current->previous != nullptr){
        path.push_back(current);
        current = current->previous;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());


    return path;
}


vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();


    vector<Vertex*> path;
    PriorityQueue<Vertex*> pQ;

    // priorityQueue where the prioritisation is based on lowest cost
    pQ.enqueue(start, start->cost);
    Vertex* v;

    while(!pQ.isEmpty()){
        v = pQ.dequeue();
        v->visited = true;
        v->setColor(GREEN);

        if(v == end){
            end = v;
            break;
        }

        // go through all edges going from the vertex v
        for(Arc* edge : v->arcs){
            Vertex* neighbour = edge->finish;

            if(!neighbour->visited){
                // cost of reaching the neighbour from the start vertex
                double cost = v->cost + edge->cost;

                // check if new cost is better than the old cost
                if(cost < neighbour->cost){
                    neighbour->cost = cost;
                    neighbour->previous = v;

                    // heuristic to make an educated and estimated guess of a cost travelling from neighbour to end
                    pQ.changePriority(neighbour, neighbour->cost + neighbour->heuristic(end));
                }

                // cost is initially 0
                if(neighbour->cost == 0){
                    neighbour->cost = cost;
                    neighbour->previous = v;

                    // heuristic to make an educated and estimated guess of a cost travelling from neighbour to end
                    pQ.enqueue(neighbour, neighbour->cost + neighbour->heuristic(end));
                    neighbour->setColor(YELLOW);
                }
            }
        }
    }

    // backtrack with previous pointer, from end vertex
    // to start vertex and then reverse to get correct order of path
    Vertex* current = end;
    while(current->previous != nullptr){
        path.push_back(current);
        current = current->previous;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while(!isEmpty(*robot)){
            delete robot;
            robot = new Robot();
            robot->teleport();
        }
        units.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState() {
    for(auto unit: units) {
        delete unit;
    }
    units.clear();
}

GameState::GameState(const GameState &gameState)
{
    // deep copies every unit from current
    // gameState object to units vector
    for (unsigned int i = 0; i < gameState.units.size(); i++){
         units.push_back(gameState.units[i]->clone());
    }

    // copy hero to new gamestate object
    hero = gameState.hero;
}

GameState& GameState::operator=(const GameState &gameState)
{
    // checks so gameState isn't the current object, (self-assignment check)
    if (this == &gameState){
        return *this;
    }
    // deallocate the memory for every unit
    for (unsigned int i = 0; i < units.size(); i++){
        delete units[i];
    }
    // remove all elements from units
    units.clear();

    // deep copies every unit from current
    // gameState object to units vector
    for (unsigned int i = 0; i < gameState.units.size(); i++){
         units.push_back(gameState.units[i]->clone());
    }

    // copy hero to new gamestate object
    hero = gameState.hero;

    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for(Unit *u: units){
        u->draw(scene);
    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Unit *u : units){
        u->moveTowards(hero.asPoint());
    }
}

void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); ++i){
        for(unsigned j=i+1; j < units.size(); ++j){
            if(units[i]->at(units[j]->asPoint())){
                units[i]->doCrash();
                units[j]->doCrash();
            }
        }
    }
}

int GameState::countToBeJunked() const {
    int numberDestroyed =0;
    for(unsigned i=0; i < units.size(); ++i){
        if(units[i]->isToBeJunked()){
            numberDestroyed++;
        }
    }
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if(units[i]->isToBeJunked()){
            Junk *junk = new Junk(units[i]->asPoint());
            delete units[i];
            units[i] = junk;
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}

bool GameState::heroDead() const {
    for(const Unit *u : units){
        if(hero.at(u->asPoint())){
            return true;
        }
    }
    return false;
}

void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {
    return hero.asPoint();
}

bool GameState::isEmpty(const Unit& unit) const {
    for(const Unit* u : units){
        if(u->at(unit)){
            return false;
        }
    }
    return true;
}


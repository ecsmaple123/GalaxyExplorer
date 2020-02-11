/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

//Inserts a new entry in the linked list whenever a new asteroid appears on the list

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    //Insert it at the end of the list for AI to shoot at existing asteroids
   asteroid_list.insertAfter(asteroid_list.beforeEnd(), asteroid);
}

//Update the position of an asteroid by matching their ID

void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {

    AsteroidListItem* currentPtr = asteroid_list.begin();//First asteroid
    while (currentPtr != nullptr) {
        if (currentPtr -> getData().getID() == asteroid.getID()) { //ID match
            currentPtr -> getData() = asteroid; //Change data
            return;
        }
        currentPtr = currentPtr -> getNext(); //Iterate
    }

}

//Called when an asteroid leaves the field without being destroyed

void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {

    //Iterator
    AsteroidListItem* currentPtr = asteroid_list.begin();
    AsteroidListItem* prevPtr = asteroid_list.beforeBegin();//Lagging one
    
    while (currentPtr != nullptr) {
        if (currentPtr -> getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(prevPtr);
            return;
        }
        currentPtr = currentPtr -> getNext();
        prevPtr = prevPtr -> getNext();
    }

}

//Called when an asteroid is destroyed
//Exact same thing as onAsteroidOutOfRange
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
     AsteroidListItem* currentPtr = asteroid_list.begin();
    AsteroidListItem* prevPtr = asteroid_list.beforeBegin();
    
    while (currentPtr != nullptr) {
        if (currentPtr -> getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(prevPtr);
            return;
        }
        currentPtr = currentPtr -> getNext();
        prevPtr = prevPtr -> getNext();
    }
}

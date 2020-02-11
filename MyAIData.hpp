/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP

/**
 * Student editable struct for storing their ai state
 * Yes, you may change this header.
 * Maybe you want to remember the last asteroid Id you shot at?
 */

struct MyAIData {
    bool debug_on = true;
};

int HitTime(AsteroidListItem* curAsteroid, const ShipState& ship_state);
AsteroidListItem* TargetAsteroid(AsteroidList *asteroidlist, const ShipState& ship_state);
double GetAngle(AsteroidListItem *Asteroid);

//Find the amount of iteration it takes for an asteroid to hit the ship
//Return -1 if it does not hit
int HitTime(AsteroidListItem* currAsteroid, const ShipState& ship_state) {

    int hitTime = 0;
    bool hit = false;

    //No health asteroid 
    if (currAsteroid -> getData().getHealth() == 0)
        return -1;

    //Getting values
    sf::IntRect rect = currAsteroid -> getData().getCurrentHitbox();
    sf::Vector2i currentVelocity = currAsteroid -> getData().getVelocity();

    while (rect.top <= ship_state.hitbox.top + ship_state.hitbox.height) { //In playing field
        if (rect.intersects(ship_state.hitbox)) { //Collision check
            hit = true;
            break;
        }
        //Updating location
        rect.top += currentVelocity.y;
        rect.left += currentVelocity.x;

        hitTime++;
    }
    if (!hit)
        hitTime = -1; //No hit 

    return hitTime;
}

//Function to choose which asteroid to target based on HitTime
AsteroidListItem* TargetAsteroid(AsteroidList *asteroidlist, const ShipState& ship_state) {
    int hitTime = 0, hitTimeTmp = 0;
    static AsteroidListItem *retAsteroid = nullptr; //Static to return
    AsteroidListItem *curItem = nullptr;


    if (asteroidlist -> isEmpty()) //No asteroid on playing field
        return retAsteroid;

    curItem = asteroidlist -> begin(); //First asteroid
    hitTime = HitTime(curItem, ship_state); //Get the hit time
    retAsteroid = curItem;

    while (curItem -> getNext() != nullptr) {
        curItem = curItem -> getNext();
        hitTimeTmp = HitTime(curItem, ship_state);
        if (hitTimeTmp >= 0) {
            //If no hit or current one hits before the previous fastest hit
            //update return pointer
            if (hitTime < 0 || hitTimeTmp < hitTime) { 
                hitTime = hitTimeTmp;
                retAsteroid = curItem;
            }
        }
    }

    return retAsteroid;

}
/* Math to calculate the angle for the ship to aim at.
 * This is done by setting up a quadratic equation to solve
 * for the exact time of collision after confirming that the
 * asteroid will hit. With the time, it is possible to figure
 * out the exact location that the ship needs to fire. With a
 * tangent, the angle is then calculated and converted into a playing
 * angle and returned.
 * 
 * The quadratic equation is found using vector calculations.
 * At a time T, the distance from the ship to the fired projectile
 * is proportionate to the speed of the projectile. This then can be
 * represented with a equation of a circle, parameterized with T.
 * This T is also proportionate to the location of the asteroid plus
 * its velocity. After substituting, an equation of ax^2+bx+c can be setup
 * where x is T to solve
 */
double GetAngle(AsteroidListItem *Asteroid) {

    double asX = (Asteroid -> getData().getCurrentHitbox().left) +
            (Asteroid -> getData().getCurrentHitbox().width) / 2;
    double asY = (Asteroid -> getData().getCurrentHitbox().top) +
            (Asteroid -> getData().getCurrentHitbox().height) / 2;
    double xDiff = asX - 10000;
    double yDiff = asY - 17999;
    double PI = atan(1) * 4;
    ;
    double theta;

    double vX = Asteroid -> getData().getVelocity().x;
    double vY = Asteroid -> getData().getVelocity().y;

    double a = (vX * vX) + (vY * vY) - 10000;
    double b = 2 * (vX * xDiff + vY * yDiff);
    double c = xDiff * xDiff + yDiff * yDiff;

    double collionT = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

    double X = collionT * vX + asX;
    double Y = collionT * vY + asY;

    if (collionT > 0) {
        theta = atan((X - 10000) / (19000 - Y));
        theta *= 180 / PI * 1000;
    } else
        theta = 0;

    return theta;
}


#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
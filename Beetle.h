#include <string>
#ifndef BEETLE_H
#define BEETLE_H
#include "Creature.h"

//Beetle class is a derived class derived from the base class - Creature
class Beetle : public Creature
{
public:
    //constructor and destructor
    
    //empty constructor
    Beetle();
    //empty destructor
    virtual ~Beetle();
    
    
    //move and breed method definitions
    std::string move(int northDist, int eastDist, int southDist, int westDist);
    std::string breed(bool N, bool E, bool S, bool W);
};
#endif

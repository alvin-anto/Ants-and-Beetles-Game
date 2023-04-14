#include <string>
#ifndef ANT_H
#define ANT_H
#include "Creature.h"

//Ant class is a derived class derived from the base class - Creature
class Ant : public Creature
{
public:
    //constructor and destructor
    
    //empty constructor
    Ant();
    //empty destructor
    virtual ~Ant();
    
    
    //move and breed method definitions
    std::string move(int northDist, int eastDist, int southDist, int westDist);
    std::string breed(bool, bool, bool, bool);
};
#endif

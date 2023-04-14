#ifndef CREATURE_H
#define CREATURE_H
#include <string>

//Creature abstract class is the base class for the derived classes - Ant and Beetle classes
class Creature
{
protected:
    //initializations
    bool hasMoved = false;
    bool hasBred = false;
    int numTurnsSinceAte = 0;
    
public:
    //constructor and destructor
    
    Creature(){} //empty constructor
    virtual ~Creature(){} //empty destructor
    
    
    //to make abstract class, creating pure virtual functions
    
    //pure virtual move function which will be overridden in Ant and Beetle
    virtual std::string move(int,int,int,int) = 0;
    //pure virtual breed function which will be overridden in Ant and Beetle
    virtual std::string breed(bool, bool, bool, bool) = 0;
    
    
    //mutators
    
    //sets hasMoved to true, indicating that the creature has moved in the turn
    void moved(){hasMoved = true;}
    //sets hasBred to true, indicating that the creature has bred in the turn
    void bred(){hasBred = true;}
    //resetMovedAndBred method sets hasMoved and hasBred to false
    void resetMovedAndBred()
    {
        hasMoved = false;
        hasBred = false;
    };
    //ate method resets numTurnsSinceAte to 0
    void ate(){numTurnsSinceAte = 0;}
    //didntEat method increments the instance variable numTurnsSinceAte by 1
    void didntEat(){numTurnsSinceAte++;}
    
    
    //accessors
    
    //returns numTurnsSinceAte the number of turns since the creature last ate
    int getNumTurnsSinceAte(){return numTurnsSinceAte;}
    //returns hasMoved - whether or not the creature has moved in the turn
    bool hasMovedOnce(){return hasMoved;}
    //returns hasBred - whether or not the creature has bred in the turn
    bool hasBredOnce(){return hasBred;}
    //returns true if the argument is 5 and false otherwise
    bool starve(int num){
        if (num == 5){return true;}
        return false;
    }
};

#endif

#include <string>
#include "Ant.h"

//overridden constructor for Ant
Ant::Ant() : Creature(){}

//empty destructor
Ant::~Ant(){}

//move method takes in the distances to the beetle in the orthogonal directions as the arguments and
//determine and return the direction the ant is to be moved
std::string Ant::move(int northDist, int eastDist, int southDist, int westDist)
{
    //declaring dir to store the direction and shortestPath to keep track of the shortest path to the beelt
    std::string dir;
    int shortestPath;
    
    //if all the arguments are negative, meaning there are no beetles in orthogonal directions, it returns an empty string
    //and then the direction for movement is determined in main
    if ((northDist < 0) && (eastDist < 0) && (southDist < 0) && (westDist < 0))
    {
        return "";
    }
    
    //if any of the values are negative
    if ((northDist < 0) || (eastDist < 0) || (southDist < 0) || (westDist < 0))
    {
        //if there is a beetle in the north direction, assigning shortestPath to the distance to that beetle and the direction to south
        if (northDist > 0)
        {
            shortestPath = northDist;
            dir = "S";
        }
        //if there is a beetle in the east direction, assigning shortestPath to the distance to that beetle and the direction to west
        else if (eastDist > 0)
        {
            shortestPath = eastDist;
            dir = "W";
        }
        //if there is a beetle in the south direction, assigning shortestPath to the distance to that beetle and the direction to north
        else if (southDist > 0)
        {
            shortestPath = southDist;
            dir = "N";
        }
        //if there is a beetle in the west direction, assigning shortestPath to the distance to that beetle and the direction to east
        else
        {
            shortestPath = westDist;
            dir = "E";
        }
        
        //findind the shortest path by checking all the arguments and storing the shortest distance to shortestPath
        //and the direction opposite to the location of the nearest beetle to dire
        if ((northDist > 0) && (shortestPath > northDist))
        {
            shortestPath = northDist;
            dir = "S";
        }
        if ((eastDist > 0) && (shortestPath > eastDist))
        {
            shortestPath = eastDist;
            dir = "W";
        }
        if ((southDist > 0) && (shortestPath > southDist))
        {
            shortestPath = southDist;
            dir = "N";
        }
        if ((westDist > 0) && (shortestPath > westDist))
        {
            shortestPath = westDist;
            dir = "E";
        }
        
        //initializing the int variable flag, which checks if there is more than one direction with the shortest distance to the beetl
        int flag = 0;
        
        //checking to see if there are multiple shortest paths
        if (shortestPath == westDist)
        {
            flag++;
        }
        if (shortestPath == southDist)
        {
            flag++;
        }
        if (shortestPath == eastDist)
        {
            flag++;
        }
        if (shortestPath == northDist)
        {
            flag++;
        }
        
        //if there are multiple shortest paths, following the prioirty N,E,S,W
        if (flag > 1)
        {
            if (northDist < 0)
            {
                return "N";
            }
            else if (eastDist < 0)
            {
                return "E";
            }
            else if (southDist < 0)
            {
                return "S";
            }
            else if (westDist < 0)
            {
                return "W";
            }
        }
        //if there are beetles in all the directions, the longest path is found and that direction is returned
        if ((northDist > 0) && (eastDist > 0) && (southDist > 0) && (westDist > 0))
        {
            int longestPath = northDist;
            dir = "N";
            if (longestPath > eastDist)
            {
                longestPath = eastDist;
                dir = "E";
            }
            if (longestPath > southDist)
            {
                longestPath = southDist;
                dir = "S";
            }
            if (longestPath > westDist)
            {
                longestPath = westDist;
                dir = "W";
            }
            
            if (longestPath == westDist)
            {
                dir = "W";
            }
            if (longestPath == southDist)
            {
                dir = "S";
            }
            if (longestPath == eastDist)
            {
                dir = "E";
            }
            if (longestPath == northDist)
            {
                dir = "N";
            }
        }
        return dir;
    }
    else
    {
        //finding the longestPath and using the N,E,S,W if there are mulitple longest paths
        int longestPath = northDist;
        dir = "N";
        if (longestPath < eastDist)
        {
            longestPath = eastDist;
            dir = "E";
        }
        if (longestPath < southDist)
        {
            longestPath = southDist;
            dir = "S";
        }
        if (longestPath < westDist)
        {
            longestPath = westDist;
            dir = "W";
        }
        if (longestPath == westDist)
        {
            dir = "W";
        }
        if (longestPath == southDist)
        {
            dir = "S";
        }
        if (longestPath == eastDist)
        {
            dir = "E";
        }
        if (longestPath == northDist)
        {
            dir = "N";
        }
        return dir;
    }
}

//breed method takes in four boolean values and determines which direction the newly born ant has to be placed
std::string Ant::breed(bool N, bool E, bool S, bool W)
{
    if (N)
    {
        return "N";
    }
    else if (E)
    {
        return "E";
    }
    else if (S)
    {
        return "S";
    }
    else if (W)
    {
        return "W";
    }
    else
    {
        return "";
    }
}

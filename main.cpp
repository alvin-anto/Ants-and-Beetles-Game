/**
 * ALVIN ANTO
 * NET ID: AXA220139
 * UTD ID: 2021686750
 * CS 2337.002
 * PROJECT 1 - Ants and Beetles - Final Submission
 */


#include <iostream>
#include <string>
#include <fstream>
#include "Creature.h"
#include "Ant.h"
#include "Beetle.h"
using namespace std;


//prototypes
static void beetleStarveHelper(Creature *grid[][10], int i, int j, bool ans);
static void breedHelper(Creature *grid[][10], int i, int j, string direction);
static bool emptySpace(Creature* grid[][10], int i, int j, string direction);
static int numAdjacentAnts(Creature *grid[][10], int i, int j);
static int beetleFindDist(Creature *grid[][10], int i, int j, string direction);
static int antFindDist(Creature *grid[][10], int i, int j, string direction);
void beetleMoveHelper(Creature *grid[][10], int j, int i, string direction);
void antMoveHelper(Creature *grid[][10], int j, int i, string direction);




int main()
{
    
    //declaring a string variable fileName and storing the file name input by the user to it and opening the file
    string fileName;
    cin >> fileName;
    ifstream input;
    input.open("world.txt");
    
    //taking the character representation for ant and beetle and the number of turns from the user and
    //initialzing the corresponding variables with those values.
    string antRep;
    string beetleRep;
    cin >> antRep;
    cin >> beetleRep;
    int desiredNumOfTurns;
    cin >> desiredNumOfTurns;
  
    //initializing constant int variables for the fixed grid - rows and colums
    const int rows = 10;
    const int columns = 10;
    
    //creating an array with objects of Creature abstract class
    Creature* grid[rows][columns] = {};
    
    //initializing the control variable for the while loop to 0 and declaring the string line to store each line of the input file
    int count = 0;
    string line;
    
    //while loop that runs 10 times and gets the line from the input file one by one each iteration and
    //creating ant or beetle instances in the Creature array (grid)
    while (count < 10)
    {
        //storing each line of the input file to the string variable line
        getline(input, line);
        
        //for loop that runs 10 times and creating ant or beetle instances in the Creature array (grid)
        //according to the character in the input file
        for (int i = 0; i < 10; i++)
        {
            //if the character is 'a', then an ant object is added to the grid at the corresponding position
            if (line[i] == 'a')
            {
                grid[count][i] = new Ant();
            }
            //if the character is 'B', then a beetle object is added to the grid at the corresponding position
            else if (line[i] == 'B')
            {
                grid[count][i] = new Beetle();
            }
            //if the character is blank, then the grid box is set to nullptr
            else
            {
                grid[count][i] = nullptr;
            }
        }
        //increments count for the next iteration
        count++;
    }
    
    //closes the input file after taking data from it
    input.close();
    
    //printing an empty line
    cout << endl;
    
    //the loop is run the number of times equal to the number of turns input by the user
    for (int k = 1; k < desiredNumOfTurns+1; k++)
    {
        //before the creature operations are made, resetMovedandBred method is called on all creatures in the grid
        //to make sure their hasMoved and hasBred instance variables are set to false because they havent moved or bred in this turn
        //this is done because hasMoved and hasBred for some cretures will be true from the previous turn
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (grid[i][j])
                {
                    grid[i][j]->resetMovedAndBred();
                }
                
            }
        }
        
        //printing the title "TURN"
        cout << "TURN " << k << endl;
        
        //the for inside the for loop checks if the object present in the grid at that position is a beetle.
        //If it is a beetle, it moves the beetle if it hasnt already been moved in this turn.
        //This is done by calling the move method in the beetle class which returns which direction to move, which is then
        //passed as an argument to beetleMoveHelper method in main
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                //checking if there is a creature present at this position
                if (grid[j][i])
                {
                    //if the creature at this position is a beetle and the beetle hasnt moved once in this turn
                    if ((dynamic_cast<Beetle*>(grid[j][i])) && (grid[j][i]->hasMovedOnce() == false))
                    {
                        //calling didntEat method on the beetle at this position to increase the number of turns
                        //since the last time the beetle ate an ant.
                        //This number of turns since the last time the beetle ate an ant is reset in the helper method
                        //if this beetle ends up eating an ant in this turn.
                        grid[j][i]->didntEat();
                        
                        //calling beetleFindDist method to find the distance to the ant in the north, east, south and west directions
                        //and then initializing the variable p,q,r and s with these values
                        int p = beetleFindDist(grid, j, i, "N");
                        int q = beetleFindDist(grid, j, i, "E");
                        int r = beetleFindDist(grid, j, i, "S");
                        int s = beetleFindDist(grid, j, i, "W");
                        
                        //calling the move method ont the beetle to find the distance the ant has to move and
                        //storing it to the string variable direction
                        string direction = grid[j][i]->move(p, q, r, s);
                        
                        //[if there are no orthogonal ants, the variable direction will be an empty string]
                        //if the direction is an empty string, then the farthest edge from the beetle is found
                        //and that direction is stored in the string variable direction
                        if (direction == "")
                        {
                            int smallest = p;
                            direction = "N";
                            if (smallest > q)
                            {
                                smallest = q;
                                direction = "E";
                            }
                            if (smallest > r)
                            {
                                smallest = r;
                                direction = "S";
                            }
                            if (smallest > s)
                            {
                                smallest = s;
                                direction = "W";
                            }
                            //if there are multiple farthest edges, using prioirty NESW.
                            //The variable direction gets updated with the next most prioirty direction if there are multiple farthest edges.
                            if (smallest == s)
                            {
                                direction = "W";
                            }
                            if (smallest == r)
                            {
                                direction = "S";
                            }
                            if (smallest == q)
                            {
                                direction = "E";
                            }
                            if (smallest == p)
                            {
                                direction = "N";
                            }
                        }
                        //calling the beetleMoveHelper method with the grid, the row and column and the direction as the arguments
                        //the method will then make movements in the grid after checking some conditions
                        beetleMoveHelper(grid, j, i, direction);
                        
                    }
                }
            }
        }
        
        //the for inside the for loop checks if the object present in the grid at that position is an ant
        //If it is an ant, it moves the ant if it hasnt already been moved in this turn.
        //This is done by calling the move method in the ant class which returns which direction to move, which is then
        //passed as an argument to antMoveHelper method in main
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                //checking if there is a creature present at this position
                if (grid[j][i])
                {
                    //if the creature at this position is an ant and the ant hasnt moved once in this turn
                    if ((dynamic_cast<Ant*>(grid[j][i])) && (grid[j][i]->hasMovedOnce() == false))
                    {
                        //calling antFindDist method to find the distance to the beetle in the north, east, south and west directions
                        //and then initializing the variable m, n, o and p with these values
                        int m = (antFindDist(grid, j, i, "N"));
                        int n = (antFindDist(grid, j, i, "E"));
                        int o = (antFindDist(grid, j, i, "S"));
                        int p = (antFindDist(grid, j, i, "W"));
                        
                        //calling the antMoveHelper method with the grid, the row and column and the direction as the arguments
                        //the method will then make movements in the grid after checking some conditions
                        antMoveHelper(grid, j, i, grid[j][i]->move(m,n,o,p));
                    }
                }
            }
        }
        
        //the for inside the for loop checks if the object present in the grid at that position is a beetle.
        //If it is a beetle, it checks how many turns have passed since the beetle ate an ant using getNumTurnsSinceAte method.
        //The method starve is called which determines whether or not the beetle needs to starve. Then, the boolean result of this
        //is passed as an argument in the beetleStarveHelper and that method makes the changes if necessary.
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                //checks if there is a creature at this position
                if (grid[j][i])
                {
                    //checks if the ceature at this positon is a beetle
                    if (dynamic_cast<Beetle*>(grid[j][i]))
                    {
                        //finding the number of turns since the beetle ate an ant the last time using getNumTurnsSinceAte method
                        //and then storing that in the int variable numTurnsSinceLastAte
                        int numTurnsSinceLastAte =grid[j][i]->getNumTurnsSinceAte();
                        
                        //calling the starve method with the number of turns since the beetle ate an ant the last time as an argument
                        //and storing the boolean result in the variable shouldStarve
                        bool shouldStarve = grid[j][i]->starve(numTurnsSinceLastAte);
                        
                        //calling the beetleStarveHelper with the grid, row, column and the value of the variable shoudlStarve as arguments
                        //The method will then make the beetle starve if necessary
                        beetleStarveHelper(grid, j, i, shouldStarve);
                    }
                }
            }
        }
        
        //if the number of turns is perfectly divisible by 3 (every 3rd turn)
        if (k%3 == 0)
        {
            //the for inside the for loop checks if the object present in the grid at that position is an ant
            //If it is an ant, the ant considers breeding if this ant wasnt newly born in the this turn.
            //Then the north, east, south and west directions are checked using emptySpace method to
            //check if there is empty space in those directions and then breed method is called using these values as parameters.
            //The breed method returns the direction of the box in which the new ant has to be born and then
            //this value is passed as an argument to breedHelper which actually does the breeding
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    //if a creature is present at this position
                    if (grid[j][i])
                    {
                        //if the creature at this position is an ant and this ant wasnt newly born in this turn
                        if ((dynamic_cast<Ant*>(grid[j][i])) && (grid[j][i]->hasBredOnce() == false))
                        {
                            //calls emptySpace methods to see if the box in the north, east, south and west directions are empty and
                            //then the values are passes as arguments for the breed function which returns the direction the ant is born
                            //The grid, row, column and this direction are passed as arguments for breedHelper function
                            //that actually creates a new ant in the grid in the appropriate box if necessary
                            bool e = emptySpace(grid, j, i, "N");
                            bool f = emptySpace(grid, j, i, "E");
                            bool g = emptySpace(grid, j, i, "S");
                            bool h = emptySpace(grid, j, i, "W");
                            breedHelper(grid, j, i, grid[j][i]->breed(e,f,g,h));
                            
                        }
                    }
                }
            }
        }
        
        //if the number of turns is perfectly divisible by 8 (every 8th turn)
        if (k%8 == 0)
        {
            //the for inside the for loop checks if the object present in the grid at that position is a beetle
            //If it is a beetle, the beetle considers breeding if this beetle wasnt newly born in the this turn.
            //Then the north, east, south and west directions are checked using emptySpace method to check
            //if there is empty space in those directions and then breed method is called using these values as parameters.
            //The breed method returns the direction of the box in which the new beetle has to be born and then
            //this value is passed as an argument to breedHelper which actually does the breeding
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    //if a creature is present at this position
                    if (grid[j][i])
                    {
                        //if the creature at this position is a beetle and this beetle wasnt newly born in this turn
                        if ((dynamic_cast<Beetle*>(grid[j][i])) && (grid[j][i]->hasBredOnce() == false))
                        {
                            //calls emptySpace methods to see if the box in the north, east, south and west directions are empty and
                            //then the values are passes as arguments for the breed function which returns the direction the beetle is born
                            //The grid, row, column and this direction are passed as arguments for breedHelper function
                            //that actually creates a new beetle in the grid in the appropriate box if necessary
                            bool e = emptySpace(grid, j, i, "N");
                            bool f = emptySpace(grid, j, i, "E");
                            bool g = emptySpace(grid, j, i, "S");
                            bool h = emptySpace(grid, j, i, "W");
                            breedHelper(grid, j, i, grid[j][i]->breed(e,f,g,h));
                            
                        }
                    }
                }
            }
        }
        
        //the for inside the for loop checks if there is a creature present at position and if so, it prints the value of
        //antRep if it is an ant and beetlRep if it is a beetle and prints an empty space if there are no creatures.
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                //if a creature is present at this position
                if (grid[i][j])
                {
                    //if the creature is an ant
                    if (dynamic_cast<Ant*>(grid[i][j]))
                    {
                        //prints the value of antRep if the creature is an ant
                        cout << antRep;
                    }
                    //if the creature is a beetle
                    else if (dynamic_cast<Beetle*>(grid[i][j]))
                    {
                        //prints the value of beetleRep if the creature is a beetle
                        cout << beetleRep;
                    }
                }
                //if there is no creature at this position
                else
                {
                    //prints an empty space if there is no creature at this position
                    cout << " ";
                }
            }
            //prints an empty line after every row in the grid
            cout << endl;
        }
        
        //prints an empty line
        cout << endl;
    }
    
    //return for main() method
    return 0;
}


//beetleStarveHelper deletes an ant from the grid if the beetle hasn't eaten an ant in 8 turns.
//the grid, row, column and a boolean value are the parameters of this function
//if the boolean value (ans) is true, it deletes the beetle at that position
static void beetleStarveHelper(Creature *grid[][10], int i, int j, bool ans)
{
    if (ans)
    {
        //if the boolean value (ans) is true, the beetle at that position is deleted and the pointer is pointed to nullptr
        delete grid[i][j];
        grid[i][j] = nullptr;
    }
}

//breedHelper method creates a new creature in the appropriate box in the grid if possible
//the grid, row, column and direction are the parameters of this function
static void breedHelper(Creature *grid[][10], int i, int j, string direction)
{
    //if the creatire is an ant
    if (dynamic_cast<Ant*>(grid[i][j]))
    {
        //if the direction is north
        if (direction == "N")
        {
            //checking the gird boundary
            if (i-1 > -1)
            {
                //creates a new Ant at the position and calls the bred method to know that this ant is newly born in this turn
                grid[i-1][j] = new Ant();
                grid[i-1][j]->bred();
            }
        }
        //if the direction is east
        else if (direction == "E")
        {
            //checking the gird boundary
            if (j+1 < 10)
            {
                //creates a new Ant at the position and calls the bred method to know that this ant is newly born in this turn
                grid[i][j+1] = new Ant();
                grid[i][j+1]->bred();
            }
        }
        //if the direction is south
        else if (direction == "S")
        {
            //checking the gird boundary
            if (i+1 < 10)
            {
                //creates a new Ant at the position and calls the bred method to know that this ant is newly born in this turn
                grid[i+1][j] = new Ant();
                grid[i+1][j]->bred();
            }
        }
        //if the direction is west
        else if (direction == "W")
        {
            //checking the gird boundary
            if (j-1 > -1)
            {
                //creates a new Ant at the position and calls the bred method to know that this ant is newly born in this turn
                grid[i][j-1] = new Ant();
                grid[i][j-1]->bred();
            }
        }
    }
    //if the creatire is a beetle
    else if (dynamic_cast<Beetle*>(grid[i][j]))
    {
        //if the direction is north
        if (direction == "N")
        {
            //checking the gird boundary
            if (i-1 > -1)
            {
                //creates a new Beetle at the position and calls the bred method to know that this Beetle is newly born in this turn
                grid[i-1][j] = new Beetle();
                grid[i-1][j]->bred();
            }
        }
        //if the direction is east
        else if (direction == "E")
        {
            //checking the gird boundary
            if (j+1 < 10)
            {
                //creates a new Beetle at the position and calls the bred method to know that this Beetle is newly born in this turn
                grid[i][j+1] = new Beetle();
                grid[i][j+1]->bred();
            }
        }
        //if the direction is south
        else if (direction == "S")
        {
            //checking the gird boundary
            if (i+1 < 10)
            {
                //creates a new Beetle at the position and calls the bred method to know that this Beetle is newly born in this turn
                grid[i+1][j] = new Beetle();
                grid[i+1][j]->bred();
            }
        }
        //if the direction is west
        else if (direction == "W")
        {
            //checking the gird boundary
            if (j-1 > -1)
            {
                //creates a new Beetle at the position and calls the bred method to know that this Beetle is newly born in this turn
                grid[i][j-1] = new Beetle();
                grid[i][j-1]->bred();
            }
        }
    }
}

//emptySpace method checks and returns if the box in a particular direction is empty
//the grid, row, column and the direction are the parameters of this function
static bool emptySpace(Creature* grid[][10], int i, int j, string direction)
{
    //if the direction is north
    if (direction == "N")
    {
        //checking the grid boundary
        if (i-1 > -1)
        {
            //if the position is not empty, return false
            if (grid[i-1][j])
            {
                return false;
            }
        }
        //if the position is not on the grid, return false because nothing can be created outside the grid
        else
        {
           return false;
        }
    }
    //if the direction is east
    else if (direction == "E")
    {
        //checking the grid boundary
        if (j+1 < 10)
        {
            //if the position is not empty, return false
            if (grid[i][j+1])
            {
                return false;
            }
        }
        //if the position is not on the grid, return false because nothing can be created outside the grid
        else
        {
           return false;
        }
    }
    //if the direction is south
    else if (direction == "S")
    {
        //checking the grid boundary
        if (i+1 < 10)
        {
            //if the position is not empty, return false
            if (grid[i+1][j])
            {
                return false;
            }
        }
        //if the position is not on the grid, return false because nothing can be created outside the grid
        else
        {
           return false;
        }
    }
    //if the direction is west
    else if (direction == "W")
    {
        //checking the grid boundary
        if (j-1 > -1)
        {
            //if the position is not empty, return false
            if (grid[i][j-1])
            {
                return false;
            }
        }
        //if the position is not on the grid, return false because nothing can be created outside the grid
        else
        {
           return false;
        }
    }
    //return true if the above condition returned false because that means that there is no creature at that spot and it is inside the grid
    return true;
}

//numAdjacentAnts method finds and returns the number of adjacent ants in both the orthogonal and diagonal directions
//the grid, row, and column are the parameters of this method
//the method checks the 8 boxes surrounding the box and if an ant is found there, the variable that
//keeps track of the number of adjacent ants that is initialized to 0 in the beginning
static int numAdjacentAnts(Creature *grid[][10], int i, int j)
{
    //initializing an int variable num to 0
    int num = 0;
    
    //if a creature is present at this position
    if (grid[i-1][j])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i-1 > -1) && (dynamic_cast<Ant*>(grid[i-1][j])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i+1][j])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i+1 < 10) && (dynamic_cast<Ant*>(grid[i+1][j])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i][j-1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((j-1 > -1) && (dynamic_cast<Ant*>(grid[i][j-1])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i][j+1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((j+1 < 10) && (dynamic_cast<Ant*>(grid[i][j+1])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i-1][j-1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i-1 > -1) && (j-1 > -1) && (dynamic_cast<Ant*>(grid[i-1][j-1])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i-1][j+1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i-1 > -1) && (j+1 < 10) && (dynamic_cast<Ant*>(grid[i-1][j+1])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i+1][j-1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i+1 < 10) && (j-1 > -1) && (dynamic_cast<Ant*>(grid[i+1][j-1])))
        {
            num++;
        }
    }
    //if a creature is present at this position
    if (grid[i+1][j+1])
    {
        //if the creature at this position is an ant, the varible num is imcremented by 1
        if ((i+1 < 10) && (j+1 < 10) && (dynamic_cast<Ant*>(grid[i+1][j+1])))
        {
            num++;
        }
    }
    //returns the number of adjacent ants
    return num;
}

//beetleFindDist method finds the distance from the beetle to the ant in a particular direction
//the grid, row, column and the direction are the parameters of the method
//the method checks every box in a direction from the beetle until it finds an ant and the distance is being kept track of.
//the number of adjacent ants to the ant is also found out using the numAdjacentAnts method and is added as a second digit to the distance.
//if there is no ant in a particular direction, the distance to the edge will be stored and returned as a negative number,
//for the move distance in the beetle class to identify that there was no ant in a particular direction
static int beetleFindDist(Creature *grid[][10], int i, int j, string direction)
{
    //declaring variables to keep track of the distance to the ant or the edge and the boolean flag to store if an ant was found
    bool flag;
    int c;
    //if the direction is north
    if (direction == "N")
    {
        //initializing the variables that keep track of the distance and presence of ant
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the north direction from the beetle to check if there is an ant in the way
        //and the distance to the ant or the edge if there is no ant
        for (int k = i-1; k > -1; k--)
        {
            //checks if there is a creature present at this position
            if (grid[k][j])
            {
                //if the creature in this position is an ant
                if (dynamic_cast<Ant*>(grid[k][j]))
                {
                    //if an ant is found, flag becomes true and c will store the distance to the ant as the first digit
                    //and the number of adjacent ants as the second digit. Also, it breaks the loop because
                    //if an ant is found, no other boxes in that direction needs to be checked
                    flag = true;
                    c = ((c * 10) + numAdjacentAnts(grid, k, j));
                    break;
                }
                //if the creature at this position is not an ant, the distance is increased by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature present in this position, the distance gets incremented by 1
            else
            {
                c++;
            }
        }
        //if there was an ant in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no ant in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //if the direction is east
    else if (direction == "E")
    {
        //initializing the variables that keep track of the distance and presence of ant
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the east direction from the beetle to check if there is an ant in the way
        //and the distance to the ant or the edge if there is no ant
        for (int k = j+1; k < 10; k++)
        {
            //checks if there is a creature present at this position
            if (grid[i][k])
            {
                //if the creature in this position is an ant
                if (dynamic_cast<Ant*>(grid[i][k]))
                {
                    //if an ant is found, flag becomes true and c will store the distance to the ant as the first digit
                    //and the number of adjacent ants as the second digit. Also, it breaks the loop because
                    //if an ant is found, no other boxes in that direction needs to be checked
                    flag = true;
                    c = ((c * 10) + numAdjacentAnts(grid, i, k));
                    break;
                }
                //if the creature at this position is not an ant, the distance is increased by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature present in this position, the distance gets incremented by 1
            else
            {
                c++;
            }
        }
        //if there was an ant in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no ant in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //if the direction is south
    else if (direction == "S")
    {
        //initializing the variables that keep track of the distance and presence of ant
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the south direction from the beetle to check if there is an ant in the way
        //and the distance to the ant or the edge if there is no ant
        for (int k = i+1; k < 10; k++)
        {
            //if there is a creature present at this position
            if (grid[k][j])
            {
                //if the creature in this position is an ant
                if (dynamic_cast<Ant*>(grid[k][j]))
                {
                    //if an ant is found, flag becomes true and c will store the distance to the ant as the first digit
                    //and the number of adjacent ants as the second digit. Also, it breaks the loop because
                    //if an ant is found, no other boxes in that direction needs to be checked
                    flag = true;
                    c = ((c * 10) + numAdjacentAnts(grid, k, j));
                    break;
                }
                //if the creature at this position is not an ant, the distance is increased by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, the distance is increased by 1
            else
            {
                c++;
            }
        }
        //if there was an ant in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no ant in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //if the direction is west
    else if (direction == "W")
    {
        //initializing the variables that keep track of the distance and presence of ant
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the west direction from the beetle to check if there is an ant in the way
        //and the distance to the ant or the edge if there is no ant
        for (int k = j-1; k > -1; k--)
        {
            //if there is a creature present in this location
            if (grid[i][k])
            {
                //if the creature present in this location is an ant
                if (dynamic_cast<Ant*>(grid[i][k]))
                {
                    //if an ant is found, flag becomes true and c will store the distance to the ant as the first digit
                    //and the number of adjacent ants as the second digit. Also, it breaks the loop because
                    //if an ant is found, no other boxes in that direction needs to be checked
                    flag = true;
                    c = ((c * 10) + numAdjacentAnts(grid, i, k));
                    break;
                }
                //if the creature at this position is not an ant, the distance is increased by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, the distance is increased by 1
            else
            {
                c++;
            }
        }
        //if there was an ant in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no ant in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //return value for the method if the direction was not north, south, east or west
    //only happens if the direction passed as an argument is invalid
    return 0;
}

//antFindDist method finds the distance from the ant to the beetle in a particular direction
//the grid, row, column and the direction are the parameters of the method
//the method checks every box in a direction from the ant until it finds a beetle and the distance is being kept track of.
//if there is no beetle in a particular direction, the distance to the edge will be stored  and returned as a negative number,
//for the move distance in the beetle class to identify that there was no ant in a particular direction
static int antFindDist(Creature *grid[][10], int i, int j, string direction)
{
    //declaring variables to keep track of the distance to the beetle or the edge and the boolean flag to store if a beetle was found
    bool flag;
    int c;
    
    //if the direction is north
    if (direction == "N")
    {
        //initializing the variables that keep track of the distance and presence of beetle
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the north direction from the ant to check if there is a beetle in the way
        //and the distance to the beetle or the edge if there is no beetle
        for (int k = i-1; k > -1; k--)
        {
            //if there is creature present in the position
            if (grid[k][j])
            {
                //if the creature present in the position is a beetle
                if (dynamic_cast<Beetle*>(grid[k][j]))
                {
                    //if a beetle is found, flag becomes true and it breaks the loop because
                    //if a beetle is found, no other boxes in that direction needs to be checked
                    flag = true;
                    break;
                }
                //if the creature in this position is not a beetle, then the distance is incremented by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, then the distance is incremented by 1
            else
            {
                c++;
            }
        }
        //if there was a beetle in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no beetle in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //if the direction is east
    else if (direction == "E")
    {
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the east direction from the ant to check if there is a beetle in the way
        //and the distance to the beetle or the edge if there is no beetle
        for (int k = j+1; k < 10; k++)
        {
            //if there is creature present in the position
            if (grid[i][k])
            {
                //if the creature present in the position is a beetle
                if (dynamic_cast<Beetle*>(grid[i][k]))
                {
                    //if a beetle is found, flag becomes true and it breaks the loop because
                    //if a beetle is found, no other boxes in that direction needs to be checked
                    flag = true;
                    break;
                }
                //if the creature in this position is not a beetle, then the distance is incremented by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, then the distance is incremented by 1
            else
            {
                c++;
            }
        }
        //if there was a beetle in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no beetle in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //if the direction is south
    else if (direction == "S")
    {
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the south direction from the ant to check if there is a beetle in the way
        //and the distance to the beetle or the edge if there is no beetle
        for (int k = i+1; k < 10; k++)
        {
            //if there is creature present in the position
            if (grid[k][j])
            {
                //if the creature present in the position is a beetle
                if (dynamic_cast<Beetle*>(grid[k][j]))
                {
                    //if a beetle is found, flag becomes true and it breaks the loop because
                    //if a beetle is found, no other boxes in that direction needs to be checked
                    flag = true;
                    break;
                }
                //if the creature in this position is not a beetle, then the distance is incremented by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, then the distance is incremented by 1
            else
            {
                c++;
            }
        }
        //if there was a beetle in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no beetle in the way, the distance is returned as a negative number
        else{
            return (0-c);
        }
    }
    //if the direction is west
    else if (direction == "W")
    {
        c = 1;
        flag = false;
        
        //for loop to check all the boxes in the west direction from the ant to check if there is a beetle in the way
        //and the distance to the beetle or the edge if there is no beetle
        for (int k = j-1; k > -1; k--)
        {
            //if there is creature present in the position
            if (grid[i][k])
            {
                //if the creature present in the position is a beetle
                if (dynamic_cast<Beetle*>(grid[i][k]))
                {
                    //if a beetle is found, flag becomes true and it breaks the loop because
                    //if a beetle is found, no other boxes in that direction needs to be checked
                    flag = true;
                    break;
                }
                //if the creature in this position is not a beetle, then the distance is incremented by 1
                else
                {
                    c++;
                }
            }
            //if there is no creature in this position, then the distance is incremented by 1
            else
            {
                c++;
            }
        }
        //if there was a beetle in the way, the distance is returned as a positive number
        if (flag)
        {
            return c;
        }
        //if there was no beetle in the way, the distance is returned as a negative number
        else
        {
            return (0-c);
        }
    }
    //return value for the method if the direction was not north, south, east or west
    //only happens if the direction passed as an argument is invalid
    return 0;
}

//beetleMoveHelper method does the movement of beetles in the 2D array (grid)
//the grid, row, column and the direction are the parameters of the method
//the method checks the boundary and then moves the beetle to the box in the direction passed as the argument if that box is empty.
//the method checks the boundary and then moves the beetle to the box in the direction passed as the argument to
//replace the ant if that box had an ant. The beetle 'eats' the ant. The ant is deleted before the beetle moves to that box.
//the method does nothing if there is a beetle already in the box in the direction that is passes as the argument
void beetleMoveHelper(Creature *grid[][10], int j, int i, string direction)
{
    //if the direction is north
    if (direction == "N")
    {
        //checks the grid boundary
        if (j-1 > -1)
        {
            //if the box in the north is empty, the beetle is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the beetle has now moved in this turn
            if (grid[j-1][i] == nullptr)
            {
                grid[j-1][i] = grid[j][i];
                grid[j-1][i]->moved();
                grid[j][i] = nullptr;
            }
            //if the box in the north had an ant in that box, the ant is deleted and then the beetle is moved to that box and
            //then previous box is pointed to nullptr
            //the moved and ate method are called to report that the beetle has moved and eaten an ant in this turn
            else if (dynamic_cast<Ant*>(grid[j-1][i]))
            {
                delete grid[j-1][i];
                grid[j-1][i] = grid[j][i];
                grid[j-1][i]->moved();
                grid[j-1][i]->ate();
                grid[j][i] = nullptr;
                
            }
        }
    }
    //if the direction is south
    else if (direction == "S")
    {
        //checking the grid boundary
        if (j+1 < 10)
        {
            //if the box in the south is empty, the beetle is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the beetle has now moved in this turn
            if (grid[j+1][i] == nullptr)
            {
                grid[j+1][i] = grid[j][i];
                grid[j+1][i]->moved();
                grid[j][i] = nullptr;
            }
            //if the box in the south had an ant in that box, the ant is deleted and then the beetle is moved to that box and
            //then previous box is pointed to nullptr
            //the moved and ate method are called to report that the beetle has moved and eaten an ant in this turn
            else if (dynamic_cast<Ant*>(grid[j+1][i]))
            {
                delete grid[j+1][i];
                grid[j+1][i] = grid[j][i];
                grid[j+1][i]->moved();
                grid[j+1][i]->ate();
                grid[j][i] = nullptr;
            }
        }
    }
    //if the direction is west
    else if (direction == "W")
    {
        //checking the grid boundary
        if (i-1 > -1)
        {
            //if the box in the west is empty, the beetle is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the beetle has now moved in this turn
            if (grid[j][i-1] == nullptr)
            {
                grid[j][i-1] = grid[j][i];
                grid[j][i-1]->moved();
                grid[j][i] = nullptr;
            }
            //if the box in the west had an ant in that box, the ant is deleted and then the beetle is moved to that box and
            //then previous box is pointed to nullptr
            //the moved and ate method are called to report that the beetle has moved and eaten an ant in this turn
            else if (dynamic_cast<Ant*>(grid[j][i-1]))
            {
                delete grid[j][i-1];
                grid[j][i-1] = grid[j][i];
                grid[j][i-1]->moved();
                grid[j][i-1]->ate();
                grid[j][i] = nullptr;
            }
        }
    }
    //if the direction is east
    else if (direction == "E")
    {
        //checking the grid boundary
        if (i+1 < 10)
        {
            //if the box in the east is empty, the beetle is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the beetle has now moved in this turn
            if (grid[j][i+1] == nullptr)
            {
                grid[j][i+1] = grid[j][i];
                grid[j][i+1]->moved();
                grid[j][i] = nullptr;
            }
            //if the box in the east had an ant in that box, the ant is deleted and then the beetle is moved to that box and
            //then previous box is pointed to nullptr
            //the moved and ate method are called to report that the beetle has moved and eaten an ant in this turn
            else if (dynamic_cast<Ant*>(grid[j][i+1]))
            {
                delete grid[j][i+1];
                grid[j][i+1] = grid[j][i];
                grid[j][i+1]->moved();
                grid[j][i+1]->ate();
                grid[j][i] = nullptr;
            }
        }
    }
}

//antMoveHelper method does the movement of ants in the 2D array (grid)
//the grid, row, column and the direction are the parameters of the method
//the method checks the boundary and then moves the ant to the box in the direction passed as the argument if that box is empty.
//the method does nothing if there is a beetle already in the box in the direction that is passes as the argument
void antMoveHelper(Creature *grid[][10], int j, int i, string direction)
{
    //if the direction is north
    if (direction == "N")
    {
        //checks the grid boundary
        if (j-1 > -1)
        {
            //if the box in the north is empty, the ant is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the ant has now moved in this turn
            if (grid[j-1][i] == nullptr)
            {
                grid[j-1][i] = grid[j][i];
                grid[j-1][i]->moved();
                grid[j][i] = nullptr;
            }
        }
    }
    //if the direction is south
    else if (direction == "S")
    {
        //checks the grid boundary
        if (j+1 < 10)
        {
            //if the box in the south is empty, the ant is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the ant has now moved in this turn
            if (grid[j+1][i] == nullptr)
            {
                grid[j+1][i] = grid[j][i];
                grid[j+1][i]->moved();
                grid[j][i] = nullptr;
            }
        }
    }
    //if the direction is west
    else if (direction == "W")
    {
        //checks the grid boundary
        if (i-1 > -1)
        {
            //if the box in the west is empty, the ant is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the ant has now moved in this turn
            if (grid[j][i-1] == nullptr)
            {
                grid[j][i-1] = grid[j][i];
                grid[j][i-1]->moved();
                grid[j][i] = nullptr;
            }
        }
    }
    //if the direction is east
    else if (direction == "E")
    {
        //checks the grid boundary
        if (i+1 < 10)
        {
            //if the box in the east is empty, the ant is moved to that box and then the previous box is pointed to nullptr
            //the moved method is used to report that the ant has now moved in this turn
            if (grid[j][i+1] == nullptr)
            {
                grid[j][i+1] = grid[j][i];
                grid[j][i+1]->moved();
                grid[j][i] = nullptr;
            }
        }
    }
}

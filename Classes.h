//problem #3 on page 695

#ifndef CLASSES_H
#define CLASSES_H
#include "Common.h"
#include <vector>
#include <iostream>
/*
  This file contains the following classes: Organism(superclass), Doodle(subclass), Ant(subclass), and Grid. 
  This file only contains the declarations of the class functions. The definitions are in the file Classes.cpp.
  The classes of this file can access all the variables from Common.h.
*/

//class prototypes
class Grid;
class Organism;
class Ant;
class Doodle;

typedef Organism* oPtr;
typedef Grid* gPtr;


class Organism
{
  public:
    //constructors
    Organism(); 
    Organism(gPtr game, int x, int y); 
    virtual ~Organism();

    //variables
    int coord_x; 
    int coord_y;
    int num_steps;
    int steps_to_breed;
    gPtr ongoing;

    //virtual functions
    virtual void move();
    virtual void breed() = 0;
    virtual bool willStarve();
    virtual std::vector<int> possMoves(int x, int y);
    virtual bool canEat() = 0;
    virtual char getChar() = 0;

    //helper functions
    void getLocation(int& x, int& y, int z) const;
    bool checkLocation(int x, int y) const;  
};

class Ant : public Organism
{
  public:
    //constructors
    Ant();
    Ant(gPtr game, int x, int y);
    ~Ant();

    //functions from superclass
    void breed();
    bool canEat() {return false;}
    char getChar() {return 'o';}

    //variables
    static int num_ants;
};

class Doodle : public Organism
{
  public:
    //constructors
    Doodle();
    Doodle(gPtr game, int x, int y);
    ~Doodle();

    //functions from superclass
    void move();
    void breed();
    bool willStarve();
    bool canEat() {return true;}
    char getChar() {return 'X';}
    std::vector<int> possMoves(int x, int y) const;

    //variables
    int hunger_till_death;
    static int num_doodles;    
};

class Grid
{
  friend class Organism;
  friend class Ant;
  friend class Doodle;

  public:
    //constructors
    Grid();
    ~Grid();

    //member functions
    void genGrid() const;
    void begin();
    void timeStep();
    
    //variables
    oPtr array[GRID_SIZE][GRID_SIZE];
    int num_steps; //counts each time step

    //helper function
    int chooseDirection(int first, int last) const;
    
};


#endif //CLASSES_H
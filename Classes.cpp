//problem #3 on page 695

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include "Classes.h"

using namespace std;

/*
  This file contains all the member function definitions of the following classes: Organism, Ant, Doodle, and Grid. 
  Common.h is already included in Classes.h, so its variables can be accessed in this file.
  The functions are separated by class by comments to avoid confusion.
*/

//static ints from Ant and Doodle classes
int Ant::num_ants = 0;
int Doodle::num_doodles = 0;


//member functions of class Organism
Organism::Organism()
{
  coord_x = 0;
  coord_y = 0;
  num_steps = 0;
  steps_to_breed = 0;
  ongoing = nullptr;  
}

Organism::~Organism(){};

Organism::Organism(gPtr game, int x, int y)
{
  this->ongoing = game;
  num_steps = ongoing->num_steps;
  steps_to_breed = 0;
  this->coord_x = x;
  this->coord_y = y;
  
}

void Organism::move() 
{
  int z, copy_x, copy_y;
  
  if(num_steps == ongoing->num_steps)
  {
    return;
  }
  
  num_steps = num_steps + 1;
  steps_to_breed = steps_to_breed - 1;

  z = ongoing->chooseDirection(UP, RIGHT);

  copy_x = coord_x;
  copy_y = coord_y;

  getLocation(copy_x, copy_y, z);

  if(checkLocation(copy_x, copy_y) == true)
  {
    if(ongoing->array[copy_x][copy_y] != nullptr)
    {
      return;
    }
    
    ongoing->array[coord_x][coord_y] = nullptr;
    ongoing->array[copy_x][copy_y] = this;
  
      coord_x = copy_x;
      coord_y = copy_y;
  }  
}

bool Organism::willStarve()
{
  return false;
}

std::vector<int> Organism::possMoves(int x, int y)
{
  std::vector<int> m;
  int copy_x, copy_y;
  
  for(int i=UP; i<=RIGHT; i++)
    {
      copy_x = x;
      copy_y = y;
      getLocation(copy_x, copy_y, i);

      if(checkLocation(copy_x, copy_y) == false)
      {
        continue;
      }
        if(ongoing->array[copy_x][copy_y] == nullptr)
        {
          m.push_back(i);
        } 
    }
  
  return m;
}

void Organism::getLocation(int& x, int& y, int z) const
{
  if(z==UP)
  {
    y = y - 1;
  }
  if(z==DOWN)
  {
    y = y + 1;
  }
  if(z==LEFT)
  {
    x = x - 1;
  }
  if(z==RIGHT)
  {
    x = x + 1;
  }
}

bool Organism::checkLocation(int x, int y) const
{
  return((x>=0) && (x<GRID_SIZE) && (y>=0) && (y<GRID_SIZE));
   
}



//member functions of class Ant
Ant::Ant() : Organism()
{
  steps_to_breed = TIME_TO_BREED_ANT;
  num_ants++;
}

Ant::~Ant()
{
  num_ants--;
}

Ant::Ant(gPtr game, int x, int y) : Organism(game, x, y)
{
  steps_to_breed = TIME_TO_BREED_ANT;
  num_ants++;
}

void Ant::breed()
{
  std::vector<int> c;
  int a, copy_x, copy_y;
  
  if(steps_to_breed>0)
  {
    return;
  }

    c = possMoves(coord_x, coord_y);

    if(c.size() == 0)
    {
      return;
    }
      a = c[ongoing->chooseDirection(0, (c.size()-1))];
      copy_x = coord_x;
      copy_y = coord_y;

      getLocation(copy_x, copy_y, a);
    
      ongoing->array[copy_x][copy_y] = new Ant(ongoing, copy_x, copy_y);

      steps_to_breed = TIME_TO_BREED_ANT;    
}



//member functions of class Doodle
Doodle::Doodle() : Organism()
{
  steps_to_breed = TIME_TO_BREED_DOODLE;
  hunger_till_death = TIME_TO_STARVE;
  num_doodles++;
}

Doodle::~Doodle()
{
  num_doodles--;
}

Doodle::Doodle(gPtr game, int x, int y) : Organism(game, x, y)
{
  steps_to_breed = TIME_TO_BREED_DOODLE;
  hunger_till_death = TIME_TO_STARVE;
  num_doodles++;
}

bool Doodle::willStarve()
{
  return hunger_till_death = 0;
}

void Doodle::move()
{
  std::vector<int> d;
  int j, copy_x, copy_y;
  
  if(num_steps != ongoing->num_steps)
  {
    d = possMoves(coord_x, coord_y); //possMovesAnts
    if(d.size() == 0)
    {
      Organism::move();
      
      hunger_till_death = hunger_till_death - 1;

      return;
    }
    else
    {
      num_steps = num_steps + 1;
      hunger_till_death = TIME_TO_STARVE;
      j = d[ongoing->chooseDirection(0, (d.size()-1))];

      copy_x = coord_x;
      copy_y = coord_y;

      getLocation(copy_x, copy_y, j);
      if(ongoing->array[copy_x][copy_y]!=NULL)
      {
        delete ongoing->array[copy_x][copy_y];
      }
      //delete ongoing->array[copy_x][copy_y];
      ongoing->array[copy_x][copy_y] = this;
      ongoing->array[coord_x][coord_y] = NULL;
      //cout<<"doodle move from "<<coord_x<<", "<<coord_y<<" to "<<copy_x<<", "<<copy_y<<endl;

      coord_x = copy_x;
      coord_y = copy_y;
      
    }   
  }
  else
  {
    return;
  }
}

void Doodle::breed()
{
  std::vector<int> c;
  int a, copy_x, copy_y;
  
  if(steps_to_breed>0)
  {
    return;
  }
  c = possMoves(coord_x, coord_y);

  if(c.size() == 0)
    {
      return;
    }
    a = c[ongoing->chooseDirection(0, (c.size()-1))];
    copy_x = coord_x;
    copy_y = coord_y;

    getLocation(copy_x, copy_y, a);
    
    ongoing->array[copy_x][copy_y] = new Doodle(ongoing, copy_x, copy_y);

    steps_to_breed = TIME_TO_BREED_DOODLE;
   
}

std::vector<int> Doodle::possMoves(int x, int y) const
{
  std::vector<int> d;
  int copy_x, copy_y;

  for(int i=UP; i<=RIGHT; i++)
    {
      copy_x = x;
      copy_y = y;

      getLocation(copy_x, copy_y, i);

      if(checkLocation(copy_x, copy_y) == false)
      {
        continue;
      }
        if(ongoing->array[copy_x][copy_y] == nullptr)
        {
          continue;
        }
  
          if(!ongoing->array[copy_x][copy_y]->canEat())
          {
            d.push_back(i);
          }
        }
  
  return d;
}


//member functions of class Grid
Grid::Grid()
{
  srand(time(NULL));
  num_steps = 0;

  for(int i=0; i<GRID_SIZE; i++)
    {
      for(int j=0; j<GRID_SIZE; j++)
        {
          array[i][j]=nullptr;
        }
    }
}

Grid::~Grid()
{
  for(int i=0; i<GRID_SIZE; i++)
  {
      for(int j=0; j<GRID_SIZE; j++)
      {
          if(array[i][j] != nullptr)
          {
            delete array[i][j];
            
          }
        }
  }
}

void Grid::genGrid() const
{
  cout<<"Timestep: "<<num_steps+1<<", Number of Ants: "<<Ant::num_ants<<", Number of Doodles: "<<Doodle::num_doodles<<endl<<endl;
  
  for(int i=0; i<GRID_SIZE; i++)
    {
      for(int j=0; j<GRID_SIZE; j++)
        {
          if(array[i][j] == nullptr)
          {
            cout<<'-';
          }
          else
          {
            cout<<array[i][j]->getChar();
          }

        }
      cout<<endl;
    }
}

void Grid::begin()
{
  int a, b, num_ants=0, num_doodles=0;

  while(num_doodles < NUM_DOODLES)
  {
    a = chooseDirection(0, (GRID_SIZE-1));
    b = chooseDirection(0, (GRID_SIZE-1));
    if(array[a][b]!=nullptr)
    {
      continue;
    } 
    array[a][b] = new Doodle(this, a, b);
    num_doodles = num_doodles + 1;
  }

  while(num_ants < NUM_ANTS)
  {
    a = chooseDirection(0, (GRID_SIZE-1));
    b = chooseDirection(0, (GRID_SIZE-1));
    if(array[a][b]!=nullptr)
    {
      continue;
    }
    array[a][b] = new Ant(this, a, b);
    num_ants = num_ants + 1;
  }
}

int Grid::chooseDirection(int first, int last) const
{
  int j;
  j = rand() % (last - first + 1) + first;

  return j;
}

void Grid::timeStep()
{
  num_steps = num_steps + 1;

  for(int i=0; i<GRID_SIZE; i++)
  {
      for(int j=0; j<GRID_SIZE; j++)
      {
          if(array[i][j] == nullptr)
          {
            continue;
          }
          array[i][j]->move();   
      }
  }
    
 for(int i=0; i<GRID_SIZE; i++)
  {
      for(int j=0; j<GRID_SIZE; j++)
      {
          if(array[i][j] == nullptr)
          {
            continue;
          }
        array[i][j]->breed();    
      }
  }
  
  for(int i=0; i<GRID_SIZE; i++)
  {
      for(int j=0; j<GRID_SIZE; j++)
      {
          if(array[i][j] == nullptr)
          {
            continue;
          }
          if(array[i][j]->willStarve())
          {
            delete array[i][j];
            array[i][j] = NULL;
          }
        }
  }

}




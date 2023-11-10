//problem #3 on page 695

#ifndef COMMON_H
#define COMMON_H

/*
  This file places all the const values to be shared among the classes in one place. All of the const values are labeled to avoid confusion. 
  Classes.h will include Common.h to access the const data.
*/

const int GRID_SIZE = 20; //for 20X20 array

const int NUM_ANTS = 100; //starting # ants
const int NUM_DOODLES = 5; //starting # doodles

const int ANT = 1; //# identifier for ant
const int DOODLE = 2; //# identifier for doodle

const int TIME_TO_BREED_ANT = 3; //# timesteps for ant to breed
const int TIME_TO_BREED_DOODLE = 8; //# timesteps for doodle to breed

const int TIME_TO_STARVE = 3; //# timesteps for doodle to starve

const int UP = 1; //direction # for up
const int DOWN = 2; //direction # for down
const int LEFT = 3; //direction # for left
const int RIGHT = 4; //direction # for right


#endif //COMMON_H
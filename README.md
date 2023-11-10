# Predator-Prey-Simulation
This project simulates a predator-prey simulation. The ants are the prey (represented by "o") and the doodlebugs are the predators (represented by "X"). Each timestamp generates an predator-prey grid, as well as a current count of the total number of ants and doodlebugs. 

The programming language used is C++. A combination of object-oriented programming and polymorphism concepts are used to create this simulation. 

**Some Things to Note**:
-   Doodlebugs can breed after 8 timesteps and ants can breed after 3 timesteps
-   Doodlebugs will starve after 3 timesteps (if an ant has not been consumed)
-   The doodlebug must be directly next to an ant to consume it
-   At the start, there are 100 ants and 5 doodlebugs
-   Each organism can move up, down, left, or right

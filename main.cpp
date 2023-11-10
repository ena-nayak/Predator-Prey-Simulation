//problem #3 on page 695

#include <iostream>
#include "Classes.h"

using namespace std;

int main() 
{
  char x;

  cout<<"You've entered the Doodlebug vs. Ant simulation."<<endl<<"\nThis simulation starts with 100 ants(prey) and 5 doodlebugs(predators). The 'X's represent the doodlebugs, and the 'o's represent the ants."<<endl<<"\nWill the ants overpower the doodlebugs?? Or will the ants go extinct?? Enter the simulation to find out..."<<endl<<endl;

  cout<<"Press any character except 'q' to begin. Entering 'q' will end the simulation."<<endl;
  cin>>x;
  cout<<endl;

  Grid object1;
  
  if(x=='q')
  {
    cout<<"\nEnding simulation."<<endl<<"Goodbye..."<<endl;
    exit(1);
  }

  object1.begin();
  cout<<"Ants vs. Doodlebugs: Starting Simulation..."<<endl<<endl;
  object1.genGrid();

  cout<<"\nPress any character except 'q' to continue. Entering 'q' will end the simulation."<<endl;
  cin>>x;

  while(x!='q')
    {
      object1.timeStep();
      object1.genGrid();
      cout<<"\nPress any character except 'q' to continue. Entering 'q' will end the simulation."<<endl;
      cin>>x;
      cout<<endl;
    }

cout<<"\nThanks for your participation! Ending of simulation."<<endl<<"Goodbye..."<<endl;
  
return 0; 
  
}
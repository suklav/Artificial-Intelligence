//Draft:(not final) Caution!! Unstructured,incomplete and bad code ahead. ! hehe !
//-------------------------------------------------------------------------

//8 puzzle problem using A star algorithm.
//test2
#include<iostream>
#include<vector>
#include<list>
#include<math.h>

#define N 8

using namespace std;
typedef vector<int> myvec;
typedef list<myvec> state;

myvec goal;
goal.push_back(99);
goal.push_back(0);
goal.push_back(1);
goal.push_back(2);
goal.push_back(3);
goal.push_back(4);
goal.push_back(5);
goal.push_back(6);
goal.push_back(7);
goal.push_back(8);


int UP(myvec *puzzle, int posittion)
{
 
  if(position <=r-1)
    return -1;
    
  int temp;
  
  temp=puzzle[position];
  puzzle[position] =puzzle[position-r];
  puzzle[position-r]=temp;
}


int DOWN(myvec *puzzle, int posittion)
{
 
  if(position >=(N-r))
    return -1;
    
  int temp;
  
  temp = puzzle[position];
  puzzle[position] = puzzle[position+r];
  puzzle[position+r] = temp;
}

int LEFT(myvec *puzzle, int posittion)
{
 
  if(position%r==0)
    return -1;
    
  int temp;
  
  temp = puzzle[position];
  puzzle[position] = puzzle[position-1];
  puzzle[position-1] = temp;
}
 
int manhatten(myvec *puzzle)
{
 myvec dist;
 int diff=0;
 int cnt=0;
 
 for(std::vector<int>::iterator ar=puzzle.begin(); ar!=puzzle.end(); ++ar)
    {
       diff=ar-cnt;
       dist.push_back(diff);
       cnt++;
             
    }
 
}

int Calculate_h_value(myvec *puzzle)
{
  int h=0;
  
  for(std::vector<int>::iterator ar=puzzle.begin(),std::vector<int>::iterator ar2=goal.begin(); ar!=puzzle.end(),ar2!=goal.end(); ++ar,++ar2)
    {
       if(ar!= ar2)
       {
         h++;
       }
    
    }
  
  return 0;
  
} 

 
 
int solve(myvec *puzzle)
{
  vector temp;
  
  while(puzzle!=goal)
  {
   calculate_h_value(puzzle);
   
  
  }
  
  
  temp=puzzle[
  



}



int main()
{
  int r;
  r=sqrt(N+1);

 myvec puzzle;
 
 takeinput(puzzle);
 solve(puzzle);
  
  
 return 0;
}

//test




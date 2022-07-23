//Nqueens solutions using a BFS search of the state-space tree
//the myvec vector records the row numbers only

#include<iostream>
#include<vector>

using namespace std;

void solvenqueen(int n);
bool ifsafe(int n, vector<int> &myvec);

int main()
{
    int n;
    char c;

    cout<<"Enter an integer N for the NxN board: ";
    cin>>n;

    solvenqueen(n);
    return 0;
}


bool ifsafe(int n, vector<int> &myvec)
{
     int row = myvec.back();
     int col = myvec.size() - 1;
    //if the queen is being placed outside the nxn board
    if(row >= n)
    	return false;

    // otherwise check if it's being attacked by other queens
    for(unsigned int i = 0; i < myvec.size() - 1; i++)
        {
         // if a queen is already there in the same row
         if (row == myvec[i])
    			return false;
    
         // if diagonally it is attacking postion
         if (abs(row - myvec[i]) == abs(col - int(i)))
    			return false;
         }
     return true;
}

void solvenqueen(int n)
{
     //the myvec vector records the row numbers only
    
     vector<int> myvec;
     
     int row,flag=0,total=0;
     //total is used to count the total number of solutions
     //flag is used to check if all possible solutions have been found
     
     //the initial queen is placed
     myvec.push_back(0);


     // Loop until one solutions is found
     while(!flag)
     {
        // if the last queen is not in a safe place
        if(!ifsafe(n,myvec))
         {
             
             //two cases: 1)out of bound, 2) last pos was bad
             
             row=myvec.back(); // Record last row tried
    
             // backtrack to last valid position without recursion(using loop) 
             if(row>=n)
             {
              do
               {
                   if (myvec.size()>1) //all solutions have not been found
                    {
                             myvec.pop_back(); // last pos removed
                             row = myvec.back();// now, work with new last position
                             myvec.pop_back();  // since this was the las bad.. removing this and 
                             myvec.push_back(row+1);  // trying with the next row
                             row = myvec.back(); // the do-while will check if it's out of bound
                    }  
                    
                    else//found all solutions
                    {
                        flag=1;
                        break;
                    }
       
                         // untill it comes within the bound
                 } while (myvec.back() >= n);
             }
             // second case: within bound but bad position
              else  
                 {
                    myvec.pop_back();
                    myvec.push_back(row + 1); //next row
                 }
           }
           
        //if last queen is safe
        else 
         {
            //goal-test
            if(myvec.size() == n)
             {
                //break;
                total++;
                row = myvec.back();
                myvec.pop_back();
                myvec.push_back(row + 1);
             }
            // if not a goal.. proceed with next column's initial row
             else myvec.push_back(0);
          }
    }
    
    
    cout<<"Total no of sols: "<<total;
}

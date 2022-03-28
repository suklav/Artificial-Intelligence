//c++ program to find out the number of nodes generated in a depth-limited search and in an iterative deepening search to depth d with branching factor b.
// ** And to find the overhead.


#include <iostream>
#include<math.h>

using namespace std;

int main()
{
    int b,d;
    unsigned long long int ids=0,dls=0;
    cout<<"Enter the value of b:";
    cin>>b;
    cout<<"Enter the value of d:";
    cin>>d;
    int j=d;
    for(int i=0;i<=d;i++)
    {
        dls+= pow(b,i);         // for dls
        ids += (j+1)*pow(b,i);  //for ids
        j--;
    }
    
    cout<<"DLS: "<<dls<<endl;
    cout<<"IDS: "<<ids<<endl;
    float r;
    r=float(ids-dls);
    r=r/dls;
    r*=100;
    cout<<"Overhead: "<<r<<endl;
    
    return 0;
}

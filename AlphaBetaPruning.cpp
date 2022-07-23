
#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<ctime>

using namespace std;



typedef struct node          // Type of a node in the adjacency list.
{
    int node_no;
    int utility;
    int current_m;		//current current_m
    int alpha;
    int beta;
    struct node *next;      // Pointer to the next adjacent node.
} node;                     // Type name ’node’

typedef struct          // Type of a graph
{
    int vN;         // Number of vertices n: {0, 1, ..., n-1}
    node *vA;      // Pointer to the header array (n elements) of
} graph;            // node list


static int prunedNodes=0;
int global_x,global_y;

//for the leaf nodes, random utility value from 0 - 99 and build tree
void buildTree(graph *g,int N,int b,int current_m);
int alphaBetaPrune(graph *g,node *curr_node,int m,int b,int alpha,int beta);
void play_against_optimal_opponent(graph *g,node *curr_top,int curr_m);
int minimax(graph *g,node *rt);



void buildTree(graph *g,int N,int b,int current_m)
{
    int start,start_temp,temp,len,cnt,i=0;
    len=1;
    cnt=0;
    start_temp=0;
    
    /*
    //error checking
    for(i=0;i<N;i++)
    {
     if(g[i].vA)
      cout<<"check1";
      
     cout<<g[i].vN;
      
    }
        
    */
    
   
    while(i<N)
    {
        g[i].vA=NULL;
        g[i].vN=i;
        i++;
    }
    
     /*
    //error checking
    for(i=0;i<N;i++)
    {
     if(g[i].vA)
      cout<<"check1";
      
     cout<<g[i].vN;
      
    }
        
    */
    
    start=start_temp;
    //cout<<start<<start_temp;
    
    temp=N-pow(b,current_m);    
    //cout<<temp;
    
    i=1;
    while(i<=N-1)
    {
        node* temp_node = (node*) calloc(1,sizeof(node));
        
        temp_node->next = NULL;
        
        start_temp++;
        
        
        temp_node->node_no = start_temp;
        
        temp_node->current_m=len;

   /*
    //error checking
    
     if(temp)
      cout<<"check1";
              
    */


        if(start_temp>=temp)
            temp_node->utility=rand()%99;
        node* temp_node2=g[cnt].vA;
        
        
        if(temp_node2==NULL)
            g[cnt].vA=temp_node;  
        else
        {
            node *x=NULL;
            while(temp_node2!=NULL)
            {
                x=temp_node2;
                temp_node2=temp_node2->next;
            }
            x->next=temp_node;
        }
        
        
        
        if(start_temp==start+pow(b,len))
        {
            len++;
            start=start_temp;
        }
        
        if(i%b==0)
            cnt++;
i++;
    }
}


int minimax(graph *g,node *rt)
{
   static int check=0;
   static int flag=0;
   
   check=rt->node_no;
   
   
   /*
    //error checking
    
     if(g)
      cout<<"check1";
              
    */

   
   
   //base condition
    if(g[rt->node_no].vA==NULL)
        return rt->utility;
    
    else
    {
     node *temp=g[rt->node_no].vA;
     
     int util=minimax(g,temp);
     
     temp=temp->next;
	
	 /*
         //error checking
         if(temp)
           cout<<"check1";
        */

        while(temp)
        {
        
            int k=minimax(g,temp);
            
            if(rt->current_m%2==0 && util<k)
            {
            
              //check++;
                util=k;
                check--;
               //cout<<"\nexecuted";
               
            }
            
            
            else if(rt->current_m%2!=0 && util>k)
            {
            
                check++;
                util=k;
                //cout<<"\nexecuted2";
                
            }
            
            
            temp=temp->next;
            flag++;
            
        }
        
        rt->utility=util;

        return util;
        
    }
}





int alphaBetaPrune(graph *g,node *curr_node,int m,int b,int alpha,int beta)
{
    
    int ret_val,count1,count2;
    
    cout<<"-->"<<curr_node->node_no;
    if(g[curr_node->node_no].vA==NULL)
        return curr_node->utility;

    else
    {
	count1++;
        node * temp_node=g[curr_node->node_no].vA;

        temp_node->alpha=alpha;
        temp_node->beta=beta;
 
        int ret_val=alphaBetaPrune(g,temp_node,m,b,temp_node->alpha,temp_node->beta);  
  
        if((curr_node->current_m%2==0 || curr_node->current_m==0)&& ret_val>curr_node->alpha)
            curr_node->alpha=ret_val;

        else if(curr_node->current_m%2!=0 && ret_val<curr_node->beta)
            curr_node->beta=ret_val;


        temp_node=temp_node->next;
        if(temp_node)
        {
            count2++;
            temp_node->alpha=curr_node->alpha;
            temp_node->beta=curr_node->beta;

        }

        while(temp_node)
        {
            if(curr_node->alpha<curr_node->beta)
            {
                int returned_val=alphaBetaPrune(g,temp_node,m,b,curr_node->alpha,curr_node->beta); 

                if(curr_node->current_m%2==0 && ret_val<returned_val)
                    ret_val=returned_val;

                else if(curr_node->current_m%2!=0 && ret_val>returned_val)
                    ret_val=returned_val;

                if(curr_node->current_m%2==0 && ret_val>curr_node->alpha)
                    curr_node->alpha=ret_val;
                    
                else if(curr_node->current_m%2!=0 && ret_val<curr_node->beta)
                    curr_node->beta=ret_val;

            }
            else
            {
               
                int newv;
                newv=(m-(curr_node->current_m));

		int vall=b*((pow(b,m-newv)-1)/(b-1))+1;
		prunedNodes+=vall;
		cout<<"\nPruned Branch at node:"<<curr_node->node_no<<endl;
            }
            temp_node=temp_node->next;
            if(temp_node)
            {
                temp_node->alpha=curr_node->alpha;
                temp_node->beta=curr_node->beta;

            }
        }

        curr_node->utility=ret_val;
        return ret_val;
    }
}




void best_least_successor(graph *g,int current)   
{

    int least,best,lesser,better,temp_node;
    node *n;
    n=g[current].vA;
    least=n->utility;
    best=n->utility;
    lesser=n->node_no;
    better=n->node_no;
    temp_node=n->current_m;
    n=n->next;

    while(n)
    {
        if(least>n->utility)
        {
            least=n->utility;
            lesser=n->node_no;
        }
        
        if(best<n->utility)
        {
            best=n->utility;
            better=n->node_no;
        }
        
        n=n->next;
    }

    global_x=lesser;
    global_y=better;
    
    
}


void play_against_optimal_opponent(graph *g,node *curr_top,int curr_m)
{

  int i=1,temp=curr_top->node_no;


  while(i<=curr_m)
    {
        best_least_successor(g,temp);

        if(i%2!=0)
        {
            cout<<"MAX->"<<global_y<<" ";
            if(g[global_y].vA==NULL)
                break;
            else
            	temp=global_y;
                
        }
        else if(i%2==0)
        {
            cout<<"MIN->"<<global_x<<" ";
            if(g[global_x].vA!=NULL)
                temp=global_x;
            else
                break;
        }
       i++;
    }
}

int main()
{
    srand(time(NULL)); 
    int b,m,N,v,minimax_var;
    cout<<"Enter branching factor(b) and game tree depth(m) :\n";
    cin>>b>>m;
    
    if(m<=1)
    {
        cout<<"M cannot be <=1.";
        return 1;
    }
    
    N=b*((pow(b,(--m))-1)/(b-1))+1;
    cout<<"\nApplying Alpha beta pruning, vertex visiting order: \n";
    
    graph g[N];
    node top;
    buildTree(g,N,b,m);


    top.current_m=top.node_no=0;
    
    
    top.alpha=-(INT_MAX-325);
    top.beta=(INT_MAX-325);


    v=alphaBetaPrune(g,&top,m,b,-(INT_MAX-325),(INT_MAX-325));

    minimax_var=minimax(g,&top);

    cout<<endl<<"\nThe optimal path is as follows:"<<endl;
    play_against_optimal_opponent(g,&top,m);
    cout<<"\nNo of Pruned nodes: "<<prunedNodes;
    cout<<"\nMinimax value of root node: "<<minimax_var<<endl;


    return 0;
}





/*
OUTPUT:

suklav@suklav:~/git-workspace/AI$ g++ AlphaBetaPruning.cpp 
suklav@suklav:~/git-workspace/AI$ ./a.out 
Enter branching factor(b) and game tree depth(m) :
2
5

Applying Alpha beta pruning, vertex visiting order: 
-->0-->1-->3-->7-->15-->16-->8-->17
Pruned Branch at node:8
-->4-->9-->19-->20-->10-->21-->22-->2-->5-->11-->23-->24-->12-->25-->26-->6-->13-->27-->28
Pruned Branch at node:6


The optimal path is as follows:
MAX->2 MIN->5 MAX->11 MIN->23 
No of Pruned nodes: 22
Minimax value of root node: 26
suklav@suklav:~/git-workspace/AI$ g++ AlphaBetaPruning.cpp 
suklav@suklav:~/git-workspace/AI$ ./a.out 
Enter branching factor(b) and game tree depth(m) :
2
5

Applying Alpha beta pruning, vertex visiting order: 
-->0-->1-->3-->7-->15-->16-->8-->17-->18-->4-->9-->19-->20-->10-->21-->22-->2-->5-->11-->23-->24-->12-->25
Pruned Branch at node:12
-->6-->13-->27-->28-->14-->29-->30

The optimal path is as follows:
MAX->1 MIN->3 MAX->8 MIN->17 
No of Pruned nodes: 15
Minimax value of root node: 41
suklav@suklav:~/git-workspace/AI$ g++ AlphaBetaPruning.cpp 
suklav@suklav:~/git-workspace/AI$ ./a.out 
Enter branching factor(b) and game tree depth(m) :
2
5

Applying Alpha beta pruning, vertex visiting order: 
-->0-->1-->3-->7-->15-->16-->8-->17-->18-->4-->9-->19-->20
Pruned Branch at node:4
-->2-->5-->11-->23-->24-->12-->25
Pruned Branch at node:12
-->6-->13-->27-->28-->14-->29-->30

The optimal path is as follows:
MAX->2 MIN->6 MAX->14 MIN->30 
No of Pruned nodes: 22
Minimax value of root node: 27
suklav@suklav:~/git-workspace/AI$ g++ AlphaBetaPruning.cpp 
suklav@suklav:~/git-workspace/AI$ ./a.out 
Enter branching factor(b) and game tree depth(m) :
2
5

Applying Alpha beta pruning, vertex visiting order: 
-->0-->1-->3-->7-->15-->16-->8-->17-->18-->4-->9-->19-->20
Pruned Branch at node:4
-->2-->5-->11-->23-->24-->12-->25
Pruned Branch at node:12

Pruned Branch at node:2


The optimal path is as follows:
MAX->1 MIN->3 MAX->8 MIN->18 
No of Pruned nodes: 25
Minimax value of root node: 36
suklav@suklav:~/git-workspace/AI$ 




*/

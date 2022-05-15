//Name: SUKLAV GHOSH, ROLL: 2021SMCS005, 
//PROBLEM: Write a C program to count the connected components of an undirected graph.


#include<stdio.h>
#include<stdlib.h>


typedef struct node{ 
	int vertex; 
	struct node *next; 
} node; 

typedef struct{
	int vN; 
	node **vA; 
} graph;


//initializes adjacency list
node **init_adj_list(graph g)
{
   if(g.vA)
      return g.vA;
   
   node** vA = (node**) calloc (g.vN,  sizeof(node*));
 
 
   for (int i = 0; i < g.vN; i++)
        vA[i] = NULL;
     
    //printf("Initialized Adjacency Lists!\n");
    return vA;
    
}

//creates a single node of type node
 node* create_node(int vertex) 
 {
    // Creates a LinkedList node to hold the vertex
    node* node1 = (node*) calloc(1, sizeof(node));
    node1->next = NULL;
    node1->vertex = vertex;
    
    return node1;
}

//adds edge to the adjacency list
void add_edge(graph g, int i, int j) {
    // Adds an edge connecting two vertices i and j
    if(!g.vA) 
    {
        printf("Adjacency Lists not initialized!\n");
        exit(1);
    }
    
    node* temp = create_node(j);
    
    temp->next = g.vA[i];
    // Make the new node as the head
    g.vA[i] = temp;
    
     node* temp2 = create_node(i);
     
      temp2->next = g.vA[j];
    // Make the new node as the head
    g.vA[j] = temp2;
    
    
 }
 
/*
//print the list
void print_list(node* list) {
    // Prints the linked list
    node* temp = list;
    while(temp) {
        printf("Node: %d  -> ", temp->vertex);
        temp = temp->next;
    }
    printf("\n");
}*/

//checks if there is any edge between two vertics i,j
int check_if_exists(graph g, int i, int j) {
    // Checks if there is an edge from vertex i to j
    if (!g.vA) {
        fprintf(stderr, "Adjacency Lists not initialized!\n");
        exit(1);
    }
    else if (i > g.vN || j > g.vN) {
        fprintf(stderr, "Invalid Vertex Number\n");
        return 0;
    }
     
    // Search for vertex j in i's adjacency list
    node* temp = g.vA[i];
    if (!temp) {
        return 0;
    }
    if (!(temp->next)) {
        if (temp->vertex == j) {
            return 1;
        }
        return 0;
    }
    while (temp->next) {
        if (temp->vertex == j) {
            // We have found an edge! Remove this element.
            return 1;
        }
        temp = temp->next;
    }
    
    node* temp1 = g.vA[j];
    if (!temp1) {
        return 0;
    }
    if (!(temp1->next)) {
        if (temp1->vertex == j) {
            return 1;
        }
        return 0;
    }
    while (temp1->next) {
        if (temp1->vertex == j) {
            // We have found an edge! Remove this element.
            return 1;
        }
        temp1 = temp1->next;
    }
    // No element found :(
    return 0;
}

//reachability function
void reach(graph g, int i,int *visited)
{
  visited[i]=1;
  printf(" %d ",i);
 
  for(int j=0;j<g.vN;j++)
  {
   if(check_if_exists(g,j,i))
   {
     if(!visited[j])
       reach(g,j,visited); 
   }
   if(check_if_exists(g,i,j))
   {
     if(!visited[j])
       reach(g,j,visited); 
   }
  
  }

}

//dfs function
void DFS(graph g) 
{
   int* visited = (int*) calloc (g.vN, sizeof(int));
   int* result = (int*) calloc (g.vN, sizeof(int));
   
   for(int i=0;i<g.vN;i++)
      visited[i]=0;
   int cnt=0;
   for(int i=0;i<g.vN;i++)
      if(visited[i]==0)
       {
       printf("\nComp-%d:",cnt+1);
       /*
       for(int ik=0;ik<g.vN;ik++)
      		printf(" %d ",visited[ik]);*/
      		
         reach(g,i,visited);
        
        result[cnt]=i;
        cnt++;
        
       }
       
      printf("\n\n ********TOPO SOR*********\n"); 
 for(int ik=0;ik<g.vN;ik++)
      		printf(" %d ",visited[ik]);
       
       printf("\n\n");
       /*
 for(int ik=0;ik<g.vN;ik++)
      		printf(" %d ",visited[ik]);*/
      		
 //printf("%d",cnt);
 
 }
 
 graph * create_graph(int v)
 {
   graph *g=(graph*)calloc(1, sizeof(graph));;
   g->vN=v;
   g->vA=NULL;
   //g={v,NULL};
   g->vA=init_adj_list(*g);
   
  int a=0,b=0;
  
  while(1)
  {
    scanf("%d %d", &a,&b);
    if((a==-1)||(b==-1))
     break;
    //printf("\n%d %d",a,b);
    if((a>=v)||(b>=v))
    {
      printf("Invalid vertex number");
      continue;
      
    }
    
    add_edge(*g,a,b);
    
  }
  
   return g;
   
  }




int main()
{

  int v;
  printf("Enter the no. of vertices: ");
  scanf("%d",&v);

  graph *g= create_graph(v);
  
  
  //graph g={v,NULL};
  //g.vA=init_adj_list(g);
  //printf("%d",g.vN);
/*
  int a=0,b=0;
  
  while(1)
  {
    scanf("%d %d", &a,&b);
    if((a==-1)||(b==-1))
     break;
    //printf("\n%d %d",a,b);
    if((a>=v)||(a>=v))
    {
      printf("Invalid vertex number");
      continue;
      
    }
    
    
    add_edge(g,a,b);
    
  }
  */
  
  /*for (int i=0; i<g.vN; i++) {
        printf("Vertex: %d , => ", i);
        print_list(g.vA[i]);
    }
  */

  DFS(*g);


 return 0;

}

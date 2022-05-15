#include<iostream>




typedef struct node{ 
	int val;
  	int alpha;
 	int beta;
  	int index;
  	int depth
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
  //incomplete
  int m,d,v;
  printf("Enter the depth and branching factor of the tree: ");
  scanf("%d%d",&d,&m);

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

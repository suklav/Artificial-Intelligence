
    #include <iostream>
    #include<vector>
    #include<queue>
    using namespace std;
     
    typedef vector<int> vertex;  //vertex
    typedef pair<int,int> edge;  //pair of vertices : edges
    typedef vector<edge> graph;  //the graph
    #define large 9999999
     
    graph *G;     
    vertex Dist;  // stores distances from source and updated if less cost found then value is updated


    void ucs_algo(int source, int N) {
        
        priority_queue<edge, vector<edge>, greater<edge> > Q;   // algorithm similar to min heap
        Dist.assign(N,large); //setting large value to distance of each vertex
        Dist[source] = 0;  // distance from source to source
        Q.push({0,source});
        while(!Q.empty()){
            int u = Q.top().second;
            Q.pop();
            for(auto &c : G[u]){
                int v = c.first;
                int w = c.second;
                if(Dist[v] > Dist[u]+w){
                    Dist[v] = Dist[u]+w;
                    Q.push({Dist[v],v});
                }
            }
        }
    }
    
    int main() {
        int N, M, u, v, w, source;  // N is total no of nodes, M is the no. of edges, 
        cout<<"Enter total no of Nodes:";
        cin >> N; 
        cout<<"Enter total no of edges:";
        cin >> M;              // u,v and w are the end vertices and the weight associated with an edge
        G = new graph[N+1];
        cout<<"Enter"<<M<<"Edges(vertex1,vertex2,weight) where vertex1 and vertex2 are adjacent.\n "<<endl;
        for(int i=0;i<M;++i)
        {
            cout<<"Enter for"<<i+1<<"th vertex.\n";
            cin >> u >> v >> w;
            G[u].push_back({v,w});
            G[v].push_back({u,w});
        }
        cout<<"Enter source vertex:";
        cin >> source;
        cout<<"Enter destination vertex";
        int goal;
        cin >> goal;
        ucs_algo(source,N);
        cout<<"The optimal cost is:";
        cout<<Dist[goal--];
        
        return 0;
    }

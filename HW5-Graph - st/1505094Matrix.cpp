#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3



class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int *color;
    int *parent;
    int *dist;
    int *start;
    int *finish;
    int time;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs();
    void dfs_visit(int u);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    start = new int[nVertices];
    finish = new int[nVertices];


}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    this->nEdges++ ;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(isEdge(u,v) == true)
    {
        this->nEdges--;
        matrix[u][v] = 0;
        //if(!directed) matrix[v][u] = 0;
    }
    else printf("Cannot be removed\n");
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(matrix[u][v] == 1 || matrix[v][u] == 1)
        return true;
    else return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices ) return INFINITY;

    int d = 0;
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i] == 1)
            d++;
    }
    return d;

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    int flag = 0;
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i] == 1 && matrix[v][i] == 1)
        {
            flag = 1;
            break;
        }
        else flag = 0;
    }
    if(flag == 1)
        return true;
    else return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    if(source<0 || source>=nVertices) return;

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    //parent[source] = -1;
    q.enqueue(source);
    //printf("%d   %d   %d\n",source,dist[source],parent[source]);
    while( !q.empty() )
    {
        //complete this part
        int u = q.dequeue();
        printf("%d ",u);

        for(int i = 0; i < nVertices; i++)
        {
            if((isEdge(u,i) == true) && color[i] == WHITE)
            {

                color[i] = GREY;
                dist[i] = dist[u] + 1;
                parent[i] = u;
                q.enqueue(i);
                //printf("%d   %d   %d\n",i,dist[i],parent[i]);
                //u = i;

            }
            color[u] = BLACK;
        }




    }
}
//int time = 0;
void Graph::dfs()
{
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        start[i] = INFINITY;
        finish[i] = INFINITY;
    }
    time = 0;

    for(int i = 0; i<nVertices; i++)
    {
        if(color[i] == WHITE)
        {
            dfs_visit(i);
        }
    }
}

void Graph::dfs_visit(int u)
{
    time = time + 1;
    start[u] = time;
    color[u] = GREY;
    //printf("%d ",u);
    for(int i = 0; i<nVertices; i++)
    {
        if(isEdge(u,i) == true && color[i] == WHITE)
        {
            parent[i] = u;
            color[i] = GREY;
            dfs_visit(i);
        }
    }
    //printf("%d %d %d\n" , u,start[u],finish[u]);
    color[u] = BLACK;
    time = time + 1;
    finish[u] = time;
    //printf("%d\n",finish[u]);
    printf("%d %d %d\n" , u,start[u],finish[u]);

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return INFINITY;
    bfs(u);
    int d = dist[v];//- dist[u];
    return d ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}


Graph::~Graph()
{
    //write your destructor here

    delete[] matrix;
    delete[] color;
    delete[] parent;
    delete[] start;
    delete[] finish;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main()
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.Remove Edges 3.Is Edge\n");
        printf("4. Degree of a vertex. 5. Print Graph  6. Has common Adjacent.\n");
        printf("7. Implementing BFS. 8. Implementing DFS. 9. Shortest path length.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            bool b = g.isEdge(u, v);
            if(b == true)
                printf("True\n");
            else printf("False\n");

        }
        else if(ch==4)
        {
            int u;
            scanf("%d", &u);
            int d = g.getDegree(u);
            if(d != INFINITY)
                printf("Degree of the given vertex is %d\n",d);
            else printf("Invalid Input\n");
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            bool b = g.hasCommonAdjacent(u, v);
            if(b == true)
                printf("True\n");
            else printf("False\n");

        }
        else if(ch==7)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
            printf("\n");
        }
        else if(ch==8)
        {
            g.dfs();
            printf("\n");
        }
        else if(ch==9)
        {
            int u,v;
            scanf("%d %d", &u,&v);
            int d = g.getDist(u,v);
            if(d != INFINITY)
                printf("Shortest distance between %d and %d is %d\n",u,v,d);
            else printf("Invalid Input\n");
        }
        else if(ch==10)
        {
            break;
        }
    }

}


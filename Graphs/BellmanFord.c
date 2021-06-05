//Bellman Ford Algorithm using Adjacency list for directed graph

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int dest;
    int weight;
    struct node *next;
};

struct Graph
{
    int numVertices;
    struct node **adjList;
};

struct node *CreateNode(int dest, int weight)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->dest = dest;
    newnode->weight = weight;
    newnode->next = NULL;
    return newnode;
}

struct Graph *CreateGraph(int v)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = v;

    graph->adjList = malloc(v * sizeof(struct node));

    for (int i = 0; i < v; i++)
    {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph *Graph, int src, int dest, int weight)
{

    struct node *newnode = CreateNode(dest, weight);
    newnode->next = Graph->adjList[src];
    Graph->adjList[src] = newnode;
}

void printGraph(struct Graph *graph)
{
    printf("Graph is \n");
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node *temp = graph->adjList[v];
        printf("Vertex %d : ", v);
        while (temp != NULL)
        {
            printf("(%d,%d) -> ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf(" NULL\n");
    }
}

void Initialise_Single_Source(struct Graph *g, int source, int *d, int *p)
{

    for (int i = 0; i > g->numVertices; i++)
    {
        d[i] = __INT_MAX__;
        p[i] = -1;
    }

    d[source] = 0;
}

void Relax(int *d, int *p, int u, int v, int w)
{
    if (d[u] + w < d[v])
    {
        d[v] = d[u] + w;
        p[v] = u;
    }
}

void printArr(int dist[], int n)
{
    printf("Vertex     Shortest Distance From Source\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d       -            %d\n", i, dist[i]);
    }
}

int Bellman(struct Graph *g, int source)
{
    int dist[g->numVertices];
    int par[g->numVertices];

    Initialise_Single_Source(g, source, dist, par);

    for (int i = 0; i < g->numVertices - 1; i++)
    {
        int u = 0;
        while (u != g->numVertices)
        {
            struct node *temp = g->adjList[u];
            while (temp != NULL)
            {
                int v = temp->dest;
                int w = temp->weight;
                // printf("(%d)-(%d)-(%d)\n", u, v, w);
                Relax(dist, par, u, v, w);
                temp = temp->next;
            }
            u++;
        }
        printf("%d cycle completes\n", i + 1);
    }
    int u = 0;
    while (u != g->numVertices)
    {
        struct node *temp = g->adjList[u];
        while (temp != NULL)
        {
            int v = temp->dest;
            int w = temp->weight;
            if (dist[v] > dist[u] + w)
            {
                printf("(%d)(%d)(%d)", u, v, w);
                return 0;
            }
            temp = temp->next;
        }
        u++;
    }

    printArr(dist, g->numVertices);

    // printf("Enter vertex to know its path\n");
    // int v;

    // scanf("%d", &v);
    // printf("Distance  = %d\n", dist[v]);
    // printf("Path is \n");
    // while (v != -1)
    // {
    //     if (v != source)
    //     {
    //         printf("%d<-", v);
    //     }
    //     else
    //     {
    //         printf("%d", v);
    //     }
    //     v = par[v];
    // }
}

int main()
{

    //User-Entered value
    int v,v1,v2,w,source;
    printf("Enter no of vertex\n");
    scanf("%d",&v);
    struct Graph *g = CreateGraph(v);

    while(v1!=-1 || v2!=-1 || w!=-1){
        printf("To finish inputting enter all values as -1\n");
        printf("Enter Vertex that are connected :  ");
        scanf("%d",&v1);
        scanf("%d",&v2);
        printf("Enter weight :  ");
        scanf("%d",&w);
        addEdge(g,v1,v2,w);
    }
    printGraph(g);

    printf("Enter source vertex : ");
    scanf("%d",&source);

    if (!Bellman(g, 0))
    {
        printf("Negative cycle exist\n");
    }

    // //Hard-Coded
    // struct Graph *graph = CreateGraph(6);
    // addEdge(graph, 0, 1, 5);
    // addEdge(graph, 1, 2, -2);
    // addEdge(graph, 1, 5, -3);
    // addEdge(graph, 2, 4, 3);
    // addEdge(graph, 3, 2, 6);
    // addEdge(graph, 3, 4, -2);
    // addEdge(graph, 5, 3, 1);
    // printGraph(graph);

    // if (!Bellman(graph, 0))
    // {
    //     printf("Negative cycle exist\n");
    // }

    return 0;
}
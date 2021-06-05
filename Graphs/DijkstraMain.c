//Dijkstra Algorithm using Adjacency list for undirected graph
//Subham Sourav Brahma - 07
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
    struct node *newnode =(struct node*) malloc(sizeof(struct node));
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

    newnode = CreateNode(src, weight);
    newnode->next = Graph->adjList[dest];
    Graph->adjList[dest] = newnode;
}

void printGraph(struct Graph* graph) {
  printf("Graph is \n");
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjList[v];
    printf("Vertex %d : ", v);
    while (temp!=NULL) {
      printf("(%d,%d) -> ",temp->dest,temp->weight);
      temp = temp->next;
    }
    printf(" NULL\n");
  }
}

struct HeapNode
{
    int v;
    int dist;
};

struct minHeap
{
    int size;
    int capacity;
    int *pos;
    struct HeapNode **array;
};

struct HeapNode *createMinHeapNode(int v, int dist)
{
    struct HeapNode *newnode =(struct HeapNode*) malloc(sizeof(struct HeapNode));
    newnode->v = v;
    newnode->dist = dist;
    return newnode;
}

struct minHeap *createMinHeap(int capacity)
{
    struct minHeap *heap =(struct minHeap*) malloc(sizeof(struct minHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->pos = (int*)malloc(capacity*sizeof(int));
    heap->array = (struct HeapNode**)malloc(capacity * sizeof(struct HeapNode));
    return heap;
}
void swapHeapNode(struct HeapNode **a, struct HeapNode **b)
{
    struct HeapNode *t;
    t = *a;
    *a = *b;
    *b = t;
}

int left(int index)
{
    return 2 * index + 1;
}

int right(int index)
{
    return 2 * index + 2;
}

int parent(int index)
{
    return (index - 1) / 2;
}

void Min_Heapify(struct minHeap *heap, int index)
{

    int smallestindex = index;
    int leftindex = left(index);
    int rightindex = right(index);

    if (leftindex < heap->size && heap->array[leftindex]->dist < heap->array[smallestindex]->dist)
    {
        smallestindex = leftindex;
    }

    if (rightindex < heap->size && heap->array[rightindex]->dist < heap->array[smallestindex]->dist)
    {
        smallestindex = rightindex;
    }

    if (smallestindex != index)
    {
        struct HeapNode *smallestNode =
			heap->array[smallestindex];
		struct HeapNode *indexNode =
				heap->array[index];

        heap->pos[smallestNode->v] = index;
        heap->pos[indexNode->v] = smallestindex;

        swapHeapNode(&heap->array[smallestindex],&heap->array[index]);
        Min_Heapify(heap, smallestindex);
    }
}

int isEmpty(struct minHeap *Heap)
{
    return Heap->size == 0;
}

struct HeapNode *Extract_min(struct minHeap *heap)
{
    if(isEmpty(heap))
    {
        return NULL;
    }
    struct HeapNode *min = heap->array[0];
    struct HeapNode *last = heap->array[heap->size -1];

    heap->array[0] = last;

    heap->pos[min->v] = heap->size -1;
    heap->pos[last->v] = 0;
    heap->size--;
    Min_Heapify(heap, 0);
    return min;
}

void decrease_key(struct minHeap *heap,int v,int dist)
{
    int index = heap->pos[v];
    heap->array[index]->dist = dist;

    while ((index > 0) && heap->array[parent(index)]->dist > heap->array[index]->dist)
    {
        heap->pos[heap->array[index]->v] = parent(index);
        heap->pos[heap->array[parent(index)]->v] = index;
        swapHeapNode(&heap->array[parent(index)],&heap->array[index]);
        index = parent(index);
    }
}

void printArr(int dist[], int n)
{  
      printf("Vertex     Shortest Distance From Source\n");
    for(int i=0;i<n;i++){
        printf("%d       -            %d\n",i,dist[i]);
    }
}

void Initialise_Single_Source(struct minHeap *pq,int size,int source,int *d,int *p){

    for(int i=0;i<size;i++){
        d[i] = __INT_MAX__;
        p[i] = -1;
        pq->array[i] = createMinHeapNode(i,d[i]);
        pq->pos[i] = i;
        pq->size++;
    }

    d[source] = 0;
    decrease_key(pq,source,d[source]);
}

void Relax(struct minHeap* pq,int *d,int *p,int u,int v,int w){
    if(d[u] + w < d[v]){
        d[v] = d[u] + w;
        p[v] = u;
        decrease_key(pq,v,d[v]);
    }
}

void Dijkstra(struct Graph *g,int source)
{

    int dist[g->numVertices];
    int par[g->numVertices];
    struct minHeap *pq = createMinHeap(g->numVertices);

    Initialise_Single_Source(pq,g->numVertices,source,dist,par);

    // for(int i=0;i< g->numVertices;i++){
    //     dist[i] = __INT_MAX__;
    //     pq->array[i] = createMinHeapNode(i,dist[i]);
    //     pq->pos[i]=i;
    //     pq->size++;
    // }

    // dist[source]=0;
    // decrease_key(pq,source,dist[source]);

    while (!isEmpty(pq))
    {
        struct HeapNode* Node = Extract_min(pq);
        int u = Node->v;
        struct node *temp = g->adjList[u];
        while (temp != NULL)
        {
            int v = temp->dest;
            int w = temp->weight;
            Relax(pq,dist,par,u,v,w);
            // if (dist[Node->v] + temp->weight < dist[temp->dest])
            // {
            //     dist[temp->dest] = dist[Node->v] + temp->weight;
            //     decrease_key(pq,temp->dest,dist[temp->dest]);
            // }
            temp = temp->next;
        }
    }

    // printf("Vertex       Distance From Source\n");
    // for(int i=0;i<g->numVertices;i++){
    //     printf("%d       -            %d\n",i,dist[i]);
    // }

    printArr(dist,g->numVertices);

    printf("Enter vertex to know its path\n");
    int v;

    scanf("%d",&v);
    printf("Distance  = %d\n",dist[v]);
    printf("Path is \n");
    while (v!=-1)
    {
        if(v!=source){
        printf("%d<-",v);
        }
        else{
            printf("%d",v);
        }
        v = par[v];
    }
}

int main()
{
    //User-Entered code
    int v,v1,v2,w,source;
    printf("Enter no of vertex\n");
    scanf("%d",&v);
    struct Graph* graph = CreateGraph(v);

    while(v1!=-1 && v2!=-1 && w!=-1){
        printf("To finish inputting enter all values as -1\n");
        printf("Enter Vertex that are connected :  ");
        scanf("%d",&v1);
        scanf("%d",&v2);
        printf("Enter weight :  ");
        scanf("%d",&w);
        addEdge(graph,v1,v2,w);
    }
    printGraph(graph);

    printf("Enter source vertex : ");
    scanf("%d",&source);
    Dijkstra(graph,source);
    
    // //HardCoded code
    // struct Graph *graph = CreateGraph(7);
    // addEdge(graph, 0, 1, 2);
    // addEdge(graph, 0, 2, 10);
    // addEdge(graph, 1, 3, 5);
    // addEdge(graph, 2, 3, 1);
    // addEdge(graph, 3, 4, 10);
    // addEdge(graph, 3, 5, 15);
    // addEdge(graph, 4, 5, 6);
    // addEdge(graph, 4, 6, 2);
    // addEdge(graph, 5, 6, 6);
    // printGraph(graph);
    // Dijkstra(graph,0);

}


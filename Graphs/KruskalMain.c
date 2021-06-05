//Kruskal's Algorithm
//Subham Sourav Brahma - 07

#include<stdio.h>
#include<stdlib.h>

struct Edge{
    int u;
    int v;
    int weight;
};

struct Graph
{
    int numVertices;
    int numEdges;
    struct Edge **EdgeArray;
};

struct Edge *createEdge(int u,int v,int weight){
    struct Edge *newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->u = u;
    newEdge->v = v;
    newEdge->weight = weight;
    return newEdge;
}

void printGraph(struct Graph* g){
    printf("Graph is \n");
    for(int i=0;i<g->numEdges;i++){
        struct Edge *x = g->EdgeArray[i];
        printf("%d-%d , weight = %d\n",x->u,x->v,x->weight);
    }

}

struct Graph *createGraph(int v,int e){

    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = v;
    graph->numEdges = e;

    graph->EdgeArray = (struct Edge**)malloc(e*sizeof(struct Edge*));

    for(int i=0;i<e;i++){
        graph->EdgeArray[graph->numEdges] = NULL;
    }
    return graph;
}

struct mst{
    int size;
    int cost;
    struct Edge **mstarr;
};

struct mst *creatMst(int Edges){
    struct mst* tree = (struct mst*)malloc(sizeof(struct mst));
    tree->size = Edges;
    tree->cost = 0;
    tree->mstarr = (struct Edge**)malloc(Edges*sizeof(struct Edge*));

    for (int i = 0;i<Edges; i++)
    {
        tree->mstarr[i]=NULL;
    }
    return tree;
}

struct node{
    int data; 
    int parent;
    int rank;
};

struct nodes{
    int size;
    struct node **SetArr;
};


struct node *createnode(int data){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->parent = newnode->data;
    newnode->rank = 0;
    return newnode;
}

struct nodes *createAllNode(int n){

    struct nodes *N =(struct nodes*)malloc(sizeof(struct nodes));
    N->size = n;
    N->SetArr = (struct node**)malloc(n*sizeof(struct node*));
    
    return N;
}

void makeset(struct nodes* all,int n){

    for(int i=0;i<n;i++){
    all->SetArr[i] = createnode(i);
    }
}

int findPar(struct nodes* all,int data){
    if(data == all->SetArr[data]->parent){
        return data;
    }
    return all->SetArr[data]->parent = findPar(all,all->SetArr[data]->parent);//Compression
}

void Union(struct nodes* all,int u,int v){
    u = findPar(all,u);
    v = findPar(all,v);

    if(all->SetArr[u]->rank < all->SetArr[v]->rank){
        all->SetArr[u]->parent = v;
    }
    else if(all->SetArr[u]->rank > all->SetArr[v]->rank){
        all->SetArr[v]->parent = u;
    }
    else{
        all->SetArr[v]->parent = u;
        all->SetArr[u]->rank++;
    }
}

int sameComponent(struct nodes* all,int u,int v){

    if(findPar(all,u)==findPar(all,v)){
        return 1;
    }
    return 0;
}

void sort(struct Graph *g){
    int minIndex;
    struct Edge* temp;
    for(int i=0;i<g->numEdges -1;i++){
        for(int j=i+1;j<g->numEdges;j++){
            minIndex = i;
            if(g->EdgeArray[j]->weight < g->EdgeArray[minIndex] ->weight){
                minIndex = j;
            }
            temp = g->EdgeArray[i];
            g->EdgeArray[i] = g->EdgeArray[minIndex];
            g->EdgeArray[minIndex] = temp;
        }
    }
}

void KrusKal(struct Graph *g,struct nodes *all){

    sort(g);
    // int costMSt = 0;
    // struct Edge* mst[20];
    struct mst* mst=creatMst(g->numVertices-1);
    // printf("%d",mst->size);

    // printf("mst edges are\n");

    for(int i=0;i<g->numEdges;i++){
        struct Edge* temp = g->EdgeArray[i];
        if(!sameComponent(all,temp->u,temp->v)){
            mst->cost+=temp->weight;
            mst->mstarr[i]=temp;
            Union(all,temp->u,temp->v);
            printf("%d-%d weight = %d\n",mst->mstarr[i]->u,mst->mstarr[i]->v,mst->mstarr[i]->weight);
        }
    }
    // printf("Minimum size = %d\n",mst->size);
    printf("Minimum Cost = %d\n",mst->cost);
    // printf("MST edges are\n");
    // for(int i=0;i<mst->size;i++){
    //     struct Edge* x = mst->mstarr[i];
    //     printf("%d-%d weight = %d\n",x->u,x->v,x->weight);

}

int main(){

    // //User-Entered Value
    // int v,e,v1,v2,w,source;
    // printf("Enter no of vertex\n");
    // scanf("%d",&v);
    // printf("Enter no of Edges\n");
    // scanf("%d",&e);
    // struct Graph* g = createGraph(v,e);
    // struct nodes* all = createAllNode(v);

    // makeset(all,v);

    // for(int i=0;i<g->numEdges;i++){
    //     printf("Enter Vertex that are connected :  ");
    //     scanf("%d",&v1);
    //     scanf("%d",&v2);
    //     printf("Enter weight :  ");
    //     scanf("%d",&w);
    //     g->EdgeArray[i] = createEdge(v1,v2,w);
    //     printf("\n");
    // }

    // printGraph(g);
    // KrusKal(g,all);


    //Hard-Coded Value
    struct Graph* g = createGraph(5,7);
    struct nodes* all = createAllNode(5);

    makeset(all,5);
    g->EdgeArray[0] = createEdge(0,1,3);
    g->EdgeArray[1] = createEdge(0,4,8);
    g->EdgeArray[2] = createEdge(0,3,7);
    g->EdgeArray[3] = createEdge(4,3,3);
    g->EdgeArray[4] = createEdge(1,3,4);
    g->EdgeArray[5] = createEdge(1,2,1);
    g->EdgeArray[6] = createEdge(2,3,2);
    printGraph(g);
    KrusKal(g,all);
    return 0;
}



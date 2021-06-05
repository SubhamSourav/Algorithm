#include<stdio.h>
#include<stdlib.h>

struct node{
    int data; 
    int parent;
    int rank;
};

struct nodes{
    int size;
    struct node **arr;
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
    N->arr = (struct node**)malloc(n*sizeof(struct node*));
    
    return N;
}

void makeset(struct nodes* all,int n){

    for(int i=0;i<n;i++){
    all->arr[i] = createnode(i);
    }

}

int findPar(struct nodes* all,int data){
    if(data == all->arr[data]->parent){
        return data;
    }
    return all->arr[data]->parent = findPar(all,all->arr[data]->parent);//Compression
}

void Union(struct nodes* all,int u,int v){
    u = findPar(all,u);
    v = findPar(all,v);

    if(all->arr[u]->rank < all->arr[v]->rank){
        all->arr[u]->parent = v;
    }
    else if(all->arr[u]->rank > all->arr[v]->rank){
        all->arr[v]->parent = u;
    }
    else{
        all->arr[v]->parent = u;
        all->arr[u]->rank++;
    }
}

int sameComponent(struct nodes* all,int u,int v){

    if(findPar(all,u)==findPar(all,v)){
        return 1;
    }
    return 0;
}

int main(){
    struct nodes* all = createAllNode(7);
    makeset(all,7);

    Union(all,0,1);
    Union(all,1,2);
    Union(all,3,4);
    Union(all,5,6);
    Union(all,4,5);
    Union(all,2,6);

    for (int i = 0; i < 7; i++)
    {
        printf("%d\t",all->arr[i]->data);
        printf("%d\t",all->arr[i]->parent);
        printf("%d\t",all->arr[i]->rank);
        printf("\n");
    }
    return 0;
}
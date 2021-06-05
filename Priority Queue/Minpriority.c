//Min Priority queue implementation using heap starting index as 0

#include <stdio.h>

void swap(int *a, int *b)
{
    int t;
    t = *b;
    *b = *a;
    *a = t;
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

int Heap_Min(int *a){
    return a[0];
}

void Min_Heapify(int *a, int index,int *heap_size)
{
    int smallestindex = index;
    int leftindex = left(index);
    int rightindex = right(index);

    if(leftindex < *heap_size && a[leftindex] < a[smallestindex])
    {
        smallestindex = leftindex;
    }
    while (rightindex < *heap_size && a[rightindex] < a[smallestindex])
    {
        smallestindex = rightindex;
    }

    if (smallestindex != index)
    {
        swap(&a[smallestindex], &a[index]);
        Min_Heapify(a,smallestindex,heap_size);
    }
}

void Build_Min_Heap(int *a,int *heap_size)
{
    for (int i = *heap_size/2 - 1; i >= 0; i--)
    {
        Min_Heapify(a,i,heap_size);
    }
}

int Extract_Min(int *a,int *heap_size)
{

    if (*heap_size == 0)
    {
        printf("Heap Underflow\n");
        return (int)NULL;
    }

    int min = a[0];
    a[0] = a[*heap_size - 1];
    (*heap_size)--;
    Min_Heapify(a,0,heap_size);
    return min;
}

void increase_key(int *a, int index, int key)
{
    if(key>a[index]){
        printf("New key is greater than the current key\n");
        return;
    }
    a[index] = key;
    while ((index > 0) && a[parent(index)] > a[index])
    {
        swap(&a[index], &a[parent(index)]);
        index = parent(index);
    }
}

void decrease_key(int *a,int index,int key,int *heapsize)
{
    if(key<a[index]){
        printf("New key is smaller than the current key\n");
        return;
    }
    a[index] = key;
    Min_Heapify(a,index,heapsize);
}

void insert(int *a,int key,int *heap_size)
{
    a[(*heap_size)++] = __INT_MAX__;
    increase_key(a, *heap_size - 1, key);
}

void print_heap(int *a,int *heap_size)
{
    printf("Heap is \n");
    for (int i = 0; i < *heap_size; i++)
    {
        printf("%d \t", a[i]);
    }
    printf("\n");
}

int main()
{
    int A[20],size=0;
    int *heapsize = &size;
    insert(A,9,heapsize);
    insert(A,14,heapsize);
    insert(A,10,heapsize);
    insert(A,3,heapsize);
    insert(A,5,heapsize);
    insert(A,2,heapsize);
    insert(A,16,heapsize);
    insert(A,1,heapsize);
    insert(A,7,heapsize);
    insert(A,8,heapsize);
    print_heap(A,heapsize);
    printf("min = %d",Extract_Min(A,heapsize));
    print_heap(A,heapsize);
    return 0;
}

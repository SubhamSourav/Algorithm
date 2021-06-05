//Heap sort starting index as 0

#include<stdio.h>
void MaxHeapify(int *arr,int i,int n){
    int largestIndex = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    while (l<n && arr[l]>arr[largestIndex])
    {
        largestIndex = l;
    }
    while (r<n && arr[r]>arr[largestIndex])
    {
        largestIndex = r;
    }
    if(i!=largestIndex){
        int temp = arr[i];
        arr[i] = arr[largestIndex];
        arr[largestIndex] = temp;
        MaxHeapify(arr,largestIndex,n);
    }
}

void BuildHeap(int *arr,int n){
    for (int i = n/2 - 1; i >= 0; i--)
    {
        MaxHeapify(arr,i,n);
    }
}


void HeapSort(int *arr,int n){
    BuildHeap(arr,n);
    for(int i=n-1;i>=0;i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        MaxHeapify(arr,0,i);
    }
}

void printArray(int *arr, int n){
    
    for (int  i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void main()
{
    int array[50],i, n;

    printf("Enter size\n");
    scanf("%d", &n);

    printf("Enter elements\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Before Sorting array is ");
    printArray(array,n);
    HeapSort(array,n);
    printf("After Sorting array is ");
    printArray(array,n);
}
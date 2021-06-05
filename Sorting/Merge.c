// Subham Sourav Brahma - 07
// Merge Sort

#include<stdio.h>
void Merge(int arr[],int low,int mid,int high){

    int i = low;
    int j = mid+1;
    int k = low;
    int B[50];

    while(i<=mid && j<=high){

        if(arr[i]<arr[j]){
            B[k] = arr[i];
            i++;
        }
        else{
            B[k] = arr[j];
            j++;
        }
        k++;
    }

    while(i<=mid){
        B[k] = arr[i];
        i++;k++;
    }

    while(j<=high){
        B[k] = arr[j];
        j++;k++;
    }
    for (int m = low; m <= high; m++)
    {
        arr[m] = B[m];
    }
}

void MergeSort(int *arr,int low,int high){
    if(low<high){
        int mid = (low+high) / 2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        Merge(arr,low,mid,high);
        // Merge(arr,low,high);
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
    MergeSort(array,0,n-1);

    printf("After Sorting array is ");
    printArray(array,n);
}


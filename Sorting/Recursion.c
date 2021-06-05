// Subham Sourav Brahma - 07
// Bubble Sort

#include <stdio.h>
void Insert(int *array,int n,int temp){
    if(n==0 || array[n-1]>=temp){
        array[n]=temp;
        return;
    }
    int val = array[n-1];
    // array[n-1]=NULL;
    Insert(array,n-1,temp);
    array[n-1] = val;
}
void RecursionSort(int *array, int n){

    if(n==1){
        return;
    }

    int temp = array[n-1];
    // array[n-1] = NULL;
    RecursionSort(array,n-1);
    Insert(array,n-1,temp);
}

void main()
{
    int array[50],n,i;

    printf("Enter size\n");
    scanf("%d", &n);

    printf("Enter elements\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Before Sorting array is ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    RecursionSort(array, n);

    printf("After Sorting array is ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}




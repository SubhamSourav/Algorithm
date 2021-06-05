// Subham Sourav Brahma - 07
// Bubble Sort

#include <stdio.h>

void InsertionSort(int *array, int n);

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
    InsertionSort(array, n);

    printf("After Sorting array is ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

void InsertionSort(int *array, int n){

    int key,i,j;

    for(i=1;i<n;i++){
        key = array[i];
        j=i-1;
        while(array[j]>key && j>=0){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }

}



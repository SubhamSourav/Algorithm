// Subham SOURAV BRAHMA
// Quick Sort

#include <stdio.h>

void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int partition(int *arr, int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    int temp;

    do
    {
        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i < j);

    temp = arr[j];
    arr[j] = arr[low];
    arr[low] = temp;

    return j;
}

void Qsort(int *arr, int low, int high)
{
    int pindex;

    if (low < high)
    {
        pindex = partition(arr, low, high);
        Qsort(arr, low, pindex - 1);
        Qsort(arr, pindex + 1, high);
    }
}

void main()
{

    int array[50], i, n;

    printf("Enter size\n");
    scanf("%d", &n);

    printf("Enter elements\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Before Sorting array is ");

    printArray(array, n);
    Qsort(array, 0,n-1);

    printf("After Sorting array is ");
    printArray(array, n);
}
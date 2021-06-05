// Subham Sourav Brahma - 07
// Bubble Sort

#include <stdio.h>

void BubbleSort(int *array, int n);

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
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    BubbleSort(array, n);

    printf("After Sorting array is ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

void BubbleSort(int *array, int n)
{

    int isSorted = 1,i,j, temp;

    for (i = 0; i < n - 1; i++)
    {
        isSorted = 1;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                isSorted = 0;
            }
        }
        if (isSorted)
        {
            return;
        }
    }
}
// Subham Sourav Brahma - 07
// Selection Sort

#include <stdio.h>

void SelectionSort(int *array, int n);

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
    SelectionSort(array, n);

    printf("After Sorting array is ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

void SelectionSort(int *array, int n)
{
    int minIndex, temp,i,j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            minIndex = i;
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
            temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }
}
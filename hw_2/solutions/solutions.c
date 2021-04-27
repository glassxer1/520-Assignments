#include <stdio.h>
#include <math.h>

#include "solutions.h"

int running_total(int val)
{
    static int x = 0;
    return x += val;
}

int *reverse(int *arr, const int len)
{
    int *res = (int *)calloc(len, sizeof(int));
    int i = 0;
    int j = len - 1;
    while (i < len)
    {
        res[j] = arr[i];
        i++;
        j--;
    }
    return res;
}

int *reverse_in_place(int *arr, const int len)
{
    int i = 0;
    int j = len - 1;
    while (i < j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
    return arr;
}

int num_occurences(int *arr, const int len, const int num)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == num)
        {
            cnt++;
        }
    }
    return cnt;
}

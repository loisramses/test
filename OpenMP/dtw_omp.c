#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define min(a, b, c) (((a) < (b)) ? (a < c ? a : c) : (b < c ? b : c))
#define NUM_THREADS 4
#define READING_NUMBER 100
int MAX_READ_NUMBER = READING_NUMBER;

int read_file(char *fileName, int **arr)
{
    FILE *file = fopen(fileName, "r");
    int n = 0, value;
    if (file == NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    int *intArray = (int *)malloc(MAX_READ_NUMBER * sizeof(int));
    if (!intArray)
    {
        printf("Error: memory allocation failed\n");
        fclose(file);
        return 0;
    }
    while (fscanf(file, "%d", &value) == 1)
    {
        if (n >= MAX_READ_NUMBER)
        {
            MAX_READ_NUMBER *= 1.50;
            int *tempArray = (int *)realloc(intArray, MAX_READ_NUMBER * sizeof(int));
            if (!tempArray)
            {
                printf("Error: memory reallocation failed\n");
                free(intArray);
                fclose(file);
                return 0;
            }
            intArray = tempArray;
        }
        intArray[n++] = value;
    }
    fclose(file);
    *arr = intArray;
    return n;
}

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void print_matrix(int n, int m, int **array)
{
    for (int i = 0; i < n; i++)
        print_array(array[i], m);
}

void build_cost_matrix(int *file_data, int *file_data1, int n, int m, int **cost)
{
    int i, j;
#pragma omp parallel private(i, j) num_threads(NUM_THREADS)
    {
#pragma omp for
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                cost[i][j] = abs(file_data[i] - file_data1[j]);
    }
}

void build_accumulated_cost_matrix(int n, int m, int **cost)
{
    int min = n < m ? n : m;
    for (int k = 1; k < min; k++)
    {
        cost[0][k] += cost[0][k - 1];
        cost[k][0] += cost[k - 1][0];
    }

    if (min == n)
        for (int k = n; k < m; k++)
            cost[0][k] += cost[0][k - 1];
    else
        for (int k = m; k < n; k++)
            cost[k][0] += cost[k - 1][0];

#pragma omp parallel shared(cost) num_threads(NUM_THREADS)
    {
#pragma omp for ordered
        for (int i = 1; i < n; i++)
#pragma omp ordered
            for (int j = 1; j < m; j++)
                cost[i][j] += min(cost[i - 1][j], cost[i - 1][j - 1], cost[i][j - 1]);
    }
}

int dtw(int *file_data, int *file_data1, int n, int m, int **cost)
{
    build_cost_matrix(file_data, file_data1, n, m, cost);
    free(file_data);
    free(file_data1);
    build_accumulated_cost_matrix(n, m, cost);
    return cost[n - 1][m - 1];
}

int main(int argc, char **argv)
{
    double start = omp_get_wtime();
    int *file_data = (int *)malloc(sizeof(int) * MAX_READ_NUMBER);
    int n = read_file(argv[1], &file_data);
    int *file_data1 = (int *)malloc(sizeof(int) * MAX_READ_NUMBER);
    int m = read_file(argv[2], &file_data1);
    int **cost = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        cost[i] = (int *)malloc(sizeof(int) * m);
    int result = dtw(file_data, file_data1, n, m, cost);
    double end = omp_get_wtime();
    printf("%d\n", result);
    printf("%f\n", end - start);
    return 0;
}


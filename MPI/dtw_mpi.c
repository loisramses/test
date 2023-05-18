#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for time()
#include <math.h>
#include "mpi.h"

#define MASTER 0
#define num_elem 2
#define min(a, b, c) (((a) < (b)) ? (a < c ? a : c) : (b < c ? b : c))
int x = 0, y = 0, canto = 0;

void add_elem_sp_matrix(int *values, int *cantos, int **aCost)
{
    if (y != 0)
    {
        if (y == 1) canto++;
        int canto1 = x * (num_elem) + num_elem - 1 + num_elem - 1;
        cantos[x] = values[canto1];
    }
    int line;
    for (int i = 0; i < num_elem - 1; i++)
        values[i] = aCost[i][num_elem - 1];
    for (int j = 0; j < num_elem; j++)
    {
        line = x * (num_elem) + num_elem - 1 + j;
        values[line] = aCost[num_elem - 1][j];
    }
}

int readFile(char *fileName, int **arr)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    int capacity = 10; // initial capacity of the array
    int size = 0;      // number of integers read from file
    int *intArray = (int *)malloc(capacity * sizeof(int));
    if (!intArray)
    {
        printf("Error: memory allocation failed\n");
        fclose(file);
        return 0;
    }
    int value;
    while (fscanf(file, "%d", &value) == 1)
    {
        if (size == capacity)
        {
            capacity *= 1.2;
            int *tempArray = (int *)realloc(intArray, capacity * sizeof(int));
            if (!tempArray)
            {
                printf("Error: memory reallocation failed\n");
                free(intArray);
                fclose(file);
                return 0;
            }
            intArray = tempArray;
        }
        intArray[size++] = value;
    }
    fclose(file);
    *arr = intArray;
    return size;
}

void printFile(int *array, int n)
{
    printf("%d", array[0]);
    for (int i = 1; i < n; i++)
        printf(" %d", array[i]);
    printf("\n");
}

int **initializeMatrix(int n)
{
    int **cost = (int **)malloc(num_elem * sizeof(int *));
    for (int i = 0; i < num_elem; i++)
        cost[i] = (int *)malloc(num_elem * sizeof(int));
    return cost;
}

void costMatrix(int **cost, int *array1, int *array2)
{
    for (int i = 0; i < num_elem; i++)
        for (int j = 0; j < num_elem; j++)
            cost[i][j] = abs(array1[j] - array2[i]);
}

void printMatrix(int **cost)
{
    for (int i = 0; i < num_elem; i++)
    {
        printf("%d", cost[i][0]);
        for (int j = 1; j < num_elem; j++)
            printf(" %d", cost[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printSparseMatrix(int *values, int n)
{
    for (int i = 0; i < num_elem - 1 + n; i++)
        printf("Value: %d\n", values[i]);
}

void printCantos(int *cantos, int n)
{
    for (int i = 0; i < canto; i++)
        printf("Canto value: %d\n", cantos[i]);
    printf("\n");
}

void firstBlock(int **cost)
{
    for (int i = 0; i < num_elem; i++)
    {
        for (int j = 0; j < num_elem; j++)
        {
            if (i == 0 && j == 0)
                cost[i][j] = cost[i][j];
            else if (i == 0)
                cost[i][j] += cost[i][j - 1];
            else if (j == 0)
                cost[i][j] += cost[i - 1][j];
            else
                cost[i][j] += min(cost[i][j - 1], cost[i - 1][j - 1], cost[i - 1][j]);
        }
    }
}

void accumulatedLine(int *values, int **cost)
{
    for (int i = 0; i < num_elem; i++)
    {
        for (int j = 0; j < num_elem; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                    cost[i][j] += values[0];
                else
                    cost[i][j] += cost[i][j - 1];
            }
            else if (j == 0)
            {
                if (i == num_elem - 1)
                    cost[i][j] += min(cost[i - 1][j], values[i - 1], values[(x - 1) * num_elem + 2 * (num_elem - 1)]);
                else if (i != 0)
                    cost[i][j] += min(cost[i - 1][j], values[i], values[i - 1]);
            }
            else
                cost[i][j] += min(cost[i - 1][j], cost[i - 1][j - 1], cost[i][j - 1]);
        }
    }
}

void accumulatedColumn(int *arrayUp, int **cost)
{
    for (int i = 0; i < num_elem; i++)
    {
        for (int j = 0; j < num_elem; j++)
        {
            if (i == 0 && j == 0)
                cost[i][j] += arrayUp[j];
            else if (i == 0)
                cost[i][j] += min(cost[i][j - 1], arrayUp[j], arrayUp[j - 1]);
            else if (j == 0)
                cost[i][j] += cost[i - 1][j];
            else
                cost[i][j] += min(cost[i - 1][j], cost[i - 1][j - 1], cost[i][j - 1]);
        }
    }
}

void accumulatedCenter(int *values, int *cantos, int *arrayUp, int **cost)
{
    for (int i = 0; i < num_elem; i++)
    {
        for (int j = 0; j < num_elem; j++)
        {
            if (i == 0 && j == 0)
                cost[i][j] += min(cantos[x - 1], arrayUp[j], values[i]);
            else if (i == 0)
                cost[i][j] += min(cost[i][j - 1], arrayUp[j], arrayUp[j - 1]);
            else if (j == 0)
            {
                if (i == num_elem - 1)
                    cost[i][j] += min(cost[i - 1][j], values[i - 1], values[(x - 1) * num_elem + 2 * (num_elem - 1)]);
                else
                    cost[i][j] += min(cost[i - 1][j], values[i - 1], values[i]);
            }
            else
                cost[i][j] += min(cost[i - 1][j], cost[i - 1][j - 1], cost[i][j - 1]);
        }
    }
}

void accumulatedCost(int *values, int *cantos, int *arrayUp, int **cost)
{
    if (y == 0 && x == 0)
        firstBlock(cost);
    else if (y == 0)
        accumulatedLine(values, cost);
    else if (x == 0)
        accumulatedColumn(arrayUp, cost);
    else
        accumulatedCenter(values, cantos, arrayUp, cost);
}

void copySubArray(int *values, int *arrayUp)
{
    for (int i = 0; i < num_elem; i++)
    {
        int position = x * num_elem + num_elem - 1 + i;
        arrayUp[i] = values[position];
    }
}

int main(int argc, char *argv[])
{

    int numtasks, taskid, message = 0;

    MPI_Status status;

    clock_t timeI = clock();

    int *array1 = NULL;
    int n = readFile(argv[1], &array1);

    int *array2 = NULL;
    int m = readFile(argv[2], &array2);

    int space = n + num_elem - 1;
    int *values = (int *)malloc((space) * sizeof(int));;
    int *cantos = (int *)malloc((n / num_elem) * sizeof(int));;

    int **cost = initializeMatrix(num_elem);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks > n / num_elem)
    {
        printf("Num Processors, must be less than n/num_element\n");
        printf("Quitting...\n");
        MPI_Abort(MPI_COMM_WORLD, message);
        exit(1);
    }

    int *arrayUp = (int *)malloc(num_elem * sizeof(int));
    for (int i = taskid * num_elem; i < m; i += ((numtasks)*num_elem))
    {
        y = i / num_elem;

        for (int j = 0; j < n; j += num_elem)
        {
            if (i != 0)
            {
                MPI_Recv(arrayUp, num_elem, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, MPI_COMM_WORLD, &status);
                cantos[x] = arrayUp[num_elem - 1];
            }
            costMatrix(cost, array1 + j, array2 + i);

            accumulatedCost(values, cantos, arrayUp, cost);

            add_elem_sp_matrix(values, cantos, cost);

            cantos[x] = arrayUp[num_elem - 1];

            copySubArray(values, arrayUp);

            MPI_Send(arrayUp, num_elem, MPI_INT, (taskid + 1) % numtasks, 1, MPI_COMM_WORLD);
            x++;
        }
        x = 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    int proc = ((n / num_elem) % numtasks) - 1;
    if (proc < 0)
        proc += numtasks;

    if (taskid == proc)
    {
        printf("Resultado: %d\n", values[num_elem - 1 + n - 1]);

        double time = clock() - timeI;
        time = ((double)time) / CLOCKS_PER_SEC;
        printf("%f\n", time);
    }

    free(cost);
    free(cantos);
    free(values);

    MPI_Finalize();
}
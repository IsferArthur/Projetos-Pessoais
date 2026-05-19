#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **alocamatriz(int, int);
void printmatriz(int **, int, int);

int main()
{
    int **m;
    int tl, tc;

    printf("Quantas linhas: ");
    scanf("%d", &tl);
    printf("Quantas colunas: ");
    scanf("%d", &tc);

    m = alocamatriz(tl, tc);
    printmatriz(m, tl, tc);

    return 0;
}

int **alocamatriz(int tl, int tc)
{
    int **m;
    int i, j;
    m = (int **)malloc(tl * sizeof(int *)); // tl linhas
    for (i = 0; i < tl; i++)
    {
        m[i] = (int *)calloc(tc, sizeof(int));
    }
    return m;
}

void printmatriz(int **m, int tl, int tc)
{
    for (int i = 0; i < tl; i++)
    {
        for (int j = 0; j < tc; j++)
        {
            printf("%d   ", m[i][j]);
        }
        printf("\n");
    }
}
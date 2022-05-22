#include <stdio.h>
#define max 105
main()
{
    int i, j, k, m, n, x, y;
    float a[max][max], l, r, t, b;
    FILE* fptr;

    fptr = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/assg3/schodinger.txt", "w");
    printf("Enter boundary conditions\n");
    printf("u[0 , y] = ");
    scanf("%f", &l);
    printf("u[1 , y] = ");
    scanf("%f", &r);
    printf("u[x , 1] = ");
    scanf("%f", &t);
    printf("u[x , 0] = ");
    scanf("%f", &b);
    printf("\nEnter length in x direction: ");
    scanf("%d", &x);
    printf("Enter number of steps in x direction: ");
    scanf("%d", &m);
    printf("Enter length in y direction: ");
    scanf("%d", &y);
    printf("Enter number of steps in y direction: ");
    scanf("%d", &n);
    m++;
    n++; //number of mesh points is one more than number of steps
    for (i = 1; i <= m; i++)   //assigning boundary values begins
    {
        a[i][1] = b;
        a[i][n] = t;
    }
    for (i = 1; i <= n; i++)
    {
        a[1][i] = l;
        a[m][i] = r;
    }

    for (i = 2; i < m; i++)
        for (j = 2; j < n; j++)
            a[i][j] = t; //initializing grid points 
    
    for (k = 0; k < (m * n); k++)
    {
        for (i = 2; i < m; i++)
        {
            for (j = 2; j < n; j++)
            {
                a[i][j] = (a[i - 1][j] + a[i + 1][j] + a[i][j - 1] + a[i][j + 1]) / 4;
            }
        }
    }                     //calculation by Gauss-Seidel Method
    
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
            fprintf(fptr, "%.2f\t", a[i][j]);
        fprintf(fptr, "\n");
        //if you need the matrix on console
        /*
        for (j = 1; j <= n; j++)
            printf("%.2f\t", a[i][j]);
        printf("\n");*/
    }
    fclose(fptr);
    printf("\nExecution Complete. Data exported.\n");
    getch();
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef PI
#define PI 4.0*atan(1.0)
#endif

#define BOX_HALF_WIDTH 0.5
#define TOL            1.e-6
#define MAX_TRIALS     1000

double foo, E;

double DpsiprimeDx(double p, double x)
{
    return foo * (-E) * p;
}

int main()
{
    double x, dx, * psi, * dpsi, dE, lastE=0, last;
    double k1p, k1pp, k2p, k2pp, k3p, k3pp, k4p, k4pp, p, pp;
    int parity, grid, i, trial;
    FILE* wfn;

    printf("Enter the no. of spatial grid points for half well :\n");
    scanf("%d", &grid);
    printf("Parity of desired solution :\n");
    scanf("%d", &parity);
    printf("Put in the initial guess of energy eigenvalue\n");
    scanf("%lf", &E);
    printf("Put in the step size\n");
    scanf("%lf", &dE);


    if (parity >= 0) 
        parity = 1; //even
    else 
        parity = -1; //odd

    foo = PI * PI / 4.0;

    dx = BOX_HALF_WIDTH / (grid - 1);
    psi = (double*)calloc(grid, sizeof(double));
    dpsi = (double*)calloc(grid, sizeof(double));
    for (i = 0; i < grid; i++)
        psi[i] = dpsi[i] = 0.0;

    trial = 1;

    while (trial <= MAX_TRIALS && fabs((E - lastE) / lastE) > TOL) 
    {

        // Setting initial conditions
        if (parity >= 0) 
        {
            dpsi[0] = 0.0;
            psi[0] = 1.0;
        }
        else 
        {
            dpsi[0] = 1.0;
            psi[0] = 0.0;
        }
        x = 0.0;
        i = 0;

        //Using RK4
        while (i < grid - 1) 
        {
            p = psi[i]; pp = dpsi[i];

            k1p = dx * pp;
            k1pp = dx * DpsiprimeDx(p, x);

            x += 0.5 * dx;

            k2p = dx * (pp + 0.5 * k1pp);
            k2pp = dx * DpsiprimeDx(p + 0.5 * k1p, x);

            k3p = dx * (pp + 0.5 * k2pp);
            k3pp = dx * DpsiprimeDx(p + 0.5 * k2p, x);

            x += 0.5 * dx;

            k4p = dx * (pp + k3pp);
            k4pp = dx * DpsiprimeDx(p + k3p, x);

            dpsi[i + 1] = dpsi[i] + (k1pp + 2.0 * k2pp + 2.0 * k3pp + k4pp) / 6.0;
            psi[i + 1] = psi[i] + (k1p + 2.0 * k2p + 2.0 * k3p + k4p) / 6.0;

            i++;
        }

        if (trial == 1)
        {
            last = psi[grid - 1] / fabs(psi[grid - 1]); E += dE;
        }
        else 
        {
            if (psi[grid - 1] * last < 0) 
            {
                dE *= 0.5;
                E -= dE;
            }
            else 
            {
                lastE = E;
                E += dE;
                last = psi[grid - 1] / fabs(psi[grid - 1]);
            }
        }
        trial++;
    }

    /* Output results: */
    if (trial >= MAX_TRIALS) 
    {
        printf("Search did not converge for %d iterations!\n", MAX_TRIALS);
        printf("Final energy value = %lf\n", E);
        exit(2);
    }
    printf("Search converged for %d iterations.\n", trial - 1);
    printf("E = %lf\n", E);

    //Writing wavefunction to file
    wfn = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/assg3/schodinger.txt", "w");

    for (i = 1; i < grid - 1; i++) 
    {
        x = -(grid - i) * dx;
        fprintf(wfn, "%lf\t%lf\n", x, parity * psi[grid - i]);
    }
    for (i = 0; i < grid; i++)
    {
        x = i * dx;
        fprintf(wfn, "%lf\t%lf\n", x, psi[i]);
    }
    fclose(wfn);

    return 0;
}


/*********************************************OUTPUT**********************************************
Enter the no. of spatial grid points for half well :
50
Parity of desired solution :
1
Put in the initial guess of energy eigenvalue
2
Put in the step size
0.01
Search converged for 213 iterations.
E = 4.000002
**************************************************************************************************/

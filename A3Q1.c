#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double monteCarlo(int n);
double imp_sampling(int n);
double f(double x, int n);
double rand_exp(int lambda, int min, int max);

void main()
{
	int n = 10;
	FILE* fptr1;
	FILE* fptr2;
	fptr1 = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/assg3/monteCarlo.txt", "w");
	fptr2 = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/assg3/imp_sampling.txt", "w");
	if (fptr1 == NULL || fptr2 == NULL)
	{
		// File not created hence exit
		printf("\nUnable to create file.\n");
		exit(EXIT_FAILURE);
	}

	while (n <= 10000)
	{
		double val1 = monteCarlo(n);
		double val2 = imp_sampling(n);
		fprintf(fptr1, "%d\t%lf\n", n, val1);
		fprintf(fptr2, "%d\t%lf\n", n, val2);
		n = n + 10;
	}
	printf("Evaluation using crude monte-carlo and importance sampled monte-carlo complete.\n");
}

double monteCarlo(int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double random = rand() / ((double)RAND_MAX);
		double res = f(random, 1);
		sum += res;
	}
	double avg = sum / n;
	return avg;
}

double imp_sampling(int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double random = rand_exp(1, 0, -1);
		double weight = 1 / f(random, 2);
		double res = f(random, 1) * weight;
		sum += res;
	}
	double avg = sum / n;
	return avg;
}

double f(double x, int n)
{
	if (n == 1)
		return exp(-x * x); //main function
	else if (n == 2)
		return 0.58*exp(-x); //target function for importance sampling
}

double rand_exp(int lambda, int min, int max)
{
	double u_min = exp(-min * lambda);
	double u_max = exp(-max * lambda);

	double u = u_min + (1.0 - rand() / (RAND_MAX + 1.0)) * (u_max - u_min);
	return -log(u) / lambda;
}


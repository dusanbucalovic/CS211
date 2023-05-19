#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("./mexpfile1.txt\n");
		return 0;
	}

	FILE *fp;
	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("error\n");
		return 0;
	}

	int i, j, c, m, n, mltply;

	fscanf(fp, "%d". &n);
	int **m = (int**)malloc(n*sizeof(int*));
	int **m1 = (int**)malloc(n*sizeof(int*));
	int **res = (int**)malloc(n*sizeof(int*));

	for (i = 0; i < n; i++)
	{
		m[i] = (int*)malloc(n*sizeof(int));
		m1[i] = (int*)malloc(n*sizeof(int));
		res[i] = (int*)malloc(n*sizeof(int));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) 
		{
			fscanf(fp, "%d", &m[i][j]);
			m1[i][j] = m[i][j];
		}
	}
	fscanf(fp, "%d", &mltply);
	for (m = 0; m < mltply - 1; m++)
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				res[i][j] = 0;
				for(c = 0; c < n; c++)
				{
					res[i][j] += m[i][c]*m1[c][j];
				}
			}
			for(i = 0; i < n; i++)
			{
				for(j = 0; j < n; j++)
				{
					m1[i][j] = res[i][j];
				}
			}
		}

	}
	for(i = 0; i <n; i++)
	{
		for(j = 0; j<n; j++)
		{
			printf("%d", res[i][j]);
		}
		printf("\n");
	}
	fclose(fp);
	return 0;
}
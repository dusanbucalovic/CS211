#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <algorithm>


void sort(char *str, int n)
{
	int i; 
	int j;
	for (i = 0; i < n - 1; ++i)
	{
		int plc = i;
		char tmp = str[i];
		
		for (j = i + 1; j < n; ++j)
		{
			if (str[j] < tmp)
			{
				plc = j;
				tmp = str[plc];
			}
		}
		str[plc] = str[i];
		str[i] = tmp;

	}
}


int main(int argc, char *argv[])
{
	char *str = argv[1];
	int i;

	for (i = 2; i < argc; ++i)
	{
		strcat(str, argv[i]);

	}

	int n = strlen(str);
	for (i = 0; i < n; ++i)
	{
		str[i] = tolower(str[i]);
	}

	sort(str, n);
	printf("%s", str);
	return 0;



}
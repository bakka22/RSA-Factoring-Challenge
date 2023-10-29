#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int arc, char **arv)
{
	int i, j;
	FILE *source;
	char *buf = NULL;
	unsigned long long int x = 0, y = 0, z = 0, w = 0;
	size_t n;

	if (arc != 2)
	{
		fprintf(stderr, "Usage: factors <file>");
		exit(EXIT_FAILURE);
	}
	for (i = 1; i < arc; i++)
	{
		source = fopen(arv[i], "r");
		if (source == NULL)
		{
			fprintf(stderr, "couldn't open file \"%s\"\n", arv[i]);
			continue;
		}
		while (getline(&buf, &n, source) != -1)
		{
			sscanf(buf, "%llu", &x);
			if (x % 2 == 0)
			{
				y = x / 2;
				z = 2;
			}
			else
			{
				w = 3;
				while (w < x)
				{
					if (x % w == 0)
					{
						y = x / w;
						z = x / y;
						break;
					}
					w += 2;
					if (x % w == 0)
					{
						y = x / w;
						z = x / y;
						break;
					}
					w += 2;
					if (x % w == 0)
					{
						y = x / w;
						z = x / y;
						break;
					}
					w += 4;
				}
			}
			if (y == 0 && z == 0)
			{
				y = x;
				z = 1;
			}
			printf("%llu=%llu*%llu\n", x, y, z);
		}
		free(buf);
		buf = NULL;
		fclose(source);
	}
	return (0);
}
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c)
{
	int m = a < b ? a : b;
	return (m < c ? m : c);
}

int main(int ac, char **av)
{
	FILE *f = (ac == 2) ? fopen(av[1], "r") : stdin;
	if (!f) return printf("Error\n"), 1;

	int rows;
	char empty, obst, full;
	if (fscanf(f, "%d%c%c%c\n", &rows, &empty, &obst, &full) != 4)
		return printf("Error\n"), 1;

	char **map = malloc(sizeof(char *) * rows);
	char *line = NULL;
	size_t n = 0;
	int cols = 0, r = 0;

	while (getline(&line, &n, f) != -1 && r < rows)
	{
		int len = 0;
		while (line[len] && line[len] != '\n') len++;

		if (!cols) cols = len;
		if (len != cols) return printf("Error\n"), 1;

		map[r] = malloc(len + 1);
        if (!map[r])
	        return printf("Error\n"), 1;

        for (int i = 0; i < len; i++)
	        map[r][i] = line[i];
        map[r][len] = '\0';
		r++;
	}
	if (r != rows) return printf("Error\n"), 1;

	int **dp = malloc(sizeof(int *) * rows);
	for (int i = 0; i < rows; i++)
		dp[i] = calloc(cols, sizeof(int));

	int max = 0, mi = 0, mj = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == empty)
			{
				if (i == 0 || j == 0)
					dp[i][j] = 1;
				else
					dp[i][j] = 1 + min(
						dp[i-1][j],
						dp[i][j-1],
						dp[i-1][j-1]);

				if (dp[i][j] > max)
				{
					max = dp[i][j];
					mi = i;
					mj = j;
				}
			}
		}
	}

	for (int i = mi; i > mi - max; i--)
		for (int j = mj; j > mj - max; j--)
			map[i][j] = full;

	for (int i = 0; i < rows; i++)
		printf("%s\n", map[i]);

	// free
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
		free(dp[i]);
	}
	free(map);
	free(dp);
	free(line);
	if (f != stdin) fclose(f);

	return 0;
}
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int width, height;

int		count(char *board, int x, int y)
{
	int dx, dy, nx, ny, count = 0;

	for (dy = -1; dy <= 1; dy++)
	{
		for (dx = -1; dx <= 1; dx++)
		{
			if (!dx && !dy)
				continue;
			nx = dx + x;
			ny = dy + y;
			if (nx >= 0 && ny >= 0 && ny < height && nx < width)
				count += board[ny * width + nx];
		}
	}
	return count;
}

int		iterate(char **board)
{
	char	*new = calloc(width * height, 1);
	if (!new)
		return 1;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int n = count(*board, x, y);
			if ((*board)[y * width + x] && (n == 2 || n == 3))
				new[y * width + x] = 1;
			else if (!(*board)[y * width + x] && n == 3)
				new[y * width + x] = 1;
		}
	}
	free(*board);
	*board = new;
	return 0;
}

void	print(char *board)
{
	int		i = 0;
	while (i < width * height)
	{
		if (board[i])
			putchar('O');
		else
			putchar(' ');
		if ((i + 1) % width == 0)
			putchar('\n');
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	int iter = atoi(argv[3]);
	if (width <= 0 || height <= 0 || iter < 0)
		return 1;
	char	*board = calloc(width * height, 1);
	if (!board)
		return 1;

	int x = 0, y = 0, pen = 0;
	char	c;

	while (read(0, &c, 1) > 0)
	{
		if (c == 'x')
			pen = !pen;
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < height - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < width - 1)
			x++;
		if (pen)
			board[y * width + x] = 1;
	}
	while (iter-- > 0)
	{
		if (iterate(&board))
		{
			free(board);
			return 1;
		}
	}
	print(board);
	free(board);
	return 0;
}
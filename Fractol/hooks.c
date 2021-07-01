#include "fractol.h"

void	ft_error(char *message)
{
	int	i;

	i = 0;
	while (message + i && message[i] != '\0')
		write(1, (message + i++), 1);
	write(1, "\n", 1);
	exit (-1);
}

int	mouse_key(int event, int x, int y, t_mlx *data)
{
	if (event == 2 && !data->act)
		data->act = 1;
	else if (event == 2 && data->act == 1)
		data->act = 25;
	else if (event == 2 && data->act == 25)
		data->act = 0;
	else if (event == 5)
		data->zoom *= 1.2;
	else if (event == 4 && data->zoom > 0.0001)
		data->zoom *= 0.8;
	else if (event == 1)
		data->color *= 251;
	else if (x || y)
		return (0);
	fractal(data);
	return (0);
}

int	key_key(int event, t_mlx *data)
{
	if (event == 53)
		exit(0);
	else if (event == 126)
		data->move_y -= 0.1 / data->zoom;
	else if (event == 125)
		data->move_y += 0.1 / data->zoom;
	else if (event == 124)
		data->move_x += 0.1 / data->zoom;
	else if (event == 123)
		data->move_x -= 0.1 / data->zoom;
	else if (event == 27)
		data->iter -= 10;
	else if (event == 24)
		data->iter += 10;
	else
		return (0);
	fractal(data);
	return (0);
}

int	mouse_circle(int x, int y, t_mlx *data)
{
	if (x > (WIDTH / 2) && y < (HEIGHT / 2))
		data->cim += 0.0003 * data->act;
	else if (y > (HEIGHT / 2) && x > (WIDTH / 2))
		data->cim -= 0.0003 * data->act;
	else if (y < (HEIGHT / 2) && x < (WIDTH / 2))
		data->cre -= 0.0003 * data->act;
	else if (y > (HEIGHT / 2) && x < (WIDTH / 2))
		data->cre += 0.0003 * data->act;
	fractal(data);
	return (0);
}


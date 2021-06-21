#include "fractol.h"

void	my_mlx_img(t_mlx *pic, int x, int y, int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->line_length + x * (pic->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	julia(int x, int y, t_mlx *data)
{
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	int		i;

	newRe = 1.5 * (x - (WIDTH / 2)) / (data->zoom * (WIDTH / 2)) + data->move_x;
	newIm = (y - (HEIGHT / 2)) / (data->zoom * (HEIGHT / 2)) + data->move_y;
	i = -1;
	while (++i < data->iter)
	{
		oldRe = newRe;
		oldIm = newIm;
		newRe = oldRe * oldRe - oldIm * oldIm + data->cre;
		newIm = 2 * oldRe * oldIm + data->cim;
		if ((newRe * newRe + newIm * newIm) > 4)
			break ;
	}
	return (i);
}

int	mondel(int x, int y, t_mlx *data)
{
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	int		i;

	data->cre = 1.6 * (x - WIDTH / 2) / (data->zoom * WIDTH / 2) + data->move_x;
	data->cim = (y - (HEIGHT / 2)) / (data->zoom * (HEIGHT / 2)) + data->move_y;
	newRe = 0;
	newIm = 0;
	i = -1;
	while (++i < data->iter)
	{
		oldRe = newRe;
		oldIm = newIm;
		newRe = oldRe * oldRe - oldIm * oldIm + data->cre;
		newIm = 2 * oldRe * oldIm + data->cim;
		if ((newRe * newRe + newIm * newIm) > 4)
			break ;
	}
	return (i);
}

int	some(int x, int y, t_mlx *data)
{
	double	temp;
	int		i;
	float	px;
	float	py;

	data->cre = (x - WIDTH / 2) / (data->zoom * WIDTH / 2) + data->move_x - 0.6;
	data->cim = (y - (HEIGHT / 2)) / (data->zoom * (HEIGHT / 2)) + data->move_y;
	px = 1;
	py = 0.19;
	i = 0;
	while ((px * px + py * py) < 4 && i < data->iter)
	{
		temp = (px * px) - (py * py) + data->cre;
		py = -2 * px * py + data->cim;
		px = temp;
		i++;
	}
	return (i);
}

void	fractal(t_mlx *data)
{
	int	y;
	int	x;
	int	i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (data->fract == 'M')
				i = mondel(x, y, data);
			else if (data->fract == 'S')
				i = some(x, y, data);
			else
				i = julia(x, y, data);
			my_mlx_img(data, x, y, i * data->color);
		}
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	}
}

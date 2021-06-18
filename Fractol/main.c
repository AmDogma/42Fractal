#include "fractol.h"

void	my_mlx_img(t_pic *pic, int x, int y, int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->line_length + x * (pic->bits_per_pixel / 8)); 
	*(unsigned int*)dst = color;
}

int julia(int x, int y, t_mlx *data)
{
	double newRe;
	double newIm; 
	double oldRe; 
	double oldIm;
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
		if((newRe * newRe + newIm * newIm) > 4)
			break;
	}
	return (i);
}

int mondel(int x, int y, t_mlx *data)
{         
	double newRe;
	double newIm; 
	double oldRe; 
	double oldIm;
	int		i;

	data->cre = 1.5 * (x - (WIDTH / 2)) / (data->zoom * (WIDTH / 2)) + data->move_x;
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
			break;
	}
	return (i);
}

void fractal(t_mlx *data)
{         
	int y;
	int x;
	int i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH) 
		{
			if (data->fract == 'M')
				i = mondel(x, y, data);
			else
    			i = julia(x, y, data);
			my_mlx_img(&(data->img), x, y, data->color * i * (data->color * (i < data->iter)));
		}
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
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
		data->color += 251;
	else
		return (0);
	fractal(data);
	return (0);
}

int key_key(int event, t_mlx *data)
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

int mouse_circle(int x, int y, t_mlx *data)
{
	if (x > (WIDTH/2) && y < (HEIGHT / 2))
		data->cim += 0.0003 * data->act;
	else if (y > (HEIGHT / 2) && x > (WIDTH / 2))
		data->cim -= 0.0003 * data->act;
	else if (y < (HEIGHT / 2) && x < (WIDTH / 2))
		data->cre -= 0.0003 * data->act;
	else if (y > (HEIGHT / 2) && x < (WIDTH / 2))
		data->cre += 0.0003 * data->act;
	else
		return(0);
	fractal(data);
	return(0);
}

int init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (0);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol");
	if (data->mlx_win == NULL)
		return (0);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img == NULL)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (data->img.addr == NULL)
		return (0);
	return (1);
}

void init_param(t_mlx *data)
{
	t_pic	img;

	data->img = img;
	data->zoom = 1.0001;
	data->move_y = 0;
	data->act = 0;
	data->move_x = 0;
	data->color = 89;
	data->iter  = 200;
	data->cre = -0.70;
	data->cim = 0.27015;
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s + i && s[i] != '\0')
		write(1, (s + i++), 1);
}

void pr_par()
{
	ft_putstr("Hey stranger!\n");
	ft_putstr("To start - type \"M\" for Mandelbrot or \"J\" for Julia set after ./fractol\n");
	ft_putstr("Use mouse scroll to zoom in and out\n");
	ft_putstr("Left click to change colors\n");
	ft_putstr("Use + and - to change ammount of iterations\n");
	ft_putstr("Use arrows to move\n");
	ft_putstr("Right click to change \"Z\" in Julia set\n");
	ft_putstr("Good luck!\n");
	exit (0);
}

int	main(int argc, char **argv)
{
	t_mlx	data;
	
	init_param(&data);
	if (init_mlx(&data) == 0) // нужно прописать ошибки 
		return (0);
	if (argc == 1 || argc > 2 || !(argv[1][0] == 'M' || argv[1][0] == 'J'))
		pr_par();
	data.fract = argv[1][0];
	fractal(&data);
	mlx_key_hook(data.mlx_win, key_key, &data);
	mlx_mouse_hook(data.mlx_win, mouse_key, &data);
	mlx_hook(data.mlx_win, 6, 1ul << 6u, mouse_circle, &data);
	mlx_loop(data.mlx);
}

// gcc  -lmlx -framework OpenGL -Ofast -framework AppKit main.c && ./a.out M
//-Imlx 
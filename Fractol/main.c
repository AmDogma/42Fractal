#include "fractol.h"

void	my_mlx_img(t_pic *pic, int x, int y, int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->line_length + x * (pic->bits_per_pixel / 8)); 
	*(unsigned int*)dst = color;
}

void mondelbrot(t_mlx *data)
{         
	double newRe, newIm, oldRe, oldIm;
	int y;
	int x;
	int i;

	y = -1;
	while (++y < 600)
	{
		x = -1;
		while (++x < 800)
		{
    		newRe = 1.5 * (x - 400) / (data->zoom * 400) + data->move_x;
    		newIm = (y - 300) / (data->zoom * 300) + data->move_y;
    		i = -1;
			while (++i < data->iter)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + data->cre;
				newIm = 2 * oldRe * oldIm + data->cim;
				if((newRe * newRe + newIm * newIm) > 2)
					break;
			}
			my_mlx_img(&(data->img), x, y, (i % 256) * 255 * data->color * (i < data->iter));
		}
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}

int	mouse_key(int event, int x, int y, t_mlx *data)
{
	printf("KEY = %d\n", event);
	if (event == 5)
		data->zoom *= 1.05;
	if (event == 4 && data->zoom > 0.0001)
		data->zoom *= 0.95;
	if (event == 1)
		data->color += 300;
	mlx_clear_window(data->mlx, data->mlx_win);
	mondelbrot(data);
	return (0);
}

int key_key(int event, t_mlx *data)
{
	printf("KEY = %d\n", event);
	if (event == 53)
		exit(0);
	if (event == 126)
		data->move_y += 0.1/data->zoom;
	if (event == 125) 
		data->move_y -= 0.1/data->zoom;
	if (event == 124)
		data->move_x -= 0.1/data->zoom;
	if (event == 123)
		data->move_x += 0.1/data->zoom;
	if (event == 27)
		data->iter -= 10;
	if (event == 24)
		data->iter += 10;
	mlx_clear_window(data->mlx, data->mlx_win);
	mondelbrot(data);	
	return (0);
}	



int	main(void)
{
	t_mlx	data;
	t_pic	img;

	data.img = img;
	
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 800, 600, "Fractol");	
	data.img.img = mlx_new_image(data.mlx, 800, 600);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	
	data.zoom = 1.0001;
	data.move_y = 0;
	data.move_x = 0;
	data.color = 3000;
	data.iter  = 122;
	data.cre = -0.7;
	data.cim = 0.27015;
	mondelbrot(&data);
	mlx_key_hook(data.mlx_win, key_key, &data);
	mlx_mouse_hook(data.mlx_win, mouse_key, &data);
	mlx_loop(data.mlx);
}

// gcc  -lmlx -framework OpenGL -framework AppKit main.c && ./a.out 
//-Imlx 
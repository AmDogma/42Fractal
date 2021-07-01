#include "fractol.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s + i && s[i] != '\0')
		write(1, (s + i++), 1);
}

void	pr_par(void)
{
	ft_putstr("\n\t\tHey stranger!\n");
	ft_putstr("\n\tTo start - type after ./fractol:");
	ft_putstr("\n\t1)\"M\" for Mandelbrot\n");
	ft_putstr("\t2)\"J\" for Julia\n");
	ft_putstr("\t3)\"S\" for Sorry face (bonus) \n");
	ft_putstr("\n\tUse mouse scroll to zoom in and out\n");
	ft_putstr("\tLeft click to change colors\n");
	ft_putstr("\tUse + and - to change ammount of iterations\n");
	ft_putstr("\tUse arrows to move\n");
	ft_putstr("\tRight click to change \"Z\" in Julia set\n");
	ft_putstr("\n\t\tGood luck!\n");
	exit (0);
}

int	init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		ft_error("MLX = NULL");
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol");
	if (data->mlx_win == NULL)
		ft_error("MLX WINDOW = NULL");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
		ft_error("MLX IMAGE = NULL");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (data->addr == NULL)
		ft_error("MLX ADDRESS = NULL");
	return (1);
}

void	init_param(t_mlx *data)
{
	data->zoom = 1.0001;
	data->move_y = 0;
	data->act = 0;
	data->move_x = 0;
	data->color = 2656;
	data->iter = 200;
	data->cre = -0.70;
	data->cim = 0.27015;
}

int	main(int argc, char **argv)
{
	t_mlx	data;

	if (argc == 1 || argc > 2 || argv[1][1] || !(argv[1][0] == 'M'
		|| argv[1][0] == 'J' || argv[1][0] == 'S'))
		pr_par();
	init_param(&data);
	init_mlx(&data);
	data.fract = argv[1][0];
	fractal(&data);
	mlx_key_hook(data.mlx_win, key_key, &data);
	mlx_mouse_hook(data.mlx_win, mouse_key, &data);
	mlx_hook(data.mlx_win, 6, 1ul << 6u, mouse_circle, &data);
	mlx_loop(data.mlx);
}


#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b)	(a > b ? a : b)

typedef	struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	double			zoom;
	double			move_g;
	double			move_h;
}	t_mlx;
	
// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;
// t_data	img;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); 
// 	*(unsigned int*)dst = color;
// }

	//img.img = mlx_new_image(mlx, 800, 600);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 1, 1);


// void mondelbrot(t_mlx *data)
// {
// 	float zi, zr, ci, cr, tmp;
//   int i, j, k;
 
//   for (i = -400; i < 400; i++) {                      //  проходим по всем пикселям оси х
 
// 	 ci = ((float)i) / (1.0 * (float)data->zoom);                    //  присваеваем мнимой части с - i/160
// 	 for (j = -570; j < 30; j++) {                 //  проходим по всем пикселям оси y6
 
// 		cr = ((float)j) / (0.8 * (float)data->zoom);             //  присваеваем вещественной части с - j/120
// 		zi = zr = 0.0;                       //  присваеваем вещественной и мнимой части z - 0
// 		for(k = 0; k < 300; k++) {         //  вычисляем множество Мандельброта
 
// 		  tmp = zr*zr - zi*zi;
// 		  zi = 2*zr*zi + ci;
// 		  zr = tmp + cr;
// 		  if (zr*zr + zi*zi > 2)        //  если |z| слишком велико, то
// 		    break;                           //  выход из цикла
// 		}
// 		if (k < 300) {
// 		    mlx_pixel_put(data->mlx, data->mlx_win, (i + data->move)%800, j + 570, 0xFFFFFFFF + (k * 19)); 
// 		}
// 		else
// 			mlx_pixel_put(data->mlx, data->mlx_win, (i + data->move)%800, j + 570, 0x00FF0F00);
		       
// 	 }
// 	}
// }
// gcc  -lmlx -framework OpenGL -framework AppKit main.c && ./a.out 
//-Imlx 
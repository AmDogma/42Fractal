#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480


typedef struct	s_pic {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_pic;

typedef	struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	double	zoom;
	double	move_y;
	double	move_x;
	double	cre;
	double 	cim;
	int		color;
	int 	act;
	char	fract;
	int		iter;
	t_pic	img;
}	t_mlx;
	





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
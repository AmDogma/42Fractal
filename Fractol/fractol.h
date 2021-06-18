#include <mlx.h>
#include <unistd.h>
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
	
void	fractal(t_mlx *data);
int		mouse_circle(int x, int y, t_mlx *data);
int		key_key(int event, t_mlx *data);
int		mouse_key(int event, int x, int y, t_mlx *data);
